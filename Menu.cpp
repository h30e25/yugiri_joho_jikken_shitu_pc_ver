#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Func.h"

const static int PLAY_Y = 240;
const static int TEBO_Y = 260;
const static int HIRAZARU_Y = 280;
const static int EXPLANATION_Y = 300;
const static int RANKING_Y = 320;


typedef enum {
    eMenu_TEBO,
    eMenu_HIRAZARU,
    eMenu_EXPLANATION,    //操作説明
    eMenu_RANKING,
    eMenu_Num,        //本項目の数
} eMenu;

int imageHandle = LoadGraph("images/1.png");

static int NowSelect = eMenu_TEBO;    //現在の選択状態(初期はゲーム選択中)
//static i
//更新
void Menu_Update() {
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
        NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
    }
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
    }       
    print_test();
 

    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
        switch (NowSelect) {//現在選択中の状態によって処理を分岐
        case eMenu_TEBO:
            CurrentPlayData_Initialize();
            UseEquipment_Update(tebo);
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Game);
            break;
        case eMenu_HIRAZARU:
            CurrentPlayData_Initialize();
            UseEquipment_Update(hirazaru);
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Game);
            break;
        case eMenu_EXPLANATION:
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Config);
            break;
        case eMenu_RANKING:
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Ranking);
        }
    }
}

//描画
void Menu_Draw() {
    int imageHandle = LoadGraph("images/1.png");
    DrawGraph(0, 0, imageHandle, TRUE); // データハンドルを使って画像を描画

    DrawString(200, 150, "メニュー画面です。", GetColor(255, 255, 255));
    DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
    DrawString(280, PLAY_Y, "プレイ", GetColor(255, 255, 255));
    DrawString(280, TEBO_Y, "てぼ", GetColor(255, 255, 255));
    DrawString(280, HIRAZARU_Y, "平ザル", GetColor(255, 255, 255));
    DrawString(280, EXPLANATION_Y, "操作説明", GetColor(255, 255, 255));
    DrawString(280, RANKING_Y, "ランキング", GetColor(255, 255, 255));
    DrawFormatString(0, 400, GetColor(255, 255, 255), "%d", NowSelect);
    int y = 0;
    switch (NowSelect) {//現在の選択状態に従って処理を分岐
    case eMenu_TEBO:
        y = TEBO_Y;
        break;
    case eMenu_HIRAZARU:
        y = HIRAZARU_Y;
        break;
    case eMenu_EXPLANATION:
        y = EXPLANATION_Y;
        break;
    case eMenu_RANKING:
        y = RANKING_Y;
        break;
    }
    DrawString(250, y, "■", GetColor(255, 255, 255));
}
