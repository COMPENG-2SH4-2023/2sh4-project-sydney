#include <iostream>
#include "MacUILib.h"
#include "objPos.h" // fundamental building block for project
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// OOD Benefit - very limited global var declaration
// in advanced OOD, you don't need global variable
GameMechs* myGM;
Player* myPlayer;
objPos myPos;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    myGM = new GameMechs(26, 13); // make the board size 26x13
    myPlayer =  new Player(myGM);

    // Think about when to generate the new food...

    // Think about whether you want to set up a debug key to call the 
    //    food generation routine for verification

    // remember, generateFood() requires player reference. You will need to 
    //     provide it AFTER player object is instantiated

}

void GetInput(void)
{
    myGM -> getInput();
}

void RunLogic(void)
{
    // char input = myGM->getInput();
    
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Check if the player has reached the food
    objPos tempPos;
    objPos foodPos;
    myPlayer->getPlayerPos(tempPos);
    myGM->getFoodPos(foodPos);

    if (tempPos.isPosEqual(&foodPos))
    {
        // Player reached the food, generate a new food position
        myGM->generateFood(tempPos);
        myGM->incrementScore();
    }

    myGM->clearInput(); // so not to repeatedly process the input
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos tempPos;
    objPos foodPos;

    myPlayer->getPlayerPos(tempPos); // get player pos

    if (!myGM->hasFoodGeneratedThisFrame())
    {
        myGM->generateFood(tempPos);
    }

    myGM->getFoodPos(foodPos);

    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            // draw border
            if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (j == tempPos.x && i == tempPos.y)
            {
                MacUILib_printf("%c", tempPos.symbol);
            }
            // include food into draw routine
            else if (j == foodPos.x && i == foodPos.y)
            {
                MacUILib_printf("%c", foodPos.getSymbol());
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }


    MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n", myGM->getScore(), tempPos.x, tempPos.y, tempPos.symbol);
    // Because we are  using the async input in MacUILib, we have to use MacUILib_printf() instead of cout

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();

    // remove heap instances
    delete myGM;
    delete myPlayer;
}
