# Arduino-PushToTalk
Ardunio sketch for a 3 button push to talk pedal


This is using an Arduino Uno Rev. 3 as an HID device to send serial signals via USB.

The UNO doesn't support HID functionality out of the box, so flashing the firmware is required. You can flash using Amtel FLIP as described [http://www.kevindemarco.com/2014/01/02/arduino-uno-as-a-usb-hid-interface/](http://www.kevindemarco.com/2014/01/02/arduino-uno-as-a-usb-hid-interface/)
Windows installation instructions can be found [here](https://www.fedevel.com/welldoneblog/2015/04/how-to-flash-arduino-bootloader-without-a-programmer/)

My workflow:
 - Program Arduino ATMega16u2 chip with Flip by plugging in USB -> short pins with paper clip -> Program with the following Hex file [https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/firmwares/atmegaxxu2/arduino-usbserial/Arduino-usbserial-atmega16u2-Uno-Rev3.hex](https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/firmwares/atmegaxxu2/arduino-usbserial/Arduino-usbserial-atmega16u2-Uno-Rev3.hex)
 - Power cycle Arduino by unplugging then re-plugging the USB
 - Upload ptt_buttons.ino sketch file to Arduino
 - Short pins and now re-program ATMega16u2 using the above process with [Arduino-keyboard-0.3.hex](https://github.com/coopermaa/USBKeyboard/blob/master/firmware/Arduino-keyboard-0.3.hex) file
 - Power cycle Arduino and you should now have a USB HID button device
 
 
To change the buttons that are triggered, simply change the serial codes at:
 
The following binds are 'Left Ctrl', '[' and ']' respectively. Note that the KEY_LEFT_CTRL is passed as a 'Modifier' at array position 0.

```#define KEY_LEFT_CTRL 0x01
#define KEY_BUTTON_A 0x2F
#define KEY_BUTTON_B 0x30
```

For serial code references please see [http://www.usb.org/developers/hidpage/Hut1_12v2.pdf](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf)



![](https://media.giphy.com/media/8lQwnL1gIp5G8/giphy.gif)
