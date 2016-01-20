//
//  GirlsSelectSecne.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/10.
//
//

#include "GirlsSelectScene.h"
#include "GatyaSimulatorScene.h"
#include "GameManager.h"

USING_NS_CC;

GirlsSelectScene::GirlsSelectScene()
: _confirmFlag(false)
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
        card->setPosition(Point(32 + (WINSIZE.width - 64)*i, WINSIZE.height/2-CARD_HEIGHT/2));
        
        card-> setScale(0.9, 0.9);
        cardSprites.push_back(card);
        
        addChild(card, Z_CARD, T_CARD);
        
        i++;
    }
}

ButtonSprite* GirlsSelectScene::createButton(ButtonSprite::ButtonType buttonType, ButtonSprite::PositionIndex positionIndex)
{
    auto button = ButtonSprite::create(positionIndex, buttonType);
    button->setPositionIndex(positionIndex);
    addChild(button, Z_BUTTON, T_BUTTON);
    
    return button;
}

void GirlsSelectScene::confirmCard()
{
    if (!getConfirmFlag()) {
        auto cover = Sprite::create("cover.png");
        cover->setAnchorPoint(Point::ZERO);
        cover->setPosition(Point::ZERO);
        addChild(cover, Z_COVER, T_COVER);
        
        _selectButton = createButton(ButtonSprite::ButtonType::Select, ButtonSprite::PositionIndex(WINSIZE.width/2, WINSIZE.height/2 + 100));
        _cancelButton = createButton(ButtonSprite::ButtonType::Cancel, ButtonSprite::PositionIndex(WINSIZE.width/2, WINSIZE.height/2 - 100));
        
        setConfirmFlag(true);
    }
}

void GirlsSelectScene::backSelectScene()
{
    removeChildByTag(T_COVER);
    removeChild(_selectButton);
    removeChild(_cancelButton);
    
    setConfirmFlag(false);
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

ButtonSprite::ButtonType GirlsSelectScene::getTouchButtonType(Point touchPos, ButtonSprite::PositionIndex withoutPosIndex)
{
    float selectButtonDistance = _selectButton->getPosition().getDistance(touchPos);
    
    if (selectButtonDistance <= BUTTON_SIZE / 2) {
        return _selectButton->getButtonType();
    }
    
    float cancelButtonDistance = _cancelButton->getPosition().getDistance(touchPos);
    
    if (cancelButtonDistance <= BUTTON_SIZE / 2) {
        return _cancelButton->getButtonType();
    }
    
    return ButtonSprite::ButtonType::None;
}

void GirlsSelectScene::createAndMoveGatyaSimulatorScene()
{
    GameManager::sharedGameManager()->selectCardNum = selectCardNum;
    GameManager::sharedGameManager()->totalAmount = 0;
    
    removeFromParentAndCleanup(true);
    auto scene = GatyaSimulatorScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool GirlsSelectScene::onTouchBegan(Touch *touch, Event* unused_event)
{
    if (getConfirmFlag()) {
        switch (getTouchButtonType(touch->getLocation())) {
            case ButtonSprite::ButtonType::Select:
                _selectButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::Cancel:
                _cancelButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::None:
                break;
            default:
                break;
        }
        
        return true;
    }
    
    _startLocation = touch->getLocation();
    
    return true;
}

void GirlsSelectScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    if (getConfirmFlag()) {
        switch (getTouchButtonType(touch->getLocation())) {
            case ButtonSprite::ButtonType::Select:
                _selectButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::Cancel:
                _cancelButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::None:
                _selectButton->changeButtonImageTexture();
                _cancelButton->changeButtonImageTexture();
                break;
            default:
                break;
        }
        
        return;
    }
}

void GirlsSelectScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    if (getConfirmFlag()) {
        switch (getTouchButtonType(touch->getLocation())) {
            case ButtonSprite::ButtonType::Select:
                _selectButton->changeButtonImageTexture();
                createAndMoveGatyaSimulatorScene();
                break;
            case ButtonSprite::ButtonType::Cancel:
                _cancelButton->changeButtonImageTexture();
                backSelectScene();
                break;
            case ButtonSprite::ButtonType::None:
                break;
            default:
                break;
        }
        
        return;
    }
    
    float movement = _startLocation.x - touch->getLocation().x;
    
    if (movement < -100) {
        movedLeftCard();
    } else if ( movement > 100) {
        movedRightCard();
    } else if (-50 < movement && movement < 50) {
        confirmCard();
    }
}

void GirlsSelectScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
