# Lightkey-Control
 An Arduino project for an ESP32 board with LCD that will function as a lighting control panel that interfaces with the Lightkey (DMX lighting control) app on an external computer.

 Interfaces with the Lightkey app running on a Mac computer by using MIDI over the network to send MIDI notes to trigger lighting cues.
 
# Getting Started
 This project can be used with an Arduino or ESP32 based board with WiFi capability and a touch LCD panel connected.

 To get started on this project: 
  - Download all the source code or clone the repository, including the "ui" directory
  - In your Arduino IDE, install the "_ui_" library found in the "ui" directory
    - You can simply copy the "ui" folder to Arduino's library directory (you can find where that is in Arduino IDE Settings, under _Sketchbook location_)
  - Open the Lightkey-Control.ino project
  - Connect and set up your Arduino/ESP32 dev board with all the neccesary configurations to be able to communicate and program the board
  - Once you confirm everything compiles and runs, start tweaking and modifying the code to your projects needs.
