#pragma once
#include <iostream>

namespace wssim {
class card {
   public:
    static constexpr int CHAR = 0;
    static constexpr int CLIMAX = 1;
    static constexpr int EVENT = 2;
    static constexpr int WHATEVER = -1;

    card(int _level, int _type, int _trigger)
        : __level(_level), __type(_type), __trigger(_trigger) {}

    std::string to_str() const;

    inline void print() const { std::cout << to_str(); }

    inline int level() const { return __level; }

    inline int type() const { return __type; }

    inline int trigger() const { return __trigger; }

    inline void set_level(const int _level) { __level = _level; }

    inline void set_type(const int _type) { __type = _type; }

    inline void set_trigger(const int _trigger) { __trigger = _trigger; }

   private:
    int __level;
    int __type;
    int __trigger;
};
}  // namespace wssim
