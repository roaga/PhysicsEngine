# Circle Engine
A simple 2D physics engine experiment that uses Vertel integration to simulate the physics of circle objects.
Written in C++ with SFML for rendering.

![Screenshot 1](https://github.com/roaga/PhysicsEngine/blob/master/Screen%20Shot%202022-09-04%20at%2011.10.56%20AM.png?raw=true)
![Screenshot 2](https://github.com/roaga/PhysicsEngine/blob/master/Screen%20Shot%202022-09-04%20at%2011.10.36%20AM.png?raw=true)


### To Run on Intel Mac
Install SFML with brew.

```
g++ main.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include -o physics -lsfml-graphics -lsfml-window -lsfml-system
./physics
```
