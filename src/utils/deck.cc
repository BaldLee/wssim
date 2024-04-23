#include "utils/deck.hh"

namespace wssim {
std::random_device Deck::rd;
std::mt19937 Deck::rng(Deck::rd());

void Deck::push_top(const Card& c) { __card_deque.push_front(c); }

void Deck::push_bottom(const Card& c) { __card_deque.push_back(c); }

Card Deck::pop_top() {
    auto top = __card_deque.front();
    __card_deque.pop_front();
    return top;
}

Card Deck::pop_bottom() {
    auto bottom = __card_deque.front();
    __card_deque.pop_front();
    return bottom;
}

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

void Deck::add_deck2top(const Deck deck) { add_cards2top(deck.__card_deque); }

void Deck::shuffle() {
    std::shuffle(__card_deque.begin(), __card_deque.end(), rng);
}

double Deck::get_compression_rate() const {
    int cx_num = 0;
    for (auto& card : __card_deque) {
        if (card.type() == Card::CLIMAX) {
            cx_num += 1;
        }
    }
    return static_cast<double>(cx_num) / __card_deque.size();
}

}  // namespace wssim
