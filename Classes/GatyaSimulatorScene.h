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
#include "ButtonSprite.h"

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

using namespace cocos2d;

class GatyaSimulatorScene : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_BACKGROUND,
        Z_BUTTON,
    };
    
    enum Tag {
        T_BACKGROUND,
        T_BUTTON,
    };
    
    void initGatyaButton(); // ガチャボタンの初期化
    void createAndMoveGatyaDrawScene(); // ガチャを引く画面を作って移動
    void createAndMoveGatyaTenDrawScene(); // 10連ガチャを引く画面を作って移動
    ButtonSprite* createButton(ButtonSprite::ButtonType buttonType, ButtonSprite::PositionIndex positionIndex); // ボタンを作る
    ButtonSprite::ButtonType getTouchButtonType(Point touchPos, ButtonSprite::PositionIndex withoutPosIndex = ButtonSprite::PositionIndex());
    
    ButtonSprite* _drawTenCardButton;
    ButtonSprite* _drawOneCardButton;
    
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
