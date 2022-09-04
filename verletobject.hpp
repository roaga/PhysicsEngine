#include "SFML/Graphics.hpp"

struct VerletObject {
    sf::Vector2f position_current;
    float radius;
    sf::Vector2f position_old;
    sf::Vector2f acceleration;

    VerletObject(sf::Vector2f position, float r) {
        position_current = position;
        radius = r;
        position_old = position_current;
        acceleration = sf::Vector2f(0.f, 0.f);
    }

    void updatePosition(float dt) {
        const sf::Vector2f velocity = position_current - position_old;
        position_old = position_current;
        // Verlet integration
        position_current = position_current + velocity + acceleration * dt * dt;
        acceleration = sf::Vector2f(0.f, 0.f);
    }

    void accelerate(sf::Vector2f acc) {
        acceleration += acc;
    }
};