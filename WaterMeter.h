#pragma once

void WaterMeter_Show(int box_number, int start_x, int start_y, int box_height, int space, int box_width, int si);
void WaterMeter_Calc(int water, int start_x, int start_y, int box_number, int box_width, int box_height, int space);
void WaterMeter_Sound(int water);
