#include "Arduino.h"

class Blink
{
  public:
    Blink(int pin);
    void on(int time);
    void off(int time);
  private:
    int _pin;
};
