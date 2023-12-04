#include "GameMechs.h"
#include "MacUILib.h"
#include <time.h>

// Think about where to see the RNG.

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    // default board size
    boardSizeX = 30; // columns
    boardSizeY = 10; // rows

    foodPos.setObjPos(-1, -1, 'o'); // initialize foodPos outside of the game board (so to not be displayed)
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    boardSizeX = boardX; 
    boardSizeY = boardY;

    foodPos.setObjPos(-1, -1, 'o');
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // Deallocate all heap data members
    // Defense against memory leakage
    // May not be needed if you do not have heap data members.
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();

        if(input == 27)
            exitFlag = true; 
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(const objPos& playerPos)
{
    // generate random x and y coord, make sure they are NOT boarder or blockOff pos.

    // check x and y against 0 and boardSizeX / boardSizeY

    // remember, in objPos class you have an isPosEqual() method. Use this instead of comparing 
    //      element-byelement for your convenience

    srand(time(NULL)); // outputting pseudo-random-numbers

    while (true)
    {
        int foodX = rand() % (boardSizeX - 2) + 1;
        int foodY = rand() % (boardSizeY - 2) + 1;

        // check if food overlaps with the player
        objPos tempPos(foodX, foodY, ' ');

        // check if food overlaps with the player
        if (!playerPos.isPosEqual(&tempPos))
        {
            foodPos.setObjPos(foodX, foodY, 'o');
            foodGeneratedThisFrame = true; // Set the flag when food is generated
            return; // Exit the function after generating food
        }
    }

    foodGeneratedThisFrame = false;

}


void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}

bool GameMechs::hasFoodGeneratedThisFrame() const
{
    return foodGeneratedThisFrame;
}

