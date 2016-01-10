//
//  GirlsSelectScene.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/10.
//
//

#ifndef __GatyaSimulator__GirlsSelectScene__
#define __GatyaSimulator__GirlsSelectScene__

#include "cocos2d.h"

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

using namespace cocos2d;

class GirlsSelectScene : public cocos2d::Layer
{
protected:
    void initBackground(); // 背景の初期化
    
public:
    GirlsSelectScene(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GirlsSelectScene); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
};

#endif /* defined(__GatyaSimulator__GirlsSelectScene__) */
