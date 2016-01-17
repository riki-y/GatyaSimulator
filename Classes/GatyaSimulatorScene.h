//
//  GatyaSimulatorScene.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/12.
//
//

#ifndef __GatyaSimulator__GatyaSimulatorScene__
#define __GatyaSimulator__GatyaSimulatorScene__

#include "cocos2d.h"

using namespace cocos2d;

class GatyaSimulatorScene : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_Background
    };
    
public:
    GatyaSimulatorScene(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GatyaSimulatorScene); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__GatyaSimulator__GatyaSimulatorScene__) */
