// Simple Game Physics - Lab 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    PhysicsCircle ball;
    ball.setCenter(Vector2f(100, 100));
    ball.setRadius(20);
    ball.applyImpulse(Vector2f(-1.0f, -0.0f));
    world.AddPhysicsBody(ball);

    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    PhysicsRectangle centerBox;
    centerBox.setSize(Vector2f(100, 100));
    centerBox.setCenter(Vector2f(400, 300));
    centerBox.setStatic(true);
    world.AddPhysicsBody(centerBox);

    int thudCount(0);
    int bangCount(0);

    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
            cout << "Thud #" << thudCount << endl;
            thudCount++;
        };
    ceiling.onCollision = floor.onCollision;
    leftWall.onCollision = floor.onCollision;
    rightWall.onCollision = floor.onCollision;
    centerBox.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
            cout << "Bang #" << bangCount << endl;
            bangCount++;
            if (bangCount == 3) {
                exit(0);
            }
        };

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (true) {
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }
        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(centerBox);
        window.display();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file