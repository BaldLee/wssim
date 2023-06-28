#include <map>

#include "wssim.hpp"

constexpr int REPEAT = 10000;
int test_sim_linglong(const player& atk, const player& def) {
  int killed_count = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    // 2 linlong
    for (int i = 0; i < 2; i++) {
      // (1) 1 hand, costing trigger 1 hand card goes first
      a.waiting_room.push_back(a.stock.back());
      a.stock.pop_back();
      for (int i = 0; i < a.hands.size(); i++) {
        if (i == a.hands.size() - 1) {
          a.waiting_room.push_back(a.hands[i]);
          a.hands.pop_back();
        } else if (a.hands[i].trigger >= 1) {
          a.waiting_room.push_back(a.hands[i]);
          std::iter_swap(a.hands.begin() + i, a.hands.end() - 1);
          a.hands.pop_back();
          break;
        }
      }
      // 4 3 4
      int res = a.linglong7();
      if (res >= 3) {
        d.take_damage(4);
      }
      if (res >= 4) {
        d.back_and_shuffle(3);
      }
      if (res >= 6) {
        d.take_damage(4);
      }
      // attack
      wssim::pattackp(a, d, 3);
    }
    // attack
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed_count++;
    }
    // std::cout << d.level.size() << std::endl;
  }
  return killed_count;
}

int main() {
  player linglong, tom;
  // tom is 2-2, deck 7/27, wr 1/2 [climax]
  tom.level.push_back(card(0, card::CHAR, 0));
  tom.level.push_back(card(0, card::CHAR, 0));
  tom.clock.push_back(card(0, card::CHAR, 0));
  tom.clock.push_back(card(0, card::CHAR, 0));
  tom.waiting_room.push_back(card(0, card::CHAR, 0));
  tom.waiting_room.push_back(card(0, card::CLIMAX, 0));
  for (int i = 0; i < 7; i++) {
    tom.deck.push_back(card(0, card::CLIMAX, 0));
  }
  for (int i = 0; i < 20; i++) {
    tom.deck.push_back(card(0, card::CHAR, 0));
  }
  // linglong is 3-4, deck 2/16, wr 4/15 [trigger]
  linglong.stock.push_back(card(0, card::CHAR, 0));
  linglong.hands.push_back(card(0, card::CHAR, 1));
  linglong.hands.push_back(card(0, card::CHAR, 0));
  linglong.hands.push_back(card(0, card::CHAR, 0));
  linglong.hands.push_back(card(0, card::CHAR, 0));
  for (int i = 0; i < 2; i++) {
    linglong.deck.push_back(card(0, card::CHAR, 0));
  }
  for (int i = 0; i < 14; i++) {
    linglong.deck.push_back(card(0, card::CHAR, 1));
  }
  for (int i = 0; i < 4; i++) {
    linglong.waiting_room.push_back(card(0, card::CHAR, 0));
  }
  for (int i = 0; i < 11; i++) {
    linglong.waiting_room.push_back(card(0, card::CHAR, 1));
  }

  auto res = test_sim_linglong(linglong, tom);
  std::cout << res << "/" << REPEAT << ":" << double(res) / REPEAT << std::endl;
  return 0;
}
