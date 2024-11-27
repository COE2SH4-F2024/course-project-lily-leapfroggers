#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20;
    boardSizeY = 10;
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
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
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
void GameMechs::generateFood(objPos blockOff)
{
    srand(time(NULL));
    int upperLim_x = boardSizeX - 2, upperLim_y = boardSizeY - 2;
    int candX, candY;
    objPos candidate;

    do
    {
        candX = (rand() % upperLim_x) + 1; // x-coordinate candidate
        candY = (rand() % upperLim_y) + 1; // y-coordinate candidate
    } while (candX == blockOff.pos->x && candY == blockOff.pos->y); // same as player location

    candidate.pos->x = candX;
    candidate.pos->y = candY;
    candidate.symbol = '*';

    food.setObjPos(candidate);
}

objPos GameMechs::getFoodPos() const
{
    return food;
}