#include "stringhelp.h"

std::string StrHelp::replace(std::string original, std::string sub, std::string rep) {
    int len = sub.size();

    while (original.find(sub) != std::string::npos) {
        size_t pos = original.find(sub);
        original.replace(pos, len, rep);
    }

    return original;
}

bool StrHelp::matchAtPos(std::string original, int pos, std::string sub) {
    int len = sub.size();
    if (pos < 0 || pos + len - 1 >= (int) original.size()) {return false;}

    int c = 0;
    for (int i = pos; i <= pos + len - 1; i++) {
        if (original[i] == sub[c]) {
            c++;
        } else {
            return false;
        }
    }
    return true;
}

bool StrHelp::isNum(char c) {
    std::string num = "0123456789";
    if (num.find(c) != std::string::npos) {
        return true;
    }
    return false;
}