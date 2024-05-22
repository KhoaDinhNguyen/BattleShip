#include <iostream>
#include <array>
#include <random>
#include "Ship.h"
#include "Grid.h"

class Map
{
private:
    
    Ship* battleship;
    Ship* destroyer;
    Grid* gridMap;
    // Map dimensions
    int xDim;
    int yDim;
    int shipCnt;
    bool clearShip;
    std::default_random_engine generator; // RNG
public:
    Ship* mothership;
    // Constructor
    Map(int , int , int , int , int );
    // Member function
    int getShipCnt();
    int updateShipCnt();
    bool getMapStatus();
    std::string getGridInfo(int, int);
    void showMap();
    void gridShot(int , int );
    // Destructor
    ~Map();
};