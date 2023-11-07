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

        virtual Child* AddNewControlledComponent(Child args) {
            if ((int) this->controlledComponents.size() >= this->maxElement) {
                std::cerr << "Manager: Overflow. Please resize array." << '\n';
                return nullptr;
            }

            this->controlledComponents.push_back(args);
            return &this->controlledComponents[this->controlledComponents.size()-1];
        }

        virtual Child* GetControlledComponent(int idx) {
            if (idx < 0 || idx >= (int) this->controlledComponents.size()) {
                return nullptr;
            }

            return &this->controlledComponents[idx];
        }

        const static int maxElement = 100000;
};

#endif