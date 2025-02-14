#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"   // For Player class
#include "GameMechs.h" // For GameMechs class

using namespace std;

#define DELAY_CONST 100000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player* playerObj;
GameMechs* gameMechsRef;

int main(void)
{

    Initialize();

    while(!(gameMechsRef->getExitFlagStatus()))
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    gameMechsRef = new GameMechs();  // Create a new GameMechs object
    playerObj = new Player(gameMechsRef);  // Pass GameMechs reference
    gameMechsRef->generateFood(playerObj->getPlayerPos());
}

void GetInput(void)
{
    char input;
    if (MacUILib_hasChar()) {
        input = MacUILib_getChar();
        gameMechsRef->setInput(input);  // Use a method in GameMechs
    }
}

void RunLogic(void)
{
    playerObj->updatePlayerDir();
    playerObj->movePlayer();
}

void DrawScreen(void) {
    MacUILib_clearScreen();

    objPosArrayList* playerPositions = playerObj->getPlayerPos();  // Getting the player position list object
    objPos foodPosition = gameMechsRef->getFoodPos(); // Get the food's position object

    bool contained;
    char symbol;

    for (int row = 0; row < gameMechsRef->getBoardSizeY(); row++) 
    {
        for (int col = 0; col < gameMechsRef->getBoardSizeX(); col++) 
        {
            contained = false;

            //Checking if the player will occupy the position
            for (int i = 0; i < playerPositions->getSize(); ++i) 
            {
                if (playerPositions->getElement(i).pos->x == col && playerPositions->getElement(i).pos->y == row) 
                {
                    contained = true;
                    symbol = (playerPositions->getElement(i)).getSymbol();
                }
            }

            if (row == 0 || row == 9 || col == 0 || col == 19) 
            {
                MacUILib_printf("%c", '#');
            } else if (contained) {
                MacUILib_printf("%c", symbol);  // Access the symbol
            } else if (row == foodPosition.pos->y && col == foodPosition.pos->x) {
                MacUILib_printf("%c", foodPosition.getSymbol());
            } else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", gameMechsRef->getScore());

    MacUILib_printf("\nToggle Debug Mode: Backspace\n");

    if(gameMechsRef->getDebugFlagStatus())
    {
        MacUILib_printf("\n------------------------ Debugging Controls ---------------------------\n");
        MacUILib_printf("Debug Keys: 'l' = lose flag, '0' = increment score, 'f' = generate food\n");

        // Debug output to verify position
        MacUILib_printf("\nHead Position: (%d, %d)\n", playerPositions->getHeadElement().pos->x, playerPositions->getHeadElement().pos->y);
        MacUILib_printf("List Size: %d\n", playerPositions->getSize());
        MacUILib_printf("Food Info: {%d, %d, %c}\n", foodPosition.pos->x, foodPosition.pos->y, foodPosition.symbol);
        MacUILib_printf("Self Colision Bool: %d\n", playerObj->checkSelfCollision());
    }

    
}




void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void) {
    MacUILib_clearScreen();
    if(gameMechsRef->getLoseFlagStatus() == true)
    {
    cout << "You Lose!" << endl;
    }
    MacUILib_uninit();
    delete playerObj;
    delete gameMechsRef;  // Prevent memory leaks
}
