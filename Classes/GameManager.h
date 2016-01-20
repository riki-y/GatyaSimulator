//
//  GameManager.hpp
//  GatyaSimulator
//
//  Created by 理貴 on 2016/01/21.
//
//

#ifndef __GatyaSimulator__GameManager__
#define __GatyaSimulator__GameManager__

#include "cocos2d.h"

class GameManager
{
private:
    GameManager();
    static GameManager* m_mySingleton;
    
public:
    static GameManager* sharedGameManager();
    
    int count;
    int totalAmount;
    int selectCardNum;
    
};

#endif /* GameManager_h */
