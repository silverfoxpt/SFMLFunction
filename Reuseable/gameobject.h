#ifndef H_GAMEOBJECT
#define H_GAMEOBJECT

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "gameManager.h"
#include "math.h"
#include "templateclass.h"
#include "componenttemplateclass.h"

class GameObject : Monobehaviour<sf::RenderWindow*>{
    public:
        sf::RenderWindow* window;

        sf::RectangleShape user;
        sf::Vector2f position;
        sf::Vector2f scale;
        float rotation; //range 0-360
        int width, height;

        //other components
        std::vector<Component*> components;

        GameObject(int width, int height);
        void SetWorldPosition(sf::Vector2f position);
        void SetScale(sf::Vector2f scale);
        void SetRotation(float rotation);
        void SetColor(sf::Color color);
        void SetTexture(sf::Texture* tex);

        void Rotate(float eulerAngle);
        void RotateToVector(sf::Vector2f vec);
        
        sf::Vector2f GetScreenPosition();
        sf::Vector2f GetWorldPosition();
        sf::Vector2f GetNormalizeRotationVector();

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        template<typename X>
        void AddComponent(X* comp) {
            Component* castedComponent = dynamic_cast<Component*>(comp);
            if (castedComponent) {
                this->components.push_back(castedComponent);
            }
        }

        template<typename T>
        T* GetComponent() {
            for (Component* component : components) {
                T* castedComponent = dynamic_cast<T*>(component);
                if (castedComponent) {
                    return castedComponent;
                }
            }
            return nullptr;
        }

    private:
};

#endif