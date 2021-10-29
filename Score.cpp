#include "Score.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Func.h"
#include <iostream>
#include <string>

using namespace std;

static int cr1 = GetColor(255, 255, 255);
//更新
void Score_Update() {
    ScoreV_Update();
    //sleep(100);

    /*
    if (CheckHitKey(KEY_INPUT_RETURN) != 0) { //エンターキーが押されていたら
        SceneChangeFlag_Forbid();
        AllPlayData_Update();
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_Ranking);//シーンをランキングに変更
    }    
    */

    if (get_buf() == 'a') {
        SceneMgr_ChangeScene(eScene_Ranking);
    }
}

//描画
void Score_Draw() {
    DrawString(0, 0, "スコア画面です。", cr1);
    DrawString(0, 20, "Enterキーを押すとランキング画面に移る", cr1);
    DrawFormatString(0, 40, cr1, "経過時間(ミリ秒): %d", Time_Get());
    DrawFormatString(0, 60, cr1, "スコア: %d", ScoreV_Get());
}