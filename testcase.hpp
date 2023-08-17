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

void test_linglong() {
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
}

int test_sim_twilight(const player& atk, const player& def) {
  int killed_count = 0;
  for (int i = 0; i < REPEAT; i++) {
    // std::cout << "hello" << std::endl;
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    // burn 1 burn 1 moka 1
    d.take_damage(1);
    d.take_damage(1);
    d.be_mokaed(1);
    // twilight: burn 3 if cancel burn 1
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);
    // dog attack
    wssim::pattackp(a, d, 3);
    // twilight: burn 3 if cancel burn 1
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed_count++;
    }
  }

  return killed_count;
}

void test_twilight() {
  player atk;
  // attack deck trigger: 8/20
  for (int i = 0; i < 8; i++) {
    atk.deck.push_back(card(0, card::CHAR, 1));
  }
  for (int i = 0; i < 12; i++) {
    atk.deck.push_back(card(0, card::CHAR, 0));
  }
  player def30_8;
  for (int i = 0; i < 8; i++) {
    def30_8.deck.push_back(card(0, card::CLIMAX, 0));
  }
  for (int i = 0; i < 22; i++) {
    def30_8.deck.push_back(card(0, card::CHAR, 0));
  }
  player def30_6;
  for (int i = 0; i < 6; i++) {
    def30_6.deck.push_back(card(0, card::CLIMAX, 0));
  }
  for (int i = 0; i < 24; i++) {
    def30_6.deck.push_back(card(0, card::CHAR, 0));
  }
  player def25_8;
  for (int i = 0; i < 8; i++) {
    def25_8.deck.push_back(card(0, card::CLIMAX, 0));
  }
  for (int i = 0; i < 17; i++) {
    def25_8.deck.push_back(card(0, card::CHAR, 0));
  }
  player def25_6;
  for (int i = 0; i < 6; i++) {
    def25_6.deck.push_back(card(0, card::CLIMAX, 0));
  }
  std::map<std::string, player> def_map;
  def_map["30/8"] = def30_8;
  def_map["30/6"] = def30_6;
  def_map["25/8"] = def25_8;
  def_map["25/6"] = def25_6;
  for (int i = 0; i < 19; i++) {
    def25_6.deck.push_back(card(0, card::CHAR, 0));
  }
  for (int i = 9; i < 28; i++) {
    int hp = i;
    int level = hp / 7;
    int clock = hp % 7;
    std::map<std::string, player> d_map;
    auto d1 = def30_8;
    auto d2 = def30_6;
    auto d3 = def25_8;
    auto d4 = def25_6;
    d1.sethp(i);
    d2.sethp(i);
    d3.sethp(i);
    d4.sethp(i);
    d_map["30/8"] = d1;
    d_map["30/6"] = d2;
    d_map["25/8"] = d3;
    d_map["25/6"] = d4;
    // std::for_each(d_map.begin(), d_map.end(), [](auto x) {
    //   std::cout << x.first << std::endl;
    //   x.second.print();
    // });
    for (auto x : d_map) {
      int res = test_sim_twilight(atk, x.second);
      std::cout << level << "-" << clock << " " << x.first << " : "
                << double(res) / REPEAT << std::endl;
    }
  }
}

int test_sim_pixar_linglong1(const player& atk, const player& def) {
  // 434 43 43
  int killed_count = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    int soul = 3;
    // 434
    d.take_damage(4);
    d.back_and_shuffle(3);
    d.take_damage(4);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);
    // 43
    d.take_damage(4);
    d.back_and_shuffle(3);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);
    // 43
    d.take_damage(4);
    d.back_and_shuffle(3);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);

    if (d.level.size() >= 4) {
      killed_count++;
    }
  }
  return killed_count;
}

int test_sim_pixar_linglong2(const player& atk, const player& def) {
  // 434 434 43
  int killed_count = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    int soul = 3;
    // 434
    d.take_damage(4);
    d.back_and_shuffle(3);
    d.take_damage(4);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);
    // 434
    d.take_damage(4);
    d.back_and_shuffle(3);
    d.take_damage(4);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);
    // 43
    d.take_damage(4);
    d.back_and_shuffle(3);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);

    if (d.level.size() >= 4) {
      killed_count++;
    }
  }
  return killed_count;
}

int test_sim_pixar_linglong3(const player& atk, const player& def) {
  // 434 434 434
  int killed_count = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    int soul = 3;
    // 434
    d.take_damage(4);
    d.back_and_shuffle(3);
    d.take_damage(4);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);
    // 434
    d.take_damage(4);
    d.back_and_shuffle(3);
    d.take_damage(4);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);
    // 434
    d.take_damage(4);
    d.back_and_shuffle(3);
    d.take_damage(4);
    if (d.gethp() == 25 || d.gethp() == 21) {
      soul = 2;
    } else {
      soul = 3;
    }
    wssim::pattackp(a, d, soul);

    if (d.level.size() >= 4) {
      killed_count++;
    }
  }
  return killed_count;
}

void test_pixar_linglong() {
  player atk;
  // attack deck trigger: 22/25
  for (int i = 0; i < 22; i++) {
    atk.deck.push_back(card(0, card::CHAR, 1));
  }
  for (int i = 0; i < 3; i++) {
    atk.deck.push_back(card(0, card::CHAR, 0));
  }
  player def;
  for (int i = 0; i < 18; i++) {
    def.deck.push_back(card(0, card::CHAR, 0));
  }
  for (int i = 0; i < 7; i++) {
    def.deck.push_back(card(0, card::CLIMAX, 0));
  }
  for (int i = 0; i < 3; i++) {
    def.waiting_room.push_back(card(0, card::CHAR, 0));
  }
  def.waiting_room.push_back(card(0, card::CLIMAX, 0));
  def.sethp(16);

  std::cout << double(test_sim_pixar_linglong1(atk, def)) / REPEAT << std::endl;
  std::cout << double(test_sim_pixar_linglong2(atk, def)) / REPEAT << std::endl;
  std::cout << double(test_sim_pixar_linglong3(atk, def)) / REPEAT << std::endl;
}

void test_marvel() {
  player m;
  wssim::push_cards_into_deck(m.deck, card(0, card::CLIMAX, 0), 8);
  wssim::push_cards_into_deck(m.deck, card(0, card::CHAR, 0), 30);
  int success = 0;
  int count = 0;
  while (success == 0) {
    count++;
    player mm = m;
    wssim::shuffle(mm.deck);
    for (int k = 0; k < 8; k++) {
      if (mm.deck[k].type != card::CLIMAX) {
        break;
      }
      if (k == 7) {
        success += 1;
      }
    }
  }
  std::cout << count << std::endl;
}

int test_sim_jotaro(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    wssim::pattackp(a, d, 3);
    for (int i = 0; i < 7; i++) {
      d.take_damage(1);
    }
    d.take_damage(7);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_jotaro() {
  player atk;
  player def;
  atk.init_attacker(20, 10);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 0, 0);
    std::cout << "8/25: " << double(test_sim_jotaro(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 0, 0);
    std::cout << "6/25: " << double(test_sim_jotaro(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 0, 0);
    std::cout << "8/30: " << double(test_sim_jotaro(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 0, 0);
    std::cout << "6/30: " << double(test_sim_jotaro(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_misuzu(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    wssim::pattackp(a, d, 3);

    for (int i = 0; i < 7; i++) {
      d.take_damage(i + 1);
    }

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_misuzu() {
  player atk;
  player def;
  atk.init_attacker(20, 10);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 0, 0);
    std::cout << "8/25: " << double(test_sim_misuzu(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 0, 0);
    std::cout << "6/25: " << double(test_sim_misuzu(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 0, 0);
    std::cout << "8/30: " << double(test_sim_misuzu(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 0, 0);
    std::cout << "6/30: " << double(test_sim_misuzu(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_carcar(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_carcar() {
  player atk;
  player def;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_carcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_carcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_carcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_carcar(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_supercarcar(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    d.take_damage(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_supercarcar() {
  player atk;
  player def;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_supercarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_supercarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_supercarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_supercarcar(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_supersupercarcar(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    d.take_damage(1);
    d.take_damage(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_supersupercarcar() {
  player atk;
  player def;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: "
              << double(test_sim_supersupercarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: "
              << double(test_sim_supersupercarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: "
              << double(test_sim_supersupercarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: "
              << double(test_sim_supersupercarcar(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_carcarcar(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);
    d.take_damage(3);
    d.back_to_top(1);
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_carcarcar() {
  player atk;
  player def;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_carcarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_carcarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_carcarcar(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_carcarcar(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_2woody(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    wssim::pattackp(a, d, 3);
    d.take_true_damage(d.woody6());
    wssim::pattackp(a, d, 3);
    d.take_true_damage(d.woody6());
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_2woody() {
  player atk;
  player def;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_2woody(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_2woody(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_2woody(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_2woody(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_3woody(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    wssim::pattackp(a, d, 3);
    d.take_true_damage(d.woody6());
    wssim::pattackp(a, d, 3);
    d.take_true_damage(d.woody6());
    wssim::pattackp(a, d, 3);
    d.take_true_damage(d.woody6());

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_3woody() {
  player atk;
  player def;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_3woody(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_3woody(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_3woody(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_3woody(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_2dog2loyd(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    d.take_damage(1);
    d.take_damage(1);
    d.be_mokaed(1);
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_2dog2loyd() {
  player atk;
  player def;
  atk.init_attacker(20, 10);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_2dog2loyd(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_2dog2loyd(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_2dog2loyd(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_2dog2loyd(atk, def)) / REPEAT
              << std::endl;
  }
}

int test_sim_3loyd(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    player a = atk;
    player d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    d.be_mokaed(1);
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);
    if (d.take_damage(3)) {
      d.take_damage(1);
    }
    wssim::pattackp(a, d, 3);

    if (d.level.size() >= 4) {
      killed += 1;
    }
  }
  return killed;
}

void test_3loyd() {
  player atk;
  player def;
  atk.init_attacker(20, 10);
  for (int hp = 14; hp < 28; hp++) {
    std::cout << hp / 7 << "-" << hp % 7 << ": " << std::endl;
    def.init_defender(hp, 25, 8, 4, 0);
    std::cout << "8/25: " << double(test_sim_3loyd(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 25, 6, 4, 0);
    std::cout << "6/25: " << double(test_sim_3loyd(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 8, 4, 0);
    std::cout << "8/30: " << double(test_sim_3loyd(atk, def)) / REPEAT
              << std::endl;
    def.init_defender(hp, 30, 6, 4, 0);
    std::cout << "6/30: " << double(test_sim_3loyd(atk, def)) / REPEAT
              << std::endl;
  }
}

int sim_aki(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    d.take_aki_smoke(3);
    wssim::pattackp(a, d, 3);
    d.take_aki_smoke(3);
    wssim::pattackp(a, d, 3);
    d.take_aki_smoke(3);
    wssim::pattackp(a, d, 3);

    if (d.death_check()) {
      killed += 1;
    }
  }
  return killed;
}

int sim_karen(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    for (int i = 0; i < 3; i++) {
      d.take_damage(1);
      d.be_mokaed(2);
      wssim::pattackp(a, d, 3);
    }

    if (d.death_check()) {
      killed += 1;
    }
  }
  return killed;
}

int sim_itsuki(player& atk, player& def) {
  int killed = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);

    for (int i = 0; i < 3; i++) {
      d.take_damage(3);
      d.be_mokaed(3);
      wssim::pattackp(a, d, 3);
    }

    if (d.death_check()) {
      killed += 1;
    }
  }
  return killed;
}

void test_second() {
  player atk, def;
  atk.init_attacker(50, 15);
  def.init_defender(1, 41, 7, 0, 0);
  // 1 2 2
  unsigned long long res0 = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    wssim::pattackp(a, d, 1);
    wssim::pattackp(a, d, 2);
    wssim::pattackp(a, d, 2);
    res0 += d.clock.size();
  }

  // 2 1 2
  unsigned long long res1 = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    wssim::pattackp(a, d, 2);
    wssim::pattackp(a, d, 1);
    wssim::pattackp(a, d, 2);
    res1 += d.clock.size();
  }

  // 2 2 1
  unsigned long long res2 = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    wssim::pattackp(a, d, 2);
    wssim::pattackp(a, d, 2);
    wssim::pattackp(a, d, 1);
    res2 += d.clock.size();
  }

  // fix(2) 1 2
  unsigned long long res3 = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    d.take_damage(2);
    wssim::pattackp(a, d, 1);
    wssim::pattackp(a, d, 2);
    res3 += d.clock.size();
  }

  // fix(2) 2 1
  unsigned long long res4 = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    d.take_damage(2);
    wssim::pattackp(a, d, 2);
    wssim::pattackp(a, d, 1);
    res4 += d.clock.size();
  }

  // fix(1) 2 2
  unsigned long long res5 = 0;
  for (int i = 0; i < REPEAT; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    d.take_damage(1);
    wssim::pattackp(a, d, 2);
    wssim::pattackp(a, d, 2);
    res5 += d.clock.size();
  }

  std::cout << "1 2 2: " << double(res0) / REPEAT << std::endl;
  std::cout << "2 1 2: " << double(res1) / REPEAT << std::endl;
  std::cout << "2 2 1: " << double(res2) / REPEAT << std::endl;
  std::cout << "fix(2) 1 2: " << double(res3) / REPEAT << std::endl;
  std::cout << "fix(2) 2 1: " << double(res4) / REPEAT << std::endl;
  std::cout << "fix(1) 2 2: " << double(res5) / REPEAT << std::endl;
}

int three_two_three_two_three_two(player atk, player def, int inner_repeat) {
  int res = 0;
  for (int i = 0; i < inner_repeat; i++) {
    auto a = atk;
    auto d = def;
    wssim::shuffle(a.deck);
    wssim::shuffle(d.deck);
    for (int i = 0; i < 3; i++) {
      wssim::pattackp(a, d, 3);
      d.take_damage(2);
    }
    if (d.death_check()) {
      res += 1;
    }
  }
  return res;
}

void test_multithread() {
  player atk, def;
  const int outer_repeat = 40;
  const int inner_repeat = 25000;
  atk.init_attacker(20, 8);
  for (int hp = 14; hp < 28; hp++) {
    def.init_defender(hp, 25, 7, 10, 1);
    int killed = wssim::multhread_sim(three_two_three_two_three_two, atk, def,
                                      outer_repeat, 40, inner_repeat);
    std::cout << hp / 7 << "-" << hp % 7 << ": " << killed << "/"
              << outer_repeat * inner_repeat << std::endl;
  }
}

int foo(int x) { return x + 1; }

void debug() {
  player atk, def;
  atk.init_attacker(20, 8);
  def.init_defender(21, 25, 7, 10, 1);
  int outer_repeat = 1;
  int inner_repeat = 1;
  wssim::multhread_sim(three_two_three_two_three_two, atk, def, outer_repeat,
                       32, inner_repeat);
}