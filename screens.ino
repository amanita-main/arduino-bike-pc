#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

class IScreen {
  public:
    virtual int loop() = 0;
  protected:
    int processKeys() {
      //TODO: read buttons & may be touch, if it is on
      int result = 0;
      if (Serial.available() > 0) {
        // read the incoming byte:
        result = Serial.read();
      }
      return result;
    }
};

class SleepModeScreen : public IScreen {
  public:
    int loop() {
      //TODO: update time, draw current total distance, current dist if riding
      //if any button pressed return 1 as signal to awake
      int result = 0;
      int keyPressed = processKeys();
      if (keyPressed > 0) {
        result = 1;
      }
      return result;
    }
};

class MainScreen : public IScreen {
  public:
    int loop() {
      //TODO
      Serial.println("loop MainScreen");
      return 0;
    }
};

class SettingsScreen : public IScreen {
  public:
    int loop() {
      //TODO
      Serial.println("loop SettingsScreen");
      return 0;
    }
};

class NavigationScreen : public IScreen {
  public:
    int loop() {
      //TODO
      Serial.println("loop NavigationScreen");
      return 0;
    }
};

class RouteScreen : public IScreen {
  public:
    int loop() {
      //TODO
      Serial.println("loop RouteScreen");
      return 0;
    }
};

SleepModeScreen sleepModeScreen;
MainScreen mainScreen;
SettingsScreen settingsScreen;
NavigationScreen navigationScreen;
RouteScreen routeScreen;
IScreen *screens[] = { 
  &sleepModeScreen,
  &mainScreen,
  &settingsScreen,
  &navigationScreen,
  &routeScreen,
};
int current_screen = 0;
const int SCREENS_SIZE = sizeof(screens)/sizeof(IScreen);
int power_saving_delay = 2000;
long previousmillis = 0;
long timer = 0;

void updateValues() {
  //TODO: update clock time, timers, speed, etc.
  timer+= millis() - previousmillis;
  previousmillis = millis();
  Serial.println(timer);
}

bool onBeforeScreenChange(int newScreenIndex) {
  Serial.println(newScreenIndex);
  if (current_screen == 0) {
    power_saving_delay = 500;
    //TODO: restore state gps & others
    //Restore current screen
    return true;
  }
  return false;
}

void changeScreen(int newIndex) {
  if (current_screen != newIndex) {
    onBeforeScreenChange(newIndex);
  }
  current_screen = newIndex;
}

void idleCheck() {
  //TODO
  updateValues();
  /*if (speed < 3km/h for 1 mins) {
   * save current screen and some settings
   * current_screen = 0;
   * power_saving_delay = 2000;
  }*/
  /* if (current_screen && sleep time > some stored value){
   *  turn gps off
   * }
   */
  /*if (current_screen == 0 && got any signal from magnet sensor or gps speed > some stored const) {
   * restore some setings & awake:
   *  changeScreen(restoredScreenIndex);
   * }
   */
}

void fakeLoop(int index) {
  //shift should be +1,0,-1
  idleCheck();
  int screenShift = screens[index]->loop();
  int result = current_screen + screenShift;
  //0 - sleep mode screen
  if (result > 0 && result < SCREENS_SIZE) {
    changeScreen(result);
  }
}

void read_settings() {
  //TODO
}

void setup() {
  Serial.begin(9600);
  Serial.println("main setup");
  tft.begin();
  //TODO: only for any kind of timer, may be I should to add rtc. It is better. Or sync by gps.
  previousmillis = millis();
  read_settings();
  Serial.println("main setup end");
}

void loop() {
  //stupid bug
  fakeLoop(current_screen);
  delay(power_saving_delay);
}


