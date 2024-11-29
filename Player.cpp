#include "Player.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList->insertHead(objPos(5, 5, 254));
    // playerPosList->insertTail(objPos(5, 6, '*'));
    // playerPosList->insertTail(objPos(5, 7, '*'));
    // playerPosList->insertTail(objPos(5, 8, '*'));
    // playerPosList->insertTail(objPos(5, 9, '*'));
    // more actions to be included
}


Player::~Player()
{
    delete[] playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // Return a reference to the entire playerPosList
}


void Player::updatePlayerDir()
{
    if (mainGameMechsRef != nullptr)
    {
        char input = mainGameMechsRef->getInput();  // Get input from the shared GameMechs object

        switch (input)
        {
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
                if (myDir != DOWN) myDir = UP;
                break;
            case 'a':
                if (myDir != RIGHT) myDir = LEFT;
                break;
            case 's':
                if (myDir != UP) myDir = DOWN;
                break;
            case 'd':
                if (myDir != LEFT) myDir = RIGHT;
                break;
            // debug keys for testing
            case 'l':
                mainGameMechsRef->setLoseFlag();
                break;
            case '0':
                mainGameMechsRef->incrementScore();
                break;
            case 'f':
                mainGameMechsRef->generateFood(playerPosList);
                break;
        }
        mainGameMechsRef->clearInput();
    }
}


void Player::movePlayer() 
{
    // Check if the GameMechs reference is valid
    if (mainGameMechsRef == nullptr) return;

    // Get the board size limits
    int maxX = mainGameMechsRef->getBoardSizeX() - 2;  // maxX is 18, valid x is from 1 to 18
    int maxY = mainGameMechsRef->getBoardSizeY() - 2;  // maxY is 8, valid y is from 1 to 8
    
    objPos playerPos = playerPosList->getHeadElement();

    // Move player based on the current direction
    switch (myDir) {
        case UP:
            if (playerPos.pos->y > 1) 
            {
                playerPos.pos->y -= 1;  // Move up
            } else {
                playerPos.pos->y = maxY;  // Wrap around to the bottom, skip border
            }
            break;

        case DOWN:
            if (playerPos.pos->y < maxY) 
            {
                playerPos.pos->y += 1;  // Move down
            } else {
                playerPos.pos->y = 1;  // Wrap around to the top, skip border
            }
            break;

        case LEFT:
            if (playerPos.pos->x > 1) 
            {
                playerPos.pos->x -= 1;  // Move left
            } else {
                playerPos.pos->x = maxX;  // Wrap around to the right, skip border
            }
            break;

        case RIGHT:
            if (playerPos.pos->x < maxX) 
            {
                playerPos.pos->x += 1;  // Move right
            } else {
                playerPos.pos->x = 1;  // Wrap around to the left, skip border
            }
            break;

        default:
            // No movement if the direction is STOP or invalid
            break;
    }
    playerPosList->insertHead(objPos(playerPos.pos->x, playerPos.pos->y, 254));

    // check for food consumption
    increasePlayerLength();

    // Check for self colision
    if(checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    

    // Debugging output to check the player's position
    MacUILib_printf("Player moved to: %d, %d\n", playerPos.pos->x, playerPos.pos->y);
}


// More methods to be added
bool Player::checkFoodConsumption()
{
    objPos playerPos = playerPosList->getHeadElement();
    objPos foodPos = mainGameMechsRef->getFoodPos();

    int playerX = playerPos.pos->x, playerY = playerPos.pos->y;
    int foodX = foodPos.pos->x, foodY = foodPos.pos->y;

    if(playerX == foodX && playerY == foodY) { return true; }
    else { return false; }
}

void Player::increasePlayerLength()
{
    if(checkFoodConsumption())
    {
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }
    else 
    {
        playerPosList->removeTail();
    }
}

bool Player::checkSelfCollision()
{
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        if (playerPosList->getElement(0).pos->x == playerPosList->getElement(i).pos->x && 
                playerPosList->getElement(0).pos->y == playerPosList->getElement(i).pos->y)
        {
            return true;
        }
    }
    return false;
}