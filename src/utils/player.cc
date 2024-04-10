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

void Player::set_hp(const int hp) {
    __clock.clear();
    __level.clear();
    __level.add_cards(0, Card::CHAR, 0, hp / 7);
    __clock.add_cards(0, Card::CHAR, 0, hp % 7);
}

bool Player::refresh_check() {
    if (__deck.size() > 0) {
        return false;
    }
    __deck = std::move(__waiting_room);
    __deck.shuffle();
    __clock.push_top(__deck.pop_top());
    levelup_check();
    return true;
}

void Player::shuffle_deck() { __deck.shuffle(); }

bool Player::take_damage(const int damage) {
    bool canceled = false;
    std::vector<Card> tmp;
    for (int i = 0; i < damage; i++) {
        auto card = __deck.pop_top();
        tmp.push_back(card);
        refresh_check();
        if (card.type() == Card::CLIMAX) {
            canceled = true;
            break;
        }
    }
    if (canceled) {
        __waiting_room.add_cards2top(tmp);
    } else {
        __clock.add_cards2top(tmp);
        levelup_check();
    }
    return canceled;
}

int Player::trigger() {
    auto card = __deck.pop_top();
    __stock.push_top(card);
    refresh_check();
    return card.trigger();
}

bool Player::attack(Player& def, const int soul) {
    return def.take_damage(soul + trigger());
}

int Player::take_michiru(const int count) {
    int res = 0;
    for (int i = 0; i < count; i++) {
        auto card = __deck.pop_bottom();
        __waiting_room.push_top(card);
        if (card.type() == Card::CLIMAX) {
            res += 1;
        }
        refresh_check();
    }
    return res;
}

}  // namespace wssim
