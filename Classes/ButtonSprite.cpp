//
//  ButtonSprite.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#include "ButtonSprite.h"

USING_NS_CC;

// コンストラクタ
ButtonSprite::ButtonSprite()
: _positionIndex(0, 0)
{
}

// インスタンス生成
ButtonSprite* ButtonSprite::create(PositionIndex positionIndex, ButtonType buttonType)
{
    ButtonSprite* pRet = new ButtonSprite();
    if (pRet && pRet->init(positionIndex, buttonType)) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    
    return pRet;
}

// 初期化
bool ButtonSprite::init(PositionIndex positionIndex, ButtonType buttonType)
{
    if (!Sprite::initWithFile(getButtonImageFilePath(buttonType))) {
        return false;
    }
    
    _buttonType = buttonType;
    setPositionIndex(positionIndex);
    
    return true;
}

// ボタンの画像を変更
void ButtonSprite::changeButtonImageTexture()
{
    setTexture(getButtonImageFilePath(_buttonType));
}

void ButtonSprite::changePushButtonImageTexture()
{
    setTexture(getPushButtonImageFilePath());
}

// 位置インデックスを返す
ButtonSprite::PositionIndex ButtonSprite::getPositionIndex()
{
    return _positionIndex;
}

// 位置インデックスとタグを変更する
void ButtonSprite::setPositionIndex(PositionIndex positionIndex)
{
    // 位置インデックスを保持する
    _positionIndex = positionIndex;
    // 位置を変更する
    setPosition(getPointForPositionIndex(_positionIndex));
    // タグをセットする
    setTag(getGenerateTag(_positionIndex));
}

// グリッド画像の取得
std::string ButtonSprite::getButtonImageFilePath(ButtonType buttonType)
{
    switch (buttonType) {
        case ButtonType::Select:
            return "select_button.png";
        case ButtonType::Cancel:
            return "cancel_button.png";
        case ButtonType::None:
            return "";
    }
}

std::string ButtonSprite::getPushButtonImageFilePath()
{
    switch (_buttonType) {
        case ButtonType::Select:
            return "push_select_button.png";
        case ButtonType::Cancel:
            return "push_cancel_button.png";
        case ButtonType::None:
            return "";
    }
}

// 位置インデックスからPointを取得
Point ButtonSprite::getPointForPositionIndex(PositionIndex positionIndex)
{
    return Point(positionIndex.x, positionIndex.y);
}

// 位置インデックスからタグを取得
int ButtonSprite::getGenerateTag(PositionIndex positionIndex)
{
    return BUTTON_TAG + positionIndex.x * 10 + positionIndex.y;
}
