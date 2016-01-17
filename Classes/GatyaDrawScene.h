//
//  GatyaDrawScene.h
//  GatyaSimulator
//
//  Created by 吉田　理貴 on 2016/01/17.
//
//

#ifndef __GatyaSimulator__GatyaDrawScene__
#define __GatyaSimulator__GatyaDrawScene__

#include "cocos2d.h"
#include <string>
#include "CardSprite.h"

using namespace std;
using namespace cocos2d;

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ
#define SR_CARD_NUM 17
#define R_CARD_NUM 137

#define CARD_WIDTH 576
#define CARD_HEIGHT 720

struct Card
{
    string filePath;
};

struct PosIndex
{
    int x;
    int y;
};

class GatyaDrawScene : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_BACKGROUND,
        Z_CARD,
    };
    
    enum Tag {
        T_BACKGROUND,
        T_CARD,
    };
    
    vector<string> SRGirlList = {
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
    
    vector<string> RGirlList = {
        "r_card/r_ai.png",
        "r_card/r_aiko.png",
        "r_card/r_airi.png",
        "r_card/r_akiha.png",
        "r_card/r_anastasia.png",
        "r_card/r_anzu.png",
        "r_card/r_aoi.png",
        "r_card/r_airsa.png",
        "r_card/r_arisu.png",
        "r_card/r_asuka.png",
        "r_card/r_atsumi.png",
        "r_card/r_aya.png",
        "r_card/r_ayuna.png",
        "r_card/r_azuki.png",
        "r_card/r_cathy.png",
        "r_card/r_chiaki.png",
        "r_card/r_chie.png",
        "r_card/r_chieri.png",
        "r_card/r_chika.png",
        "r_card/r_chizuru.png",
        "r_card/r_clarice.png",
        "r_card/r_ema.png",
        "r_card/r_emi.png",
        "r_card/r_frederica.png",
        "r_card/r_fuka.png",
        "r_card/r_fumika.png",
        "r_card/r_hajime.png",
        "r_card/r_haru.png",
        "r_card/r_haruna.png",
        "r_card/r_helen.png",
        "r_card/r_hijiri.png",
        "r_card/r_hikaru.png",
        "r_card/r_hina.png",
        "r_card/r_hinako.png",
        "r_card/r_hiromi.png",
        "r_card/r_hitomi.png",
        "r_card/r_honami.png",
        "r_card/r_honoka.png",
        "r_card/r_hotaru.png",
        "r_card/r_ibuki.png",
        "r_card/r_itsuki.png",
        "r_card/r_izumi.png",
        "r_card/r_kaede.png",
        "r_card/r_kai.png",
        "r_card/r_kanade.png",
        "r_card/r_kanna.png",
        "r_card/r_kaoru.png",
        "r_card/r_karen.png",
        "r_card/r_karin.png",
        "r_card/r_kiyomi.png",
        "r_card/r_koharu.png",
        "r_card/r_kotoka.png",
        "r_card/r_koume.png",
        "r_card/r_kozue.png",
        "r_card/r_kumiko.png",
        "r_card/r_kurumi.png",
        "r_card/r_layla.png",
        "r_card/r_mahiru.png",
        "r_card/r_mai.png",
        "r_card/r_makino.png",
        "r_card/r_marina.png",
        "r_card/r_mary.png",
        "r_card/r_mayu.png",
        "r_card/r_megumi.png",
        "r_card/r_michiru.png",
        "r_card/r_mika.png",
        "r_card/r_miku.png",
        "r_card/r_mirei.png",
        "r_card/r_misaki.png",
        "r_card/r_miu.png",
        "r_card/r_miyabi.png",
        "r_card/r_miyako.png",
        "r_card/r_miyo.png",
        "r_card/r_miyu.png",
        "r_card/r_miyuki.png",
        "r_card/r_mizuki.png",
        "r_card/r_mutsumi.png",
        "r_card/r_naho.png",
        "r_card/r_nana.png",
        "r_card/r_nao.png",
        "r_card/r_natsuki.png",
        "r_card/r_natsumi.png",
        "r_card/r_nene.png",
        "r_card/r_noa.png",
        "r_card/r_nono.png",
        "r_card/r_otoha.png",
        "r_card/r_reina.png",
        "r_card/r_rena.png",
        "r_card/r_riina.png",
        "r_card/r_rika.png",
        "r_card/r_rin.png",
        "r_card/r_rina.png",
        "r_card/r_risa.png",
        "r_card/r_rumi.png",
        "r_card/r_ryo.png",
        "r_card/r_sae.png",
        "r_card/r_saki.png",
        "r_card/r_sakura.png",
        "r_card/r_sana.png",
        "r_card/r_saori.png",
        "r_card/r_sarina.png",
        "r_card/r_saya.png",
        "r_card/r_seira.png",
        "r_card/r_setsuna.png",
        "r_card/r_shiki.png",
        "r_card/r_shino.png",
        "r_card/r_shinobu.png",
        "r_card/r_shiori.png",
        "r_card/r_shizuku.png",
        "r_card/r_suzuho.png",
        "r_card/r_syoko.png",
        "r_card/r_syuko.png",
        "r_card/r_takumi.png",
        "r_card/r_tamami.png",
        "r_card/r_tomo.png",
        "r_card/r_tomoe.png",
        "r_card/r_tomoka.png",
        "r_card/r_tsubaki.png",
        "r_card/r_tsukasa.png",
        "r_card/r_umi.png",
        "r_card/r_uzuki.png",
        "r_card/r_yasuha.png",
        "r_card/r_yoko.png",
        "r_card/r_yoriko.png",
        "r_card/r_yui.png",
        "r_card/r_yuka.png",
        "r_card/r_yukari.png",
        "r_card/r_yuki.png",
        "r_card/r_yukimi.png",
        "r_card/r_yuko.png",
        "r_card/r_yume.png",
        "r_card/r_yumi.png",
        "r_card/r_yuriko.png",
        "r_card/r_yuu.png",
        "r_card/r_yuuki.png",
        "r_card/r_yuzu.png",
    };
    
    Card _card;
    CardSprite* _cardSprite;
    
    void initCard();
    CardSprite* createCard(CardSprite::PositionIndex positionIndex);
    
    bool isSRCard();
    void getTouchCard(Point touchPos);
    void moveCard();
    
public:
    GatyaDrawScene(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GatyaDrawScene); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__GatyaSimulator__GatyaDrawScene__) */
