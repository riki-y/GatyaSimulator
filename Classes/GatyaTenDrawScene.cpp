//
//  GatyaTenDrawScene.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#include "GatyaTenDrawScene.h"

USING_NS_CC;

// コンストラクタ
GatyaTenDrawScene::GatyaTenDrawScene()
{
}

// シーンの生成
Scene* GatyaTenDrawScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GatyaTenDrawScene::create();
    scene->addChild(layer);
    
    return scene;
}

// 初期化
bool GatyaTenDrawScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GatyaTenDrawScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GatyaTenDrawScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GatyaTenDrawScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GatyaTenDrawScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool GatyaTenDrawScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    return false;
}

void GatyaTenDrawScene::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GatyaTenDrawScene::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GatyaTenDrawScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}