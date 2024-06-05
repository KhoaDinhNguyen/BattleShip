#include "Map.h"

// Constructor
Map::Map(std::vector<int> n, int xDim, int yDim ){
    
    // Initialize ships
    // n - array of number of ship for {mothership, battleship, destroyer, stealth ship, patrol ship}
    mothership = new Ship[n[0]];
    battleship = new Ship[n[1]];
    destroyer = new Ship[n[2]];
    stealth = new Ship[n[3]];
    patrol = new Ship[n[4]];
    shipCnt2 = n;
    // Initialize ship arrays
    for(int i = 0 ; i < n[0] ; ++i){
        mothership[i].setName("M");
        mothership[i].setCnt(5);
        // Set default coordination
        mothership[i].setCoor({{0,0},{1,1},{1,-1},{-1,1},{-1,-1}});
    }
    for(int i = 0 ; i < n[1] ; ++i){
        battleship[i].setName("B");
        battleship[i].setCnt(4);        
        // Set default coordination
        battleship[i].setCoor({{0,0},{0,1},{1,0},{1,1}});
    }
    for(int i = 0 ; i < n[2] ; ++i){
        destroyer[i].setName("D");
        destroyer[i].setCnt(3);
        destroyer[i].setCoor({{0,0},{1,1},{1,-1}});
    }
    for(int i = 0 ; i < n[3] ; ++i){
        stealth[i].setName("S");
        stealth[i].setCnt(2);
        stealth[i].setCoor({{0,0},{0,1}});
    }
    for(int i = 0 ; i < n[4] ; ++i){
        patrol[i].setName("P");
        patrol[i].setCnt(3);
        patrol[i].setCoor({{0,0},{0,1},{0,-1}});
    }
    shipCnt = n[0] + n[1] + n[2] + n[3] + n[4];
    if(!shipCnt){        
        clearShip = false;
    }
    else{
        clearShip = true;
    }
    // Initialize the map
    this->xDim = xDim;
    this->yDim = yDim;
    //gridMap = new Grid[xDim * yDim];
    // Matrix form
    gridMap = new Grid*[yDim];
    for(int i = 0 ; i < yDim; ++i){
        gridMap[i] = new Grid[xDim];
    }

    this->shotToClear = 0;
    // Place ship
    for (int i = 0; i < n[0]; i++)
    {
        placeShip(mothership[i]);
        shotToClear += mothership[i].getCnt();
    }
    for (int i = 0; i < n[1]; i++)
    {
        placeShip(battleship[i]);
        shotToClear += battleship[i].getCnt();
    }
    for (int i = 0; i < n[2]; i++)
    {
        placeShip(destroyer[i]);
        shotToClear += destroyer[i].getCnt();
    }
    for (int i = 0; i < n[3]; i++)
    {
        placeShip(stealth[i]);
        shotToClear += stealth[i].getCnt();
    }
    for (int i = 0; i < n[4]; i++)
    {
        placeShip(patrol[i]);
        shotToClear += patrol[i].getCnt();
    }
}

// Get the number of active ships on the map
int Map::getShipCnt(){
    return shipCnt;
}

int Map::getShotCnt(){
    return shotToClear;
}

int Map::updateShipCnt(){
    return shipCnt--; // Consider loss of ship only
}

void Map::showMap()
{
    // Header
    std::cout << std::setw(2) << "";
    for(int i = 0; i < xDim; ++i){
        std::cout << std::setw(3) << (char)(65 + i);
    }    
    std::cout << std::endl;
    // Header separator
    std::cout << std::setw(3) << "+";
    for(int i = 0; i < xDim - 1; ++i){
        std::cout << "---";
    }
    std::cout << "---+" << std::endl;
    // Grid printer
    for(int j = 0; j < yDim; j++){
        std::cout << std::setw(2) << std::right << j + 1 << "|" ;
        for(int i = 0; i < xDim; i++){
            if(gridMap[j][i].getGridRevealStatus()){
                std::cout << " " + gridMap[j][i].getGridChar() + " ";
            }
            else{
                std::cout << " ~ ";
            }
        }
        std::cout << "|" << std::endl;
    }
    // Footer separator
    std::cout << std::setw(3) << "+";
    for(int i = 0; i < xDim - 1; ++i){
        std::cout << "---";
    }
    std::cout << "---+" << std::endl;
}

int Map::gridShot(int x, int y)
{
    this->gridMap[y][x].setGridRevealStatus(true);
    // std::cout << gridMap[y][x].getGridRevealStatus() << std::endl;
    const std::string currentGridChar = gridMap[y][x].getGridChar();
    if(currentGridChar == "~"){
        std::cout << "Miss shot!!!" << std::endl;
        gridMap[y][x].setGridChar("o");
        return 0;
    }
    else{
        if(currentGridChar == "x" || currentGridChar == "o"){
            // Attempt to shot a location multiple times
            std::cout << "The location has already been bombarded!!!" << std::endl;            
            // Count as miss shot
            return 0;
        }
        else{
            int shipIdx {};
            int coorIdx {};
            std::string shipName{};
            bool shipDestroyed {false}; // Signal where the ship is destroyed
            if(currentGridChar == "M")
            {
                for(int i = 0; i < shipCnt2[0]; i++){
                    // std::cout << "Address of Mothership i: " << &mothership[i] << std::endl;
                    coorIdx = findShipCoor(mothership[i], {x,y});
                    //std::cout << "Coor Index: " << coorIdx << std::endl;
                    if(coorIdx != -1){
                        mothership[i].getHit(coorIdx);
                        //std::cout << "HP: " << mothership[i].getCnt() << std::endl;
                        if(mothership[i].getCnt() == 0){
                            std::cout << "DIRECT HIT! \nCongratulation! The enemy mothership has been destroyed!!!" << std::endl;
                            shipDestroyed = true;
                            this->shipCnt--;
                        }
                        shipIdx = i;
                        break;
                    }
                }
                shipName = "mothership";
            }
            else if(currentGridChar == "B"){
                for(int i = 0; i < shipCnt2[0]; i++){
                    coorIdx = findShipCoor(battleship[i], {x,y});
                    if(coorIdx != -1){
                        battleship[i].getHit(coorIdx);
                        if(battleship[i].getCnt() == 0){
                            std::cout << "DIRECT HIT! \nCongratulation! The enemy battleship has been destroyed!!!" << std::endl;
                            shipDestroyed = true;
                            this->shipCnt--;
                        }
                        shipIdx = i;
                        break;
                    }
                }
                shipName = "battleship";
            }
            else if(currentGridChar == "D"){
                for(int i = 0; i < shipCnt2[0]; i++){
                    coorIdx = findShipCoor(destroyer[i], {x,y});
                    if(coorIdx != -1){
                        destroyer[i].getHit(coorIdx);
                        if(destroyer[i].getCnt() == 0){
                            std::cout << "DIRECT HIT! \nCongratulation! The enemy destroyer has been destroyed!!!" << std::endl;
                            shipDestroyed = true;
                            this->shipCnt--;
                        }
                        shipIdx = i;
                        break;
                    }
                }
                shipName = "destroyer";
            }
            else if(currentGridChar == "S"){
                for(int i = 0; i < shipCnt2[0]; i++){
                    coorIdx = findShipCoor(stealth[i], {x,y});
                    if(coorIdx != -1){
                        stealth[i].getHit(coorIdx);
                        if(stealth[i].getCnt() == 0){
                            std::cout << "DIRECT HIT! \nCongratulation! The enemy stealth ship has been destroyed!!!" << std::endl;
                            shipDestroyed = true;
                            this->shipCnt--;
                        }
                        shipIdx = i;
                        break;
                    }
                }
                shipName = "stealth ship";
            }
            else if(currentGridChar == "P"){
                for(int i = 0; i < shipCnt2[0]; i++){
                    coorIdx = findShipCoor(patrol[i], {x,y});
                    if(coorIdx != -1){
                        patrol[i].getHit(coorIdx);
                        if(patrol[i].getCnt() == 0){
                            std::cout << "DIRECT HIT! \nCongratulation! The enemy patrol ship has been destroyed!!!" << std::endl;
                            shipDestroyed = true;
                            this->shipCnt--;
                        }
                        shipIdx = i;
                        break;
                    }
                }
                shipName = "patrol ship";
            }
            else{
                shipName = "random";
            }                
            //std::cout << "The shot is landed on enemy vessel!!!" << std::endl; // Test hit
            if(!shipDestroyed){
                std::cout << "DIRECT HIT! The shot has landed on enemy " << shipName << " " << shipIdx + 1 << "." << std::endl;
            }
            gridMap[y][x].setGridChar("x");
            return 1;
        }
    }
}

bool Map::getMapStatus()
{
    return clearShip;
}

void Map::placeShip(Ship& ship){
    // RNG
    std::random_device rd;
    std::mt19937_64 mt_engine{rd()}; // Coordinate generator
    std::mt19937_64 mt_engine2{rd()}; // Ship rotation generator
    std::uniform_int_distribution<int> distribution_x(0,this->xDim);
    std::uniform_int_distribution<int> distribution_y(0,this->yDim);
    std::uniform_int_distribution<int> distribution_rot(0,3);

    // Place ship
    // Get information of the ship
    std::string shipName = ship.getName();
    bool shipPlaced {false}; // Check whether the ship is deployed on the map
    bool validPlacement {false}; // Whether the deployment zone is a valie one
    std::array<int,2> center{};
    int rotateTime = distribution_rot(mt_engine2); // Generate the number of time the ship is rotated
    // std::cout << "Rotation time: " << rotateTime << std::endl;
    ship.rotateShip(rotateTime); // Rotate the ship    
    std::vector<std::array<int,2>> newCoor = ship.getCoor();
    
    // for(size_t i = 0; i < newCoor.size(); i++){
    //     std::cout << "{" << newCoor[i][0] << "," << newCoor[i][1] << "}";
    // }
    // std::cout << std::endl;

    // Try to find a proper deployment zone
    do{        
        // Generate the coordinte
        int c_cor1 = distribution_x(mt_engine);
        int c_cor2 = distribution_y(mt_engine);
        center[0] = c_cor1;
        center[1] = c_cor2;  
        size_t coorSize = newCoor.size(); // Size of the ship coordinate array
        validPlacement = checkBoundary(center, newCoor);
        // Alternate the coordinate according to a center of a ship
    }while(!validPlacement);

    if(validPlacement){ // Fail-safe
        for(int i = 0 ; i < newCoor.size(); ++i){
            adjustCoor(center, newCoor[i]);
            //std::cout << "x = " << newCoor[i][0] << "  y = " << newCoor[i][1] << std::endl;
            gridMap[newCoor[i][1]][newCoor[i][0]].setGridChar(shipName);
        }
        // for(int i = 0 ; i < newCoor.size(); ++i){
        //     std::cout << "x = " << newCoor[i][0] << "  y = " << newCoor[i][1] << std::endl;
        // }
        // Set a new coordinate for the ship
        //std::cout << &newCoor << std::endl;
        ship.setCoor(newCoor);
        //std::vector<std::array<int,2>> testCoor = ship.getCoor();
        //std::cout << "Address when place ship: " << &ship << std::endl;
    }

    // Set occupation for grid
    int minX = newCoor[0][0];
    int minY = newCoor[0][1];
    
    int maxX = newCoor[0][0];
    int maxY = newCoor[0][1];
    for(int i = 1; i < newCoor.size(); i++){
        // std::cout << &newCoor[i] << std::endl;
        int x = newCoor[i][0];
        int y = newCoor[i][1];
        // Find min and max on x-dir
        if(x < minX){
            minX = x;
        }
        else if(x > maxX){
            maxX = x;
        }
        // Find min and max on y-dir
        if(y < minY){
            minY = y;
        }
        else if(y > maxY){
            maxY = y;
        }
        // std::cout << "Min X: " << minX << "\tMax X: " << maxX << std::endl;
        // std::cout << "Min Y: " << minY << "\tMax Y: " << maxY << std::endl;
    }
    for(int i = minX; i <= maxX; i++){
        for(int j = minY; j <= maxY; j++){
            gridMap[j][i].setGridOccupy(true);
        }
    }
}

// Check if the ship still remain in the gird
bool Map::checkBoundary(std::array<int,2> centerGrid, std::vector<std::array<int,2>> shipCoors){    
    for(std::array<int,2> coor:shipCoors){        
        int xCoor = centerGrid[0] + coor[0];
        int yCoor = centerGrid[1] + coor[1];
        // INVALID CONDITIONS
        // Check with map boundary
        // std::cout << xCoor << " " << yCoor << std::endl;
        if(xCoor < 0 || xCoor >= xDim || yCoor < 0 || yCoor >= yDim){
            return false;
        }
        // Check with other ships' boundaries
        if(gridMap[yCoor][xCoor].getGridOccupy()){
            return false;
        }
    }

    return true;
}

// Adjust the ship location based on randomizing the ship center
void Map::adjustCoor(std::array<int,2> centerGrid, std::array<int,2> &shipCoor){
    shipCoor[0] += centerGrid[0];
    shipCoor[1] += centerGrid[1];
}

int Map::findShipCoor(Ship ship, std::array<int, 2> coor){
    std::vector<std::array<int, 2>> shipCoor = ship.getCoor();
    // std::cout << "{" << coor[0] << "," << coor[1] << "}" << std::endl;    
    int size = shipCoor.size();
    // for(int i = 0; i < size; i++){
    //     std::cout << "{" << shipCoor[i][0] << "," << shipCoor[i][1] << "}";
    // }
    // std::cout << std::endl;
    for(int i = 0; i < size; i++){
        if(shipCoor[i][0] == coor[0] && shipCoor[i][1] == coor[1]){
            return i;
        }
    }
    return -1;
}

// Destructor
Map::~Map(){
    delete[] mothership;

    
    delete[] battleship;
    delete[] destroyer;
  
    for(int i = 0 ; i < yDim; ++i){
        delete[] gridMap[i];
    }
    delete[] gridMap;
};