#include <iostream>
#include <iomanip>
#include <map>
#include <array>
#include <random>
#include "Ship.h"
#include "Grid.h"

class Map
{
private:    
    Ship* mothership;
    Ship* battleship;
    Ship* destroyer;
    Ship* stealth;
    Ship* patrol;
    Grid** gridMap;
    bool clearShip;
    // Map dimensions
    int xDim; // number of columns
    int yDim; // number of rows
    int shipCnt;
    int shotToClear; // Number of shot required to clear the map
    std::vector<int> shipCnt2;
    std::default_random_engine generator; // RNG
public:
    // Constructor
    Map(std::vector<int> , int , int );
    // Member function
    int getShipCnt(); // Number of active ships
    int getShotCnt();
    int updateShipCnt(); // Change the number of ships
    bool getMapStatus(); 
    std::string getGridInfo(int, int);
    void showMap();
    int gridShot(int , int );
    void placeShip(Ship&); // Place ship on the grid map
    bool checkBoundary(std::array<int,2> , std::vector<std::array<int,2>>);
    void adjustCoor(std::array<int,2>, std::array<int,2>&);
    int findShipCoor(Ship, std::array<int,2> ); // Find the ship based on the coordinate in Ship array
    // Destructor
    ~Map();
};