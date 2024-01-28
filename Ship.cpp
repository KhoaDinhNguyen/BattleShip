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

// Destructor
Ship::~Ship(){
}