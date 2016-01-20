//
//  GatyaSimulatorScene.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/12.
//
//

#include "GatyaSimulatorScene.h"
#include "GatyaDrawScene.h"
#include "GatyaTenDrawScene.h"
#include "GameManager.h"

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
    
    initGatyaButton();
    initTotalAmountLabel();
    
    return true;
}

void GatyaSimulatorScene::initGatyaButton()
{
    _drawOneCardButton = createButton(ButtonSprite::ButtonType::DrawOneCard, ButtonSprite::PositionIndex(WINSIZE.width/2, WINSIZE.height/2 + 100));
    _drawTenCardButton = createButton(ButtonSprite::ButtonType::DrawTenCard, ButtonSprite::PositionIndex(WINSIZE.width/2, WINSIZE.height/2 - 100));
}

void GatyaSimulatorScene::initTotalAmountLabel()
{
    string totalAmountString = StringUtils::format("%d", GameManager::sharedGameManager()->totalAmount);
    auto totalAmount = Label::createWithSystemFont(totalAmountString + " mc", "Arial", 30);
    totalAmount->setPosition(Point(WINSIZE.width - totalAmount->getContentSize().width, WINSIZE.height - totalAmount->getContentSize().height));
    totalAmount->setTextColor(Color4B::WHITE);
    addChild(totalAmount, Z_LABEL, T_LABEL);
}

ButtonSprite* GatyaSimulatorScene::createButton(ButtonSprite::ButtonType buttonType, ButtonSprite::PositionIndex positionIndex)
{
    auto button = ButtonSprite::create(positionIndex, buttonType);
    button->setPositionIndex(positionIndex);
    addChild(button, Z_BUTTON, T_BUTTON);
    
    return button;
}

ButtonSprite::ButtonType GatyaSimulatorScene::getTouchButtonType(Point touchPos, ButtonSprite::PositionIndex withoutPosIndex)
{
    float drawOneCardButtonDistance = _drawOneCardButton->getPosition().getDistance(touchPos);
    
    if (drawOneCardButtonDistance <= BUTTON_SIZE / 2) {
        return _drawOneCardButton->getButtonType();
    }
    
    float drawTenCardButtonDistance = _drawTenCardButton->getPosition().getDistance(touchPos);
    
    if (drawTenCardButtonDistance <= BUTTON_SIZE / 2) {
        return _drawTenCardButton->getButtonType();
    }
    
    return ButtonSprite::ButtonType::None;
}

void GatyaSimulatorScene::createAndMoveGatyaDrawScene()
{
    removeFromParentAndCleanup(true);
    GameManager::sharedGameManager()->totalAmount += 300;
    auto scene = GatyaDrawScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GatyaSimulatorScene::createAndMoveGatyaTenDrawScene()
{
    removeFromParentAndCleanup(true);
    GameManager::sharedGameManager()->totalAmount += 3000;
    auto scene = GatyaTenDrawScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool GatyaSimulatorScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    switch (getTouchButtonType(touch->getLocation())) {
        case ButtonSprite::ButtonType::DrawOneCard:
            _drawOneCardButton->changePushButtonImageTexture();
            break;
        case ButtonSprite::ButtonType::DrawTenCard:
            _drawTenCardButton->changePushButtonImageTexture();
            break;
        case ButtonSprite::ButtonType::None:
            break;
        default:
            break;
    }
    
    return true;
}

void GatyaSimulatorScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    switch (getTouchButtonType(touch->getLocation())) {
        case ButtonSprite::ButtonType::DrawOneCard:
            _drawOneCardButton->changePushButtonImageTexture();
            break;
        case ButtonSprite::ButtonType::DrawTenCard:
            _drawTenCardButton->changePushButtonImageTexture();
            break;
        case ButtonSprite::ButtonType::None:
            _drawOneCardButton->changeButtonImageTexture();
            _drawTenCardButton->changeButtonImageTexture();
            break;
        default:
            break;
    }
}

void GatyaSimulatorScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    switch (getTouchButtonType(touch->getLocation())) {
        case ButtonSprite::ButtonType::DrawOneCard:
            _drawOneCardButton->changeButtonImageTexture();
            createAndMoveGatyaDrawScene();
            break;
        case ButtonSprite::ButtonType::DrawTenCard:
            _drawTenCardButton->changeButtonImageTexture();
            createAndMoveGatyaTenDrawScene();
            break;
        case ButtonSprite::ButtonType::None:
            break;
        default:
            break;
    }

}

void GatyaSimulatorScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
