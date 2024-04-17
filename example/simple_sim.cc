#include <iostream>

#include "benchmark/benchmark.hh"
#include "utils/player.hh"

// w114_049
void sim_w114_049(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 3; i++) {
            if (def.take_michiru(2)) {
                def.take_damage(2);
            }
        }
        atk.attack(def, 3);
    }
}

// w101_079
void sim_w101_079(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        if (def.take_michiru(5)) {
            def.take_damage(1);
            def.take_damage(1);
        }
        atk.attack(def, 3);
    }
}

// w112_003
void sim_w112_003(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        int x = def.take_michiru(4);
        for (int i = 0; i < x; i++) {
            def.take_damage(1);
        }
        atk.attack(def, 3);
    }
    def.take_damage(3);
}

// s109_060
void sim_s109_060(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        int x = def.take_michiru(6);
        for (int i = 0; i < x; i++) {
            def.take_damage(1);
        }
        atk.attack(def, 3);
    }
}

// s108_003
void sim_s108_003(wssim::Player& atk, wssim::Player& def) {
    def.pop_bottom_until_climax(2);
    for (int i = 0; i < 3; i++) {
        int x = def.take_michiru(3);
        for (int i = 0; i < x; i++) {
            def.take_damage(2);
        }
        atk.attack(def, 3);
    }
}

// s108_083
void sim_s108_083(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        def.take_damage(2);
        atk.attack(def, 3);
    }
}

// brainstorm test
void sim_brain_storm() {
    // Brainstorm 4 test
    std::cout << "Brainstorm 4 test" << std::endl;
    for (int deck = 20; deck < 34; deck += 2) {
        for (int climax = 4; climax < 9; climax++) {
            wssim::Player player;
            player.deck().add_cards(0, wssim::Card::CHAR, 0, deck - climax);
            player.deck().add_cards(0, wssim::Card::CLIMAX, 0, climax);
            int count = 0;
            for (int i = 0; i < 10000; i++) {
                auto p = player;
                p.deck().shuffle();
                count += p.brainstorm(4);
            }
            std::cout << climax << "/" << deck << ": "
                      << static_cast<double>(count) / 10000 << std::endl;
        }
    }

    // Brainstorm 5 test
    std::cout << "Brainstorm 5 test" << std::endl;
    for (int deck = 20; deck < 34; deck += 2) {
        for (int climax = 4; climax < 9; climax++) {
            wssim::Player player;
            player.deck().add_cards(0, wssim::Card::CHAR, 0, deck - climax);
            player.deck().add_cards(0, wssim::Card::CLIMAX, 0, climax);
            int count = 0;
            for (int i = 0; i < 10000; i++) {
                auto p = player;
                p.deck().shuffle();
                count += p.brainstorm(5);
            }
            std::cout << climax << "/" << deck << ": "
                      << static_cast<double>(count) / 10000 << std::endl;
        }
    }
}

// Whatif direct attak after 3 cards "mokaed"
void sim_moka3_direct(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        def.take_moka(3);
        atk.attack(def, 4);
    }
}

// Whatif 4 3 4 3 4 3 after maseki
void sim_moseki_s108_t17(wssim::Player& atk, wssim::Player& def) {
    def.take_maseki();
    for (int i = 0; i < 3; i++) {
        def.take_damage(4);
        atk.attack(def, 3);
    }
}

// Whatif 2 3 2 3 2 3 after maseki
void sim_moseki_s108_083(wssim::Player& atk, wssim::Player& def) {
    def.take_maseki();
    for (int i = 0; i < 3; i++) {
        def.take_damage(2);
        atk.attack(def, 3);
    }
}

int main() {
    wssim::benchmark(20000, sim_moseki_s108_t17);
    return 0;
}
