#include "utils/card.hh"

namespace wssim {
std::string card::to_str() const {
    std::stringstream ss;
    std::string type_str;
    switch (__type) {
        case CHAR:
            type_str = "CHAR";
            break;
        case CLIMAX:
            type_str = "CLIMAX";
            break;
        case EVENT:
            type_str = "EVENT";
            break;
        default:
            type_str = "NOTYPE";
    }
    ss << "{lv" << __level << "," << type_str << "," << __trigger << "} ";
    return ss.str();
}

void card::print() const { std::cout << to_str(); }

int card::level() const { return __level; }

int card::type() const { return __type; }

int card::trigger() const { return __trigger; }

void card::set_level(const int _level) { __level = _level; }

void card::set_type(const int _type) { __type = _type; }

void card::set_trigger(const int _trigger) { __trigger = _trigger; }
}  // namespace wssim
