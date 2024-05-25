#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <cmath>
#include <set>
#include <cstdlib>
#include <ctime>

// Vector2 template struct
template <typename T>
struct Vector2 {
    T x, y;

    Vector2(T x = 0, T y = 0) : x(x), y(y) {}
};

// DOP Version
namespace DOP {
    struct Node {
        int x, y;
        float g, h;
        int parentX, parentY;

        Node(int x = 0, int y = 0, float g = 0, float h = 0, int parentX = -1, int parentY = -1)
            : x(x), y(y), g(g), h(h), parentX(parentX), parentY(parentY) {}
    };

    struct CompareNode {
        bool operator()(const Node& a, const Node& b) const {
            return (a.g + a.h) > (b.g + b.h);
        }
    };

    float heuristic(Vector2<int> a, Vector2<int> b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    void AStar(std::vector<std::vector<int>>& grid, Vector2<int> start, Vector2<int> goal) {
        std::priority_queue<Node, std::vector<Node>, CompareNode> openSet;
        std::unordered_map<int, Node> closedSet;
        std::set<std::pair<int, int>> openSetLookup;  // To check if a node is already in the open set

        openSet.emplace(start.x, start.y, 0, heuristic(start, goal));
        openSetLookup.insert({start.x, start.y});

        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();
            openSetLookup.erase({current.x, current.y});

            if (current.x == goal.x && current.y == goal.y) {
                std::cout << "Path found in DOP A*" << std::endl;
                return;
            }

            int currentKey = current.x * grid[0].size() + current.y;
            closedSet[currentKey] = current;

            std::vector<Vector2<int>> neighbors = {
                {current.x - 1, current.y}, {current.x + 1, current.y},
                {current.x, current.y - 1}, {current.x, current.y + 1}
            };

            for (const auto& neighbor : neighbors) {
                if (neighbor.x < 0 || neighbor.x >= grid.size() || neighbor.y < 0 || neighbor.y >= grid[0].size() || grid[neighbor.x][neighbor.y] == 1) {
                    continue;
                }

                Node neighborNode(neighbor.x, neighbor.y, current.g + 1, heuristic(neighbor, goal), current.x, current.y);
                int neighborKey = neighbor.x * grid[0].size() + neighbor.y;

                if (closedSet.find(neighborKey) != closedSet.end() || openSetLookup.find({neighbor.x, neighbor.y}) != openSetLookup.end()) {
                    continue;
                }

                openSet.push(neighborNode);
                openSetLookup.insert({neighbor.x, neighbor.y});
            }
        }

        std::cout << "Path not found in DOP A*" << std::endl;
    }
}

// OOP Version
namespace OOP {
    class Node {
    public:
        int x, y;
        float g, h;
        Node* parent;

        Node(int x = 0, int y = 0, float g = 0, float h = 0, Node* parent = nullptr)
            : x(x), y(y), g(g), h(h), parent(parent) {}
    };

    class CompareNode {
    public:
        bool operator()(const Node* a, const Node* b) const {
            return (a->g + a->h) > (b->g + b->h);
        }
    };

    float heuristic(const Node* a, const Node* b) {
        return std::sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
    }

    void AStar(std::vector<std::vector<int>>& grid, Vector2<int> start, Vector2<int> goal) {
        std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
        std::unordered_map<int, Node*> closedSet;
        std::set<std::pair<int, int>> openSetLookup;  // To check if a node is already in the open set

        Node* startNode = new Node(start.x, start.y, 0, heuristic(new Node(start.x, start.y), new Node(goal.x, goal.y)));
        openSet.push(startNode);
        openSetLookup.insert({start.x, start.y});

        while (!openSet.empty()) {
            Node* current = openSet.top();
            openSet.pop();
            openSetLookup.erase({current->x, current->y});

            if (current->x == goal.x && current->y == goal.y) {
                std::cout << "Path found in OOP A*" << std::endl;
                // Free all nodes in closedSet and openSet
                for (auto& pair : closedSet) {
                    delete pair.second;
                }
                while (!openSet.empty()) {
                    delete openSet.top();
                    openSet.pop();
                }
                delete current;
                return;
            }

            int currentKey = current->x * grid[0].size() + current->y;
            closedSet[currentKey] = current;

            std::vector<Vector2<int>> neighbors = {
                {current->x - 1, current->y}, {current->x + 1, current->y},
                {current->x, current->y - 1}, {current->x, current->y + 1}
            };

            for (const auto& neighbor : neighbors) {
                if (neighbor.x < 0 || neighbor.x >= grid.size() || neighbor.y < 0 || neighbor.y >= grid[0].size() || grid[neighbor.x][neighbor.y] == 1) {
                    continue;
                }

                Node* neighborNode = new Node(neighbor.x, neighbor.y, current->g + 1, heuristic(new Node(neighbor.x, neighbor.y), new Node(goal.x, goal.y)), current);
                int neighborKey = neighbor.x * grid[0].size() + neighbor.y;

                if (closedSet.find(neighborKey) != closedSet.end() || openSetLookup.find({neighbor.x, neighbor.y}) != openSetLookup.end()) {
                    delete neighborNode;
                    continue;
                }

                openSet.push(neighborNode);
                openSetLookup.insert({neighbor.x, neighbor.y});
            }
        }

        std::cout << "Path not found in OOP A*" << std::endl;
        // Free all nodes in closedSet
        for (auto& pair : closedSet) {
            delete pair.second;
        }
        while (!openSet.empty()) {
            delete openSet.top();
            openSet.pop();
        }
    }
}

// Function to generate a grid with random walls
std::vector<std::vector<int>> generateGrid(int rows, int cols, float wallProbability) {
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));
    std::srand(std::time(nullptr));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (std::rand() / static_cast<float>(RAND_MAX) < wallProbability) {
                grid[i][j] = 1;
            }
        }
    }

    // Ensure start and goal are not walls
    grid[0][0] = 0;
    grid[rows - 1][cols - 1] = 0;

    return grid;
}

int main(int argc, char* argv[]) {
    int rows = argc > 1 ? atoi(argv[1]) : 20;
    int cols = rows;
    float wallProbability = 0.2f;

    std::vector<std::vector<int>> grid = generateGrid(rows, cols, wallProbability);

    Vector2<int> start(0, 0);
    Vector2<int> goal(rows - 1, cols - 1);

    // DOP A* Performance
    auto start_time = std::chrono::high_resolution_clock::now();
    DOP::AStar(grid, start, goal);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dop_duration = end_time - start_time;
    std::cout << "DOP A* Duration: " << dop_duration.count() << " seconds\n";

    // OOP A* Performance
    start_time = std::chrono::high_resolution_clock::now();
    OOP::AStar(grid, start, goal);
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> oop_duration = end_time - start_time;
    std::cout << "OOP A* Duration: " << oop_duration.count() << " seconds\n";

    return 0;
}
