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
    // int n = coorList.size();
    // this->coor.resize(n);
    // for(int i = 0 ; i < n; ++i){
    //     this->coor[i][0] = coorList[i][0];
    //     this->coor[i][1] = coorList[i][1]; 
    // }
    this->coor = coorList;
    // for(int i = 0 ; i < this->coor.size(); ++i){
    //     std::cout << this->coor[i][0] << " ";
    //     //this->coor[i][1] = coorList[i][1]; 
    // }
    // std::cout << std :: endl;
}

std::vector<std::array<int, 2>> Ship::getCoor()
{
    // for(int i = 0 ; i < this->coor.size(); ++i){
    //     std::cout << this->coor[i][0] << " ";
    //     //this->coor[i][1] = coorList[i][1]; 
    // }
    // std::cout << std::endl;
    return this->coor;
}

void Ship::rotateShip(int n)
{
    size_t ship_size = this->coor.size();
    for(size_t i = 0; i < ship_size; i++){
        for(int j = 1; j <= n; j++){
            int temp = this->coor[i][0]; // temporarily save x
            this->coor[i][0] = coor[i][1];
            this->coor[i][1] = temp * (-1);
        }
    }
}

void Ship::getHit(int n){
    // Check whether the position is correct
    this->coor.erase(this->coor.begin() + n);
    this->cnt--;
}
// Destructor
Ship::~Ship(){
}