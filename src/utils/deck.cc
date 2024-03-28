#include "utils/deck.hh"

namespace wssim {
std::random_device deck::rd;
std::mt19937 deck::rng(deck::rd());
}  // namespace wssim
