#include "stringhelp.h"

std::string StrHelp::replace(std::string original, std::string sub, std::string rep) {
    int len = sub.size();

    while (original.find(sub) != std::string::npos) {
        size_t pos = original.find(sub);
        original.replace(pos, len, rep);
    }

    return original;
}