#include "MediaKeyboard.h"

#if defined(USBCON)
#include "usbd_hid_consumer_if.h"

uint8_t m[3] = {0x02, 0x00, 0x00 };

MediaKeyboard_::MediaKeyboard_(void) {
}
 
void MediaKeyboard_::begin(void) {
	HID_Composite_Init(HID_CONSUMER);
}
 
void MediaKeyboard_::end(void) {
	HID_Composite_DeInit(HID_CONSUMER);
}

void MediaKeyboard_::press(uint8_t mediaKey) {
	m[1] = mediaKey;
	HID_Composite_consumer_sendReport(m, 3);
}

void MediaKeyboard_::release() {
	delay(10);
	m[1] = 0x00;
	HID_Composite_consumer_sendReport(m, 3);
}

MediaKeyboard_ MediaKeyboard;

#endif