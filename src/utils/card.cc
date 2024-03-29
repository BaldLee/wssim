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
    ss << "{lv" << __level << "," << type_str << "," << __trigger << "}";
    return ss.str();
}
}  // namespace wssim
