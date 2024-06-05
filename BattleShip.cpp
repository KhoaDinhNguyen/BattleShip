#include <iostream>
#include <vector>
#include <cmath>
#include "Game.h"

int main(){
    // Initialize map
    // Map map({1,1,1,1,1},12,10);
    // if(map.getMapStatus())
    //     std::cout << map.getShipCnt() << std::endl;
    // else
    //     std::cout << "Game Over!" << std::endl; 
    // std::vector coor = map.mothership->getCoor();
    // std::cout << "Before rotation: ";
    // std::cout << coor[2][0] << "  " <<coor[2][1] << std::endl;
    // map.mothership->rotateShip(4);
    // std::cout << "After rotation: ";
    // coor = map.mothership->getCoor();
    // std::cout << coor[2][0] << "  " <<coor[2][1] << std::endl;
    // map.showMap();
    
    // map.gridShot(0,1);
    // map.showMap();
    // map.gridShot(2,0);
    // map.showMap();

    // std::vector<std::array<int,2>> shipCoor = map.mothership[0].getCoor();
    // for(int i = 0; i < shipCoor.size(); i++){
    //     std::cout << "x(" << i << ") = " << shipCoor.at(i).at(0) << std::endl;
    //     std::cout << "y(" << i << ") = " << shipCoor.at(i).at(1) << std::endl;   
    // }

    //std::cout << M_PI_2 << std::endl;

    Game game;

    return 0;
}