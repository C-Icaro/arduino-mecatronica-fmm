#include <HT16K33Disp.h>

HT16K33Disp dsp;

int um = 0x70;
int dois = 0x71;
int tres = 0x72;
int quatro = 0x73;
int cinco = 0x74;
int seis = 0x75;

void setup() {

  dsp.Init(um, 8);
  dsp.Clear(um);
  dsp.Init(dois, 8);
  dsp.Clear(dois);
  dsp.Init(tres, 8);
  dsp.Clear(tres);
  dsp.Init(quatro, 8);
  dsp.Clear(quatro);
  dsp.Init(cinco, 8);
  dsp.Clear(cinco);
  dsp.Init(seis, 8);
  dsp.Clear(seis);

}

void loop() {
   dsp.Text(um, "Um");
   dsp.Text(dois, "Dois");
   dsp.Text(tres, "Tres");
   dsp.Text(quatro, "Quatro");
   dsp.Text(cinco, "Cinco");
   dsp.Text(seis, "Seis");

}
