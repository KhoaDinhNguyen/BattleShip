#include "Grid.h"

Grid::Grid()
{
    this->isOccupied = false;
    this->isReveal = true;
    this->gridChar = "~";
}

void Grid::setGridChar(std::string letter)
{
    this->gridChar = letter;
}

std::string Grid::getGridChar()
{
    return this->gridChar;
}

void Grid::setGridOccupy(bool status)
{
    this->isOccupied = status;
}

bool Grid::getGridOccupy()
{
    return this->isOccupied;
}

void Grid::setGridRevealStatus(bool status)
{
    this->isReveal = status;
}

bool Grid::getGridRevealStatus()
{
    return this->isReveal;
}

Grid::~Grid(){

}