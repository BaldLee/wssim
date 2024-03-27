#include "utils/deck.hh"

namespace wssim {
std::random_device deck::rd;
std::mt19937 deck::rng(deck::rd());

std::size_t deck::size() const { return __card_deque.size(); }

card& deck::peek_top() { return __card_deque.front(); }

card& deck::peek_bottom() { return __card_deque.back(); }

void deck::push_top(const card& c) { __card_deque.push_front(c); }

void deck::push_bottom(const card& c) { __card_deque.push_back(c); }

card deck::pop_top() {
    auto top = __card_deque.front();
    __card_deque.pop_front();
    return top;
}

card deck::pop_bottom() {
    auto bottom = __card_deque.front();
    __card_deque.pop_front();
    return bottom;
}

void deck::print() const {
    std::for_each(__card_deque.begin(), __card_deque.end(),
                  [](auto x) { x.print(); });
    std::cout << std::endl;
}

void deck::shuffle() {
    std::shuffle(__card_deque.begin(), __card_deque.end(), rng);
}

void deck::clear() { __card_deque.clear(); }

card& deck::at(int index) { return __card_deque.at(index); }
}  // namespace wssim
