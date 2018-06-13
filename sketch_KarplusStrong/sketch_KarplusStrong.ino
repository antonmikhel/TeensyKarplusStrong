#include "CKarplusStrong.h"

KarplusStrongString      string1;
AudioSynthWaveformSine   sine1;
AudioMixer4              mixer;
AudioOutputI2S           i2s1;
AudioConnection          patchCord10(sine1, 0, mixer, 1);
AudioConnection          patchCord0(string1, 0, mixer, 0);
AudioConnection          patchCord1(mixer, 0, i2s1, 0); 
AudioConnection          patchCord2(mixer, 0, i2s1, 1); 
AudioControlSGTL5000     sgtl5000_1;

void setup() 
{
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);
  sine1.frequency(300);
  sine1.amplitude(1);
  mixer.gain(0, 0.15);
  mixer.gain(1, 0);

  string1.setFreq(200);
  string1.pluck(1);
  delay(700);
}
int sine_f = 300;
int s_f = 100;

void loop() {
  sine_f += 1;
  sine1.frequency(sine_f);

  string1.setFreq(100);
  string1.pluck(.9);
  delay(4000);

  string1.setFreq(200);
  string1.pluck(.8);
  delay(3000);
  
  string1.setFreq(300);
  string1.pluck(.7);
  delay(2000);

  string1.setFreq(400);
  string1.pluck(.6);
  delay(1000);
}
