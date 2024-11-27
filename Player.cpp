#include "Player.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList->insertHead(objPos(5, 5, '*'));
    playerPosList->insertTail(objPos(5, 6, '*'));
    playerPosList->insertTail(objPos(5, 7, '*'));
    playerPosList->insertTail(objPos(5, 8, '*'));
    playerPosList->insertTail(objPos(5, 9, '*'));
    // more actions to be included
}


Player::~Player()
{
    delete[] playerPosList;
    // delete any heap members here
}

objPosArrayList& Player::getPlayerPos() const
{
    return *playerPosList; // Return a reference to the entire playerPosList
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
            // cases for testing
            case 'l':
                mainGameMechsRef->setLoseFlag();
                break;
            case '0':
                mainGameMechsRef->incrementScore();
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
    int maxX = mainGameMechsRef->getBoardSizeX() - 1;  // maxX is 19, valid x is from 1 to 18
    int maxY = mainGameMechsRef->getBoardSizeY() - 1;  // maxY is 9, valid y is from 1 to 8
    
    objPos playerPos = playerPosList->getHeadElement();

    // Move player based on the current direction
    switch (myDir) {
        case UP:
            if (playerPos.pos->y > 1) 
            {
                playerPos.pos->y -= 1;  // Move up
            } else {
                playerPos.pos->y = maxY - 1;  // Wrap around to the bottom, skip border
            }
            break;

        case DOWN:
            if (playerPos.pos->y < maxY - 1) 
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
                playerPos.pos->x = maxX - 1;  // Wrap around to the right, skip border
            }
            break;

        case RIGHT:
            if (playerPos.pos->x < maxX - 1) 
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

    playerPosList->insertHead(objPos(playerPos.pos->x, playerPos.pos->y, '*'));

    playerPosList->removeTail();

    // Debugging output to check the player's position
    MacUILib_printf("Player moved to: %d, %d\n", playerPos.pos->x, playerPos.pos->y);
}




// More methods to be added