#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "3rd_party/BS_thread_pool.hpp"
#include "3rd_party/json.hpp"
#include "utils/player.hh"

namespace wssim {
template <typename Func>
void benchmark(const int iterations, Func func);
template <typename Func>
int multithread_sim(BS::thread_pool& pool, const int thread_num,
                    const int inner_loop, Func func, const Player& atk,
                    const Player& def);
template <typename Func>
int single_thread_task(Func func, const Player& atk, const Player& def,
                       const int inner_loop);

template <typename Func>
void benchmark(const int iterations, Func func) {
    nlohmann::json j;
    Player atk;
    const int thread_num = std::thread::hardware_concurrency() / 2;
    const int inner_loop = iterations / thread_num;
    const int true_iteraroins = thread_num * inner_loop;
    BS::thread_pool pool(thread_num);
    /* We assume the triggers in attacker's deck in 7/21 */
    atk.deck().add_cards(0, Card::CHAR, 0, 7);
    atk.deck().add_cards(0, Card::CHAR, 1, 14);
    /* We will go through
     *  4/20, 4/25, 4/30
     *  6/20, 6/25, 6/30
     *  8/20, 8/25, 8/30 */
    for (int climax = 4; climax <= 8; climax += 2) {
        for (int deck = 20; deck <= 30; deck += 5) {
            Player def;
            def.deck().add_cards(0, Card::CLIMAX, 0, climax);
            def.deck().add_cards(0, Card::CHAR, 0, deck - climax);
            def.waiting_room().add_cards(0, Card::CLIMAX, 0, 8 - climax);
            /* We assume number of non-climax in waiting is:
             *       climax / deck * (8 - climax)           */
            def.waiting_room().add_cards(
                0, Card::CHAR, 0,
                static_cast<int>(static_cast<double>(climax) / deck *
                                 (8 - climax)));
            std::string json_index =
                std::to_string(climax) + "/" + std::to_string(deck);
            for (int hp = 14; hp < 28; hp++) {
                def.set_hp(hp);
                auto res = multithread_sim(pool, thread_num, inner_loop, func,
                                           atk, def);
                j[json_index][std::to_string(hp)] =
                    static_cast<double>(res) / true_iteraroins;
            }
        }
    }

    // std::cout << j << std::endl;

    // TODO: output file path should not be hard coded
    std::ofstream o("./output.json");
    o << std::setw(4) << j << std::endl;
}

template <typename Func>
int multithread_sim(BS::thread_pool& pool, const int thread_num,
                    const int inner_loop, Func func, const Player& atk,
                    const Player& def) {
    std::vector<std::future<int>> futures(thread_num);
    for (int i = 0; i < thread_num; i++) {
        // futures[i] = pool.submit(single_thread_task, func, atk, def,
        // inner_loop);
        futures[i] = pool.submit(
            [=]() { return single_thread_task(func, atk, def, inner_loop); });
    }
    int res = 0;
    for (int i = 0; i < thread_num; i++) {
        res += futures[i].get();
    }
    return res;
}

template <typename Func>
int single_thread_task(Func func, const Player& atk, const Player& def,
                       const int inner_loop) {
    int res = 0;
    for (int i = 0; i < inner_loop; i++) {
        Player a = atk;
        Player d = def;
        a.shuffle_deck();
        d.shuffle_deck();
        func(a, d);
        if (d.death_check()) {
            res += 1;
        }
    }
    return res;
}
}  // namespace wssim
