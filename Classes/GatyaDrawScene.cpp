//
//  GatyaDrawScene.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#include <random>
#include "GatyaDrawScene.h"
#include "GatyaSimulatorScene.h"
#include "GameManager.h"

USING_NS_CC;

// コンストラクタ
GatyaDrawScene::GatyaDrawScene()
: _reverseFlag(false)
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
        int i = arc4random_uniform((int)SRGirlList.size());
        _card.filePath = SRGirlList.at(i);
    } else {
        int i = arc4random_uniform((int)RGirlList.size());
        _card.filePath = RGirlList.at(i);
    }
    
    _cardSprite = createCard(CardSprite::PositionIndex(WINSIZE.width/2, WINSIZE.height/2+50));
}

void GatyaDrawScene::initButton()
{
    _backButton = createButton(ButtonSprite::ButtonType::Back, ButtonSprite::PositionIndex(WINSIZE.width/4, BUTTON_SIZE));
    _retryButton = createButton(ButtonSprite::ButtonType::Retry, ButtonSprite::PositionIndex(WINSIZE.width*3/4, BUTTON_SIZE));
}

CardSprite* GatyaDrawScene::createCard(CardSprite::PositionIndex positionIndex)
{
    auto card = CardSprite::create(positionIndex);
    card->setPositionIndex(positionIndex);
    card->setScale(0.9);
    addChild(card, Z_CARD);
        
    return card;
}

ButtonSprite* GatyaDrawScene::createButton(ButtonSprite::ButtonType buttonType, ButtonSprite::PositionIndex positionIndex)
{
    auto button = ButtonSprite::create(positionIndex, buttonType);
    button->setPositionIndex(positionIndex);
    addChild(button, Z_BUTTON, T_BUTTON);
    
    return button;
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
        setReverseFlag(true);
        initButton();
    }
}

ButtonSprite::ButtonType GatyaDrawScene::getTouchButtonType(Point touchPos, ButtonSprite::PositionIndex withoutPosIndex)
{
    float backButtonDistance = _backButton->getPosition().getDistance(touchPos);
    
    if (backButtonDistance <= BUTTON_SIZE / 2) {
        return _backButton->getButtonType();
    }
    
    float retryButtonDistance = _retryButton->getPosition().getDistance(touchPos);
    
    if (retryButtonDistance <= BUTTON_SIZE / 2) {
        return _retryButton->getButtonType();
    }
    
    return ButtonSprite::ButtonType::None;
}

void GatyaDrawScene::backGatyaSimulatorScene()
{
    removeFromParentAndCleanup(true);
    auto scene = GatyaSimulatorScene::createScene();
    Director::getInstance()->replaceScene(scene);

}

void GatyaDrawScene::retryGatyaDrawScene()
{
    GameManager::sharedGameManager()->totalAmount += 300;
    
    removeFromParentAndCleanup(true);
    auto scene = GatyaDrawScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool GatyaDrawScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    if (getReverseFlag()) {
        switch (getTouchButtonType(touch->getLocation())) {
            case ButtonSprite::ButtonType::Back:
                _backButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::Retry:
                _retryButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::None:
                break;
            default:
                break;
        }
    }
    
    return true;
}

void GatyaDrawScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    if (getReverseFlag()) {
        switch (getTouchButtonType(touch->getLocation())) {
            case ButtonSprite::ButtonType::Back:
                _backButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::Retry:
                _retryButton->changePushButtonImageTexture();
                break;
            case ButtonSprite::ButtonType::None:
                _backButton->changeButtonImageTexture();
                _retryButton->changeButtonImageTexture();
                break;
            default:
                break;
        }
    }
}

void GatyaDrawScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    if (getReverseFlag()) {
        switch (getTouchButtonType(touch->getLocation())) {
            case ButtonSprite::ButtonType::Back:
                _backButton->changeButtonImageTexture();
                backGatyaSimulatorScene();
                break;
            case ButtonSprite::ButtonType::Retry:
                _retryButton->changeButtonImageTexture();
                retryGatyaDrawScene();
                break;
            case ButtonSprite::ButtonType::None:
                break;
            default:
                break;
        }
    } else {
        getTouchCard(touch->getLocation());   
    }
}

void GatyaDrawScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
