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

  mixer.gain(0, 0.4);
  mixer.gain(1, 0);

  string1.setFreq(100);
  
  delay(700);
}


void loop() {
 OSCMix testMix = {0.0f, 0.0f, 0.0f, 5.0f, 0.0f};
 string1.setMix(testMix);
 string1.pluck(1);
 delay(5000);

 testMix = {5.0f, 0.0f, 0.0f, 0.0f, 0.0f};
 string1.setMix(testMix);
 string1.pluck(1);
 delay(5000);

 testMix = {0.0f, 5.0f, 0.0f, 0.0f, 0.0f};
 string1.setMix(testMix);
 string1.pluck(1);
 delay(5000);
}
