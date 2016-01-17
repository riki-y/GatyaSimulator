//
//  CardSprite.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/18.
//
//

#ifndef __GatyaSimulator__CardSprite__
#define __GatyaSimulator__CardSprite__

#include "cocos2d.h"
#include <string>

#define CARD_TAG 200

using namespace cocos2d;
using namespace std;

class CardSprite : public cocos2d::Sprite
{
public:
    // 位置インデックス
    struct PositionIndex {
        // コンストラクタ
        PositionIndex() {
            x = 0;
            y = 0;
        }
        
        // コンストラクタ
        PositionIndex(int _x, int _y) {
            x = _x;
            y = _y;
        }
        int x; // x方向のインデックス
        int y; // y方向のインデックス
    };
    
    CardSprite(); // コンストラクタ
    static CardSprite* create(PositionIndex positionIndex); // インスタンス生成
    virtual bool init(PositionIndex positionIndex); // 初期化
    static cocos2d::Point getPointForPositionIndex(PositionIndex positionIndex); // 位置インデックスからポイントを取得
    static int getGenerateTag(PositionIndex positionIndex); // 位置インデックスからタグを取得
    void reverseCard(string filePath);
    string _filePath;
    
    CC_PROPERTY(PositionIndex, _positionIndex, PositionIndex); // 位置インデックス
};

#endif /* defined(__GatyaSimulator__CardSprite__) */
