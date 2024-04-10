#include "utils/player.hh"

namespace wssim {
bool Player::levelup_check() {
    if (__clock.size() < 7) {
        return false;
    }
    int index_to_level = 0;
    for (int i = 6; i >= 0; i--) {
        if (__clock.at(i).type() != Card::CLIMAX) {
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
}  // namespace wssim
