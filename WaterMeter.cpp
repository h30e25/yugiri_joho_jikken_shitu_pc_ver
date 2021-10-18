#include "DxLib.h"
#include "WaterMeter.h"
#include "Sound.h"

void WaterMeter_Show(int box_number, int start_x, int start_y, int box_height, int space, int box_width, int si) {
    int box_sx;
    int box_sy;
    for (int i = 0; i < box_number; i++) {
        box_sx = start_x;
        box_sy = start_y + (box_height + space) * i;
        if (si <= i && i <= 4) {
            DrawBox(box_sx, box_sy, box_sx + box_width, box_sy + box_height, GetColor(0, 133, 201), TRUE);
        }
    }
}

void WaterMeter_Calc(int water, int start_x, int start_y, int box_number, int box_width, int box_height, int space) {
    if (1 <= water && water <= 20) {
        WaterMeter_Show(box_number, start_x, start_y, box_height, space, box_width, 4);
    }
    else if (20 <= water && water <= 39) {
        WaterMeter_Show(box_number, start_x, start_y, box_height, space, box_width, 3);
    }
    else if (40 <= water && water <= 59) {
        WaterMeter_Show(box_number, start_x, start_y, box_height, space, box_width, 2);
    }
    else if (60 <= water && water <= 79) {
        WaterMeter_Show(box_number, start_x, start_y, box_height, space, box_width, 1);
    }
    else if (80 <= water && water <= 100) {
        WaterMeter_Show(box_number, start_x, start_y, box_height, space, box_width, 0);
    }
}

void WaterMeter_Sound(int water) {
    switch (water) {
    case 80:
        Enter_Sound();
        break;
    case 60:
        Enter_Sound();
        break;
    case 40:
        Enter_Sound();
        break;
    case 20:
        Enter_Sound();
        break;
    case 1:
        static int Handle = LoadSoundMem("sounds/Š½º‚Æ”Žè.mp3");
        PlaySoundMem(Handle, DX_PLAYTYPE_BACK);
        break;
    }
}