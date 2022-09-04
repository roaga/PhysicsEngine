#include "SFML/Graphics.hpp"
#include "vector"
#include "solver.hpp"

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Circle Engine");

    // define shapes
    VerletObject obj1(sf::Vector2f(820.f, 450.f), 25.f);
    VerletObject obj2(sf::Vector2f(510.f, 470.f), 10.f);
    VerletObject obj3(sf::Vector2f(600.f, 450.f), 50.f);

    // Physics Engine Solver
    Solver engine;
    engine.verletObjects.push_back(obj1);
    engine.verletObjects.push_back(obj2);
    engine.verletObjects.push_back(obj3);

    // constraint window
    sf::CircleShape constraint(400, 100);
    constraint.setPosition(400.f, 50.f);
    constraint.setFillColor(sf::Color::White);
 
    int iters = 0;
    while (window.isOpen()) {
        iters++;
        if (iters % 1000 == 0) {
            // spawning
            if (engine.verletObjects.size() < 200) {
                VerletObject obj(sf::Vector2f(800.f, 200.f), 10.f + rand() % 10);
                engine.verletObjects.push_back(obj);
            }
            iters = 0;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // update shape positions
        engine.update(0.01f); // TODO: calculate dt

        // render    
        window.clear(sf::Color(200, 200, 200));
        window.draw(constraint);
        std::vector<VerletObject>::iterator it;
        for (it = engine.verletObjects.begin(); it != engine.verletObjects.end(); it++) {
            sf::CircleShape shape(it->radius);
            shape.setPosition(it->position_current - sf::Vector2f(it->radius, it->radius));
            shape.setFillColor(sf::Color::Black);

            window.draw(shape);
        }
        window.display();
    }
    return 0;
}