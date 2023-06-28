#ifndef _WSSIM_HPP_
#define _WSSIM_HPP_ 1
#include <algorithm>
#include <iostream>
#include <random>

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

  static void pattackp(player& atk, player& def, int soul);
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
  void refresh_check();
  void levelup_check();
  void take_damage(int damage);
  void back_and_shuffle(int count);
  int linglong7();
};

/* defination */
/* class card */
void card::print() {
  std::cout << "{" << level << "," << type << "," << trigger << "} ";
}

/* class wssim */
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

void wssim::pattackp(player& atk, player& def, int soul) {
  int damage = soul + atk.deck.back().trigger;
  atk.stock.push_back(atk.deck.back());
  atk.deck.pop_back();
  atk.refresh_check();
  def.take_damage(damage);
}

/* class player */
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

void player::take_damage(int damage) {
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
}

void player::back_and_shuffle(int count) {
  int found_card = 0;
  std::vector<card> temp;
  for (auto it = waiting_room.begin(); it != waiting_room.end();) {
    if (it->type != card::CLIMAX) {
      temp.push_back(*it);
      std::iter_swap(it, waiting_room.end() - 1);
      waiting_room.pop_back();
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
#endif /*_WSSIM_HPP_*/