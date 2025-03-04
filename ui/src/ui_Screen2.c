// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: Lightkey-Control

#include "ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0x323232), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HomeButton2 = lv_imgbtn_create(ui_Screen2);
    lv_imgbtn_set_src(ui_HomeButton2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icn_home_png, NULL);
    lv_imgbtn_set_src(ui_HomeButton2, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icn_home_png, NULL);
    lv_imgbtn_set_src(ui_HomeButton2, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icn_home_png, NULL);
    lv_obj_set_height(ui_HomeButton2, 35);
    lv_obj_set_width(ui_HomeButton2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_HomeButton2, 10);
    lv_obj_set_y(ui_HomeButton2, 10);
    lv_obj_set_style_img_recolor(ui_HomeButton2, lv_color_hex(0x2095F6), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_HomeButton2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui_HomeButton2, lv_color_hex(0x5A5A5A), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_img_recolor_opa(ui_HomeButton2, 200, LV_PART_MAIN | LV_STATE_DISABLED);

    ui_SettingsButton2 = lv_imgbtn_create(ui_Screen2);
    lv_imgbtn_set_src(ui_SettingsButton2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icn_settings_wht_sm_png, NULL);
    lv_imgbtn_set_src(ui_SettingsButton2, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icn_settings_wht_sm_png, NULL);
    lv_imgbtn_set_src(ui_SettingsButton2, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icn_settings_wht_sm_png, NULL);
    lv_obj_set_height(ui_SettingsButton2, 35);
    lv_obj_set_width(ui_SettingsButton2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SettingsButton2, -10);
    lv_obj_set_y(ui_SettingsButton2, 10);
    lv_obj_set_align(ui_SettingsButton2, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_style_img_recolor(ui_SettingsButton2, lv_color_hex(0x84C0F1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_SettingsButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_SettingsButton2, lv_color_hex(0x2095F6), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_SettingsButton2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui_SettingsButton2, lv_color_hex(0x5A5A5A), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_img_recolor_opa(ui_SettingsButton2, 200, LV_PART_MAIN | LV_STATE_DISABLED);

    ui_Container1 = lv_obj_create(ui_Screen2);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 468);
    lv_obj_set_height(ui_Container1, 259);
    lv_obj_set_x(ui_Container1, 0);
    lv_obj_set_y(ui_Container1, 54);
    lv_obj_set_align(ui_Container1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_scroll_dir(ui_Container1, LV_DIR_VER);

    ui_Panel1 = lv_obj_create(ui_Container1);
    lv_obj_set_width(ui_Panel1, 428);
    lv_obj_set_height(ui_Panel1, 103);
        lv_obj_set_align(ui_Panel1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblSSID = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_lblSSID, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblSSID, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblSSID, 0);
    lv_obj_set_y(ui_lblSSID, 5);
    lv_label_set_text(ui_lblSSID, "WiFi SSID");

    ui_txtSSID = lv_textarea_create(ui_Panel1);
    lv_obj_set_width(ui_txtSSID, 196);
    lv_obj_set_height(ui_txtSSID, LV_SIZE_CONTENT);    /// 31
    lv_obj_set_x(ui_txtSSID, 81);
    lv_obj_set_y(ui_txtSSID, -5);
    lv_textarea_set_placeholder_text(ui_txtSSID, "SSID");
    lv_textarea_set_one_line(ui_txtSSID, true);
    lv_obj_set_style_text_font(ui_txtSSID, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_lblPassword = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_lblPassword, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblPassword, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblPassword, 0);
    lv_obj_set_y(ui_lblPassword, 50);
    lv_label_set_text(ui_lblPassword, "WiFi Pass");

    ui_txtPassword = lv_textarea_create(ui_Panel1);
    lv_obj_set_width(ui_txtPassword, 196);
    lv_obj_set_height(ui_txtPassword, LV_SIZE_CONTENT);    /// 31
    lv_obj_set_x(ui_txtPassword, 81);
    lv_obj_set_y(ui_txtPassword, 40);
    lv_textarea_set_placeholder_text(ui_txtPassword, "Password");
    lv_textarea_set_one_line(ui_txtPassword, true);
    lv_textarea_set_password_mode(ui_txtPassword, true);
    lv_obj_set_style_text_font(ui_txtPassword, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_ConnectButton = lv_btn_create(ui_Panel1);
    lv_obj_set_width(ui_ConnectButton, 100);
    lv_obj_set_height(ui_ConnectButton, 50);
    lv_obj_set_align(ui_ConnectButton, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_ConnectButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblConnectBtn = lv_label_create(ui_ConnectButton);
    lv_obj_set_width(ui_lblConnectBtn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblConnectBtn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblConnectBtn, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblConnectBtn, "Connect");

    ui_Panel2 = lv_obj_create(ui_Container1);
    lv_obj_set_width(ui_Panel2, 428);
    lv_obj_set_height(ui_Panel2, 86);
    lv_obj_set_x(ui_Panel2, 0);
    lv_obj_set_y(ui_Panel2, 108);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblRemoteIP = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_lblRemoteIP, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblRemoteIP, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblRemoteIP, 0);
    lv_obj_set_y(ui_lblRemoteIP, 34);
    lv_label_set_text(ui_lblRemoteIP, "IP Address");

    ui_txtRemoteIP = lv_textarea_create(ui_Panel2);
    lv_obj_set_width(ui_txtRemoteIP, 196);
    lv_obj_set_height(ui_txtRemoteIP, LV_SIZE_CONTENT);    /// 31
    lv_obj_set_x(ui_txtRemoteIP, 81);
    lv_obj_set_y(ui_txtRemoteIP, 23);
    if("0123456789." == "") lv_textarea_set_accepted_chars(ui_txtRemoteIP, NULL);
    else lv_textarea_set_accepted_chars(ui_txtRemoteIP, "0123456789.");
    lv_textarea_set_placeholder_text(ui_txtRemoteIP, "192.168.x.x");
    lv_textarea_set_one_line(ui_txtRemoteIP, true);
    lv_obj_set_style_text_font(ui_txtRemoteIP, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_Label1 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, -5);
    lv_label_set_text(ui_Label1, "Lightkey Computer");

    ui_SaveButton = lv_btn_create(ui_Container1);
    lv_obj_set_width(ui_SaveButton, 428);
    lv_obj_set_height(ui_SaveButton, 50);
    lv_obj_set_x(ui_SaveButton, 0);
    lv_obj_set_y(ui_SaveButton, 198);
    lv_obj_set_align(ui_SaveButton, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_SaveButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SaveButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblSaveButton = lv_label_create(ui_SaveButton);
    lv_obj_set_width(ui_lblSaveButton, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblSaveButton, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblSaveButton, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblSaveButton, "Save Settings");

    ui_Keyboard1 = lv_keyboard_create(ui_Screen2);
    lv_obj_set_width(ui_Keyboard1, 431);
    lv_obj_set_height(ui_Keyboard1, 136);
    lv_obj_set_x(ui_Keyboard1, 0);
    lv_obj_set_y(ui_Keyboard1, -5);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_WifiIcon2 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_WifiIcon2, &ui_img_443613123);
    lv_obj_set_width(ui_WifiIcon2, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_height(ui_WifiIcon2, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_WifiIcon2, -20);
    lv_obj_set_y(ui_WifiIcon2, 3);
    lv_obj_set_align(ui_WifiIcon2, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_WifiIcon2, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WifiIcon2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_WifiIcon2, 150);

    ui_MidiIcon2 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_MidiIcon2, &ui_img_2037930486);
    lv_obj_set_width(ui_MidiIcon2, LV_SIZE_CONTENT);   /// 48
    lv_obj_set_height(ui_MidiIcon2, LV_SIZE_CONTENT);    /// 48
    lv_obj_set_x(ui_MidiIcon2, 20);
    lv_obj_set_y(ui_MidiIcon2, 3);
    lv_obj_set_align(ui_MidiIcon2, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_MidiIcon2, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_MidiIcon2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_MidiIcon2, 150);

    ui_tip2 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_tip2, 266);
    lv_obj_set_height(ui_tip2, 28);
    lv_obj_set_x(ui_tip2, 0);
    lv_obj_set_y(ui_tip2, -132);
    lv_obj_set_align(ui_tip2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_tip2, lv_color_hex(0x313031), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tip2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblTip2 = lv_label_create(ui_tip2);
    lv_obj_set_width(ui_lblTip2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblTip2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblTip2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblTip2, "Connecting to WiFi...");
    lv_obj_set_style_text_color(ui_lblTip2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblTip2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_HomeButton2, ui_event_HomeButton2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_txtSSID, ui_event_txtSSID, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_txtPassword, ui_event_txtPassword, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ConnectButton, ui_event_ConnectButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_txtRemoteIP, ui_event_txtRemoteIP, LV_EVENT_ALL, NULL);

}
