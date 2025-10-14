#include <HT16K33Disp.h>

HT16K33Disp dsp;

int add = 0x70;

void setup() {

  dsp.Init(add, 8);
  dsp.Clear(add);

}

void loop() {
   dsp.Text(add, "GAME");
   delay(1000);
   dsp.Text(add, "OVER");
   delay(1000);

}
