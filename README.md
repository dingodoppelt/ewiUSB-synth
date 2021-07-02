## AKAI EWI-USB Teensy 4.0 Synth
This is a small patch for using the **AKAI EWI-USB** on the go with a **Teensy 4.0 dev board + Audio Shield (Rev.D)**
It uses the Teensy's internal Audio Library ( https://github.com/PaulStoffregen/Audio ) to model an analog synth lead patch.
It features:
* four oscillators (waveform: variable triangle) in unison or voiced
* voltage controlled amplifier and filter reacting to breath control
* two semitones pitchbend on positive pitchwheel input
* a cool fourths voicing (4th down, 9th down, octave down) on negative pitchwheel input
* a custom waveshaping transfer function to add warmth and saturation
* a gentle chorus effect
* stereo output

**What is needed:**
* Teensy 4.0 dev board ( https://www.pjrc.com/store/teensy40.html )
* Audio Shield for Teensy 4.0 ( https://www.pjrc.com/audio-shield-for-teensy-4-0/ )
* a soldering iron to solder pin headers, sockets and wires to the Teensy and Audio Shield
* USB Type A connector with wires to solder to the Teensy's USB host pads for connecting your EWI ( https://www.pjrc.com/store/cable_usb_host_t36.html )
* USB powerbank with USB micro-B plug for powering the Teensy
* Headphones or active speakers
* **optional:** a 3D printer for printing a case to acommodate the parts

## Installation
* Platform specific instructions on how to get your Teensy board up and running can be found here: https://www.pjrc.com/store/teensy40.html
* Download this patch and upload it to your Teensy through the Arduino IDE
* Connect your EWI, Headphones or speakers
* Power up the Teensy with a powerbank or USB charger
* **Do not touch any metal parts on the EWI until the green LED lights up (to not mess up the EWI's self-calibration)**
