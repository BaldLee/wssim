#pragma once
#include "utils/player.hh"

namespace wssim {
int player::hp() const { return __level.size() * 7 + __clock.size(); }
void player::clean_all() {
    __deck.clear();
    __waiting_room.clear();
    __level.clear();
    __clock.clear();
    __stock.clear();
    __memory.clear();
    __stage.clear();
    __hands.clear();
}
bool player::death_check() const { return __level.size() >= 4; }
bool player::levelup_check() {
    if (__clock.size() < 7) {
        return false;
    }
    int index_to_level = 0;
    for (int i = 6; i >= 0; i--) {
        if (__clock.at(i).type() != card::CLIMAX) {
            index_to_level = i;
            break;
        }
    }
    for (int i = 0; i < 7; i++) {
        if (i != index_to_level) {
            __waiting_room.push_top(__clock.pop_bottom());
        } else {
            __level.push_top(__clock.pop_bottom());
        }
    }
    return true;
}
bool player::refresh_check() {
    if (__deck.size() > 0) {
        return false;
    }
    __deck = std::move(__waiting_room);
    __deck.shuffle();
    __clock.push_top(__deck.pop_top());
    levelup_check();
    return true;
}
}  // namespace wssim
