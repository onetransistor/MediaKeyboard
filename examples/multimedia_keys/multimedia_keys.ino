/*
 * USB Composite device consisting of keyboard and consumer HID
 * Extends the features of Keyboard library by adding
 * multimedia keys support. Depends on MediaKeyboard library.
 * 
 * A rotary encoder and four push buttons are required. See the schematic at
 * https://www.onetransistor.eu/2020/03/usb-multimedia-keys-on-arduino-stm32.html
 *
 * RotaryEncoder library by Matthias Hertel is required for successful compilation. 
 * You can find it in Library Manager or at:
 * http://www.mathertel.de/Arduino/RotaryEncoderLibrary.aspx
 *
 * USB HID support must be enabled from Tools menu.
 * 
 * Copyright (C) 2020 One Transistor (https://www.onetransistor.eu).
 */

#include <MediaKeyboard.h>
#include <Keyboard.h>
#include <RotaryEncoder.h>

RotaryEncoder encoder(PB8, PB9);
int pos = 0;

#define PIN_MUTE PB7
#define PIN_PREV PB3
#define PIN_STOP PB4
#define PIN_PLAY PB5
#define PIN_NEXT PB6

#define DEBOUNCE_DELAY 250

void setup() {
  pinMode(PIN_MUTE, INPUT_PULLUP);
  pinMode(PIN_PREV, INPUT_PULLUP);
  pinMode(PIN_STOP, INPUT_PULLUP);
  pinMode(PIN_PLAY, INPUT_PULLUP);
  pinMode(PIN_NEXT, INPUT_PULLUP);

  MediaKeyboard.begin();
  delay(1000); // wait long enough to let the host configure device

  // Keyboard class can be used in the same time
  // Do not call both Keyboard.begin() and MediaKeyboard.begin()
  char *s = "Hello from STM32 USB Keyboard.\r\n"
            "Use the rotary encoder to change volume and\r\n"
            "the buttons to play and change media.\0";
    int i = 0;
    while (s[i] != 0) {
    Keyboard.write(s[i]);
    i++;
    }
}

void loop() {
  // evaluate potential button presses
  if (digitalRead(PIN_MUTE) == LOW) {
    MediaKeyboard.press(VOLUME_MUTE);
    MediaKeyboard.release();
    delay(DEBOUNCE_DELAY);
  }

  if (digitalRead(PIN_PREV) == LOW) {
    MediaKeyboard.press(MEDIA_PREV);
    MediaKeyboard.release();
    delay(DEBOUNCE_DELAY);
  }

  if (digitalRead(PIN_STOP) == LOW) {
    MediaKeyboard.press(MEDIA_STOP);
    MediaKeyboard.release();
    delay(DEBOUNCE_DELAY);
  }

  if (digitalRead(PIN_PLAY) == LOW) {
    MediaKeyboard.press(MEDIA_PLAY_PAUSE);
    MediaKeyboard.release();
    delay(DEBOUNCE_DELAY);
  }

  if (digitalRead(PIN_NEXT) == LOW) {
    MediaKeyboard.press(MEDIA_NEXT);
    MediaKeyboard.release();
    delay(DEBOUNCE_DELAY);
  }

  // check encoder
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos) {
    if (newPos < pos) {
      MediaKeyboard.press(VOLUME_DOWN);
      MediaKeyboard.release();
    }
    else {
      MediaKeyboard.press(VOLUME_UP);
      MediaKeyboard.release();
    }
    pos = newPos;
  }
}
