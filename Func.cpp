#include "Func.h"
#include "DxLib.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "SerialClass.h"

//using std::this_thread::sleep_for;

static int sceneChangeFlag = 0; //0:画面遷移を禁止 1:画面遷移を許可

static SaveData currentPlayData;

static int imageHandle = LoadGraph("images/1.png");

static SaveData allPlayData[100] = {};

static int playDataNumber = 0; //allPlayDataの要素数を管理する変数

/*
void sleep(int ms) {
	sleep_for(std::chrono::milliseconds(ms));
}
*/

void timer(int second) {
    int timediff = 1;
    LONGLONG timelimit = GetNowHiPerformanceCount() + second * 1000000;
    while (timediff > 0) {
        timediff = int(timelimit - GetNowHiPerformanceCount());
        ClearDrawScreen();
        DrawFormatString(5, 5, GetColor(255, 255, 255), "%02d'%02d'%d%d", timediff / 60000000, (timediff % 60000000) / 1000000, ((timediff % 60000000) % 1000000) / 100000, (((timediff % 60000000) % 1000000) % 100000) / 10000);
        ScreenFlip();
    }
}




int Time_Get() {
    return(currentPlayData.time);
}

void Time_Draw(int x, int y, int cr) {
    //DrawFormatString(x, y, cr, "経過時間(ミリ秒): %d", currentPlayData.time);
    DrawFormatString(x, y+100, cr, "経過時間(h:m:s): %02d:%02d:%02d", (currentPlayData.time / 1000) /3600, ((currentPlayData.time / 1000) % 3600) / 60, (currentPlayData.time/1000) % 60);
}

void Time_Update() {
    currentPlayData.time = GetNowCount() - currentPlayData.startTime;
}



void ScoreV_Update() {
    switch (currentPlayData.equipment) {
    case tebo:
        currentPlayData.score = 10000 - currentPlayData.time + 10;
        break;
    case hirazaru:
        currentPlayData.score = 10000 - currentPlayData.time + 100;
        break;
    }
    if (currentPlayData.score < 1) {
        currentPlayData.score = 1;
    }
}

int ScoreV_Get() {
    return(currentPlayData.score);
}

void ScoreV_Finalize() {
    currentPlayData.score = 0;
}




int UseEquipment_Get() {
    return(currentPlayData.equipment);
}

void UseEquipment_Update(eKind kind) {
    currentPlayData.equipment = kind;
}

void UseEquipment_Draw(int x, int y, int cr) {
    switch (currentPlayData.equipment) {
    case tebo:
        DrawString(x, y, "てぼモード", cr);
        break;
    case hirazaru:
        DrawString(x, y, "ひらざるモード", cr);
        break;
    }
}



int SceneChangeFlag_Get() {
    return(sceneChangeFlag);
}

void SceneChangeFlag_Allow() {
    sceneChangeFlag = 1;
}

void SceneChangeFlag_Forbid() {
    sceneChangeFlag = 0;
}




SaveData CurrentPlayData_Get() {
    return(currentPlayData);
}

void CurrentPlayData_Initialize() {
    currentPlayData = {
        GetNowCount(),
        0,
        0,
        init
    };
}




void AllPlayData_Update() {
    allPlayData[playDataNumber] = currentPlayData;
    playDataNumber = playDataNumber + 1;
}





int compar(const void* a, const void* b) {
    if (((SaveData*)a)->score < ((SaveData*)b)->score) {
        return 1;
    }
    else {
        return -1;
    }
}

void AllPlayData_Draw(int x, int y) {
    static int cr;
    qsort(allPlayData, 10, sizeof(SaveData), compar);
    DrawString(x, y-20, "順位　時間　スコア　器具", GetColor(255, 255, 255));
    for (int i = 0; i < 10; i++) {
        if (currentPlayData.time == allPlayData[i].time) { //ここの比較方法あまり良くないかも
            cr = GetColor(255, 255, 0);
        }
        else {
            cr = GetColor(255, 255, 255);
        }
        switch (allPlayData[i].equipment) {
        case tebo:
            DrawFormatString(x, y + i * 20, cr, "%d位 %d %d てぼ", i + 1, allPlayData[i].time, allPlayData[i].score);
            break;
        case hirazaru:
            DrawFormatString(x, y + i * 20, cr, "%d位 %d %d ひらざる", i + 1, allPlayData[i].time, allPlayData[i].score);
            break;   
        }
    }
}



void File_Output() {
    FILE* fp = fopen("savedata.dat", "wb");//バイナリファイルを開く
    fwrite(&currentPlayData, sizeof(SaveData), sizeof(currentPlayData) / sizeof(currentPlayData), fp); // SaveData_t構造体の中身を出力
    fclose(fp);
}