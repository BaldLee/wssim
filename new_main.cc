#include <map>

#include "wssim.hpp"

void test_sim_linglong(int deck_size = 18, int deck_trigger = 14,
                       int waiting_size = 8, int waiting_trigger = 5) {
  player op;
  for (int i = 0; i < 4; i++) {
    op.waiting_room.push_back(card(-1, -1, 1));
  }
  for (int i = 0; i < 6; i++) {
    op.waiting_room.push_back(card(-1, -1, 0));
  }
  for (int i = 0; i < 6; i++) {
    op.deck.push_back(card(-1, -1, 0));
  }
  for (int i = 0; i < 14; i++) {
    op.deck.push_back(card(-1, -1, 1));
  }

  std::map<std::pair<int, int>, int> res_map;
  for (int repeat = 0; repeat < 10000; repeat++) {
    player p = op;
    wssim::shuffle(p.deck);
    int four = 0;
    int three = 0;
    for (int i = 0; i < 3; i++) {
      int trigger_count = 0;
      for (int j = 0; j < 7; j++) {
        trigger_count += p.deck.back().trigger;
        p.waiting_room.push_back(p.deck.back());
        p.deck.pop_back();
        if (p.deck.empty()) {
          p.refresh();
        }
      }
      if (trigger_count >= 6) {
        four += 2;
        three += 1;
      } else if (trigger_count >= 4) {
        four += 1;
        three += 1;
      } else if (trigger_count >= 3) {
        four += 1;
      }
      p.waiting_room.push_back(p.deck.back());
      p.deck.pop_back();
      if (p.deck.empty()) {
        p.refresh();
      }
    }
    auto key = std::make_pair(four, three);
    if (res_map.count(key) == 0) {
      res_map[key] = 0;
    }
    res_map[key] += 1;
  }

  for (auto kv : res_map) {
    std::cout << "<" << kv.first.first << ", " << kv.first.second
              << ">: " << kv.second << std::endl;
  }
}

int main() {
  test_sim_linglong();
  return 0;
}
