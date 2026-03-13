/********************************** (C) COPYRIGHT
 * ******************************* File Name          : composite_km_desc.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/18
 * Description        : All descriptors for the keyboard and mouse composite
 * device.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*******************************************************************************/
/* Header File */
#include "usbd_desc.h"

/*******************************************************************************/
/* Device Descriptor */
const uint8_t MyDevDescr[] = {
    0x12, // bLength
    0x01, // bDescriptorType
    0x00,
    0x02,               // bcdUSB
    0x00,               // bDeviceClass
    0x00,               // bDeviceSubClass
    0x00,               // bDeviceProtocol
    DEF_USBD_UEP0_SIZE, // bMaxPacketSize0
    (uint8_t)DEF_USB_VID,
    (uint8_t)(DEF_USB_VID >> 8), // idVendor
    (uint8_t)DEF_USB_PID,
    (uint8_t)(DEF_USB_PID >> 8), // idProduct
    0x03,
    DEF_IC_PRG_VER, // bcdDevice
    0x01,           // iManufacturer
    0x02,           // iProduct
    0x03,           // iSerialNumber
    0x01,           // bNumConfigurations
};

/* Configuration Descriptor Set */
const uint8_t MyCfgDescr[] = {
    /* Configuration Descriptor */
    0x09,       // bLength
    0x02,       // bDescriptorType
    0x3B, 0x00, // wTotalLength
    0x02,       // bNumInterfaces
    0x01,       // bConfigurationValue
    0x04,       // iConfiguration
    0xA0,       // bmAttributes: Bus Powered; Remote Wakeup
    0x96,       // MaxPower: 100mA

    /* Interface Descriptor (Mouse) */
    0x09, // bLength
    0x04, // bDescriptorType
    0x00, // bInterfaceNumber
    0x00, // bAlternateSetting
    0x01, // bNumEndpoints
    0x03, // bInterfaceClass
    0x01, // bInterfaceSubClass
    0x02, // bInterfaceProtocol: Keyboard
    0x00, // iInterface

    /* HID Descriptor (Mouse) */
    0x09,       // bLength
    0x21,       // bDescriptorType
    0x11, 0x01, // bcdHID
    0x00,       // bCountryCode
    0x01,       // bNumDescriptors
    0x22,       // bDescriptorType
    0x43, 0x00, // wDescriptorLength

    /* Endpoint Descriptor (Mouse) */
    0x07,       // bLength
    0x05,       // bDescriptorType
    0x81,       // bEndpointAddress: IN Endpoint 1
    0x03,       // bmAttributes
    0x08, 0x00, // wMaxPacketSize
    0x01,       // bInterval: 10mS

    /* Interface Descriptor (Keyboard ?) */
    0x09, // bLength
    0x04, // bDescriptorType
    0x01, // bInterfaceNumber
    0x00, // bAlternateSetting
    0x01, // bNumEndpoints
    0x03, // bInterfaceClass
    0x00, // bInterfaceSubClass
    0x00, // bInterfaceProtocol: Mouse
    0x00, // iInterface

    /* HID Descriptor (Keyboard ?) */
    0x09,       // bLength
    0x21,       // bDescriptorType
    0x11, 0x01, // bcdHID
    0x00,       // bCountryCode
    0x01,       // bNumDescriptors
    0x22,       // bDescriptorType
    0x97, 0x00, // wDescriptorLength

    /* Endpoint Descriptor (Keyboard ?) */
    0x07,       // bLength
    0x05,       // bDescriptorType
    0x82,       // bEndpointAddress: IN Endpoint 2
    0x03,       // bmAttributes
    0x14, 0x00, // wMaxPacketSize
    0x01        // bInterval: 1mS
};

/* Mouse Report Descriptor */
const uint8_t MouseRepDesc[] = {
    0x05, 0x01,       // Usage Page (Generic Desktop)
    0x09, 0x02,       // Usage (Mouse)
    0xA1, 0x01,       // Collection (Application)
    0x09, 0x01,       // Usage (Pointer)
    0xA1, 0x00,       // Collection (Physical)
    0x05, 0x09,       // Usage Page (Button)
    0x19, 0x01,       // Usage Minimum (Button 1)
    0x29, 0x10,       // Usage Maximum (Button 16)
    0x15, 0x00,       // Logical Minimum (0)
    0x25, 0x01,       // Logical Maximum (1)
    0x95, 0x10,       // Report Count (16)
    0x75, 0x01,       // Report Size (1)
    0x81, 0x02,       // Input (Data,Variable,Absolute)
    0x05, 0x01,       // Usage Page (Generic Desktop)
    0x16, 0x01, 0x80, // Logical Minimum (-32767)
    0x26, 0xFF, 0x7F, // Logical Maximum (32767)
    0x75, 0x10,       // Report Size (16)
    0x95, 0x02,       // Report Count (2)
    0x09, 0x30,       // Usage (X)
    0x09, 0x31,       // Usage (Y)
    0x81, 0x06,       // Input (Data,Variable,Relative)
    0x15, 0x81,       // Logical Minimum (-127)
    0x25, 0x7F,       // Logical Maximum (127)
    0x75, 0x08,       // Report Size (8)
    0x95, 0x01,       // Report Count (1)
    0x09, 0x38,       // Usage (Wheel)
    0x81, 0x06,       // Input (Data,Variable,Relative)
    0x05, 0x0C,       // Usage Page (Consumer)
    0x0A, 0x02, 0x38, // Usage (AC Pan)
    0x95, 0x01,       // Report Count (1)
    0x81, 0x06,       // Input (Data,Variable,Relative)
    0xC0,             // End Collection
    0xC0              // End Collection
};

/* Keyboard Report Descriptor */
const uint8_t KeyRepDesc[] = {
    0x05, 0x01,       // Usage Page (Generic Desktop Controls)
    0x09, 0x06,       // Usage (Keyboard)
    0xA1, 0x01,       // Collection (Application)
    0x85, 0x01,       //   Report ID (1)
    0x05, 0x07,       //   Usage Page (Keyboard/Keypad)
    0x19, 0xE0,       //   Usage Minimum (0xE0)
    0x29, 0xE7,       //   Usage Maximum (0xE7)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x01,       //   Logical Maximum (1)
    0x75, 0x01,       //   Report Size (1)
    0x95, 0x08,       //   Report Count (8)
    0x81, 0x02,       //   Input (Data,Var,Abs)
    0x81, 0x03,       //   Input (Const,Var,Abs)
    0x95, 0x06,       //   Report Count (6)
    0x75, 0x08,       //   Report Size (8)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xA4, 0x00, //   Logical Maximum (164)
    0x19, 0x00,       //   Usage Minimum (0x00)
    0x2A, 0xA4, 0x00, //   Usage Maximum (0xA4)
    0x81, 0x00,       //   Input (Data,Array,Abs)
    0xC0,             // End Collection
    0x05, 0x0C,       // Usage Page (Consumer)
    0x09, 0x01,       // Usage (Consumer Control)
    0xA1, 0x01,       // Collection (Application)
    0x85, 0x03,       //   Report ID (3)
    0x75, 0x10,       //   Report Size (16)
    0x95, 0x02,       //   Report Count (2)
    0x15, 0x01,       //   Logical Minimum (1)
    0x26, 0x8C, 0x02, //   Logical Maximum (652)
    0x19, 0x01,       //   Usage Minimum (0x01)
    0x2A, 0x8C, 0x02, //   Usage Maximum (0x28C)
    0x81, 0x00,       //   Input (Data,Array,Abs)
    0xC0,             // End Collection
    0x05, 0x01,       // Usage Page (Generic Desktop Controls)
    0x09, 0x80,       // Usage (System Control)
    0xA1, 0x01,       // Collection (Application)
    0x85, 0x04,       //   Report ID (4)
    0x75, 0x02,       //   Report Size (2)
    0x95, 0x01,       //   Report Count (1)
    0x15, 0x01,       //   Logical Minimum (1)
    0x25, 0x03,       //   Logical Maximum (3)
    0x09, 0x82,       //   Usage (System Sleep)
    0x09, 0x81,       //   Usage (System Power Down)
    0x09, 0x83,       //   Usage (System Wake Up)
    0x81, 0x60,       //   Input (Data,Array,Abs)
    0x75, 0x06,       //   Report Size (6)
    0x81, 0x03,       //   Input (Const,Var,Abs)
    0xC0,             // End Collection
    0x06, 0x00, 0xFF, // Usage Page (Vendor-Defined 0xFF00)
    0x09, 0x01,       // Usage (0x01)
    0xA1, 0x01,       // Collection (Application)
    0x85, 0x10,       //   Report ID (16)
    0x75, 0x08,       //   Report Size (8)
    0x95, 0x06,       //   Report Count (6)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x09, 0x01,       //   Usage (0x01)
    0x81, 0x00,       //   Input (Data,Array,Abs)
    0x09, 0x01,       //   Usage (0x01)
    0x91, 0x00,       //   Output (Data,Array,Abs)
    0xC0,             // End Collection
    0x06, 0x00, 0xFF, // Usage Page (Vendor-Defined 0xFF00)
    0x09, 0x02,       // Usage (0x02)
    0xA1, 0x01,       // Collection (Application)
    0x85, 0x11,       //   Report ID (17)
    0x75, 0x08,       //   Report Size (8)
    0x95, 0x13,       //   Report Count (19)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x09, 0x02,       //   Usage (0x02)
    0x81, 0x00,       //   Input (Data,Array,Abs)
    0x09, 0x02,       //   Usage (0x02)
    0x91, 0x00,       //   Output (Data,Array,Abs)
    0xC0              // End Collection
};

/* Qualifier Descriptor */
const uint8_t MyQuaDesc[] = {
    0x0A,       // bLength
    0x06,       // bDescriptorType
    0x00, 0x02, // bcdUSB
    0x00,       // bDeviceClass
    0x00,       // bDeviceSubClass
    0x00,       // bDeviceProtocol
    0x40,       // bMaxPacketSize0
    0x00,       // bNumConfigurations
    0x00        // bReserved
};

/* Language Descriptor */
const uint8_t MyLangDescr[] = {0x04, 0x03, 0x09, 0x04};

/* Manufacturer Descriptor */
const uint8_t MyManuInfo[] = {0x12, 0x03, 'L', 0,   'o', 0,   'g', 0,   'i',
                              0,    't',  0,   'e', 0,   'c', 0,   'h', 0};

/* Product Information */
const uint8_t MyProdInfo[] = {
    0x24, 0x03, 'G', 0, 'a', 0, 'm', 0, 'i', 0, 'n', 0, 'g', 0, ' ', 0, 'M', 0,
    'o',  0,    'u', 0, 's', 0, 'e', 0, ' ', 0, 'G', 0, '4', 0, '0', 0, '2', 0};

/* Serial Number Information */
const uint8_t MySerNumInfo[] = {0x1A, 0x03, '8', 0,   'D', 0,   '8', 0,   'B',
                                0,    '3',  0,   '4', 0,   '6', 0,   'B', 0,
                                '5',  0,    '4', 0,   '5', 0,   '5', 0};
