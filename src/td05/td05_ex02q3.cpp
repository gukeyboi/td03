#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_set>

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

    Position operator+(Direction const& a) const {
        Position result = *this;
        result += a;
        return result;
    }
};


namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>{}(pos.x) * 31 + std::hash<int>{}(pos.y);;
        }
    };
}

struct WalkResult {
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
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

WalkResult simulate_guard(Input_Structure mapimap) {
    WalkResult walk_result;

    walk_result.steps_taken = 0;
    walk_result.visited_positions.insert(mapimap.gardePos);

    while(true) {
        Position next_position = mapimap.gardePos + mapimap.gardeDir;

        if(next_position.x >= mapimap.mapWidth || next_position.y >= mapimap.mapHeight || next_position.x < 0 || next_position.y < 0) {
            break;
        }

        if(isObstacle(mapimap.obstacles, next_position)) {
            mapimap.gardeDir = turn_right(mapimap.gardeDir);
        } else {
            mapimap.gardePos = next_position;
            walk_result.visited_positions.insert(next_position);
            walk_result.steps_taken++;
        }
    }
    walk_result.final_position = {mapimap.gardePos.x, mapimap.gardePos.y};
    return walk_result;
}


int main() {

    std::ifstream file("../src/td05/map.txt");

    if (!file) {
        std::cerr << "Erreur fichier" << std::endl;
        return 1;
    }

    Input_Structure map = read_input(file);
    WalkResult result = simulate_guard(map);

    std::cout << result.visited_positions.size() << std::endl;

    printMap(map);

    //Position endroit {3, 6};
    //Position endroit2 {3, 6};
    //endroit2 += endroit;
    //std::cout << endroit2 << std::endl;
}
