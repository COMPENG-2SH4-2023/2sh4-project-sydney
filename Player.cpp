#include "Player.h"


Player::Player(GameMechs* thisGMRef) : mainGameMechsRef(thisGMRef)
{
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    // no deap member yet - never used new keyword
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    // delete any heap members here
    // we can leave empty for now.
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;

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

    objPos currHead; // holding the pos information of the current head
    playerPosList->getHeadElement(currHead);

    switch(myDir)
    {
        case LEFT:
            currHead.x--;
            if(currHead.x <= 0)
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2; 
            break;
        
        case RIGHT:
            currHead.x++;
            if(currHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
                currHead.x = 1;
            break;
        
        case UP:
            currHead.y--;
            if(currHead.y <= 0)
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;

        case DOWN:
            currHead.y++;
            if (currHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
                currHead.y = 1;  // Change this line
            break;
        
        case STOP:
        default:
            break;  
    }

    
    // if new head position overlaps with food
    objPos tempFoodPos;
    mainGameMechsRef->getFoodPos(tempFoodPos);

    // if player reaches food, generate new food position
    if(currHead.isPosEqual(&tempFoodPos))
    {
        mainGameMechsRef->generateFood(currHead);
        mainGameMechsRef->incrementScore();
    }
    else
    {

        for (int i = 1; i < playerPosList->getSize(); i++)
        {
            objPos tempBody;
            playerPosList->getElement(tempBody, i);
            if (currHead.isPosEqual(&tempBody))
            {
                mainGameMechsRef->setLoseFlag();
                return;
            }
        }

        if (mainGameMechsRef->getScore() >= playerPosList->getSize())
        {
            playerPosList->insertHead(currHead);
        }
        else
        {
            playerPosList->insertHead(currHead);
            playerPosList->removeTail();
        }
    }
}

 bool Player::checkSelfCollision()
 {

 }
