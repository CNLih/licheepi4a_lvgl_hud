// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: Futuristic_Ebike

#ifndef _FUTURISTIC_EBIKE_UI_H
#define _FUTURISTIC_EBIKE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void ui_event_Driving(lv_event_t * e);

extern lv_obj_t * ui_main;
extern lv_obj_t * ui_Driving;
extern lv_obj_t * ui_Speed_Number_2;
extern lv_obj_t * ui_Speed_Number_1;
extern lv_obj_t * ui_Label_Speed;
extern lv_obj_t * ui_Label_kmh1;


LV_FONT_DECLARE(ui_font_Big);
LV_FONT_DECLARE(ui_font_Medium);
LV_FONT_DECLARE(ui_font_Number);
LV_FONT_DECLARE(ui_font_Small);


void ui_main_screen_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
