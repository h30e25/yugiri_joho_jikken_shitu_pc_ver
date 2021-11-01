#include "Ranking.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Func.h"
//更新

void Ranking_Update() {
    //sleep(100);
    /*
    if (CheckHitKey(KEY_INPUT_RETURN) == 0 && SceneChangeFlag_Get() == 0) {
        SceneChangeFlag_Allow();
    }
    if (CheckHitKey(KEY_INPUT_RETURN) != 0 && SceneChangeFlag_Get() == 1) {
        SceneChangeFlag_Forbid();
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_End);//シーンを終了画面に変更
    }    
    */
    if (get_buf_h8maikon() == 'a') {
        SceneMgr_ChangeScene(eScene_End);
    }

}

//描画
void Ranking_Draw() {
    DrawString(0, 0, "ランキング画面です。", GetColor(255, 255, 255));
    DrawString(0, 20, "Enterキーを押すと終了画面に移る", GetColor(255, 255, 255));
    AllPlayData_Draw(0, 80);
}