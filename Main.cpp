#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "Game.h"
#include "Func.h"
#include "Sound.h"
#include "erslib19.h" //シリアル通信を簡単にしてくれるヘッダファイル


//シリアル通信のために必須な変数4つ
#define BUFSIZE 5000
static int com = 1;
static char buf[1000];
static int r;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    int MouseInput;

    ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    r = ERS_Open(com, BUFSIZE, BUFSIZE);    // rs232cのポートをオープンする
    ERS_Config(com, ERS_9600);		// 通信速度を9600bpsにする(デフォルト)
    Game_Initialize(); //シリアル通信の準備
    Sound_Initialize(); //サウンド読み込み（いつでも使える状態にしておく）
    Opening_Sound();
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        Keyboard_Update();
        SceneMgr_Update();
        SceneMgr_Draw();
        if (ERS_CheckRecv(com) > 0) {  // シリアル通信の受信データあり
            DrawString(200, 100, "受信データあり", GetColor(254, 247, 240));
            r = ERS_Recv(com, buf, 1);
            DrawFormatString(200, 120, GetColor(255, 255, 255), "rの値：%d", r);
            DrawFormatString(200, 140, GetColor(255, 255, 255), "buf[0]の値：%c", buf[0]);
            DrawFormatString(200, 160, GetColor(255, 255, 255), "buf[1]の値：%c", buf[1]);

            if (buf[0] < 920) {
                DrawString(200, 100, "buf[0]は数値データです", GetColor(254, 247, 240));
            }
        }

    }

    DxLib_End();
    return 0;
}