//
//  GirlsSelectSecne.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/10.
//
//

#include "GirlsSelectScene.h"

USING_NS_CC;

GirlsSelectScene::GirlsSelectScene()
{
}

Scene* GirlsSelectScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GirlsSelectScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GirlsSelectScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GirlsSelectScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GirlsSelectScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GirlsSelectScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GirlsSelectScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initBackground(); // 背景の初期化
    
    return true;
}

void GirlsSelectScene::initBackground()
{
}

bool GirlsSelectScene::onTouchBegan(Touch *touch, Event* unused_event) {
    return false;
}

void GirlsSelectScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    
}

void GirlsSelectScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    
}

void GirlsSelectScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
