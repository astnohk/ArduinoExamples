# WioBot

The simple robot runs on [Wio Terminal](https://jp.seeedstudio.com/Wio-Terminal-p-4509.html) with [Grove Servo](https://www.seeedstudio.com/Grove-Servo.html) and [Sound Direction Sensor](https://github.com/meerstern/Sound_Direction_Sensor).


## Notice

Wio Terminal uses ATSAMD51 as CPU.
However, Arduino Servo library is corrupted for SAMD51 so you need to replace original library with the pull request [#34 SAMD51 support](https://github.com/arduino-libraries/Servo/pull/34).


## Setup

Connect `Grove Servo` to the bottom right Grove connector.
Connect `Sound Direction Sensor` to the bottom left Grove connector.
Fix `Grove Servo` at the left side and point the axis to the left.
Rotate Wio Terminal 90 deg counterclockwise.
Fix `Grove Servo` axis to the ground (fix servo's plate with screws to large heavy panels).


## Run

Connect USB Type-C to Wio Terminal and PC.
Compile and Upload the sketch.
Reset the Wio Terminal.


## Trouble Shooting

Sometimes WioBot freezes with keeping its face switching between normal and smile.
If it occurs then you need to power reset by pulling out your USB or turning OFF the switch.
