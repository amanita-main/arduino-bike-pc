#ifndef Screens_h
#define Screens_h

class IScreen {
  public:
    virtual int loop() = 0;
  protected:
    int processKeys();
};
class SleepModeScreen : public IScreen {
  public:
    int loop();
};
class MainScreen : public IScreen {
  public:
    int loop();
};
class SettingsScreen : public IScreen {
  public:
    int loop();
};
class NavigationScreen : public IScreen {
  public:
    int loop();
};
class RouteScreen : public IScreen {
  public:
    int loop();
};
#endif
