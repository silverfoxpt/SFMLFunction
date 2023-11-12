#ifndef H_STRINGHELP
#define H_STRINGHELP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class StrHelp {
    public:
        static std::string replace(std::string original, std::string sub, std::string rep);
        static bool matchAtPos(std::string original, int pos, std::string sub);
        
        static bool isNum(char c);
        static bool isAlpha(char c);

    private:
        
};

#endif