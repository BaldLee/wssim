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
  wssim::basic_bench(test_sim_carcar, 20, 8, true);
  return 0;
}
