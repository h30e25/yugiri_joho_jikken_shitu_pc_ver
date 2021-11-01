#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "Game.h"
#include "Func.h"
#include "Sound.h"
// #include "erslib19.h" //シリアル通信を簡単にしてくれるヘッダファイル


//シリアル通信のために必須な変数4つ
/*
#define BUFSIZE 5000
static int com = 1;
static char buf[1000];
static int r;
*/

static int yello = GetColor(255, 241, 0);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    int MouseInput;

    ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    serial_initialize();
    Game_Initialize(); //シリアル通信の準備    

    Sound_Initialize(); //サウンド読み込み（いつでも使える状態にしておく）
    Opening_Sound();
    
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        Keyboard_Update();
        SceneMgr_Update();
        SceneMgr_Draw();
        /*
        DrawString(200, 100, "test", yello);
        int i = 100;
        if (ERS_CheckRecv(com) > 0) {  // シリアル通信の受信データあり
            
            DrawString(200, i, "受信データあり", yello);
            r = ERS_Recv(com, buf, 1);
            set_buf(buf[0]);
            r = get_buf();
            DrawFormatString(200, i + 20, GetColor(255, 255, 255), "rの値：%d", r);
            DrawFormatString(200, i + 40, GetColor(255, 255, 255), "buf[0]の値：%c", buf[0]);
            DrawFormatString(200, i + 60, GetColor(255, 255, 255), "buf[1]の値：%c", buf[1]);
            if (buf[0] < 920) {
                DrawString(200, 100, "buf[0]は数値データです", GetColor(254, 247, 240));
            }
            if (buf[0] == 'a') {
                DrawString(250, i, "aだあああああああああああああああああああ", yello);
            }
        }          
        */
      
    }
    DxLib_End();
    return 0;
}