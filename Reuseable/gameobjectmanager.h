#ifndef H_GAMEOBJECTMANAGER
#define H_GAMEOBJECTMANAGER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "gameobject.h"
#include "managertemplateclass.h"
#include "templateclass.h"

class GameobjectManager: public Monobehaviour<sf::RenderWindow*> , public Manager<GameObject>{
    public:
        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        GameObject* AddNewControlledComponent(GameObject obj) override;
        GameObject* GetControlledComponent(int idx) override;

        static GameobjectManager* GetInstance() {
            if (!instance) {
                instance = new GameobjectManager();
            }
            return instance;
        }

    private:
        static GameobjectManager* instance;
        
};


#endif