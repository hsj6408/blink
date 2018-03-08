#include "Blink.h"

Blink blink(D4);

void setup()
{
  Serial.begin(115200);
  Serial.println("\nBlink Version 1.0 Seok Jin Ha");
}
void loop()
{
  blink.on(500);
  blink.off(300);
}
