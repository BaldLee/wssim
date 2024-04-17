#pragma once
#include <algorithm>
#include <deque>
#include <iostream>
#include <random>
#include <type_traits>

#include "utils/card.hh"

/* Every list of cards is a deck.
 * Stock, clock, hands , waiting room, level and deck are all deck.
 * We choose deque to manage deck, because we have to pop and push at the front
 * and back, and we have to access elements with index while shuffling the deck.
 */

namespace wssim {
class Deck {
   public:
    Deck() {}

    inline std::size_t size() const { return __card_deque.size(); }

    inline Card& peek_top() { return __card_deque.front(); }

    inline Card& peek_bottom() { return __card_deque.back(); }

    void push_top(const Card& c);

    void push_bottom(const Card& c);

    Card pop_top();

    Card pop_bottom();

    std::string to_str() const;

    inline void print() const { std::cout << to_str() << std::endl; }

    void shuffle();

    inline void clear() { __card_deque.clear(); }

    inline Card& at(int index) { return __card_deque.at(index); }

    void add_cards(int _level, int _type, int _trigger, int _count = 1);

    // void add_cards2top(const std::vector<Card>& cards);

    void add_deck2top(const Deck deck);

    template <typename Container>
    void add_cards2top(const Container& container) {
        static_assert(std::is_same_v<typename Container::value_type,
                                     typename std::deque<Card>::value_type>);
        __card_deque.insert(__card_deque.end(), container.begin(),
                            container.end());
    }

    inline bool is_empty() const { return __card_deque.empty(); }

   private:
    // <TOP> [card, card, ..., card] <BOTTOM>
    std::deque<Card> __card_deque;
    static std::mt19937 rng;
    static std::random_device rd;
};
}  // namespace wssim
