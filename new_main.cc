#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <stack>
#include <vector>

class card {
 public:
  int level;
  int type;  // 0 for character, 1 for climax, 2 for event
  int trigger;
  card(int _level, int _type, int _trigger)
      : level(_level), type(_type), trigger(_trigger) {}
  void print() {
    std::cout << "{" << type << "," << level << "," << trigger << "} ";
  }
};

class wssim {
 private:
  static std::random_device rd;
  static std::mt19937 gen;

 public:
  wssim() {}
  static void print_deck(const std::vector<card>& deck) {
    std::for_each(deck.begin(), deck.end(), [](auto x) { x.print(); });
    std::cout << std::endl;
  }

  static std::vector<card> shuffle_copy(std::vector<card> deck) {
    std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
    for (int i = 0; i < deck.size(); i++) {
      std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
    }
    return deck;
  }

  static void shuffle(std::vector<card>& deck) {
    std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
    for (int i = 0; i < deck.size(); i++) {
      std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
    }
  }
  /*
    std::vector<bool> generate_deck(int deck_size, int cx_num) {
      assert(deck_size >= cx_num);
      std::vector<bool> deck;
      for (int i = 0; i < cx_num; i++) {
        deck.push_back(true);
      }
      for (int i = cx_num; i < deck_size; i++) {
        deck.push_back(false);
      }
      return deck;
    }

    void moka(std::vector<bool>& deck, int count) {
      int rou_num = 0;
      for (int i = 0; i < 3; i++) {
        if (!deck.back()) {
          rou_num++;
        }
        deck.pop_back();
      }
      for (int i = 0; i < rou_num; i++) {
        deck.push_back(false);
      }
    }

    bool take_damage(std::vector<bool>& deck, int damage) {
      int hit = true;
      for (int i = 0; i < damage; i++) {
        if (deck.back()) {
          hit = false;
          break;
        }
        deck.pop_back();
      }
      return hit;
    }

    void print_map(std::map<int, int>& res_map) {
      for (auto kv : res_map) {
        std::cout << kv.first << ", " << kv.second << std::endl;
      }
    }
    */
};

class player {
 public:
  std::vector<card> deck;
  std::vector<card> waiting_room;
  std::vector<card> level;
  std::vector<card> stock;
  std::vector<card> clock;
  std::vector<card> memory;
  std::vector<card> stage;
  std::vector<card> hands;
  player() {}
  player(std::vector<card>& _deck, std::vector<card>& _waiting_room,
         std::vector<card>& _level, std::vector<card>& _stock,
         std::vector<card>& _clock, std::vector<card>& _memory,
         std::vector<card>& _stage, std::vector<card>& _hands)
      : deck(_deck),
        waiting_room(_waiting_room),
        level(_level),
        stock(_stock),
        clock(_clock),
        memory(_memory),
        stage(_stage),
        hands(_hands) {}
  void refresh() {
    deck.insert(deck.end(), waiting_room.begin(), waiting_room.end());
    waiting_room.clear();
    wssim::shuffle(deck);
    clock.push_back(deck.back());
    deck.pop_back();
    levelup_check();
  }
  void levelup_check() {
    if (clock.size() >= 7) {
      level.push_back(clock.back());
      clock.pop_back();
      waiting_room.insert(waiting_room.end(), clock.begin(), clock.end());
      clock.clear();
    }
  }
};

std::random_device wssim::rd;
std::mt19937 wssim::gen(wssim::rd());

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

/*
<1, 1>: 24557
<2, 1>: 75443
<3, 2>: 48123
<4, 2>: 51927
<4, 3>: 9265
<5, 2>: 1154
<5, 3>: 65727
<6, 3>: 23804

<4, 2>: 8
<4, 3>: 934
<5, 2>: 121
<5, 3>: 6612
<6, 3>: 2325

<3, 2>: 68
<4, 2>: 585
<4, 3>: 3745
<5, 2>: 569
<5, 3>: 4366
<6, 3>: 667

<2, 2>: 49
<3, 1>: 13
<3, 2>: 911
<3, 3>: 2543
<4, 1>: 66
<4, 2>: 1994
<4, 3>: 3633
<5, 2>: 377
<5, 3>: 414
*/