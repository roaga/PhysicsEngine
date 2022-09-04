#include "vector"
#include <cmath>
#include "SFML/Graphics.hpp"
#include "verletobject.hpp"

struct Solver {
    std::vector<VerletObject> verletObjects;
    sf::Vector2f gravity;

    Solver() {
        gravity = sf::Vector2f(0.f, 2.f);
    }

    void update(float dt) {
        const uint32_t subSteps = 1;
        const float subDt = dt / static_cast<float>(subSteps);
        for (uint32_t i = 0; i < subSteps; i++) {
            applyGravity();
            applyConstraint();
            solveCollisions();
            updatePositions(subDt);
        }
    }

    void updatePositions(float dt) {
        std::vector<VerletObject>::iterator it;
        for (it = verletObjects.begin(); it != verletObjects.end(); it++) {
            it->updatePosition(dt);
        }
    }

    void applyGravity() {
        std::vector<VerletObject>::iterator it;
        for (it = verletObjects.begin(); it != verletObjects.end(); it++) {
            it->accelerate(gravity);
        }
    }

    void applyConstraint() {
        const sf::Vector2f position = sf::Vector2f(800.f, 450.f);
        const float radius = 400.f;
        std::vector<VerletObject>::iterator it;
        for (it = verletObjects.begin(); it != verletObjects.end(); it++) {
            const sf::Vector2f toObj = it->position_current - position;
            const float dist = pow((toObj.x*toObj.x) + (toObj.y*toObj.y), 0.5);

            if (dist > radius - it->radius) {
                const sf::Vector2f n = toObj / dist;
                it->position_current = position + n * (radius - it->radius);
            }
        }
    }

    void solveCollisions() {
        const uint32_t objectCount = verletObjects.size();

        for (uint32_t i = 0; i < objectCount; i++) {
            VerletObject object1 = verletObjects[i];

            for (uint32_t j = i + 1; j < objectCount; j++) {
                VerletObject object2 = verletObjects[j];

                const sf::Vector2f collisionAxis = object1.position_current - object2.position_current;
                const float dist = pow((collisionAxis.x*collisionAxis.x) + (collisionAxis.y*collisionAxis.y), 0.5);
                const float minDist = object1.radius + object2.radius;
                
                if (dist < minDist) {
                    const sf::Vector2f n = collisionAxis / dist;
                    const float delta = minDist - dist;
                    verletObjects.at(i).position_current = object1.position_current + 0.5f * delta * n;
                    verletObjects.at(j).position_current = object2.position_current - 0.5f * delta * n;
                }
            }
        }
    }
};