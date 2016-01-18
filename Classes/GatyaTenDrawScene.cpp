//
//  GatyaTenDrawScene.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#include "GatyaTenDrawScene.h"
#include <random>
#include "GatyaSimulatorScene.h"

USING_NS_CC;

// コンストラクタ
GatyaTenDrawScene::GatyaTenDrawScene()
: _reverseFlag(false)
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
    
    initCard();
    
    return true;
}

void GatyaTenDrawScene::initCard()
{
    _cards.clear();
    
    for (int i=0;i<CARD_NUM;i++) {
        Cards card;
        if (isSRCard()) {
            int j = arc4random_uniform(SR_CARD_NUM + 1);
            card.filePath = SRGirlList.at(j);
        } else {
            int j = arc4random_uniform(R_CARD_NUM + 1);
            card.filePath = RGirlList.at(j);
        }
        
        _cards.push_back(card);
    }
    
    int tag = 1;
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 3; y++) {
            if(y == 2 && x > 1) {
                break;
            }
            createCard(CardSprite::PositionIndex((ONE_CARD_WIDTH*CARD_SCALE)*x+(ONE_CARD_WIDTH*CARD_SCALE)/2+(ONE_CARD_WIDTH*CARD_SCALE)*(x+1)/5, WINSIZE.height*4/5 - ONE_CARD_HEIGHT*CARD_SCALE*y - 25*y), tag);
            tag++;
        }
    }
}

void GatyaTenDrawScene::initButton()
{
    _backButton = createButton(ButtonSprite::ButtonType::Back, ButtonSprite::PositionIndex(WINSIZE.width/4, BUTTON_SIZE));
    _retryButton = createButton(ButtonSprite::ButtonType::Retry, ButtonSprite::PositionIndex(WINSIZE.width*3/4, BUTTON_SIZE));
}

CardSprite* GatyaTenDrawScene::createCard(CardSprite::PositionIndex positionIndex, int tag)
{
    auto card = CardSprite::create(positionIndex);
    card->setPositionIndex(positionIndex);
    card->setScale(CARD_SCALE);
    addChild(card, Z_CARD, CARD_TAG+tag);
    
    return card;
}

ButtonSprite* GatyaTenDrawScene::createButton(ButtonSprite::ButtonType buttonType, ButtonSprite::PositionIndex positionIndex)
{
    auto button = ButtonSprite::create(positionIndex, buttonType);
    button->setPositionIndex(positionIndex);
    addChild(button, Z_BUTTON, T_BUTTON);
    
    return button;
}

bool GatyaTenDrawScene::isSRCard()
{
    int i = arc4random_uniform(1000);
    
    if (i < 15) {
        return true;
    }
    
    return false;
}

ButtonSprite::ButtonType GatyaTenDrawScene::getTouchButtonType(Point touchPos, ButtonSprite::PositionIndex withoutPosIndex)
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

void GatyaTenDrawScene::backGatyaSimulatorScene()
{
    auto scene = GatyaSimulatorScene::createScene();
    Director::getInstance()->replaceScene(scene);
    
}

void GatyaTenDrawScene::retryGatyaDrawScene()
{
    auto scene = GatyaTenDrawScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool GatyaTenDrawScene::onTouchBegan(Touch* touch, Event* unused_event)
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

void GatyaTenDrawScene::onTouchMoved(Touch* touch, Event* unused_event)
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

void GatyaTenDrawScene::onTouchEnded(Touch* touch, Event* unused_event)
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
        for (int tag = 1; tag <= 10; tag++) {
            auto cardSprite = (CardSprite*)getChildByTag(CARD_TAG + tag);
            cardSprite->reverseCard(_cards[tag-1].filePath);
        }
        
        setReverseFlag(true);
        initButton();
    }
}

void GatyaTenDrawScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
