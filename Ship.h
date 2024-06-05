#include <iostream>
#include <array>
#include <vector>

// Ship class (abstract class)
class Ship
{
private:
    std::string name; // Ship name
    int cnt; // Number of tile
    std::vector<std::array<int,2>> coor;
public:
    // Constructor
    Ship();
    Ship(std::string , int );
    // Member functions
    // Ship name
    std::string getName();
    void setName(std::string );
    // Ship Cnt (HP)
    int getCnt();
    void setCnt(int );
    // Ship coordinate
    void setCoor(std::vector<std::array<int,2>>);
    std::vector<std::array<int,2>> getCoor();
    void rotateShip(int ); // Rotate ship n times
    void getHit(int );
    // Destructor
    ~Ship();
};