#include "benchmark/benchmark.hh"
#include "utils/player.hh"

// w114_049
void sim_w114_049(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 3; i++) {
            if (def.take_michiru(2)) {
                def.take_damage(2);
            }
        }
        atk.attack(def, 3);
    }
}

// w101_079
void sim_w101_079(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        if (def.take_michiru(5)) {
            def.take_damage(1);
            def.take_damage(1);
        }
        atk.attack(def, 3);
    }
}

// w112_003
void sim_w112_003(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        int x = def.take_michiru(4);
        for (int i = 0; i < x; i++) {
            def.take_damage(1);
        }
        atk.attack(def, 3);
    }
}

// s109_060
void sim_s109_060(wssim::Player& atk, wssim::Player& def) {
    for (int i = 0; i < 3; i++) {
        int x = def.take_michiru(6);
        for (int i = 0; i < x; i++) {
            def.take_damage(1);
        }
        atk.attack(def, 3);
    }
}

// s108_003
void sim_s108_003(wssim::Player& atk, wssim::Player& def) {
    def.pop_bottom_until_climax(2);
    for (int i = 0; i < 3; i++) {
        int x = def.take_michiru(3);
        for (int i = 0; i < x; i++) {
            def.take_damage(2);
        }
        atk.attack(def, 3);
    }
}

int main() {
    wssim::benchmark(10000, sim_s108_003);
    return 0;
}
