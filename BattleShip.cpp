#include <iostream>
#include <vector>
#include <cmath>
#include "Map.h"

int main(){
    Map map(1,0,0,12,10);
    if(map.getMapStatus())
        std::cout << map.getShipCnt() << std::endl;
    else
        std::cout << "Game Over!" << std::endl; 
    
    std::vector coor = map.mothership->getCoor();
    std::cout << coor[2][1] << std::endl;

    map.showMap();
    map.gridShot(0,1);
    map.showMap();
    std::cout << M_PI_2 << std::endl;
    return 0;
}