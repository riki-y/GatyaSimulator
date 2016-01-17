//
//  GirlsSelectScene.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/10.
//
//

#ifndef __GatyaSimulator__GirlsSelectScene__
#define __GatyaSimulator__GirlsSelectScene__

#include "cocos2d.h"
#include <string>

using namespace std;
using namespace cocos2d;

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ
#define CARD_WIDTH 576
#define CARD_HEIGHT 720

class GirlsSelectScene : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_Background,
        Z_CARD,
        Z_COVER,
        Z_BUTTON
    };
    
    void craftCardList(); // カード一覧を作る
    void confirmCard(); // カードの確認
    void movedRightCard(); // カードを右位置に変更
    void movedLeftCard(); // カードを左位置に変更
    
    vector<Sprite*> cardSprites;
    int selectCardNum = 0;
    int selectCardMaxNum;
    cocos2d::Vec2 _startLocation;
    
    vector<string> girlList = {
        "sr_card/sr_anastasia.png",
        "sr_card/sr_anzu.png",
        "sr_card/sr_hotaru.png",
        "sr_card/sr_izumi.png",
        "sr_card/sr_kaede.png",
        "sr_card/sr_koume.png",
        "sr_card/sr_kozue.png",
        "sr_card/sr_mayu.png",
        "sr_card/sr_michiru.png",
        "sr_card/sr_nina.png",
        "sr_card/sr_nono.png",
        "sr_card/sr_sachiko.png",
        "sr_card/sr_sana.png",
        "sr_card/sr_shin.png",
        "sr_card/sr_yukimi.png",
        "sr_card/sr_yuuki.png",
        "sr_card/sr_yuzu.png",
    };
    
public:
    GirlsSelectScene(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GirlsSelectScene); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
};

#endif /* defined(__GatyaSimulator__GirlsSelectScene__) */
