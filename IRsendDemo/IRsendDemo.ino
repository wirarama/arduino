/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = D2;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

uint16_t rawData[135] = {4554, 4502,  614, 1632,  612, 1632,  610, 1634,  640, 484,  560, 562,  640, 484,  562, 562,  612, 512,  560, 1682,  614, 1630,  610, 1660,  614, 482,  560, 564,  560, 562,  560, 562,  614, 510,  560, 564,  612, 1630,  612, 512,  642, 482,  560, 564,  610, 512,  614, 510,  668, 456,  560, 1684,  612, 510,  610, 1660,  612, 1604,  638, 1606,  614, 1630,  562, 1682,  668, 1574,  642, 46748,  4646, 4394,  672, 1574,  642, 1600,  672, 1572,  672, 452,  670, 452,  642, 482,  668, 454,  668, 456,  642, 1602,  644, 1600,  642, 1602,  670, 454,  640, 482,  642, 482,  640, 482,  668, 456,  672, 450,  642, 1602,  728, 396,  670, 454,  642, 480,  640, 482,  700, 422,  642, 482,  668, 1600,  646, 452,  644, 1600,  644, 1626,  644, 1572,  672, 1574,  642, 1602,  644, 1600,  642};  // SAMSUNG E0E040BF

void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
  Serial.println("mengirim infrared");
  irsend.sendRaw(rawData, 135, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
}
