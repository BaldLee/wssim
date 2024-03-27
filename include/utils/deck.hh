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

    card& peek_top();
    card& peek_bottom();
    void push_top(const card& c);
    void push_bottom(const card& c);
    card pop_top();
    card pop_bottom();
    std::size_t size() const;
    void print() const;
    void shuffle();
    void clear();
    card& at(int index);

   private:
    // <TOP> [card, card, ..., card] <BOTTOM>
    std::deque<card> __card_deque;
    static std::mt19937 rng;
    static std::random_device rd;
};
}  // namespace wssim
