// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: Lightkey-Control

#include "ui.h"
#include "ui_helpers.h"

int login_flag = 0;
int UI_CONTAINER1_ORIG_HEIGHT;
///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_CueButton1;
lv_obj_t * ui_lblCue1;
lv_obj_t * ui_CueButton2;
lv_obj_t * ui_lblCue2;
lv_obj_t * ui_CueButton3;
lv_obj_t * ui_lblCue3;
lv_obj_t * ui_CueButton4;
lv_obj_t * ui_lblCue4;
lv_obj_t * ui_CueButton5;
lv_obj_t * ui_lblCue5;
lv_obj_t * ui_CueButton6;
lv_obj_t * ui_lblCue6;
lv_obj_t * ui_HomeButton1;
void ui_event_SettingsButton1(lv_event_t * e);
lv_obj_t * ui_SettingsButton1;
lv_obj_t * ui_WifiIcon1;
lv_obj_t * ui_MidiIcon1;
lv_obj_t * ui_tip1;
lv_obj_t * ui_lblTip1;


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t * ui_Screen2;
void ui_event_HomeButton2(lv_event_t * e);
lv_obj_t * ui_HomeButton2;
lv_obj_t * ui_SettingsButton2;
lv_obj_t * ui_Container1;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_lblSSID;
void ui_event_txtSSID(lv_event_t * e);
lv_obj_t * ui_txtSSID;
lv_obj_t * ui_lblPassword;
void ui_event_txtPassword(lv_event_t * e);
lv_obj_t * ui_txtPassword;
void ui_event_ConnectButton(lv_event_t * e);
lv_obj_t * ui_ConnectButton;
lv_obj_t * ui_lblConnectBtn;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_lblRemoteIP;
void ui_event_txtRemoteIP(lv_event_t * e);
lv_obj_t * ui_txtRemoteIP;
lv_obj_t * ui_Label1;
lv_obj_t * ui_SaveButton;
lv_obj_t * ui_lblSaveButton;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui_WifiIcon2;
lv_obj_t * ui_MidiIcon2;
lv_obj_t * ui_tip2;
lv_obj_t * ui_lblTip2;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_714157327[1] = {&ui_img_2037930486};
const lv_img_dsc_t * ui_imgset_535857063[1] = {&ui_img_443613123};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_SettingsButton1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen2_screen_init);
    }
}
void ui_event_HomeButton2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen1_screen_init);
    }
}
void ui_event_txtSSID(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        _ui_keyboard_set_target(ui_Keyboard1,  ui_txtSSID);
        lv_obj_set_style_max_height(ui_Keyboard1, LV_HOR_RES * 2 / 3, 0);
        lv_obj_update_layout(ui_Container1);   /*Be sure the sizes are recalculated*/
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT - lv_obj_get_height(ui_Keyboard1));
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        // lv_obj_scroll_to_view_recursive(target, LV_ANIM_OFF);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        _ui_keyboard_set_target(ui_Keyboard1,  NULL);
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT);
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_indev_reset(NULL, target);
        
    }
    else if(event_code == LV_EVENT_READY || event_code == LV_EVENT_CANCEL) {
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT);
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_obj_clear_state(target, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, target);   /*To forget the last clicked object to make it focusable again*/
    }
}
void ui_event_txtPassword(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        _ui_keyboard_set_target(ui_Keyboard1,  ui_txtPassword);
        lv_obj_set_style_max_height(ui_Keyboard1, LV_HOR_RES * 2 / 3, 0);
        lv_obj_update_layout(ui_Container1);   /*Be sure the sizes are recalculated*/
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT - lv_obj_get_height(ui_Keyboard1));
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        lv_obj_scroll_to_view_recursive(target, LV_ANIM_OFF);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        _ui_keyboard_set_target(ui_Keyboard1,  NULL);
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT);
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_indev_reset(NULL, target);
        
    }
    else if(event_code == LV_EVENT_READY || event_code == LV_EVENT_CANCEL) {
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT);
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_obj_clear_state(target, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, target);   /*To forget the last clicked object to make it focusable again*/
    }
}
void ui_event_ConnectButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        login_flag = 1;
    }
}
void ui_event_txtRemoteIP(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        _ui_keyboard_set_target(ui_Keyboard1,  ui_txtRemoteIP);
        lv_obj_set_style_max_height(ui_Keyboard1, LV_HOR_RES * 2 / 3, 0);
        lv_obj_update_layout(ui_Container1);   /*Be sure the sizes are recalculated*/
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT - lv_obj_get_height(ui_Keyboard1));
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        lv_obj_scroll_to_view_recursive(target, LV_ANIM_OFF);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        _ui_keyboard_set_target(ui_Keyboard1,  NULL);
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT);
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_indev_reset(NULL, target);
        
    }
    else if(event_code == LV_EVENT_READY || event_code == LV_EVENT_CANCEL) {
        lv_obj_set_height(ui_Container1, UI_CONTAINER1_ORIG_HEIGHT);
        _ui_flag_modify(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_obj_clear_state(target, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, target);   /*To forget the last clicked object to make it focusable again*/
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    UI_CONTAINER1_ORIG_HEIGHT = lv_obj_get_height(ui_Container1);
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
