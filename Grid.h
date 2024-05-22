#include <iostream>
class Grid{
private:
    bool isOccupied; // Has ship of not?
    bool isReveal; // Whether player can see what the true value of the grid
    std::string gridChar;
public:
    // Constructor
    Grid();
    // Member function
    // Grid char
    void setGridChar(std::string );
    std::string getGridChar();
    // Grid occupation
    void setGridOccupy(bool );
    bool getGridOccupy();
    // Grid reveallation
    void setGridRevealStatus(bool );
    bool getGridRevealStatus();
    // Destructor
    ~Grid();
};