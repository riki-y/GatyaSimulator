//
//  GameManager.cpp
//  GatyaSimulator
//
//  Created by 理貴 on 2016/01/21.
//
//

#include "SimpleAudioEngine.h"
#include "GameManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    
}

GameManager* GameManager::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new GameManager();
    }
    
    //Return the singleton object
    return m_mySingleton;
}
