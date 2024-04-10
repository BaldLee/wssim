#include "utils/card.hh"

namespace wssim {
std::string Card::to_str() const {
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
    // ss << "{lv" << __level << "," << type_str << "," << __trigger << "}";
    return std::string("{lv" + std::to_string(__level) + "," + type_str + "," +
                       std::to_string(__trigger) + "}");
}
}  // namespace wssim
