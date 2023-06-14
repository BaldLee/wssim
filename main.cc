#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <stack>
#include <vector>

class wssim {
 private:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dist_boom;
  std::map<int, int> empty_map;

 public:
  wssim()
      : gen(std::mt19937(rd)),
        dist_boom(std::uniform_int_distribution<>(0, 100)),
        empty_map({{0, 0},  {1, 0},  {2, 0},  {3, 0},  {4, 0},  {5, 0},
                   {6, 0},  {7, 0},  {8, 0},  {9, 0},  {10, 0}, {11, 0},
                   {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0},
                   {18, 0}, {19, 0}, {20, 0}}) {}
  void print_deck(std::vector<bool>& deck) {
    std::for_each(deck.begin(), deck.end(),
                  [](auto x) { std::cout << x << " "; });
    std::cout << std::endl;
  }

  std::vector<bool> shuffle(std::vector<bool> deck, std::random_device& rd) {
    std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
    for (int i = 0; i < deck.size(); i++) {
      std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
    }
    return deck;
  }

  void shuffle_nocopy(std::vector<bool>& deck, std::random_device& rd) {
    std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
    for (int i = 0; i < deck.size(); i++) {
      std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
    }
  }

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

  bool is_boom(double boom_p) { return boom_p * 100 > dist_boom(gen); }

  void print_map(std::map<int, int>& res_map) {
    for (auto kv : res_map) {
      std::cout << kv.first << ", " << kv.second << std::endl;
    }
  }
};

class wsplayer {
 private:
  std::random_device rd;
  std::mt19937 gen;

 public:
  std::vector<int> stock;
  std::vector<int> hands;
  std::vector<int> level;
  std::vector<int> clock;
  std::vector<int> stage;
  std::vector<int> deck;
  std::vector<int> waiting;
  void shuffle_nocopy(std::vector<int>& deck, std::random_device& rd) {
    std::uniform_int_distribution<> dist_deck(0, deck.size() - 1);
    for (int i = 0; i < deck.size(); i++) {
      std::iter_swap(deck.begin() + i, deck.begin() + dist_deck(gen));
    }
  }
  void refresh() {
    if (!deck.empty()) {
      std::cerr << "deck must be empty" << std::endl;
    }
    deck.insert(deck.end(), waiting.begin(), waiting.end());
    waiting.clear();
    shuffle_nocopy(deck, rd);
  }
};

void test0(wssim& sim, double boomp, std::vector<bool>& deck,
           std::map<int, int>& res_map) {
  int damage;
  int total_damage = 0;
  // moka3 attack3 moka3 attack3 attack3
  sim.moka(deck, 3);
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  sim.moka(deck, 3);
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  res_map[total_damage] += 1;
}

void test1(wssim& sim, double boomp, std::vector<bool>& deck,
           std::map<int, int>& res_map) {
  int damage;
  int total_damage = 0;
  // damage3 attack3 damage3 attack3 attack3
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  res_map[total_damage] += 1;
}

void test2(wssim& sim, double boomp, std::vector<bool>& deck,
           std::map<int, int>& res_map) {
  int damage;
  int total_damage = 0;
  // moka2 attack3 moka2 attack3 attack3
  sim.moka(deck, 2);
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  sim.moka(deck, 2);
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  res_map[total_damage] += 1;
}

void test3(wssim& sim, double boomp, std::vector<bool>& deck,
           std::map<int, int>& res_map) {
  int damage;
  int total_damage = 0;
  // damage2 attack3 damage2 attack3 attack3
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  damage = 3 + sim.is_boom(boomp);
  if (sim.take_damage(deck, damage)) {
    total_damage += damage;
  }
  res_map[total_damage] += 1;
}

int main() {
  wssim sim;
  std::vector<bool> deck_30_8 = sim.generate_deck(30, 6);
  std::random_device rd;
  std::map<int, int> empty_map = {
      {0, 0},  {1, 0},  {2, 0},  {3, 0},  {4, 0},  {5, 0},  {6, 0},
      {7, 0},  {8, 0},  {9, 0},  {10, 0}, {11, 0}, {12, 0}, {13, 0},
      {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0}, {19, 0}, {20, 0}};
  auto res_map = empty_map;
  std::cout << "moka3 attack3 moka3 attack3 attack3" << std::endl;
  for (int i = 0; i < 50000; i++) {
    auto deck = sim.shuffle(deck_30_8, rd);
    test0(sim, 0.15, deck, res_map);
  }
  sim.print_map(res_map);
  res_map = empty_map;
  std::cout << "attack3 attack3 attack3 attack3 attack3" << std::endl;
  for (int i = 0; i < 50000; i++) {
    auto deck = sim.shuffle(deck_30_8, rd);
    test1(sim, 0.15, deck, res_map);
  }
  sim.print_map(res_map);
  res_map = empty_map;
  std::cout << "moka2 attack3 moka2 attack3 attack3" << std::endl;
  for (int i = 0; i < 50000; i++) {
    auto deck = sim.shuffle(deck_30_8, rd);
    test2(sim, 0.15, deck, res_map);
  }
  sim.print_map(res_map);
  res_map = empty_map;
  std::cout << "attack2 attack3 attack2 attack3 attack3" << std::endl;
  for (int i = 0; i < 50000; i++) {
    auto deck = sim.shuffle(deck_30_8, rd);
    test3(sim, 0.15, deck, res_map);
  }
  sim.print_map(res_map);
  return 0;
}
