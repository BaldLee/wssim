#pragma once
#include "utils/deck.hh"

namespace wssim {
class Player {
   public:
    Player(const Deck& _deck, const Deck& _waiting_room, const Deck& _level,
           const Deck& _clock, const Deck& _stock, const Deck& _memory,
           const Deck& _statge, const Deck& _hands)
        : __deck(_deck),
          __waiting_room(_waiting_room),
          __level(_level),
          __clock(_clock),
          __stock(_stock),
          __memory(_memory),
          __stage(_statge),
          __hands(_hands) {}

    inline int hp() const { return __level.size() * 7 + __clock.size(); }

    inline void clean_all() {
        __deck.clear();
        __waiting_room.clear();
        __level.clear();
        __clock.clear();
        __stock.clear();
        __memory.clear();
        __stage.clear();
        __hands.clear();
    }

    inline bool death_check() const { return __level.size() >= 4; }

    bool levelup_check();

    inline bool refresh_check() {
        if (__deck.size() > 0) {
            return false;
        }
        __deck = std::move(__waiting_room);
        __deck.shuffle();
        __clock.push_top(__deck.pop_top());
        levelup_check();
        return true;
    }

   private:
    Deck __deck;
    Deck __waiting_room;
    Deck __level;
    Deck __clock;
    Deck __stock;
    Deck __memory;
    Deck __stage;
    Deck __hands;
};
}  // namespace wssim
