#include "utils/deck.hh"

namespace wssim {
std::random_device Deck::rd;
std::mt19937 Deck::rng(Deck::rd());

std::string Deck::to_str() const {
    std::string ret("[");
    std::for_each(__card_deque.begin(), __card_deque.end(),
                  [&](auto x) { ret += x.to_str() + ","; });
    ret += "]";
    return ret;
}

void Deck::add_cards(int _level, int _type, int _trigger, int _count) {
    Card c(_level, _type, _trigger);
    for (int i = 0; i < _count; i++) {
        __card_deque.push_back(c);
    }
}
}  // namespace wssim
