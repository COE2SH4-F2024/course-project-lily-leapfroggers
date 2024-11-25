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

    while(gameMechsRef->getExitFlagStatus() == false)
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
    objPos playerPosition = playerObj->getPlayerPos();  // Get the player's position object
    objPos playerPosCopy = playerPosition.getObjPos();  // Get the actual position and symbol from the objPos

    // Debug output to verify position
    cout << "Player Position: (" << playerPosCopy.pos->x << ", " << playerPosCopy.pos->y << ")" << endl;
    cout << "Food Position: (" << gameMechsRef->getFoodInfo().pos->x << ", " << gameMechsRef->getFoodInfo().pos->y << ")" << endl;

    for (int row = 0; row < 10; row++) 
    {
        for (int col = 0; col < 20; col++) {
            if (row == 0 || row == 9 || col == 0 || col == 19) {
                MacUILib_printf("%c", '#');
            } else if (row == playerPosCopy.pos->y && col == playerPosCopy.pos->x) {
                MacUILib_printf("%c", playerPosCopy.getSymbol());  // Access the symbol
            } else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    cout << "Score: " << gameMechsRef->getScore() << endl;
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
