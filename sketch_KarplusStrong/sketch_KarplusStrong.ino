#include "CKarplusStrong.h"
// OK , Sorry for deleting some of your code. 
// I find it easier to navigate when it's simplified. 
// Let's try and keep the code to a minimum ^-)
// 
// A brief overview of the proceedings of tonight's fine evening: 

// I took inspiration from the source and modeled some of what he does!! Very elegant code he writes!!
// Basically, I figured out through using processorUsage functions, that 
// we were using way too much CPU. the integer was supposed to be between 
// 1 - 100, yet for the 100Hz object, it showed usage of '122'.Alarming....
// That's why the processor never got around to updating the array or answering 
// the other calls, because the update interrupt didn't have sufficient time to finish his own recourse
// so he effectively blocked FLOW of OPERATION.
// So it turns out that in the Real -- Time  Para.digm  -  I guess we can't really use that inner recursive loop
// that we saw work in Java...
// I suppose the processor just isn't as capable...(??)

// So , when I looked at his code, I realised we never really needed that inner recursion loop. 
// i.e. calling tick (which iterates the array) within each iteration of the NUM_BLOCK 
// cycle (of 128 samples). 

// You just use  m_bufferIndex instead.. .. ... .. .....

// 
// I hope this inspires you  (in some really geeky and weird way) !!! 

// And towards that end, here is a bunch of issues... 
// (I'll gladly make you a unit, and give you a LED strip to integrate with as well if you want..)

// If you have any ideas, I'd love to hear them out! 


//-----------------------      TOO ..  DOO       -----------------------
// -- ---- ---- ---- ---- Finishing the KS Object ---- ---- ---- ---- --
// 
// 1. Implement noteOn(float frequency, float velocity) & noteOff(); 
// see audio library source
// 2. Implement 'Super Strings' (multiple instances attached to one 
// master controller);
// 3. Prepare for integration with movement sensors by creating a 
// function:`stimulate`, which takes in a float, probably a relative 
// value indicating the change in the sensor's magnitude. 
// Since the movement happens to be directions, like AC, 
// there is no real 'Directionality', hence, you mainly work with 
// changes in amplitude (unless taking multiple axis into configruation)..
// Anyhow, This function should use dynamic adjustments to the 
// decay_factor in real time, as to mimic the spontaneous re-excitation
// of the string (which is very long and can therefore vibrate for more 
// than 10-20 seconds.... and it can also become more agile after 
// seeming to slow down already....)

// So, ideally, you'd wanna be there in person to see it..
// Theoretically though, if you had a collection of 'movement sets' , 
// which you could load into the project, and monitor on a graph, 
// (I can make you a sketch for that -- if you REALLY want me to) 
// That would give you a fair indication of how the string is moving, 
// I mean it's just moving you know?!?! 
//   W E   C A N   A L S O     M E E T   U P    O N    S U N D A Y    
//               A T      T H E      T O I _ L A B   :: -- ) -- )) 

// Wahh.. Movement is..... 
// Confusing!!

// **** HARDCORE ****  
// Number @!!..22.>!@<

// The matter of changing over to digital sensors (which I am not 
// using currently thanks to an issue I had with them in the past). 
// Making this change would mean many more analog inputs untouched, 
// which are quite useful and 'expensive'.


// And Now..!. !.... !........ ?? ....... 



  //\\          :!:!:!:!::!:!:!:!::!:!:            //\\
 //  \\         :!:!:!:!:SOUND:!:!:!:!:           //  \\
//    \\        :!:!:!:!::!:!:!:!::!:!:          //    \\

// 
// 4. Experimenting with different averaging methods. 
// currently we are simply using 2 member averages, 
// we can try and mix different members, different quantities,
// See what kinds of filtering effect you can achieve by
// using different filtering strategies with your 
// averaging variables. 

// 5. Using the Teensy Audio library to create an effect rack.
// If you want to try this one out, mainly stick to Reverb and
// flanger as your main effects, and experiment with other effects if 
// you want. The trick would be to experiment with different 
// values for the effect's parameters, and mixing different effects 
// together. To aid you in this process, you can turn the controllers
// mounted on the box into the parameters of the effects , by ... 

// 5** If you're feeling savy, you can try some FM modulation objects
// from the teensy library, rather than audio effects. 

// 6. :: Creating 'Menu Patches' ::
//    :: i.E. :: 

//    Read states of potentiometer values (given ANALOG PIN NUMBERS) 
//    Then feed those into different configurations of parameters.
//    One for controlling the 5 different oscillators.
//    another for controlling KS parameters.  
//    one for "global settings"  

// 7. :: Integrating LEDs into the Project :: 
// 

// XTRA Points (Would BE - A M AAA ZI NG ) :: :: :: :: 

// Simon Interaction :) 
// SIMON: https://www.youtube.com/watch?v=1Yqj76Q4jJ4
// You have 4 LED Strips, one on each metal wire (SS = Simon String/s)
// Assume you can detect when a string is being 'Plucked!'
// create an option in the main frame of the app, 
// to play simon instead of 'jamming' the strings. 
// where the software comes up with a random sequence of notes,
// that the player has to repeat in that order in order to continue.



// Notes to SELF:
// Solder another Teensy set...
// Put them wires in them Shreeenks 
// Prepare LEDs, Controller, and ample Samples. 



KarplusStrongString      string1;
KarplusStrongString      string2;
KarplusStrongString      string3;
KarplusStrongString      string4;

AudioSynthKarplusStrong  s1;
AudioSynthWaveformSine   sine1;
AudioMixer4              mixer;
AudioOutputI2S           i2s1;
AudioConnection          patchCord11(string1, 0, mixer, 0);
AudioConnection          patchCord10(string4, 0, mixer, 3);
AudioConnection          patchCord0(string3, 0, mixer, 2);
AudioConnection          patchCord12(string2, 0, mixer, 1);
AudioConnection          patchCord1(mixer, 0, i2s1, 0); 
AudioConnection          patchCord2(mixer, 0, i2s1, 1); 

AudioControlSGTL5000     sgtl5000_1;

float                    midi[127];
int16_t                  QUARTER_LENGTH = 600;

void setup() 
{
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.4);

  mixer.gain(0, 0.3);
  mixer.gain(1, 0.2);
  mixer.gain(2, 0.2);
  mixer.gain(3, 0.2);


  OSCMix testMix = {0.0f, 1.0f, 0.0f, 0.0f, 0.0f};

  string1.setMix(testMix);
  string2.setMix(testMix);
  string3.setMix(testMix);
  string4.setMix(testMix);

  int a = 440;
  for (int i=0; i<127; ++i){
    midi[i] = (a / 32 ) * ( 2 ^ ((i-9) / 12));
  }

  delay(700);
}






int rootKey = 60;

void loop() {
 int val = random(10);
 int p = random(2);
 if (p==0) p = -1;

 if (val>2)
  rootKey += 1 * p;
 if (val>4)
  rootKey += 3 * p;
 if (val>6)
  rootKey += 5 * p;
 if (val>8)
  rootKey += 7 * p;
  
 float root = midi[rootKey];

 string1.setFreq(root);
 string1.pluck(1);
 delay(2);
 
 string2.setFreq(2 * root);
 string2.pluck(1);
 delay(2);
 
 string3.setFreq(3 * root);
 string3.pluck(1);
 delay(2);
 
 string4.setFreq(4 * root);
 string4.pluck(1);
 delay(QUARTER_LENGTH);
 
}
