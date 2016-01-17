//
//  GatyaSimulatorScene.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/12.
//
//

#include "GatyaSimulatorScene.h"

USING_NS_CC;

// コンストラクタ
GatyaSimulatorScene::GatyaSimulatorScene()
{
}

// シーンの生成
Scene* GatyaSimulatorScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GatyaSimulatorScene::create();
    scene->addChild(layer);
    
    return scene;
}

// 初期化
bool GatyaSimulatorScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GatyaSimulatorScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GatyaSimulatorScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GatyaSimulatorScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GatyaSimulatorScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool GatyaSimulatorScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    return false;
}

void GatyaSimulatorScene::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GatyaSimulatorScene::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GatyaSimulatorScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
