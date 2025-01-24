#include<Arduino.h>
#include <lvgl.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "FT6236.h"
#include <ui.h>
// #include <ui_events.h>
// #include <ui_helpers.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#define APPLEMIDI_INITIATOR
#include <AppleMIDI.h>
#include <Preferences.h>

Preferences preferences;

const int i2c_touch_addr = TOUCH_I2C_ADD;

const char* ssid     = "";     // WIFI
const char* password = ""; // WIFI
char* ssid1     ;
char* password1 ;
char* remoteStr;
String stored_ssid;
String stored_password;
String stored_IP;
IPAddress remote;

/* Define constants for MIDI notes sent by cue buttons */
const byte note1 = 29;
const byte note2 = 30;
const byte note3 = 31;
const byte note4 = 32;
const byte note5 = 33;
const byte note6 = 34;

/* Define constant values for cue button labels */
const char* lblCue1 = "House Lights";
const char* lblCue2 = "Stage Lights";
const char* lblCue3 = "Back Lights";
const char* lblCue4 = "Blue";
const char* lblCue5 = "Purple";
const char* lblCue6 = "Warm White";

#define LCD_BL 46

#define SDA_FT6236 38
#define SCL_FT6236 39
//FT6236 ts = FT6236();

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ILI9488 _panel_instance;
    lgfx::Bus_Parallel16 _bus_instance;
  public:
    LGFX(void)
    {
      {
        auto cfg = _bus_instance.config();
        cfg.port = 0;
        cfg.freq_write = 80000000;
        cfg.pin_wr = 18;
        cfg.pin_rd = 48;
        cfg.pin_rs = 45;

        cfg.pin_d0 = 47;
        cfg.pin_d1 = 21;
        cfg.pin_d2 = 14;
        cfg.pin_d3 = 13;
        cfg.pin_d4 = 12;
        cfg.pin_d5 = 11;
        cfg.pin_d6 = 10;
        cfg.pin_d7 = 9;
        cfg.pin_d8 = 3;
        cfg.pin_d9 = 8;
        cfg.pin_d10 = 16;
        cfg.pin_d11 = 15;
        cfg.pin_d12 = 7;
        cfg.pin_d13 = 6;
        cfg.pin_d14 = 5;
        cfg.pin_d15 = 4;
        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);
      }

      {
        auto cfg = _panel_instance.config();

        cfg.pin_cs = -1;
        cfg.pin_rst = -1;
        cfg.pin_busy = -1;
        cfg.memory_width = 320;
        cfg.memory_height = 480;
        cfg.panel_width = 320;
        cfg.panel_height = 480;
        cfg.offset_x = 0;
        cfg.offset_y = 0;
        cfg.offset_rotation = 2;
        cfg.dummy_read_pixel = 8;
        cfg.dummy_read_bits = 1;
        cfg.readable = true;
        cfg.invert = false;
        cfg.rgb_order = false;
        cfg.dlen_16bit = true;
        cfg.bus_shared = true;
        _panel_instance.config(cfg);
      }
      setPanel(&_panel_instance);
    }
};

LGFX tft;
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 5 ];


/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  tft.startWrite();
  tft.setAddrWindow( area->x1, area->y1, w, h );
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready( disp );
}

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
  int pos[2] = {0, 0};

  ft6236_pos(pos);
  if (pos[0] > 0 && pos[1] > 0)
  {
    data->state = LV_INDEV_STATE_PR;
//    data->point.x = tft.width()-pos[1];
//    data->point.y = pos[0];
    data->point.x = tft.width()-pos[1];
    data->point.y = pos[0];
    Serial.printf("x-%d,y-%d\n", data->point.x, data->point.y);
  }
  else {
    data->state = LV_INDEV_STATE_REL;
  }
}


void touch_init()
{
  // I2C init
  Wire.begin(SDA_FT6236, SCL_FT6236);
  byte error, address;

  Wire.beginTransmission(i2c_touch_addr);
  error = Wire.endTransmission();

  if (error == 0)
  {
    Serial.print("I2C device found at address 0x");
    Serial.print(i2c_touch_addr, HEX);
    Serial.println("  !");
  }
  else if (error == 4)
  {
    Serial.print("Unknown error at address 0x");
    Serial.println(i2c_touch_addr, HEX);
  }
}

unsigned long previousBlinkTime = 0;
unsigned long t1 = millis();
int8_t isConnected = 0;

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();

void setup()
{
  Serial.begin( 115200 ); /* prepare for possible serial debug */
  
  tft.begin();          /* TFT init */
  tft.setRotation( 1 ); /* Landscape orientation, flipped */
  tft.fillScreen(TFT_BLACK);
  delay(500);
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  touch_init();

  //  if (!ts.begin(0, SDA_FT6236, SCL_FT6236)) {
  //    Serial.println("Unable to start the capacitive touch Screen.");
  //  }

  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 5 );

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

  
  ui_init();
  set_cue_btn_labels();
  attach_btn_events();
  toggle_buttons(false);
  
  preferences.begin("connections", false);
  stored_ssid = preferences.getString("ssid", "");
  stored_password = preferences.getString("password", "");
  stored_IP = preferences.getString("remoteip", "");
  preferences.end();
  lv_textarea_set_text(ui_txtSSID, stored_ssid.c_str());
  lv_textarea_set_text(ui_txtPassword, stored_password.c_str());
  lv_textarea_set_text(ui_txtRemoteIP, stored_IP.c_str());

  ssid1 = (char*)lv_textarea_get_text(ui_txtSSID);
  password1 = (char*)lv_textarea_get_text(ui_txtPassword);
  if (strcmp(ssid1, "") != 0 && strcmp(password1, "") != 0)
  {
    Serial.println("Auto connecting to WiFi");
    login_flag = 1;
    //WIFI - TIME
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid1, password1);
    unsigned long currentMillis = millis();
    previousBlinkTime = currentMillis;

    lv_label_set_text(ui_lblTip2, "Connecting...");
    lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
    while (WiFi.status() != WL_CONNECTED)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousBlinkTime >= 10000)
      {
        login_flag = 0;
        Serial.println("WiFi failed to connect");
        lv_label_set_text(ui_lblTip2, "WiFi failed to connect");
        delay(2000);
        lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_CLICKABLE);
        lv_scr_load_anim(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 0, 2000, false);                 
        break;
      }
      else if (currentMillis - previousBlinkTime <= 0)
      {
        previousBlinkTime = currentMillis;
      }
      Serial.print(".");
      lv_timer_handler();
      delay(10);
    }
  } else
  {
    login_flag = 0;
    // lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_CLICKABLE);
    lv_scr_load_anim(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 0, 2000, false);
  }
  Serial.println( "Setup done" );
  while (login_flag == 0)
  {
    lv_label_set_text(ui_lblTip2, "Connecting to MIDI device...");
    while (login_flag == 0)
    {
      lv_timer_handler();
    }
    ssid1 = (char*)lv_textarea_get_text(ui_txtSSID);
    password1 = (char*)lv_textarea_get_text(ui_txtPassword);
    if (strcmp(ssid1, "") != 0 && strcmp(password1, "") != 0)
    {
      //WIFI - TIME
      WiFi.disconnect();
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid1, password1);
      unsigned long currentMillis = millis();
      previousBlinkTime = currentMillis;

      lv_label_set_text(ui_lblTip2, "Connecting...");
      lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
      while (WiFi.status() != WL_CONNECTED)
      {
        unsigned long currentMillis = millis();
        if (currentMillis - previousBlinkTime >= 10000)
        {
          login_flag = 0;
          Serial.println("WiFi failed to connect");
          lv_label_set_text(ui_lblTip2, "WiFi failed to connect");
          delay(2000);
          lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
          // lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_CLICKABLE);                 
          break;
        }
        else if (currentMillis - previousBlinkTime <= 0)
        {
          previousBlinkTime = currentMillis;
        }
        Serial.print(".");
        lv_timer_handler();
        delay(10);
      }
    } else
    {
      login_flag = 0;
      // lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_CLICKABLE);
    }
  }
  Serial.println("WiFi connected!");
  
  // lv_textarea_set_text(ui_txtSSID, "");
  // lv_textarea_set_text(ui_txtPassword, "");
  lv_obj_clear_flag(ui_WifiIcon1, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_flag(ui_WifiIcon2, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_lblTip2, "WiFi connected");
  lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
  delay(2000);
  lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
  
  MIDI.begin();

  // Stay informed on connection status
  AppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t & ssrc, const char* name) {
    isConnected++;
    String printStr = String("Connected to session: " + String(ssrc) + " " + name);
    Serial.println(printStr);
    lv_obj_clear_flag(ui_MidiIcon1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_MidiIcon2, LV_OBJ_FLAG_HIDDEN);
    toggle_buttons(true);
  });
  AppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t & ssrc) {
    isConnected--;
    Serial.println("Disconnected " + String(ssrc));
    lv_obj_add_flag(ui_MidiIcon1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_MidiIcon2, LV_OBJ_FLAG_HIDDEN);
    toggle_buttons(false);
  });

  MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
    if (note == note1) {
      lv_obj_add_state(ui_CueButton1, LV_STATE_CHECKED);
    }
    if (note == note2) {
      lv_obj_add_state(ui_CueButton2, LV_STATE_CHECKED);
    }
    if (note == note3) {
      lv_obj_add_state(ui_CueButton3, LV_STATE_CHECKED);
    }
    if (note == note4) {
      lv_obj_add_state(ui_CueButton4, LV_STATE_CHECKED);
    }
    if (note == note5) {
      lv_obj_add_state(ui_CueButton5, LV_STATE_CHECKED);
    }
    if (note == note6) {
      lv_obj_add_state(ui_CueButton6, LV_STATE_CHECKED);
    }
    Serial.println("NoteOn " + String(note));
  });
  MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
    if (note == note1) {
      lv_obj_clear_state(ui_CueButton1, LV_STATE_CHECKED);
    }
    if (note == note2) {
      lv_obj_clear_state(ui_CueButton2, LV_STATE_CHECKED);
    }
    if (note == note3) {
      lv_obj_clear_state(ui_CueButton3, LV_STATE_CHECKED);
    }
    if (note == note4) {
      lv_obj_clear_state(ui_CueButton4, LV_STATE_CHECKED);
    }
    if (note == note5) {
      lv_obj_clear_state(ui_CueButton5, LV_STATE_CHECKED);
    }
    if (note == note6) {
      lv_obj_clear_state(ui_CueButton6, LV_STATE_CHECKED);
    }
    Serial.println("NoteOff " + String(note));
  });

  remoteStr = (char*)lv_textarea_get_text(ui_txtRemoteIP);
  if (strcmp(remoteStr, "") != 0)
  {
    remote.fromString(remoteStr);
    // Initiate the session
    AppleMIDI.sendInvite(remote, DEFAULT_CONTROL_PORT); // port is 5004 by default

    Serial.print(F("Connecting to "));
    Serial.print(remote);
    Serial.println(" Port:" + String(DEFAULT_CONTROL_PORT) + " (Name:" + AppleMIDI.getName() + ")");
    Serial.println(F("Watch as this session is added to the Participants list"));
    Serial.println(F("Then open a MIDI listener and monitor incoming notes"));
  }

  Serial.print("If autoconnect failed, add device in MIDI Network Setup with Host:");
  Serial.print(WiFi.localIP()); 
  Serial.println(" Port:" + String(AppleMIDI.getPort()) + " (Name: " + AppleMIDI.getName() + ")");
  Serial.println("Select and then press the Connect button");

  preferences.begin("connections", false);
  preferences.putString("ssid", ssid1);
  preferences.putString("password", password1);
  preferences.putString("remoteip", remoteStr);
  preferences.end();

  lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 0, 100, false);
}

void loop()
{
  //***************************************************WIFI_setting********************
  while (login_flag == 0)
  {
    lv_label_set_text(ui_lblTip2, "Re-connecting to MIDI session...");
    while (login_flag == 0)
    {
      lv_timer_handler();
    }

    ssid1 = (char*)lv_textarea_get_text(ui_txtSSID);
    password1 = (char*)lv_textarea_get_text(ui_txtPassword);
    if (strcmp(ssid1, "") != 0 && strcmp(password1, "") != 0)
    {
      //WIFI - TIME
      WiFi.disconnect();
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid1, password1);
      unsigned long currentMillis = millis();
      previousBlinkTime = currentMillis;

      lv_label_set_text(ui_lblTip2, "Connecting...");
      lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
      while (WiFi.status() != WL_CONNECTED)
      {
        unsigned long currentMillis = millis();
        //Check for arrival time interval
        if (currentMillis - previousBlinkTime >= 10000)
        { //If the time interval is reached
          login_flag = 0;
          Serial.println("WiFi failed to connect");
          lv_label_set_text(ui_lblTip2, "WiFi failed to connect");
          delay(2000);
          lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
          // lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_CLICKABLE);                 
          break;
        }
        else if (currentMillis - previousBlinkTime <= 0)
        { // If the millis time overflow
          previousBlinkTime = currentMillis;
        }
        Serial.print(".");
        lv_timer_handler();
        delay(20);
      }
      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println("WiFi connected!");
        // lv_textarea_set_text(ui_txtSSID, "");
        // lv_textarea_set_text(ui_txtPassword, "");
        lv_label_set_text(ui_lblTip2, "Starting MIDI session...");
        lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
        lv_timer_handler();
        
        MIDI.begin();
        // Initiate the session
        AppleMIDI.sendInvite(remote, DEFAULT_CONTROL_PORT); // port is 5004 by default

        Serial.print(F("Connecting to "));
        Serial.print(remote);
        Serial.println(" Port:" + String(DEFAULT_CONTROL_PORT) + " (Name:" + AppleMIDI.getName() + ")");
        Serial.println(F("Watch as this session is added to the Participants list"));
        Serial.println(F("Then open a MIDI listener and monitor incoming notes"));

        lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
        lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 0, 100, false);
        login_flag = 1;
      }
    } else
    {
      login_flag = 0;
      // lv_obj_clear_flag(ui_ConnectButton, LV_OBJ_FLAG_CLICKABLE);
    }
  }
  
  lv_timer_handler(); /* let the GUI do its work */
  // delay( 5 );

  // Listen to incoming notes
  MIDI.read();

  if (WiFi.status() == WL_DISCONNECTED)
  {
    login_flag = 0;
    lv_obj_add_flag(ui_WifiIcon1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_WifiIcon2, LV_OBJ_FLAG_HIDDEN);
    AppleMIDI.end();
  }
}

static void attach_btn_events()
{
  // Cue Buttons
  lv_obj_add_event_cb(ui_CueButton1, cue_btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_CueButton2, cue_btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_CueButton3, cue_btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_CueButton4, cue_btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_CueButton5, cue_btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_CueButton6, cue_btn_event_cb, LV_EVENT_ALL, NULL);

  // Save Button
  lv_obj_add_event_cb(ui_SaveButton, save_btn_event_cb, LV_EVENT_ALL, NULL);
}

static void save_btn_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    ssid1 = (char*)lv_textarea_get_text(ui_txtSSID);
    password1 = (char*)lv_textarea_get_text(ui_txtPassword);
    remoteStr = (char*)lv_textarea_get_text(ui_txtRemoteIP);
    preferences.begin("connections", false);
    preferences.putString("ssid", ssid1);
    preferences.putString("password", password1);
    preferences.putString("remoteip", remoteStr);
    preferences.end();
    
    Serial.println("Settings saved");
    lv_obj_clear_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui_lblTip2, "Settings saved");
    delay(2000);
    lv_obj_add_flag(ui_tip2, LV_OBJ_FLAG_HIDDEN);
  }
}

static void cue_btn_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    if (btn == ui_CueButton1) {
      MIDI.sendNoteOn(note1, 1, 1);
      MIDI.sendNoteOff(note1, 1, 1);
    }
    else if (btn == ui_CueButton2) {
      MIDI.sendNoteOn(note2, 1, 1);
      MIDI.sendNoteOff(note2, 1, 1);
    }
    else if (btn == ui_CueButton3) {
      MIDI.sendNoteOn(note3, 1, 1);
      MIDI.sendNoteOff(note3, 1, 1);
    }
    else if (btn == ui_CueButton4) {
      MIDI.sendNoteOn(note4, 1, 1);
      MIDI.sendNoteOff(note4, 1, 1);
    }
    else if (btn == ui_CueButton5) {
      MIDI.sendNoteOn(note5, 1, 1);
      MIDI.sendNoteOff(note5, 1, 1);
    }
    else if (btn == ui_CueButton6) {
      MIDI.sendNoteOn(note6, 1, 1);
      MIDI.sendNoteOff(note6, 1, 1);
    }
  }
}

static void toggle_buttons(bool enable)
{
  if (enable) {
    lv_obj_clear_state(ui_CueButton1, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_CueButton2, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_CueButton3, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_CueButton4, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_CueButton5, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_CueButton6, LV_STATE_DISABLED);
  }
  else {
    lv_obj_add_state(ui_CueButton1, LV_STATE_DISABLED);
    lv_obj_add_state(ui_CueButton2, LV_STATE_DISABLED);
    lv_obj_add_state(ui_CueButton3, LV_STATE_DISABLED);
    lv_obj_add_state(ui_CueButton4, LV_STATE_DISABLED);
    lv_obj_add_state(ui_CueButton5, LV_STATE_DISABLED);
    lv_obj_add_state(ui_CueButton6, LV_STATE_DISABLED);
  }
  
}

static void set_cue_btn_labels()
{
  lv_label_set_text(ui_lblCue1, lblCue1);
  lv_label_set_text(ui_lblCue2, lblCue2);
  lv_label_set_text(ui_lblCue3, lblCue3);
  lv_label_set_text(ui_lblCue4, lblCue4);
  lv_label_set_text(ui_lblCue5, lblCue5);
  lv_label_set_text(ui_lblCue6, lblCue6);
}
