#ifndef _WSSIM_HPP_
#define _WSSIM_HPP_ 1
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <random>

#include "BS_thread_pool.hpp"
#include "json.hpp"

/* declare */
class card;
class wssim;
class player;

class card {
 public:
  int level;    // -1 for whatever
  int type;     // 0 for character, 1 for climax, 2 for event, -1 for whatever
  int trigger;  // 0 or 1 or 2
  static constexpr int CHAR = 0;
  static constexpr int CLIMAX = 1;
  static constexpr int EVENT = 2;
  static constexpr int WHATEVER = -1;

  card(int _level, int _type, int _trigger)
      : level(_level), type(_type), trigger(_trigger) {}
  void print();
};

class wssim {
 private:
  static std::random_device rd;
  static std::mt19937 gen;

 public:
  wssim() {}
  static void print_deck(const std::vector<card>& deck);
  static std::vector<card> shuffle_copy(std::vector<card> deck);
  static void shuffle(std::vector<card>& deck);
  static bool pattackp(player& atk, player& def, int soul);
  static void push_cards_into_deck(std::vector<card>& deck, card card, int num);
  static int multhread_sim(int (*func)(player, player, int), const player& atk,
                           const player& def, const int count = 10000,
                           int thread_num = 1, int inner_repeat = 1);
  static void basic_bench(int (*sim)(player&, player&), int attacker_deck = 20,
                          int attacker_trigger = 8);
  static void basic_bench_json(int (*sim)(player&, player&),
                               int attacker_deck = 20, int attacker_trigger = 8,
                               std::string out_path = "out.json");
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
  player(int _hp, int _deck, int _climax_in_deck, int _waiting_room,
         int _climax_in_waiting_room);
  void sethp(int hp);
  void clearall();
  void init_attacker(int _deck, int _trigger);
  void init_defender(int _hp, int _deck, int _climax_in_deck, int _waiting_room,
                     int _climax_in_waiting_room);
  int gethp();
  void print();
  bool death_check();
  void refresh_check();
  void levelup_check();
  bool take_damage(int damage);
  void take_true_damage(int damage);
  void be_mokaed(int count);
  void back_and_shuffle(int count);
  void back_to_top(int count);
  int linglong7();
  void take_aki_smoke(int smoke);
  int woody6();
};

/* Defination */
/* Class card */
void card::print() {
  std::cout << "{" << level << "," << type << "," << trigger << "} ";
}

/* Class wssim */
std::random_device wssim::rd;
std::mt19937 wssim::gen(wssim::rd());

void wssim::print_deck(const std::vector<card>& deck) {
  std::for_each(deck.begin(), deck.end(), [](auto x) { x.print(); });
  std::cout << std::endl;
}

std::vector<card> wssim::shuffle_copy(std::vector<card> deck) {
  std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
  for (int i = 0; i < deck.size(); i++) {
    std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
  }
  return deck;
}

void wssim::shuffle(std::vector<card>& deck) {
  std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
  for (int i = 0; i < deck.size(); i++) {
    std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
  }
}

bool wssim::pattackp(player& atk, player& def, int soul) {
  int damage = soul + atk.deck.back().trigger;
  atk.stock.push_back(atk.deck.back());
  atk.deck.pop_back();
  atk.refresh_check();
  return def.take_damage(damage);
}

void wssim::push_cards_into_deck(std::vector<card>& deck, card card, int num) {
  for (int i = 0; i < num; i++) {
    deck.push_back(card);
  }
}

int wssim::multhread_sim(int (*func)(player, player, int), const player& atk,
                         const player& def, const int count, int thread_num,
                         int inner_repeat) {
  if (thread_num <= 0) {
    thread_num = std::thread::hardware_concurrency() - 2;
  }
  BS::thread_pool pool(thread_num);
  std::vector<std::future<int>> futures(count);
  int res = 0;
  for (int i = 0; i < count; i++) {
    futures[i] = pool.submit(func, atk, def, inner_repeat);
  }
  for (int i = 0; i < count; i++) {
    res += futures[i].get();
  }
  return res;
}

void wssim::basic_bench(int (*sim)(player&, player&), int attacker_deck,
                        int attacker_trigger) {
  int REPEAT = 10000;
  player atk;
  player def;
  atk.init_attacker(attacker_deck, attacker_trigger);

  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 10, 0);
    std::cout << "8/25: " << double(sim(atk, def)) / REPEAT << std::endl;
    def.init_defender(hp, 25, 6, 10, 2);
    std::cout << "6/25: " << double(sim(atk, def)) / REPEAT << std::endl;
    def.init_defender(hp, 30, 8, 10, 0);
    std::cout << "8/30: " << double(sim(atk, def)) / REPEAT << std::endl;
    def.init_defender(hp, 30, 6, 10, 2);
    std::cout << "6/30: " << double(sim(atk, def)) / REPEAT << std::endl;
  }
}

void wssim::basic_bench_json(int (*sim)(player&, player&), int attacker_deck,
                             int attacker_trigger, std::string out_path) {
  int REPEAT = 10000;
  player atk;
  player def;
  atk.init_attacker(attacker_deck, attacker_trigger);

  nlohmann::json j;
  double res = 0.0;
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 10, 0);
    j[std::to_string(hp)]["8/25"] = double(sim(atk, def)) / REPEAT;
    std::cout << "8/25: " << j[std::to_string(hp)]["8/25"] << std::endl;
    def.init_defender(hp, 25, 6, 10, 2);
    j[std::to_string(hp)]["6/25"] = double(sim(atk, def)) / REPEAT;
    std::cout << "6/25: " << j[std::to_string(hp)]["6/25"] << std::endl;
    def.init_defender(hp, 30, 8, 10, 0);
    j[std::to_string(hp)]["8/30"] = double(sim(atk, def)) / REPEAT;
    std::cout << "8/30: " << j[std::to_string(hp)]["8/30"] << std::endl;
    def.init_defender(hp, 30, 6, 10, 2);
    j[std::to_string(hp)]["6/30"] = double(sim(atk, def)) / REPEAT;
    std::cout << "6/30: " << j[std::to_string(hp)]["6/30"] << std::endl;
  }
  std::ofstream o(out_path);
  o << std::setw(4) << j << std::endl;
}

/* Class player */
void player::sethp(int hp) {
  int _level = hp / 7;
  int _clock = hp % 7;
  level.clear();
  clock.clear();
  for (int i = 0; i < _level; i++) {
    level.push_back(card(0, card::CHAR, 0));
  }
  for (int i = 0; i < _clock; i++) {
    clock.push_back(card(0, card::CHAR, 0));
  }
}

void player::clearall() {
  deck.clear();
  waiting_room.clear();
  level.clear();
  stock.clear();
  clock.clear();
  memory.clear();
  stage.clear();
  hands.clear();
}

void player::init_attacker(int _deck, int _triggers) {
  clearall();
  wssim::push_cards_into_deck(deck, card(0, card::CHAR, 0), _deck - _triggers);
  wssim::push_cards_into_deck(deck, card(0, card::CHAR, 1), _triggers);
}

void player::init_defender(int _hp, int _deck, int _climax_in_deck,
                           int _waiting_room, int _climax_in_waiting_room) {
  clearall();
  int _level = _hp / 7;
  int _clock = _hp % 7;
  if (_hp >= 28) {
    std::cout << "Warning: player's level is not less than 4. Player is "
              << _level << "-" << _clock << " now." << std::endl;
  }
  if (_deck > 50) {
    std::cout << "Warning: deck is larger than 50, it's " << _deck << " now."
              << std::endl;
  }
  if (_climax_in_deck + _climax_in_waiting_room > 8) {
    std::cout << "Warning: player has more than 8 climax." << std::endl;
  }
  sethp(_hp);
  wssim::push_cards_into_deck(deck, card(0, card::CHAR, 0),
                              _deck - _climax_in_deck);
  wssim::push_cards_into_deck(deck, card(0, card::CLIMAX, 0), _climax_in_deck);
  wssim::push_cards_into_deck(waiting_room, card(0, card::CHAR, 0),
                              _waiting_room - _climax_in_waiting_room);
  wssim::push_cards_into_deck(waiting_room, card(0, card::CLIMAX, 0),
                              _climax_in_waiting_room);
}

int player::gethp() { return level.size() * 7 + clock.size(); }

void player::print() {
  std::cout << "deck: " << deck.size() << std::endl;
  for_each(deck.begin(), deck.end(), [](auto x) { x.print(); });
  std::cout << std::endl
            << "waiting_room: " << waiting_room.size() << std::endl;
  for_each(waiting_room.begin(), waiting_room.end(), [](auto x) { x.print(); });
  std::cout << std::endl << "level: " << level.size() << std::endl;
  for_each(level.begin(), level.end(), [](auto x) { x.print(); });
  std::cout << std::endl << "stock: " << stock.size() << std::endl;
  for_each(stock.begin(), stock.end(), [](auto x) { x.print(); });
  std::cout << std::endl << "clock: " << clock.size() << std::endl;
  for_each(clock.begin(), clock.end(), [](auto x) { x.print(); });
  std::cout << std::endl << "memory: " << memory.size() << std::endl;
  for_each(memory.begin(), memory.end(), [](auto x) { x.print(); });
  std::cout << std::endl << "stage: " << stage.size() << std::endl;
  for_each(stage.begin(), stage.end(), [](auto x) { x.print(); });
  std::cout << std::endl << "hands: " << hands.size() << std::endl;
  for_each(hands.begin(), hands.end(), [](auto x) { x.print(); });
  std::cout << std::endl;
}

bool player::death_check() { return level.size() >= 4; }

void player::refresh_check() {
  if (deck.empty()) {
    deck.insert(deck.end(), waiting_room.begin(), waiting_room.end());
    waiting_room.clear();
    wssim::shuffle(deck);
    clock.push_back(deck.back());
    deck.pop_back();
    levelup_check();
  }
}

void player::levelup_check() {
  if (clock.size() >= 7) {
    // Only first 7 cards in clock can be leveled up
    // We can only pop and push vector's back, so we have to reverse it
    // XXXXXXXOOO --(reverse)--> OOOXXXXXXX (We focus on "X")
    std::reverse(clock.begin(), clock.end());

    bool uped = false;
    for (int i = 0; i < 7; i++) {
      if (i == 6 && !uped) {
        level.push_back(clock[clock.size() - 1]);
        clock.pop_back();
        break;
      }
      if (uped) {
        waiting_room.push_back(clock[clock.size() - 1]);
        clock.pop_back();
      } else if (clock[clock.size() - 1].type == card::CLIMAX) {
        waiting_room.push_back(clock[clock.size() - 1]);
        clock.pop_back();
      } else {
        uped = true;
        level.push_back(clock[clock.size() - 1]);
        clock.pop_back();
      }
    }
    // reverse clock to original order
    std::reverse(clock.begin(), clock.end());
  }
}

bool player::take_damage(int damage) {
  bool canceled = false;
  std::vector<card> temp;
  for (int i = 0; i < damage; i++) {
    temp.push_back(deck.back());
    deck.pop_back();
    refresh_check();
    if (temp.back().type == card::CLIMAX) {
      canceled = true;
      break;
    }
  }
  if (canceled) {
    waiting_room.insert(waiting_room.end(), temp.begin(), temp.end());
  } else {
    clock.insert(clock.end(), temp.begin(), temp.end());
    levelup_check();
  }
  return canceled;
}

void player::take_true_damage(int damage) {
  std::vector<card> temp;
  for (int i = 0; i < damage; i++) {
    temp.push_back(deck.back());
    deck.pop_back();
    refresh_check();
  }
  clock.insert(clock.end(), temp.begin(), temp.end());
  levelup_check();
}

void player::be_mokaed(int count) {
  int n = count;
  if (deck.size() < count) {
    n = deck.size();
  }
  std::vector<card> tmp;
  for (int i = 0; i < n; i++) {
    if (deck.back().type != card::CLIMAX) {
      tmp.push_back(deck.back());
    }
    deck.pop_back();
  }
  int nn = tmp.size();
  for (int i = 0; i < nn; i++) {
    deck.push_back(tmp.back());
    tmp.pop_back();
  }
}

void player::back_and_shuffle(int count) {
  int found_card = 0;
  std::vector<card> temp;
  for (auto it = waiting_room.begin(); it != waiting_room.end();) {
    if (it->type != card::CLIMAX) {
      temp.push_back(*it);
      it = waiting_room.erase(it);
      found_card++;
    } else {
      it++;
    }
    if (found_card >= count) {
      break;
    }
  }
  deck.insert(deck.end(), temp.begin(), temp.end());
  wssim::shuffle(deck);
}

void player::back_to_top(int count) {
  int found_card = 0;
  std::vector<card> temp;
  for (auto it = waiting_room.begin(); it != waiting_room.end();) {
    if (it->type != card::CLIMAX) {
      temp.push_back(*it);
      it = waiting_room.erase(it);
      found_card++;
    } else {
      it++;
    }
    if (found_card >= count) {
      break;
    }
  }
  deck.insert(deck.end(), temp.begin(), temp.end());
}

int player::linglong7() {
  int triggers = 0;
  for (int i = 0; i < 7; i++) {
    triggers += deck.back().trigger;
    waiting_room.push_back(deck.back());
    deck.pop_back();
    refresh_check();
  }
  return triggers;
}

int player::woody6() {
  int res = 0;
  std::vector<card> temp;
  for (int i = 0; i < 6; i++) {
    if (deck.empty()) {
      break;
    }
    temp.push_back(deck.back());
    deck.pop_back();
    if (temp.back().type == card::CLIMAX) {
      res++;
    }
  }
  deck.insert(deck.end(), temp.begin(), temp.end());
  wssim::shuffle(deck);
  return res;
}

void player::take_aki_smoke(int smoke) {
  std::reverse(deck.begin(), deck.end());
  int smoked = 0;
  for (int i = 0; i < smoke; i++) {
    smoked++;
    if (deck.back().type == card::CLIMAX) {
      break;
    } else {
      deck.pop_back();
    }
  }

  int count = 0;
  for (int i = 0; i < 4; i++) {
    if (deck.back().type == card::CLIMAX) {
      count += 1;
    }
    deck.pop_back();
    refresh_check();
  }
  std::reverse(deck.begin(), deck.end());
  for (int i = 0; i < count; i++) {
    take_damage(1);
  }

  if (smoke - smoked >= 0) {
    std::reverse(deck.begin(), deck.end());
    for (int i = 0; i < smoke - smoked; i++) {
      if (deck.back().type == card::CLIMAX) {
        break;
      } else {
        deck.pop_back();
      }
    }
    std::reverse(deck.begin(), deck.end());
  }
}

// WARNING: unfinished.
void output_json(std::string path, const std::map<int, int> res) {
  std::ofstream fout(path, std::ios::out);
}
#endif /*_WSSIM_HPP_*/