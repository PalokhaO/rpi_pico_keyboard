/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+

#define KB_REPORT_LENGTH 8

// from USB HID Specification 1.1, Appendix B.1
static const uint8_t desc_hid_report[] = {
  0x05, 0x01,                    // Usage Page (Generic Desktop)
  0x09, 0x06,                    // Usage (Keyboard)
  0xa1, 0x01,                    // Collection (Application)

  0x85,  0x01,                   // Report ID 1

  // Modifier byte

  0x75, 0x01,                    //   Report Size (1)
  0x95, 0x08,                    //   Report Count (8)
  0x05, 0x07,                    //   Usage Page (Key codes)
  0x19, 0xe0,                    //   Usage Minimum (Keyboard LeftControl)
  0x29, 0xe7,                    //   Usage Maxium (Keyboard Right GUI)
  0x15, 0x00,                    //   Logical Minimum (0)
  0x25, 0x01,                    //   Logical Maximum (1)
  0x81, 0x02,                    //   Input (Data, Variable, Absolute)

  // Reserved byte

  0x75, 0x01,                    //   Report Size (1)
  0x95, 0x08,                    //   Report Count (8)
  0x81, 0x03,                    //   Input (Constant, Variable, Absolute)

  // LED report + padding

  0x95, 0x05,                    //   Report Count (5)
  0x75, 0x01,                    //   Report Size (1)
  0x05, 0x08,                    //   Usage Page (LEDs)
  0x19, 0x01,                    //   Usage Minimum (Num Lock)
  0x29, 0x05,                    //   Usage Maxium (Kana)
  0x91, 0x02,                    //   Output (Data, Variable, Absolute)

  0x95, 0x01,                    //   Report Count (1)
  0x75, 0x03,                    //   Report Size (3)
  0x91, 0x03,                    //   Output (Constant, Variable, Absolute)

  // Keycodes

  0x95, 0x06,                    //   Report Count (6)
  0x75, 0x08,                    //   Report Size (8)
  0x15, 0x00,                    //   Logical Minimum (0)
  0x25, 0xff,                    //   Logical Maximum (1)
  0x05, 0x07,                    //   Usage Page (Key codes)
  0x19, 0x00,                    //   Usage Minimum (Reserved (no event indicated))
  0x29, 0xff,                    //   Usage Maxium (Reserved)
  0x81, 0x00,                    //   Input (Data, Array)

  0xc0,                          // End collection
};
static const size_t desc_hid_size = sizeof(desc_hid_report);

enum
{
  REPORT_ID_KEYBOARD = 1,
  // REPORT_ID_MOUSE,
  // REPORT_ID_CONSUMER_CONTROL,
  // REPORT_ID_GAMEPAD,
  // REPORT_ID_COUNT
};

#endif /* USB_DESCRIPTORS_H_ */
