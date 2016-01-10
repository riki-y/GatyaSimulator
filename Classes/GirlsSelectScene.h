//
//  GirlsSelectSecne.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/10.
//
//

#ifndef __GatyaSimulator__GirlsSelectSecne__
#define __GatyaSimulator__GirlsSelectSecne__

#include "cocos2d.h"

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

using namespace cocos2d;

class GirlsSelectSecne : public cocos2d::Layer
{
protected:
    void initBackground(); // 背景の初期化
    
public:
    GirlsSelectSecne(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GirlsSelectSecne); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
};

#endif /* defined(__GatyaSimulator__GirlsSelectSecne__) */
