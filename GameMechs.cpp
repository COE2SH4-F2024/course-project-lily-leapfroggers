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
void GameMechs::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));

    int i = 0;
    int upperLim_x = boardSizeX - 2, upperLim_y = boardSizeY - 2;

    int candX = (rand() % upperLim_x) + 1, candY = (rand() % upperLim_y) + 1;
    objPos candidate;

    while(i < blockOff->getSize())
    {
        if (candX == blockOff->getElement(i).pos->x && candY == blockOff->getElement(i).pos->y)
        {
            int candX = (rand() % upperLim_x) + 1;
            int candY = (rand() % upperLim_y) + 1;
        }
        else {i++;}
    }

    candidate.pos->x = candX;
    candidate.pos->y = candY;
    candidate.symbol = 233;

    foodPos.setObjPos(candidate);
}

objPos GameMechs::getFoodPos() const
{
    return foodPos;
}