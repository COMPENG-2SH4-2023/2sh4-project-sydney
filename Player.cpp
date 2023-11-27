#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    // no deap member yet - never used new keyword
}


Player::~Player()
{
    // delete any heap members here
    // we can leave empty for now.
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    // where do i get the input? how do i check for inputs?
    // Hint 1: definitely not by calling MacUILib_getChar()
    // Hint 2: coordinate with your team member  who's designing 
    //         GameMechanism class
    // Hint 3: There will be a method in GameMechanism class that 
    //         collectively checks input and stores the most recent 
    //         input. You just need to figure out how do to get to 
    //         it...

    // How?? It lies within the GameMechs* inside your private member

    char input = mainGameMechsRef->getInput();

    if(input != 0)
        switch(input)
        {
            case 'w':
                if (myDir != UP && myDir != DOWN)
                    myDir = UP;
                break;
            
            case 'a':
                if (myDir != LEFT && myDir != RIGHT)
                    myDir = LEFT;
                break;
            
            case 's':
                if (myDir != UP && myDir != DOWN)
                    myDir = DOWN;
                break;

            case 'd':
                if(myDir != LEFT && myDir != RIGHT)
                    myDir = RIGHT;
                break;
            
            default:
                break;
        }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic


    switch(myDir)
    {
        case LEFT:
            playerPos.x--;
            break;
        
        case RIGHT:
            playerPos.x++;
            break;
        
        case UP:
            playerPos.y--;
            break;

        case DOWN:
            playerPos.y++;
            break;

        default:
            break;  
    }

    // x-coordinate of player wraparound
    if (playerPos.x == 0) 
        playerPos.x = mainGameMechsRef->getBoardSizeX() - 2; // Wrap to the right edge
    else if (playerPos.x == mainGameMechsRef->getBoardSizeX() - 1) 
        playerPos.x = 1; // Wrap to the left edge

    // y-coordinate of player wrap around
    if (playerPos.y == 0) 
        playerPos.y = mainGameMechsRef->getBoardSizeY() - 2; // Wrap to the right edge
    else if (playerPos.y == mainGameMechsRef->getBoardSizeY() - 1) 
        playerPos.y = 1; // Wrap to the left edge

}

