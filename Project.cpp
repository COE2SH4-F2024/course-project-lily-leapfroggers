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

    //Getting the player position list object
    objPosArrayList& playerPositions = playerObj->getPlayerPos();
    objPos foodPosition = gameMechsRef->getFoodInfo(); // Get food position

    // Debug output to verify position
    cout << "Player Position: (" << playerPositions.getHeadElement().pos->x << ", " << playerPositions.getHeadElement().pos->y << ")" << endl;
    cout << "Food Position: (" << gameMechsRef->getFoodInfo().pos->x << ", " << gameMechsRef->getFoodInfo().pos->y << ")" << endl;

    bool contained;
    char symbol;

    for (int row = 0; row < 10; row++) 
    {
        for (int col = 0; col < 20; col++) 
        {
            contained = false;

            //Checking if the player will occupy the position
            for (int i = 0; i < playerPositions.getSize(); ++i) 
            {
                if (playerPositions.getElement(i).pos->x == col && playerPositions.getElement(i).pos->y == row) 
                {
                    contained = true;
                    symbol = (playerPositions.getElement(i)).getSymbol();
                }
            }

            if (row == 0 || row == 9 || col == 0 || col == 19) 
            {
                MacUILib_printf("%c", '#');
            } 
            else if (contained == true) 
            {
                MacUILib_printf("%c", symbol);  // Access the symbol
            } 
            else 
            {
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
