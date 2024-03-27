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

    int hp() const;
    void clean_all();
    bool death_check() const;
    bool levelup_check();
    bool refresh_check();

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
