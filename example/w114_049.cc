#include <vector>

#include "benchmark/benchmark.hh"
#include "utils/player.hh"

void sim(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 2; i++) {
            if (def.take_michiru(2)) {
                def.take_damage(2);
            }
        }
        atk.attack(def, 3);
    }
}

int main() {
    wssim::benchmark(10000, sim);
    return 0;
}
