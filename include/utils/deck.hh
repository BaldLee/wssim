#pragma once
#include <algorithm>
#include <deque>
#include <random>

#include "utils/card.hh"

/* Every list of cards is a deck.
 * Stock, clock, hands , waiting room, level and deck are all deck.
 */

namespace wssim {
class deck {
   public:
    deck() {}

    inline std::size_t size() const { return __card_deque.size(); }

    inline card& peek_top() { return __card_deque.front(); }

    inline card& peek_bottom() { return __card_deque.back(); }

    inline void push_top(const card& c) { __card_deque.push_front(c); }

    inline void push_bottom(const card& c) { __card_deque.push_back(c); }

    inline card pop_top() {
        auto top = __card_deque.front();
        __card_deque.pop_front();
        return top;
    }

    inline card pop_bottom() {
        auto bottom = __card_deque.front();
        __card_deque.pop_front();
        return bottom;
    }

    inline std::string to_str() const {
        std::stringstream ss;
        ss << '[';
        std::for_each(__card_deque.begin(), __card_deque.end(),
                      [&](auto x) { ss << x.to_str() << ','; });
        ss << ']';
        return ss.str();
    }

    inline void print() const { std::cout << to_str() << std::endl; }

    inline void shuffle() {
        std::shuffle(__card_deque.begin(), __card_deque.end(), rng);
    }

    inline void clear() { __card_deque.clear(); }

    inline card& at(int index) { return __card_deque.at(index); }

    inline void add_cards(int _level, int _type, int _trigger, int _count = 1) {
        card c(_level, _type, _trigger);
        for (int i = 0; i < _count; i++) {
            __card_deque.push_back(c);
        }
    }

   private:
    // <TOP> [card, card, ..., card] <BOTTOM>
    std::deque<card> __card_deque;
    static std::mt19937 rng;
    static std::random_device rd;
};
}  // namespace wssim
