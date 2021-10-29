#include "Game.h"
#include "SceneMgr.h"
#include "Func.h"
#include "WaterMeter.h"
#include <math.h>
#include "DxLib.h"
// #include "erslib19.h" //シリアル通信を簡単にしてくれるヘッダファイル

/*
#include <iostream>
#include <chrono>
#include <thread>
using std::this_thread::sleep_for;
*/
#define PI 3.141592654f
static int x;
static int y;

static int water = 100;
unsigned int cr = GetColor(0, 0, 0);
unsigned int background_cr = GetColor(254, 247, 240);
static char c;
static int tebo_image;
static int hirazaru_image;
static int logo_image;
static int count = 0;

//シリアル通信のために必須な変数4つ
/*
#define BUFSIZE 5000
static int com = 5;
static char buf[1000];
static int r;
*/


//シリアル通信を行うための準備と画像読み込み
void Game_Initialize() {
    /*
    r = ERS_Open(com, BUFSIZE, BUFSIZE);    // rs232cのポートをオープンする
    ERS_Config(com, ERS_9600);		// 通信速度を9600bpsにする(デフォルト)    
    */


    tebo_image = LoadGraph("images/いらすとや_てぼ.png");
    hirazaru_image = LoadGraph("images/はいむ_ひらざる.jpg");
    logo_image = LoadGraph("images/fcac755457d6a1c96093e16707ad773c_t.jpeg");
}

void Game_Update() {
    Time_Update();
    /*
    if (ERS_CheckRecv(com) > 0) {  // シリアル通信の受信データあり
        DrawString(200, 100, "受信データあり", cr);
        r = ERS_Recv(com, buf, 1);
        DrawFormatString(200, 120, GetColor(255, 255, 255), "rの値：%d", r);
        c = buf[0];
        DrawFormatString(200, 140, GetColor(255, 255, 255), "buf[0]の値：%c", buf[0]);
        DrawFormatString(200, 160, GetColor(255, 255, 255), "buf[1]の値：%c", buf[1]);

        DrawFormatString(200, 180, GetColor(255, 255, 255), "cの値：%c", c);
        if (buf[0] < 920) {
            DrawString(200, 100, "buf[0]は数値データです", cr);
        }
        switch (buf[0]) {
        case 'l':
            water -= 1;
            break;
        case 'm':
            water -= 5;
            break;
        case 'h':
            water -= 10;
            break;
        }
    }    
    */

    

    if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
        water -= 1;
    }
    if (water <= 0) {
        water = 100;
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_Score);
    }
}

//描画
void Game_Draw() {
    SetBackgroundColor(254, 247, 240);
    int imageHandle = LoadGraph("images/fcac755457d6a1c96093e16707ad773c_t.jpeg");
    //DrawRotaGraph(310, 225, 1.4, 0.0, imageHandle, TRUE); //画像の描画
    SetFontSize(64);
    DrawString(0, 0, "ゲーム画面", cr);
    SetFontSize(20);
    //DrawString(0, 80, "水分メータ", cr);
    WaterMeter_Calc(water, 500, 100, 5, 100, 50, 2);
    DrawFormatString(500, 400, cr, "水分量: %d", water);
    WaterMeter_Sound(water);

    UseEquipment_MoveDraw(100, 100, 0, 50, 10);
    Time_Draw(0, 60, cr);
    count++;
}

void UseEquipment_MoveDraw(int x0, int y0, int dx, int dy, int t) {
    x = x0 + dx * cos(2 * PI / t * count);
    y = y0 + dy * sin(2 * PI / t * count);
    switch (UseEquipment_Get()) {
    case tebo:
        DrawGraph(x, y, tebo_image, TRUE);
        break;
    case hirazaru:
        DrawGraph(x, y, hirazaru_image, TRUE);
        break;
    }
    count++;
}