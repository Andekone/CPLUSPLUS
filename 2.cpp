
#include <iostream>
#include <windows.h>  // для Sleep()
#include <ctime>      // для std::time и std::srand
#include <cstdlib>    // для std::rand и std::abs
#include <cmath>      // для std::sqrt

using namespace std;

class Point2D {
public:
    int x;
    int y;

    Point2D(int x = 0, int y = 0) : x(x), y(y) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    int distanceTo(const Point2D& other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

class Character {
public:
    Point2D position;

    Character(int x = 0, int y = 0) : position(x, y) {}

    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

    Point2D getPosition() const {
        return position;
    }

    virtual void move(int dx, int dy) {
        position.move(dx, dy);
    }
};

class Prey : public Character {
public:
    Prey(int x = 0, int y = 0) : Character(x, y) {}

    void autoMove(const Point2D& predatorPos, int width, int height) {
        // Move away from the predator
        if (position.x < predatorPos.x)
            position.x--;
        else if (position.x > predatorPos.x)
            position.x++;

        if (position.y < predatorPos.y)
            position.y--;
        else if (position.y > predatorPos.y)
            position.y++;

        // Make sure Prey stays within the bounds of the arena
        if (position.x < 0)
            position.x = 0;
        else if (position.x >= width)
            position.x = width - 1;

        if (position.y < 0)
            position.y = 0;
        else if (position.y >= height)
            position.y = height - 1;
    }
};

class Predator : public Character {
public:
    Predator(int x = 0, int y = 0) : Character(x, y) {}

    void moveTowardPrey(const Point2D& preyPos) {
        // Move towards the prey
        if (position.x < preyPos.x)
            position.x++;
        else if (position.x > preyPos.x)
            position.x--;

        if (position.y < preyPos.y)
            position.y++;
        else if (position.y > preyPos.y)
            position.y--;
    }
};

class Arena {
public:
    const int width;
    const int height;
    const int movesLimit;
    Prey prey;
    Predator predator;

    Arena(int width, int height, int movesLimit)
        : width(width), height(height), movesLimit(movesLimit), prey(), predator() {
        std::srand(std::time(NULL));
        prey.setPosition(std::rand() % width, std::rand() % height);
        predator.setPosition(std::rand() % width, std::rand() % height);
    }

    void display() const {
        system("cls");
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (x == predator.getPosition().x && y == predator.getPosition().y)
                    std::cout << "$ ";
                else if (x == prey.getPosition().x && y == prey.getPosition().y)
                    std::cout << "@ ";
                else
                    std::cout << ". ";
            }
            std::cout << std::endl;
        }
        std::cout << "Prey - @    Predator - $" << std::endl;
    }

    bool checkCollision() const {
        return prey.getPosition().x == predator.getPosition().x &&
            prey.getPosition().y == predator.getPosition().y;
    }
};

int main() {
    int WIDTH = 20;
    int HEIGHT = 20;
    int MOVES_LIMIT = 40;

    Arena arena(WIDTH, HEIGHT, MOVES_LIMIT);
    bool validUserInput;
    char ch;

    do {
        validUserInput = true;
        std::cout << "Choose hero:" << std::endl;
        std::cout << "1. Predator" << std::endl;
        std::cout << "2. Prey" << std::endl;
        std::cin >> ch;

        if (ch == '1') {
            std::cout << "Predator" << std::endl;
            std::srand(std::time(nullptr));
            int limit = MOVES_LIMIT;

            while (limit > 0) {
                arena.display();
                char direction;
                std::cout << "Direction:" << std::endl;
                std::cout << "w - up    s - down   a - left   d - right" << std::endl;
                std::cin >> direction;

                switch (direction) {
                case 'w':
                    arena.predator.move(0, -1);
                    break;
                case 's':
                    arena.predator.move(0, 1);
                    break;
                case 'a':
                    arena.predator.move(-1, 0);
                    break;
                case 'd':
                    arena.predator.move(1, 0);
                    break;
                }

                // Ensure Predator doesn't go out of bounds
                if (arena.predator.getPosition().x < 0)
                    arena.predator.setPosition(0, arena.predator.getPosition().y);
                else if (arena.predator.getPosition().x >= WIDTH)
                    arena.predator.setPosition(WIDTH - 1, arena.predator.getPosition().y);

                if (arena.predator.getPosition().y < 0)
                    arena.predator.setPosition(arena.predator.getPosition().x, 0);
                else if (arena.predator.getPosition().y >= HEIGHT)
                    arena.predator.setPosition(arena.predator.getPosition().x, HEIGHT - 1);

                if (arena.checkCollision()) {
                    std::cout << "GAME OVER. YOU WIN" << std::endl;
                    Sleep(5000);
                    break;
                }

                arena.prey.autoMove(arena.predator.getPosition(), WIDTH, HEIGHT);

                if (arena.checkCollision()) {
                    std::cout << "GAME OVER. YOU LOSE" << std::endl;
                    Sleep(5000);
                    break;
                }

                --limit;

                if (limit == 0) {
                    std::cout << "GAME OVER. YOU LOSE" << std::endl;
                    Sleep(5000);
                }
            }
        }
        else if (ch == '2') {
            std::cout << "Prey" << std::endl;
            std::srand(std::time(nullptr));
            int limit = MOVES_LIMIT;

            while (limit > 0) {
                arena.display();

                if (arena.checkCollision()) {
                    std::cout << "GAME OVER. YOU LOSE" << std::endl;
                    Sleep(5000);


                    break;
                }

                char direction;
                std::cout << "Direction:" << std::endl;
                std::cout << "w - up    s - down   a - left   d - right" << std::endl;
                std::cin >> direction;

                switch (direction) {
                case 'w':
                    arena.prey.move(0, -1);
                    break;
                case 's':
                    arena.prey.move(0, 1);
                    break;
                case 'a':
                    arena.prey.move(-1, 0);
                    break;
                case 'd':
                    arena.prey.move(1, 0);
                    break;
                }

                if (arena.prey.getPosition().x < 0)
                    arena.prey.setPosition(0, arena.prey.getPosition().y);
                else if (arena.prey.getPosition().x >= WIDTH)
                    arena.prey.setPosition(WIDTH - 1, arena.prey.getPosition().y);

                if (arena.prey.getPosition().y < 0)
                    arena.prey.setPosition(arena.prey.getPosition().x, 0);
                else if (arena.prey.getPosition().y >= HEIGHT)
                    arena.prey.setPosition(arena.prey.getPosition().x, HEIGHT - 1);

                arena.predator.moveTowardPrey(arena.prey.getPosition());

                if (arena.checkCollision()) {
                    std::cout << "GAME OVER. YOU LOSE" << std::endl;
                    Sleep(5000);
                    break;
                }

                --limit;

                if (limit == 0) {
                    std::cout << "GAME OVER. YOU WIN" << std::endl;
                    Sleep(5000);
                }
            }
        }
        else {
            validUserInput = false;
        }
    } while (!validUserInput);
}
