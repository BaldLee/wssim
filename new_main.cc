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
  void print() {
    std::cout << "{" << type << "," << level << "," << trigger << "} ";
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
  player() {}
  player(std::vector<card>& _deck, std::vector<card>& _waiting_room,
         std::vector<card>& _level, std::vector<card>& _stock,
         std::vector<card>& _clock, std::vector<card>& _memory,
         std::vector<card>& _stage)
      : deck(_deck),
        waiting_room(_waiting_room),
        level(_level),
        stock(_stock),
        clock(_clock),
        memory(_memory),
        stage(_stage) {}
};

class wssim {
 private:
  static std::random_device rd;
  static std::mt19937 gen;

 public:
  wssim() {}
  void print_deck(const std::vector<card>& deck) {
    std::for_each(deck.begin(), deck.end(), [](auto x) { x.print(); });
    std::cout << std::endl;
  }

  std::vector<card> shuffle_copy(std::vector<card> deck) {
    std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
    for (int i = 0; i < deck.size(); i++) {
      std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
    }
    return deck;
  }

  void shuffle(std::vector<card>& deck) {
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

std::random_device wssim::rd;
std::mt19937 wssim::gen(std::mt19937(wssim::rd));