#include "objPos.h"

//Default Constructor
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

// Alternative Constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Copy Constructor
objPos::objPos(const objPos &sObjPos)
{
    pos = new Pos;
    pos->x = sObjPos.pos->x; 
    pos->y = sObjPos.pos->y;
    symbol = sObjPos.symbol;
}

// Copy Assignment Operator
objPos& objPos::operator=(const objPos &sObjPos)
{
    pos = new Pos;
    
    if (this != &sObjPos)
    {
        this->pos->x = sObjPos.pos->x;
        this->pos->y = sObjPos.pos->y;
        this->symbol = sObjPos.symbol;
    }
    return *this;
}

objPos::~objPos() //Destructor
{
    delete pos;
}

// Respect the rule of six / minimum four

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
