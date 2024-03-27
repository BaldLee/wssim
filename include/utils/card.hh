#pragma once
#include <iostream>
#include <sstream>

namespace wssim {
class card {
   public:
    static constexpr int CHAR = 0;
    static constexpr int CLIMAX = 1;
    static constexpr int EVENT = 2;
    static constexpr int WHATEVER = -1;

    card(int _level, int _type, int _trigger)
        : __level(_level), __type(_type), __trigger(_trigger) {}

    void print() const;
    std::string to_str() const;
    int level() const;
    int type() const;
    int trigger() const;
    void set_level(const int _level);
    void set_type(const int _type);
    void set_trigger(const int _trigger);

   private:
    int __level;
    int __type;
    int __trigger;
};
}  // namespace wssim
