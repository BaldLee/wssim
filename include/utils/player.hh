#pragma once
#include "utils/deck.hh"

namespace wssim {
class player {
   public:
    player(const deck& _deck, const deck& _waiting_room, const deck& _level,
           const deck& _clock, const deck& _stock, const deck& _memory,
           const deck& _statge, const deck& _hands)
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
    deck __deck;
    deck __waiting_room;
    deck __level;
    deck __clock;
    deck __stock;
    deck __memory;
    deck __stage;
    deck __hands;
};
}  // namespace wssim
