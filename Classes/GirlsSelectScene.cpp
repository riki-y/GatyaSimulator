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
    craftCardList();
    
    selectCardMaxNum = (int)girlList.size();
    
    return true;
}

void GirlsSelectScene::craftCardList()
{
    int i = 0;
    
    for(auto list : girlList) {
        auto card = Sprite::create(list);
        card->setAnchorPoint(Point::ZERO);
        card->setPosition(Point(32 + (WINSIZE.width - 64)*i, WINSIZE.height/4));
        
        card-> setScale(0.9, 0.9);
        cardSprites.push_back(card);
        
        addChild(card);
        
        i++;
    }
}

void GirlsSelectScene::movedRightCard()
{
    if (selectCardNum < selectCardMaxNum - 1) {
        for(auto card : cardSprites) {
            card->setPosition(card->getPosition() + Point(-CARD_WIDTH, 0));
        }
        
        selectCardNum++;
    }
}

void GirlsSelectScene::movedLeftCard()
{
    if (selectCardNum > 0) {
        for(auto card : cardSprites) {
            card->setPosition(card->getPosition() + Point(CARD_WIDTH, 0));
        }
        
        selectCardNum--;
    }
}

bool GirlsSelectScene::onTouchBegan(Touch *touch, Event* unused_event) {
    if (touch->getLocation().x < WINSIZE.width / 2) {
        movedLeftCard();
    } else {
        movedRightCard();
    }
    
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
