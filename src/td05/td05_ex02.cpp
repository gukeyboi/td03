#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

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
Position(size_t x, size_t y) : x(x), y(y) {}

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

struct Input_Structure {
    Position gardePos;
    Direction gardeDir;
    std::vector<Position> obstacles;
    size_t mapWidth;
    size_t mapHeight;
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

Input_Structure read_input(std::istream& input_stream) {
   
    Input_Structure map;
    
     map.mapHeight = 0;

    size_t rowIndex = 0;

    for (std::string line{}; std::getline(input_stream, line, '\n') and line != "";) {
        map.mapWidth = line.size();
        for (size_t i = 0; i < line.size(); i++)
        {   
            switch (line[i])
            {
            case '#':
                map.obstacles.push_back(Position{i, rowIndex});
                break;

            case '^':
                map.gardePos = Position{i, rowIndex};
                map.gardeDir = Direction::Haut;
            break;

            case '>':
                map.gardePos = Position{i, rowIndex};
                map.gardeDir = Direction::Droite;
            break;

            case 'v':
                map.gardePos = Position{i, rowIndex};
                map.gardeDir = Direction::Bas;
            break;

            case '<':
                map.gardePos = Position{i, rowIndex};
                map.gardeDir = Direction::Gauche;
            break;
            
            default:
                continue;;
            }
            
        }
        rowIndex++;
        
    }
    map.mapHeight = rowIndex;
    return map;
}

bool isObstacle(const std::vector<Position>& vecteur, const Position& cible) {

    auto it = std::find(vecteur.begin(), vecteur.end(), cible);
    
    return it != vecteur.end();
}

void printMap(Input_Structure const& mapimap) {
    for (size_t i = 0; i < mapimap.mapHeight; i++)
    {
        for (size_t j = 0; j < mapimap.mapWidth; j++)
        {
            if (isObstacle(mapimap.obstacles, Position {j, i})) {
                std::cout << "#";
            }

            else if (Position{j, i} == mapimap.gardePos) {
                switch (mapimap.gardeDir)
                {
                case Direction::Haut:
                    std::cout << "^";
                    break;

                case Direction::Droite:
                    std::cout << ">";
                    break;    

                case Direction::Bas:
                    std::cout << "v";
                    break;
                    
                case Direction::Gauche:
                    std::cout << "<";
                    break;   
                
                default:
                    break;
                }
            }

            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
        
    }
    
}

int main() {

    std::ifstream file("../src/td05/guard_patrol.txt");

    if (!file) {
        std::cerr << "Erreur fichier" << std::endl;
        return 1;
    }

    Input_Structure map = read_input(file);

    printMap(map);

    //Position endroit {3, 6};
    //Position endroit2 {3, 6};
    //endroit2 += endroit;
    //std::cout << endroit2 << std::endl;
}
