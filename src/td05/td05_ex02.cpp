#include <vector>
#include <algorithm>
#include <iostream>

size_t folding_string_hash(std::string const& s, size_t max) {
    size_t total = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        total += int(s[i]);
        total = total % max;
    }
    return total;
    
}

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t total = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        total += (int(s[i]) * (i + 1));
        total = total % max;
    }
    return total;
    
}



enum Direction {
    Haut,
    Bas,
    Gauche,
    Droite
};

struct Position {
    int x;
    int y;

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}

    Position& operator+=(Position const& a) {
        x += a.x;
        y += a.y;
        return *this;
    }
    
    Position& operator+=(Direction const& a) {
        switch (a)
    {
    case Direction::Haut:
        y += -1;
        break;

    case Direction::Droite:
        x += 1;
        break;
        
    case Direction::Bas:
        y += 1;
        break;

    case Direction::Gauche:
        x += -1;
        break;
    }
    return *this;
    };
};



bool operator==(Position const& a, Position const& b) {
    return a.x == b.x && a.y == b.y;
}

Direction turn_right(Direction const& a) {
    switch (a)
    {
    case Direction::Haut:
        return Direction::Droite;
        break;

    case Direction::Droite:
        return Direction::Bas;
        break;
        
    case Direction::Bas:
        return Direction::Gauche;
        break;

    case Direction::Gauche:
        return Direction::Haut;
        break;
    }

    }

std::ostream& operator<<(std::ostream& os, Position const& c) {
    return os << "coordonnée x =" << c.x << "coordonnée y =" << c.y;
}


int main() {
    Position endroit {3, 6};
    Position endroit2 {3, 6};
    endroit2 += endroit;
    std::cout << endroit2 << std::endl;
}
