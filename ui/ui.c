
#include "ui.h"

///////////////////// VARIABLES ////////////////////
void ui_event_Driving(lv_event_t * e);
lv_obj_t * ui_main;
lv_obj_t * ui_Speed;
lv_obj_t * ui_Speed_Number_1;
lv_obj_t * ui_Speed_Number_2;
lv_obj_t * ui_Speed_num;
lv_obj_t * ui_Speed_kmh1;
lv_obj_t * ui_Speed_meter;
static char speed_str[10];

lv_obj_t * ui_Gas;
lv_obj_t * ui_Gas_Number_1;
lv_obj_t * ui_Gas_Number_2;
lv_obj_t * ui_Gas_num;
lv_obj_t * ui_Gas_kmh1;
lv_obj_t * ui_Gas_meter;
static char gas_str[10];

lv_obj_t * ui_Icon;
lv_obj_t * handbrake;
lv_obj_t * belt;

static void set_value_speed(void * indic, int32_t v)
{
    if (v == 100)
        if (lv_obj_has_flag(handbrake, LV_OBJ_FLAG_HIDDEN))
            lv_obj_clear_flag(handbrake, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(handbrake, LV_OBJ_FLAG_HIDDEN);

    if (v == 100)
        if (lv_obj_has_flag(belt, LV_OBJ_FLAG_HIDDEN))
            lv_obj_clear_flag(belt, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(belt, LV_OBJ_FLAG_HIDDEN);

    lv_meter_set_indicator_value(ui_Speed_meter, indic, v);
    sprintf(speed_str, "%d\0", v);
    lv_label_set_text(ui_Speed_Number_1, speed_str);
    lv_label_set_text(ui_Speed_Number_2, speed_str);
}

static void set_value_gas(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(ui_Gas_meter, indic, 100 - v);
    sprintf(gas_str, "%d\0", 100 - v);
    lv_label_set_text(ui_Gas_Number_1, gas_str);
    lv_label_set_text(ui_Gas_Number_2, gas_str);
}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Driving(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
    }
}

///////////////////// SCREENS ////////////////////

void ui_main_screen_init(void)
{
    ui_main = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_main, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

//////////   MID   ////////

    handbrake = lv_img_create(ui_main);
    lv_img_set_src(handbrake, "ui/handbrake_icon.png");
    lv_obj_set_align(handbrake, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_x(handbrake, -200);
    lv_obj_set_y(handbrake, -60);

    belt = lv_img_create(ui_main);
    lv_img_set_src(belt, "ui/belt_icon.png");
    lv_obj_set_align(belt, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_x(belt, 200);
    lv_obj_set_y(belt, -60);

//////////   LEFT   ////////

    ui_Speed = lv_obj_create(ui_main);
    lv_obj_set_width(ui_Speed, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Speed, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_Speed, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_x(ui_Speed, 15);
    lv_obj_set_y(ui_Speed, -10);

    ui_Speed_meter = lv_meter_create(ui_Speed);
    lv_obj_center(ui_Speed_meter);
    lv_obj_set_size(ui_Speed_meter, 400, 400);

    /*Add a scale first*/
    lv_meter_scale_t * speed_scale = lv_meter_add_scale(ui_Speed_meter);
    lv_meter_set_scale_ticks(ui_Speed_meter, speed_scale, 41, 3, 20, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(ui_Speed_meter, speed_scale, 8, 6, 25, lv_color_black(), 10);

    lv_meter_indicator_t * speed_indic;

    /*Add a blue arc to the start*/
    speed_indic = lv_meter_add_arc(ui_Speed_meter, speed_scale, 15, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(ui_Speed_meter, speed_indic, 0);
    lv_meter_set_indicator_end_value(ui_Speed_meter, speed_indic, 20);

    /*Make the tick lines blue at the start of the speed_scale*/
    speed_indic = lv_meter_add_scale_lines(ui_Speed_meter, speed_scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE),
                                     false, 0);
    lv_meter_set_indicator_start_value(ui_Speed_meter, speed_indic, 0);
    lv_meter_set_indicator_end_value(ui_Speed_meter, speed_indic, 20);

    /*Add a red arc to the end*/
    speed_indic = lv_meter_add_arc(ui_Speed_meter, speed_scale, 15, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(ui_Speed_meter, speed_indic, 80);
    lv_meter_set_indicator_end_value(ui_Speed_meter, speed_indic, 100);

    /*Make the tick lines red at the end of the speed_scale*/
    speed_indic = lv_meter_add_scale_lines(ui_Speed_meter, speed_scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false,
                                     0);
    lv_meter_set_indicator_start_value(ui_Speed_meter, speed_indic, 80);
    lv_meter_set_indicator_end_value(ui_Speed_meter, speed_indic, 100);

    /*Add a needle line indicator*/
    speed_indic = lv_meter_add_needle_line(ui_Speed_meter, speed_scale, 12, lv_palette_main(LV_PALETTE_GREY), -10);

    ui_Speed_Number_2 = lv_label_create(ui_Speed);
    lv_obj_set_width(ui_Speed_Number_2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Speed_Number_2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Speed_Number_2, 0);
    lv_obj_set_y(ui_Speed_Number_2, 0);
    lv_obj_set_align(ui_Speed_Number_2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Speed_Number_2, "50");
    lv_obj_set_style_text_color(ui_Speed_Number_2, lv_color_hex(0x47230B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Speed_Number_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Speed_Number_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Speed_Number_2, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Speed_Number_1 = lv_label_create(ui_Speed);
    lv_obj_set_width(ui_Speed_Number_1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Speed_Number_1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Speed_Number_1, -6);
    lv_obj_set_y(ui_Speed_Number_1, 0);
    lv_obj_set_align(ui_Speed_Number_1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Speed_Number_1, "50");
    lv_obj_set_style_text_color(ui_Speed_Number_1, lv_color_hex(0xFFE69C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Speed_Number_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Speed_Number_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Speed_Number_1, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Speed_num = lv_label_create(ui_Speed);
    lv_obj_set_width(ui_Speed_num, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Speed_num, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Speed_num, 16);
    lv_obj_set_y(ui_Speed_num, -66);
    lv_obj_set_align(ui_Speed_num, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Speed_num, "Speed");
    lv_obj_set_style_text_color(ui_Speed_num, lv_color_hex(0x94AEB4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Speed_num, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Speed_num, &ui_font_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Speed_kmh1 = lv_label_create(ui_Speed);
    lv_obj_set_width(ui_Speed_kmh1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Speed_kmh1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Speed_kmh1, 19);
    lv_obj_set_y(ui_Speed_kmh1, 58);
    lv_obj_set_align(ui_Speed_kmh1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Speed_kmh1, "km/h");
    lv_obj_set_style_text_color(ui_Speed_kmh1, lv_color_hex(0x94AEB4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Speed_kmh1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Speed_kmh1, &ui_font_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Speed, ui_event_Driving, LV_EVENT_ALL, NULL);

    /*Create an animation to set the value*/
    lv_anim_t a_speed;
    lv_anim_init(&a_speed);
    lv_anim_set_exec_cb(&a_speed, set_value_speed);
    lv_anim_set_var(&a_speed, speed_indic);
    lv_anim_set_values(&a_speed, 0, 100);
    lv_anim_set_time(&a_speed, 8000);
    lv_anim_set_repeat_delay(&a_speed, 100);
    lv_anim_set_playback_time(&a_speed, 500);
    lv_anim_set_playback_delay(&a_speed, 100);
    lv_anim_set_repeat_count(&a_speed, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_speed);

//////////   RIGHT   ////////

    ui_Gas = lv_obj_create(ui_main);
    lv_obj_set_width(ui_Gas, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Gas, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_Gas, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_x(ui_Gas, -15);
    lv_obj_set_y(ui_Gas, -10);

    ui_Gas_meter = lv_meter_create(ui_Gas);
    lv_obj_center(ui_Gas_meter);
    lv_obj_set_size(ui_Gas_meter, 400, 400);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(ui_Gas_meter);
    lv_meter_set_scale_ticks(ui_Gas_meter, scale, 41, 3, 20, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(ui_Gas_meter, scale, 8, 6, 25, lv_color_black(), 10);

    lv_meter_indicator_t * gas_indic;

    /*Add a blue arc to the start*/
    gas_indic = lv_meter_add_arc(ui_Gas_meter, scale, 15, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(ui_Gas_meter, gas_indic, 0);
    lv_meter_set_indicator_end_value(ui_Gas_meter, gas_indic, 20);

    /*Make the tick lines blue at the start of the scale*/
    gas_indic = lv_meter_add_scale_lines(ui_Gas_meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED),
                                     false, 0);
    lv_meter_set_indicator_start_value(ui_Gas_meter, gas_indic, 0);
    lv_meter_set_indicator_end_value(ui_Gas_meter, gas_indic, 20);

    /*Add a red arc to the end*/
    gas_indic = lv_meter_add_arc(ui_Gas_meter, scale, 15, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(ui_Gas_meter, gas_indic, 80);
    lv_meter_set_indicator_end_value(ui_Gas_meter, gas_indic, 100);

    /*Make the tick lines red at the end of the scale*/
    gas_indic = lv_meter_add_scale_lines(ui_Gas_meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false,
                                     0);
    lv_meter_set_indicator_start_value(ui_Gas_meter, gas_indic, 80);
    lv_meter_set_indicator_end_value(ui_Gas_meter, gas_indic, 100);

    /*Add a needle line indicator*/
    gas_indic = lv_meter_add_needle_line(ui_Gas_meter, scale, 12, lv_palette_main(LV_PALETTE_GREY), -10);

    ui_Gas_Number_2 = lv_label_create(ui_Gas);
    lv_obj_set_width(ui_Gas_Number_2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Gas_Number_2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Gas_Number_2, 0);
    lv_obj_set_y(ui_Gas_Number_2, 0);
    lv_obj_set_align(ui_Gas_Number_2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Gas_Number_2, "50");
    lv_obj_set_style_text_color(ui_Gas_Number_2, lv_color_hex(0x47230B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Gas_Number_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Gas_Number_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Gas_Number_2, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Gas_Number_1 = lv_label_create(ui_Gas);
    lv_obj_set_width(ui_Gas_Number_1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Gas_Number_1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Gas_Number_1, -6);
    lv_obj_set_y(ui_Gas_Number_1, 0);
    lv_obj_set_align(ui_Gas_Number_1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Gas_Number_1, "50");
    lv_obj_set_style_text_color(ui_Gas_Number_1, lv_color_hex(0xEA4F40), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Gas_Number_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Gas_Number_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Gas_Number_1, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Gas_num = lv_label_create(ui_Gas);
    lv_obj_set_width(ui_Gas_num, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Gas_num, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Gas_num, 16);
    lv_obj_set_y(ui_Gas_num, -66);
    lv_obj_set_align(ui_Gas_num, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Gas_num, "Gas");
    lv_obj_set_style_text_color(ui_Gas_num, lv_color_hex(0x94AEB4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Gas_num, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Gas_num, &ui_font_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Gas_kmh1 = lv_label_create(ui_Gas);
    lv_obj_set_width(ui_Gas_kmh1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Gas_kmh1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Gas_kmh1, 19);
    lv_obj_set_y(ui_Gas_kmh1, 58);
    lv_obj_set_align(ui_Gas_kmh1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Gas_kmh1, "persent");
    lv_obj_set_style_text_color(ui_Gas_kmh1, lv_color_hex(0x94AEB4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Gas_kmh1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Gas_kmh1, &ui_font_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Create an animation to set the value*/
    lv_anim_t a_gas;
    lv_anim_init(&a_gas);
    lv_anim_set_exec_cb(&a_gas, set_value_gas);
    lv_anim_set_var(&a_gas, gas_indic);
    lv_anim_set_values(&a_gas, 0, 100);
    lv_anim_set_time(&a_gas, 8000);
    lv_anim_set_repeat_delay(&a_gas, 100);
    lv_anim_set_playback_time(&a_gas, 500);
    lv_anim_set_playback_delay(&a_gas, 100);
    lv_anim_set_repeat_count(&a_gas, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a_gas);

    lv_obj_add_event_cb(ui_main, ui_event_Driving, LV_EVENT_ALL, NULL);
}
