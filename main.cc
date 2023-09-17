#include "testcase.hpp"

int main() {
  // test_linglong();
  // test_twilight();
  // test_pixar_linglong();
  // test_marvel();
  // test_jotaro();
  // test_misuzu();
  // test_carcar();
  // test_supercarcar();
  // test_supersupercarcar();
  // test_carcarcar();
  // test_2woody();
  // test_3woody();
  // test_2dog2loyd();
  // test_3loyd();
  // wssim::basic_bench(test_sim_2woody, 20, 8, true);
  // wssim::basic_bench(test_sim_3woody, 20, 8, true);
  // wssim::basic_bench(test_sim_carcar, 20, 8, true);
  // wssim::basic_bench(sim_aki, 20, 8, true);
  // wssim::basic_bench(test_sim_carcarcar, 20, 8, true);
  // wssim::basic_bench(sim_karen, 20, 8, true);
  // wssim::basic_bench_json(sim_itsuki, 20, 8);
  // test_second();
  // test_multithread();
  // debug();
  // wssim::basic_bench_json(sim_aki, 20, 6);
  // wssim::basic_bench_json(sim_karen, 20, 6);
  // wssim::basic_bench_json(sim_dengeki_asuna, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3dengeki_asuna, 20, 6);
  // wssim::basic_bench_json_parallel(sim_2dengeki_asuna_mao, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3shana, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3linglong, 20, 17);
  // wssim::basic_bench_json_parallel(sim_2shana_kokei, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3anna, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3woody, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3wuyue, 20, 6);
  // wssim::basic_bench_json_parallel(sim_3liang, 20, 6);
  player atk;
  wssim::push_cards_into_deck(atk.deck, card(0, card::CLIMAX, 0), 6);
  wssim::push_cards_into_deck(atk.deck, card(0, card::CHAR, 0), 5);
  wssim::push_cards_into_deck(atk.deck, card(0, card::CHAR, 1), 4);
  wssim::basic_bench_json_parallel(sim_3bocchi, atk);
  return 0;
}
