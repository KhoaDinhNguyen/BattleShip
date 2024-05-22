#include <iostream>
#include "Ship.h"

// Constructor
Ship::Ship(){
    this->name = "";
    this->cnt = 0;
}

Ship::Ship(std::string name, int cnt){
    this->name = name;
    this->cnt = cnt;
}

std::string Ship::getName(){
    return this->name;
}

void Ship::setName(std::string name){
    this->name = name;
}

int Ship::getCnt(){
    return this->cnt;
}

void Ship::setCnt(int cnt){
    this->cnt = cnt;
}

void Ship::setCoor(std::vector<std::array<int, 2>> coorList)
{
    this->coor = coorList;
}

std::vector<std::array<int, 2>> Ship::getCoor()
{
    return this->coor;
}

void Ship::rotateShip(int n)
{
    size_t ship_size = this->coor.size();
    //std::cout << ship_size << std::endl;
    for(size_t i = 0; i < ship_size; i++){
        for(int j = 0; j < n; j++){
            int temp = this->coor[i][0]; // temporarily save x
            this->coor[i][0] = coor[i][1];
            this->coor[i][1] = temp * (-1);
        }
    }
}

// Destructor
Ship::~Ship(){
}