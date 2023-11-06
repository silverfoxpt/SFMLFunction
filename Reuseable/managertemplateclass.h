#ifndef H_MANAGERTEMPLATECLASS
#define H_MANAGERTEMPLATECLASS

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

template <typename Child>
class Manager {
    protected:
        std::vector<Child> controlledComponents;

    public:
        //IMPORTANT: REMEMBER TO CALL THIS 
        Manager() {
            this->controlledComponents.reserve(100000);
        }
        virtual Child* AddNewControlledComponent(Child args)   = 0;
        virtual Child* GetControlledComponent(int idx) = 0;

        const static int maxElement = 100000;
};

#endif