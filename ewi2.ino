#include "USBHost_t36.h"
#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=1783.1943359375,2173.8887939453125
AudioSynthWaveform       waveform2;      //xy=1786.0833740234375,2222.0833740234375
AudioSynthWaveform       waveform4;      //xy=1787.0833740234375,2311.0833740234375
AudioSynthWaveform       waveform3;      //xy=1789.0833740234375,2266.0833740234375
AudioSynthWaveformDc     breath;         //xy=1930.6943359375,2407.8887939453125
AudioMixer4              mixer2;         //xy=2022.0833282470703,2203.0833282470703
AudioEffectMultiply      multiply1;      //xy=2165.9442749023438,2330.388671875
AudioEffectWaveshaper    waveshape1;     //xy=2178.6942138671875,2203.6387939453125
AudioFilterStateVariable filter1;        //xy=2308.6943359375,2401.8887939453125
AudioEffectChorus        chorus2;        //xy=2523.0828857421875,2441.0836181640625
AudioEffectChorus        chorus1;        //xy=2525.0828857421875,2399.0836181640625
AudioMixer4              mixerL;         //xy=2655.0828857421875,2366.0836181640625
AudioMixer4              mixerR;         //xy=2666.0828857421875,2524.0836181640625
AudioOutputI2S           i2s1;           //xy=2876.6942138671875,2353.8887939453125
AudioConnection          patchCord1(waveform1, 0, mixer2, 0);
AudioConnection          patchCord2(waveform2, 0, mixer2, 1);
AudioConnection          patchCord3(waveform4, 0, mixer2, 3);
AudioConnection          patchCord4(waveform3, 0, mixer2, 2);
AudioConnection          patchCord5(breath, 0, multiply1, 1);
AudioConnection          patchCord6(breath, 0, filter1, 1);
AudioConnection          patchCord7(mixer2, waveshape1);
AudioConnection          patchCord8(multiply1, 0, filter1, 0);
AudioConnection          patchCord9(waveshape1, 0, multiply1, 0);
AudioConnection          patchCord10(filter1, 0, chorus1, 0);
AudioConnection          patchCord11(filter1, 0, chorus2, 0);
AudioConnection          patchCord12(filter1, 0, mixerL, 0);
AudioConnection          patchCord13(filter1, 0, mixerR, 0);
AudioConnection          patchCord14(chorus2, 0, mixerR, 1);
AudioConnection          patchCord15(chorus1, 0, mixerL, 1);
AudioConnection          patchCord16(mixerL, 0, i2s1, 0);
AudioConnection          patchCord18(mixerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2457.0833740234375,2222.0836181640625
// GUItool: end automatically generated code



USBHost myusb;
MIDIDevice midi1(myusb);
float freq, currFreq = 440;
float waveshape[32769];
short delayBufferL[128 * AUDIO_BLOCK_SAMPLES];
short delayBufferR[144 * AUDIO_BLOCK_SAMPLES];
int bendrange = 2;
float bendfactor = 1.0;
float detunefactor[3] = { 0.999, 0.997, 1.002 };
int transposition[7] = { 0, -2, 10, 3, -9, 12, -12 };
int transp = 0;
float LFOphase = 0.0;
unsigned int msec = 0;
float LFOfreq = 10.0;
float LFOfactor = 1.0;
int LFOrange = 3;
float Fs = 1e3;
float biteSensor = 0.0;
float glideOffset = 1.0;
float glideTime = 20.0;

void setup() {
  float amp_gain = 1.0;
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  sgtl5000_1.audioProcessorDisable();
  AudioMemory(120);
  Serial.println("USB Host On...");
  myusb.begin();
  midi1.setHandleNoteOn(myNoteOn);
  midi1.setHandleAfterTouch(myAfterTouch);
  midi1.setHandlePitchChange(myPitchChange);
  midi1.setHandleControlChange(myControlChange);
  float bereich = 2.0;
  float inc = bereich / 32769.0;
  float j = (bereich / 2) - bereich;
  for (int i = 0; i <= 32768; i++) {
    waveshape[i] = tanh(j);
    j = j + inc;
  }
  waveshape1.shape(waveshape, 32769);
  filter1.frequency(100);
  filter1.octaveControl(7);
  filter1.resonance(0.7);
  breath.amplitude(0.0);
  mixer2.gain(0, 1.0 * amp_gain);
  mixer2.gain(1, 0.7 * amp_gain);
  mixer2.gain(2, 0.7 * amp_gain);
  mixer2.gain(3, 0.7 * amp_gain);
  mixerL.gain(0, 0.5);
  mixerL.gain(1, 0.15);
  mixerR.gain(0, 0.5);
  mixerR.gain(1, 0.15);
  waveform1.begin(1.0, freq, WAVEFORM_TRIANGLE_VARIABLE);
  waveform2.begin(1.0, freq, WAVEFORM_TRIANGLE_VARIABLE);
  waveform3.begin(1.0, freq, WAVEFORM_TRIANGLE_VARIABLE);
  waveform4.begin(1.0, freq, WAVEFORM_TRIANGLE_VARIABLE);
  chorus1.begin(delayBufferL, 24 * AUDIO_BLOCK_SAMPLES, 2);
  chorus2.begin(delayBufferR, 16 * AUDIO_BLOCK_SAMPLES, 2);
}


void loop() {
  midi1.read();
  LFOUpdate();
  if (glideOffset != 1.0) {
    updateGlide(); 
  }
}

void LFOUpdate() {
  unsigned long currentMicros = micros();
  if (currentMicros - msec >= Fs) {
    msec = currentMicros;
    LFOphase += 1/Fs;
  }
  if (LFOphase > 1) {
    LFOphase -= 1;  
  }
  LFOfactor = pow(2, (sin(LFOfreq*2.0*PI*LFOphase)*LFOrange*biteSensor)/12);
  if (LFOfactor > 1) {
    setOSC(bendfactor < 1);
  }
}

void updateGlide () {
  glideOffset = glideOffset - (glideOffset - 1) / glideTime;
  setOSC(bendfactor < 1);
}

void myNoteOn(byte channel, byte note, byte velocity) {
  if (note == 99) toggleTransposition();
  freq = 440.0 * powf(2.0, (float)(note - 69 + transposition[transp]) * 0.08333333);
  glideOffset = currFreq/freq;
}

void myAfterTouch(byte channel, byte pressure) {
  float pressVal = (float)pressure / 127.00;
  breath.amplitude(pow(pressVal, 3), 3);
  waveform1.pulseWidth(pressVal);
  waveform2.pulseWidth(pressVal);
  waveform3.pulseWidth(pressVal);
  waveform4.pulseWidth(pressVal);
}

void myPitchChange(byte channel, int pitch) {
  float bendF = (((float)pitch / 8192) * bendrange);
  bendfactor = pow(2, bendF / 12);
  setOSC(bendfactor < 1);
}

void myControlChange(byte channel, byte control, byte value) {
  if (control == 1) {
    biteSensor = float(value) / 127.0;
  }
}

void setOSC(bool voicing) {
  if (voicing == 0) {
    currFreq = freq * glideOffset * bendfactor * LFOfactor;
    waveform1.frequency(currFreq);
    waveform2.frequency(currFreq * detunefactor[0]);
    waveform3.frequency(currFreq * detunefactor[1]);
    waveform4.frequency(currFreq * detunefactor[2]);
  } else {
    currFreq = freq * glideOffset * LFOfactor;
    waveform1.frequency(currFreq);
    waveform2.frequency(currFreq * 0.749153538438); // perfect fourth down
    waveform3.frequency(currFreq * 0.561231024154); // major ninth down
    waveform4.frequency(currFreq / 2);              // octave down
  }
}

void toggleTransposition () {
  if (transp >= 6) {
    transp = 0;
  } else {
    transp++;
  }
}
