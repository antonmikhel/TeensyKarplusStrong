#include "CKarplusStrong.h"

KarplusStrongString      string1;
AudioSynthWaveformSine   sine1;
AudioMixer4              mixer;
AudioOutputI2S           i2s1;
AudioConnection          patchCord0(string1, 0, mixer, 0);
AudioConnection          patchCord3(sine1, 0, mixer, 1);
AudioConnection          patchCord1(mixer, 0, i2s1, 0);
AudioConnection          patchCord2(mixer, 0, i2s1, 1); 
AudioControlSGTL5000     sgtl5000_1;

void setup() 
{
  AudioMemory(15);  
  string1.setFreq(200);
  string1.pluck(1.0f);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  mixer.gain(0, 0.15);
  mixer.gain(1, 0.15);
  //sine1.frequency(500);
  //sine1.amplitude(0.5);
  delay(700);
}

void loop() {
  // put your main code here, to run repeatedly:  
}
