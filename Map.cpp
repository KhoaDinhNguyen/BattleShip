#include "Map.h"

// Constructor
Map::Map(int n1, int n2, int n3, int xDim, int yDim){
    
    // Initialize ships
    mothership = new Ship[n1];
    battleship = new Ship[n2];
    destroyer = new Ship[n3];
    // Initialize ship arrays
    for(int i = 0 ; i < n1 ; ++i){
        mothership[i].setName("Mothership");
        mothership[i].setCnt(5);
        // Set default coordination
        mothership[i].setCoor({{0,0},{1,1},{-1,-1},{1,-1},{-1,-1}});
    }
    for(int i = 0 ; i < n2 ; ++i){
        battleship[i].setName("Battleship");
        battleship[i].setCnt(4);
        battleship[i].setCoor({{0,0},{0,1},{1,0},{1,1}});
    }
    for(int i = 0 ; i < n3 ; ++i){
        destroyer[i].setName("Destroyer");
        destroyer[i].setCnt(3);
    }
    shipCnt = n1 + n2 + n3;
    if(!shipCnt){        
        clearShip = false;
    }
    else{
        clearShip = true;
    }
    // Initialize the map
    this->xDim = xDim;
    this->yDim = yDim;
    gridMap = new Grid[xDim * yDim];
}

// Member function
int Map::getShipCnt(){
    return shipCnt;
}

int Map::updateShipCnt(){
    return shipCnt--; // Consider loss of ship only
}

std::string Map::getGridInfo(int x, int y)
{
    return this->gridMap[x * 12 + y].getGridChar();
}

void Map::showMap()
{
    for(int i = 0; i < yDim; i++){
        for(int j = 0; j < xDim; j++)
        if(gridMap[i * yDim + j].getGridRevealStatus()){
            std::cout << gridMap[i * yDim + j].getGridChar();
        }
        else{
            std::cout <<"~";
        }
        std::cout << std::endl;
    }
}

void Map::gridShot(int x, int y)
{
    int shotLocation = x * this->xDim + y;
    this->gridMap[shotLocation].setGridRevealStatus(true);
    std::cout << gridMap[shotLocation].getGridRevealStatus() << std::endl;
    if(gridMap[shotLocation].getGridChar() == "~"){
        std::cout << "Miss shot!!!" << std::endl;
        gridMap[shotLocation].setGridChar("o");
    }
}

bool Map::getMapStatus()
{
    return clearShip;
}

// Destructor
Map::~Map(){
    delete[] mothership;
    delete[] battleship;
    delete[] destroyer;
    delete[] gridMap;
};