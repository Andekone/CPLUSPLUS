#include <iostream>
#include <cstdlib>  // для std::rand и std::srand
#include <ctime>    // для std::time

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

class Entity {
public:
    Point2D position;

    Entity(int x = 0, int y = 0) : position(x, y) {}

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

class Player : public Entity {
public:
    Player(int x = 0, int y = 0) : Entity(x, y) {}

    void move(char direction) {
        switch (direction) {
        case 'w':
            position.move(0, -1);
            break;
        case 's':
            position.move(0, 1);
            break;
        case 'a':
            position.move(-1, 0);
            break;
        case 'd':
            position.move(1, 0);
            break;
        }
    }
};

class Enemy : public Entity {
public:
    Enemy(int x = 0, int y = 0) : Entity(x, y) {}

    void moveToward(const Point2D& target) {
        int step = 1;
        if (target.x < position.x)
            position.x -= step;
        else if (target.x > position.x)
            position.x += step;

        if (target.y < position.y)
            position.y -= step;
        else if (target.y > position.y)
            position.y += step;
    }
};

class Arena {
public:
    const int width;
    const int height;
    Entity player;
    Entity enemy;

    Arena(int width, int height)
        : width(width), height(height), player(width / 2, height / 2), enemy(rand() % width, rand() % height) {}

    void display() const {
        system("cls");
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (x == player.getPosition().x && y == player.getPosition().y)
                    cout << "@ ";
                else if (x == enemy.getPosition().x && y == enemy.getPosition().y)
                    cout << "$ ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
        cout << "Player - @    Enemy - $" << endl;
    }

    bool checkCollision() const {
        return player.getPosition().x == enemy.getPosition().x && player.getPosition().y == enemy.getPosition().y;
    }
};

int main() {
    int WIDTH = 30;
    int HEIGHT = 15;

    srand(time(nullptr));
    Arena arena(WIDTH, HEIGHT);
    char direction;

    do {
        arena.display();

        if (arena.checkCollision()) {
            cout << "GAME OVER. YOU LOSE" << endl;
            break;
        }

        cout << "Direction (w/a/s/d): ";
        cin >> direction;

        switch (direction) {
        case 'w':
        case 'a':
        case 's':
        case 'd':
            arena.player.move(direction);
            break;
        default:
            cout << "Invalid input!" << endl;
        }

        arena.enemy.moveToward(arena.player.getPosition());

    } while (true);

    return 0;
}
