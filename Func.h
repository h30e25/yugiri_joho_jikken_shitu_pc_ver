#pragma once


typedef enum {
	init,
    tebo,
    hirazaru
} eKind;

typedef struct
{
	int startTime;
	int time;
	int score;
	int equipment;
} SaveData;

void sleep(int ms);

void timer(int second);

int Time_Get();
void Time_Update();
void Time_Draw(int x, int y, int cr);
void Time_Finalize();

void ScoreV_Update();
int ScoreV_Get();
void ScoreV_Finalize();

int UseEquipment_Get();
void UseEquipment_Update(eKind kind);
void UseEquipment_Draw(int x, int y, int cr);

int SceneChangeFlag_Get();
void SceneChangeFlag_Allow();
void SceneChangeFlag_Forbid();

SaveData CurrentPlayData_Get();
void CurrentPlayData_Initialize();

void AllPlayData_Update();
void AllPlayData_Draw(int x, int y);

void Enter_Sound();

int sensor1();

void Opening_Sound();


void serial_initialize();
char get_buf_h8maikon();
char get_buf_shogeki();
void send_current_equipment();


void print_test();