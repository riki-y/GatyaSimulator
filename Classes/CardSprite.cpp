//
//  CardSprite.cpp
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/18.
//
//

#include "CardSprite.h"

USING_NS_CC;

// コンストラクタ
CardSprite::CardSprite()
: _positionIndex(0, 0)
{
}

// インスタンス生成
CardSprite* CardSprite::create(PositionIndex positionIndex)
{
    CardSprite* pRet = new CardSprite();
    if (pRet && pRet->init(positionIndex)) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    
    return pRet;
}

// 初期化
bool CardSprite::init(PositionIndex positionIndex)
{
    if (!Sprite::initWithFile("card_back.png")) {
        return false;
    }
    
    setPositionIndex(positionIndex);
    
    return true;
}

// 位置インデックスを返す
CardSprite::PositionIndex CardSprite::getPositionIndex()
{
    return _positionIndex;
}

// 位置インデックスとタグを変更する
void CardSprite::setPositionIndex(PositionIndex positionIndex)
{
    // 位置インデックスを保持する
    _positionIndex = positionIndex;
    // 位置を変更する
    setPosition(getPointForPositionIndex(_positionIndex));
    // タグをセットする
    setTag(getGenerateTag(_positionIndex));
}

// 位置インデックスからPointを取得
Point CardSprite::getPointForPositionIndex(PositionIndex positionIndex)
{
    return Point(positionIndex.x, positionIndex.y);
}

void CardSprite::setScale(float scale)
{
    cocos2d::Sprite::setScale(scale, scale);
    _scale = scale;
}

float CardSprite::getScale()
{
    return _scale;
}

// 位置インデックスからタグを取得
int CardSprite::getGenerateTag(PositionIndex positionIndex)
{
    return CARD_TAG + positionIndex.x * 10 + positionIndex.y;
}

void CardSprite::reverseCard(string filePath)
{
    _filePath = filePath;
    auto scale1 = ScaleTo::create(0.1, 0, _scale);
    auto func = CallFunc::create([&]() {
        setTexture(_filePath);
    });
    auto scale2 = ScaleTo::create(0.1, _scale, _scale);
    
    auto seq = Sequence::create(scale1, func, scale2, NULL);
    
    runAction(seq);
}
