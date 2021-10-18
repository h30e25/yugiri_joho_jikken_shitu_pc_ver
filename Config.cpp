#include "Config.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Func.h"

static int mImageHandle;    //画像ハンドル格納用変数

//初期化
void Config_Initialize() {
    mImageHandle = LoadGraph("images/1.png");//画像のロード
    LoadGraphScreen(50, 100, "images/1.png", TRUE); // 画像を描画する
}

//終了処理
void Config_Finalize() {
    DeleteGraph(mImageHandle);//画像の解放
}
//更新
void Config_Update() {
    if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {//Escキーが押されていたら
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
    }
}

//描画
void Config_Draw() {
    DrawString(0, 0, "操作説明画面です。", GetColor(255, 255, 255));
    DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}