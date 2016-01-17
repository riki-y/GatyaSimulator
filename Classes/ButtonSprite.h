//
//  ButtonSprite.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#ifndef __GatyaSimulator__ButtonSprite__
#define __GatyaSimulator__ButtonSprite__

#include "cocos2d.h"

#define BUTTON_SIZE 150
#define BUTTON_TAG 100

using namespace cocos2d;

class ButtonSprite : public cocos2d::Sprite
{
public:
    enum class ButtonType
    {
        Select,
        Cancel,
        Back,
        Retry,
        DrawOneCard,
        DrawTenCard,
        None,
    };
    
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
    
    ButtonSprite(); // コンストラクタ
    static ButtonSprite* create(PositionIndex positionIndex, ButtonType buttonType); // インスタンス生成
    virtual bool init(PositionIndex positionIndex, ButtonType buttonType); // 初期化
    void changeButtonImageTexture(); // ボタンの画像を変更
    void changePushButtonImageTexture(); // 押下ボタンの画像に変更
    std::string getButtonImageFilePath(ButtonType buttonType); // ボタン画像取得
    std::string getPushButtonImageFilePath(); // ボタン押下時の画像取得 
    static cocos2d::Point getPointForPositionIndex(PositionIndex positionIndex); // 位置インデックスからポイントを取得
    static int getGenerateTag(PositionIndex positionIndex); // 位置インデックスからタグを取得
    
    CC_PROPERTY(PositionIndex, _positionIndex, PositionIndex); // 位置インデックス
    CC_SYNTHESIZE(ButtonType, _buttonType, ButtonType); // ボタンの種類
};

#endif /* defined(__GatyaSimulator__ButtonSprite__) */
