#include "utils/deck.hh"

namespace wssim {
std::random_device deck::rd;
std::mt19937 deck::rng(deck::rd());

std::string deck::to_str() const {
    std::stringstream ss;
    ss << '[';
    std::for_each(__card_deque.begin(), __card_deque.end(),
                  [&](auto x) { ss << x.to_str() << ','; });
    ss << ']';
    return ss.str();
}

void deck::add_cards(int _level, int _type, int _trigger, int _count) {
    card c(_level, _type, _trigger);
    for (int i = 0; i < _count; i++) {
        __card_deque.push_back(c);
    }
}
}  // namespace wssim
