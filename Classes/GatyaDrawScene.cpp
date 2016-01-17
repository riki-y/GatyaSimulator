//
//  GatyaDrawScene.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#include "GatyaDrawScene.h"
#include <random>

USING_NS_CC;

// コンストラクタ
GatyaDrawScene::GatyaDrawScene()
{
}

// シーンの生成
Scene* GatyaDrawScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GatyaDrawScene::create();
    scene->addChild(layer);
    
    return scene;
}

// 初期化
bool GatyaDrawScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GatyaDrawScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GatyaDrawScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GatyaDrawScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GatyaDrawScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initCard();
    
    return true;
}

void GatyaDrawScene::initCard()
{
    if (isSRCard()) {
        int i = arc4random_uniform(SR_CARD_NUM + 1);
        _card.filePath = SRGirlList.at(i);
    } else {
        int i = arc4random_uniform(R_CARD_NUM + 1);
        _card.filePath = RGirlList.at(i);
    }
    
    _cardSprite = createCard(CardSprite::PositionIndex(WINSIZE.width/2, WINSIZE.height/2));
}

CardSprite* GatyaDrawScene::createCard(CardSprite::PositionIndex positionIndex)
{
    auto card = CardSprite::create(positionIndex);
    card->setPositionIndex(positionIndex);
    card->setScale(0.9, 0.9);
    addChild(card, Z_CARD);
        
    return card;
}

bool GatyaDrawScene::isSRCard()
{
    int i = arc4random_uniform(1000);
    
    if (i < 15) {
        return true;
    }
    
    return false;
}

void GatyaDrawScene::getTouchCard(Point touchPos)
{
    float distance = _cardSprite->getPosition().getDistance(touchPos);
    
    if (distance <= CARD_WIDTH / 2) {
        _cardSprite->reverseCard(_card.filePath);
    }
}

bool GatyaDrawScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    getTouchCard(touch->getLocation());
    return false;
}

void GatyaDrawScene::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GatyaDrawScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    getTouchCard(touch->getLocation());
}

void GatyaDrawScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
