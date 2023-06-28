#ifndef _WSSIM_HPP_
#define _WSSIM_HPP_ 1
#include <algorithm>
#include <iostream>
#include <random>

class card {
 public:
  int level;    // -1 for whatever
  int type;     // 0 for character, 1 for climax, 2 for event, -1 for whatever
  int trigger;  // -1 for whatever
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

#endif /*_WSSIM_HPP_*/