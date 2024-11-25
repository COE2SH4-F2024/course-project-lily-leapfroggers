#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20;
    boardSizeY = 10;

    food.pos->x = 0;
    food.pos->y = 0;
    food.symbol = '*';
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    
    if (boardX < 3) {boardSizeX = 20;}
    else {boardSizeX = boardX;}

    if (boardY < 3) {boardSizeY = 10;}
    else {boardSizeY = boardY;}

    food.pos->x = 0;
    food.pos->y = 0;
    food.symbol = '*';
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete food.pos;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here
objPos GameMechs::getFoodInfo() const
{
    return food;
}