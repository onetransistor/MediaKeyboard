# MediaKeyboard
STM32 Arduino Library with support for USB consumer control device (media keys). Installation and usage:

- Install STM32 support in Arduino IDE. See https://www.onetransistor.eu/2020/01/stm32-bluepill-arduino-support.html and https://github.com/stm32duino/Arduino_Core_STM32.
- Download this library (clone the repository) in your Arduino/libraries folder.
- When you select STM32 board enable **USB support** in **HID (keyboard and mouse)** mode (options should appear in Tools menu).
- Use sample sketch or this very simple example:

```
#include <MediaKeyboard.h>

void setup() {
  MediaKeyboard.begin();
  delay(1000); // wait long enough to let the host configure device
  
  MediaKeyboard.press(MEDIA_PLAY_PAUSE);
  MediaKeyboard.release();
}

void loop() {
}
```

For more information see [USB multimedia keys on Arduino STM32](https://www.onetransistor.eu/2020/03/usb-multimedia-keys-on-arduino-stm32.html).
