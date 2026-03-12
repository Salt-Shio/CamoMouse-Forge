# HID Information

## Device Descriptor

<details>
    <summary>Device Descriptor</summary>

```
DEVICE DESCRIPTOR
    o bLength: 18
    o bDescriptorType: 0x01 (DEVICE)
    o bcdUSB: 0x0200
    o bDeviceClass: Device (0x00)
    o bDeviceSubClass: 0
    o bDeviceProtocol: 0 (Use class code info from Interface Descriptors)
    o bMaxPacketSize0: 64
    o idVendor: Logitech, Inc. (0x046d)
    o idProduct: G402 Gaming Mouse (0xc07e)
    o bcdDevice: 0x9003
    o iManufacturer: 1
    o iProduct: 2
    o iSerialNumber: 3
    o bNumConfigurations: 1
```
</details>

<details>
    <summary>Configuration Descriptor</summary>

```
CONFIGURATION DESCRIPTOR
    o bLength: 9
    o bDescriptorType: 0x02 (CONFIGURATION)
    o wTotalLength: 59
    o bNumInterfaces: 2
    o bConfigurationValue: 1
    o iConfiguration: 4
    o Configuration bmAttributes: 0xa0  NOT SELF-POWERED  REMOTE-WAKEUP
         1... .... = Must be 1: Must be 1 for USB 1.1 and higher
         .0.. .... = Self-Powered: This device is powered from the USB bus
         ..1. .... = Remote Wakeup: This device supports REMOTE WAKEUP
    o bMaxPower: 150  (300mA)
```
</details>

<details>
    <summary>Interface Descriptor (0.0) - Mouse/HID</summary>

```
INTERFACE DESCRIPTOR (0.0): class HID
    o bLength: 9
    o bDescriptorType: 0x04 (INTERFACE)
    o bInterfaceNumber: 0
    o bAlternateSetting: 0
    o bNumEndpoints: 1
    o bInterfaceClass: HID (0x03)
    o bInterfaceSubClass: Boot Interface (0x01)
    o bInterfaceProtocol: Mouse (0x02)
    o iInterface: 0

HID DESCRIPTOR
    o bLength: 9
    o bDescriptorType: 0x21 (HID)
    o bcdHID: 0x0111
    o bCountryCode: Not Supported (0x00)
    o bNumDescriptors: 1
    o bDescriptorType: HID Report (0x22)
    o wDescriptorLength: 67

ENDPOINT DESCRIPTOR
    o bLength: 7
    o bDescriptorType: 0x05 (ENDPOINT)
    o bEndpointAddress: 0x81  IN  Endpoint:1
        1... .... = Direction: IN Endpoint
        .... 0001 = Endpoint Number: 0x1
    o bmAttributes: 0x03
        .... ..11 = Transfertype: Interrupt-Transfer (0x3)
    o wMaxPacketSize: 8
        ...0 0... .... .... = Transactions per microframe: 1 (0)
        .... .000 0000 1000 = Maximum Packet Size: 8
    o bInterval: 1
```
</details>

<details>
    <summary>Interface Descriptor (1.0) - Keyboard/HID</summary>

```
INTERFACE DESCRIPTOR (1.0): class HID
    o bLength: 9
    o bDescriptorType: 0x04 (INTERFACE)
    o bInterfaceNumber: 1
    o bAlternateSetting: 0
    o bNumEndpoints: 1
    o bInterfaceClass: HID (0x03)
    o bInterfaceSubClass: No Subclass (0x00)
    o bInterfaceProtocol: 0x00 (挺特殊，正常來講要是 Keyboard: 0x1, Mouse: 0x2)
    o iInterface: 0

HID DESCRIPTOR
    o bLength: 9
    o bDescriptorType: 0x21 (HID)
    o bcdHID: 0x0111
    o bCountryCode: Not Supported (0x00)
    o bNumDescriptors: 1
    o bDescriptorType: HID Report (0x22)
    o wDescriptorLength: 151

ENDPOINT DESCRIPTOR
    o bLength: 7
    o bDescriptorType: 0x05 (ENDPOINT)
    o bEndpointAddress: 0x82  IN  Endpoint:2
        1... .... = Direction: IN Endpoint
        .... 0010 = Endpoint Number: 0x2
    o bmAttributes: 0x03
        .... ..11 = Transfertype: Interrupt-Transfer (0x3)
    o wMaxPacketSize: 20
        ...0 0... .... .... = Transactions per microframe: 1 (0)
        .... .000 0001 0100 = Maximum Packet Size: 20
    o bInterval: 1
```
</details>

<details>
    <summary>Mouse HID Report Descriptor (67 bytes)</summary>

```
    HID Report
        Usage Page (Generic Desktop Controls)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0000 .... = bTag: Usage Page (0x0)
            Usage Page: Generic Desktop Controls (0x01)
        Usage (Mouse)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: Mouse (0x02)
        Collection (Application)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1010 .... = bTag: Collection (0xa)
            Collection type: Application (0x01)
            Usage (Pointer)
                Header
                    .... ..01 = bSize: 1 byte (1)
                    .... 10.. = bType: Local (2)
                    0000 .... = bTag: Usage (0x0)
                Usage: Pointer (0x01)
            Collection (Physical)
                Header
                    .... ..01 = bSize: 1 byte (1)
                    .... 00.. = bType: Main (0)
                    1010 .... = bTag: Collection (0xa)
                Collection type: Physical (0x00)
                Usage Page (Button)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0000 .... = bTag: Usage Page (0x0)
                    Usage Page: Button (0x09)
                Usage Minimum (0x01)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 10.. = bType: Local (2)
                        0001 .... = bTag: Usage Minimum (0x1)
                    Usage minimum: 0x01
                Usage Maximum (0x10)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 10.. = bType: Local (2)
                        0010 .... = bTag: Usage Maximum (0x2)
                    Usage maximum: 0x10
                Logical Minimum (0)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0001 .... = bTag: Logical Minimum (0x1)
                    Logical minimum: 0
                Logical Maximum (1)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0010 .... = bTag: Logical Maximum (0x2)
                    Logical maximum: 1
                Report Count (16)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        1001 .... = bTag: Report Count (0x9)
                    Report count: 16
                Report Size (1)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0111 .... = bTag: Report Size (0x7)
                    Report size: 1
                Input (Data,Var,Abs)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 00.. = bType: Main (0)
                        1000 .... = bTag: Input (0x8)
                    .... .... 0 = Data/constant: Data
                    .... ...1 . = Data type: Variable
                    .... ..0. . = Coordinates: Absolute
                    .... .0.. . = Min/max wraparound: No Wrap
                    .... 0... . = Physical relationship to data: Linear
                    ...0 .... . = Preferred state: Preferred State
                    ..0. .... . = Has null position: No Null position
                    .0.. .... . = [Reserved]: False
                    0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
                Usage Page (Generic Desktop Controls)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0000 .... = bTag: Usage Page (0x0)
                    Usage Page: Generic Desktop Controls (0x01)
                Logical Minimum (-32767)
                    Header
                        .... ..10 = bSize: 2 bytes (2)
                        .... 01.. = bType: Global (1)
                        0001 .... = bTag: Logical Minimum (0x1)
                    Logical minimum: -32767
                Logical Maximum (32767)
                    Header
                        .... ..10 = bSize: 2 bytes (2)
                        .... 01.. = bType: Global (1)
                        0010 .... = bTag: Logical Maximum (0x2)
                    Logical maximum: 32767
                Report Size (16)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0111 .... = bTag: Report Size (0x7)
                    Report size: 16
                Report Count (2)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        1001 .... = bTag: Report Count (0x9)
                    Report count: 2
                Usage (X)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 10.. = bType: Local (2)
                        0000 .... = bTag: Usage (0x0)
                    Usage: X (0x30)
                Usage (Y)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 10.. = bType: Local (2)
                        0000 .... = bTag: Usage (0x0)
                    Usage: Y (0x31)
                Input (Data,Var,Rel)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 00.. = bType: Main (0)
                        1000 .... = bTag: Input (0x8)
                    .... .... 0 = Data/constant: Data
                    .... ...1 . = Data type: Variable
                    .... ..1. . = Coordinates: Relative
                    .... .0.. . = Min/max wraparound: No Wrap
                    .... 0... . = Physical relationship to data: Linear
                    ...0 .... . = Preferred state: Preferred State
                    ..0. .... . = Has null position: No Null position
                    .0.. .... . = [Reserved]: False
                    0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
                Logical Minimum (-127)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0001 .... = bTag: Logical Minimum (0x1)
                    Logical minimum: -127
                Logical Maximum (127)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0010 .... = bTag: Logical Maximum (0x2)
                    Logical maximum: 127
                Report Size (8)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0111 .... = bTag: Report Size (0x7)
                    Report size: 8
                Report Count (1)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        1001 .... = bTag: Report Count (0x9)
                    Report count: 1
                Usage (Wheel)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 10.. = bType: Local (2)
                        0000 .... = bTag: Usage (0x0)
                    Usage: Wheel (0x38)
                Input (Data,Var,Rel)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 00.. = bType: Main (0)
                        1000 .... = bTag: Input (0x8)
                    .... .... 0 = Data/constant: Data
                    .... ...1 . = Data type: Variable
                    .... ..1. . = Coordinates: Relative
                    .... .0.. . = Min/max wraparound: No Wrap
                    .... 0... . = Physical relationship to data: Linear
                    ...0 .... . = Preferred state: Preferred State
                    ..0. .... . = Has null position: No Null position
                    .0.. .... . = [Reserved]: False
                    0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
                Usage Page (Consumer)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        0000 .... = bTag: Usage Page (0x0)
                    Usage Page: Consumer (0x0c)
                Usage (Instance 14338)
                    Header
                        .... ..10 = bSize: 2 bytes (2)
                        .... 10.. = bType: Local (2)
                        0000 .... = bTag: Usage (0x0)
                    Usage: Instance 14338 (0x3802)
                Report Count (1)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 01.. = bType: Global (1)
                        1001 .... = bTag: Report Count (0x9)
                    Report count: 1
                Input (Data,Var,Rel)
                    Header
                        .... ..01 = bSize: 1 byte (1)
                        .... 00.. = bType: Main (0)
                        1000 .... = bTag: Input (0x8)
                    .... .... 0 = Data/constant: Data
                    .... ...1 . = Data type: Variable
                    .... ..1. . = Coordinates: Relative
                    .... .0.. . = Min/max wraparound: No Wrap
                    .... 0... . = Physical relationship to data: Linear
                    ...0 .... . = Preferred state: Preferred State
                    ..0. .... . = Has null position: No Null position
                    .0.. .... . = [Reserved]: False
                    0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
                End Collection
                    Header
                        .... ..00 = bSize: 0 bytes (0)
                        .... 00.. = bType: Main (0)
                        1100 .... = bTag: End Collection (0xc)
            End Collection
                Header
                    .... ..00 = bSize: 0 bytes (0)
                    .... 00.. = bType: Main (0)
                    1100 .... = bTag: End Collection (0xc)
```
</details>

<details>
    <summary>Key HID Report Descriptor (151 bytes)</summary>

```
HID Report
    Usage Page (Generic Desktop Controls)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 01.. = bType: Global (1)
            0000 .... = bTag: Usage Page (0x0)
        Usage Page: Generic Desktop Controls (0x01)
    Usage (Keyboard)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 10.. = bType: Local (2)
            0000 .... = bTag: Usage (0x0)
        Usage: Keyboard (0x06)
    Collection (Application)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 00.. = bType: Main (0)
            1010 .... = bTag: Collection (0xa)
        Collection type: Application (0x01)
        Report ID (0x01)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1000 .... = bTag: Report ID (0x8)
            Report ID: 0x01
        Usage Page (Keyboard/Keypad)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0000 .... = bTag: Usage Page (0x0)
            Usage Page: Keyboard/Keypad (0x07)
        Usage Minimum (0xe0)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0001 .... = bTag: Usage Minimum (0x1)
            Usage minimum: 0xe0
        Usage Maximum (0xe7)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0010 .... = bTag: Usage Maximum (0x2)
            Usage maximum: 0xe7
        Logical Minimum (0)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0001 .... = bTag: Logical Minimum (0x1)
            Logical minimum: 0
        Logical Maximum (1)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0010 .... = bTag: Logical Maximum (0x2)
            Logical maximum: 1
        Report Size (1)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 1
        Report Count (8)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1001 .... = bTag: Report Count (0x9)
            Report count: 8
        Input (Data,Var,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 0 = Data/constant: Data
            .... ...1 . = Data type: Variable
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        Input (Const,Var,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 1 = Data/constant: Constant
            .... ...1 . = Data type: Variable
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        Report Count (6)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1001 .... = bTag: Report Count (0x9)
            Report count: 6
        Report Size (8)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 8
        Logical Minimum (0)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0001 .... = bTag: Logical Minimum (0x1)
            Logical minimum: 0
        Logical Maximum (164)
            Header
                .... ..10 = bSize: 2 bytes (2)
                .... 01.. = bType: Global (1)
                0010 .... = bTag: Logical Maximum (0x2)
            Logical maximum: 164
        Usage Minimum (0x00)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0001 .... = bTag: Usage Minimum (0x1)
            Usage minimum: 0x00
        Usage Maximum (0xa4)
            Header
                .... ..10 = bSize: 2 bytes (2)
                .... 10.. = bType: Local (2)
                0010 .... = bTag: Usage Maximum (0x2)
            Usage maximum: 0xa4
        Input (Data,Array,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        End Collection
            Header
                .... ..00 = bSize: 0 bytes (0)
                .... 00.. = bType: Main (0)
                1100 .... = bTag: End Collection (0xc)
    Usage Page (Consumer)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 01.. = bType: Global (1)
            0000 .... = bTag: Usage Page (0x0)
        Usage Page: Consumer (0x0c)
    Usage (Consumer Control)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 10.. = bType: Local (2)
            0000 .... = bTag: Usage (0x0)
        Usage: Consumer Control (0x01)
    Collection (Application)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 00.. = bType: Main (0)
            1010 .... = bTag: Collection (0xa)
        Collection type: Application (0x01)
        Report ID (0x03)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1000 .... = bTag: Report ID (0x8)
            Report ID: 0x03
        Report Size (16)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 16
        Report Count (2)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1001 .... = bTag: Report Count (0x9)
            Report count: 2
        Logical Minimum (1)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0001 .... = bTag: Logical Minimum (0x1)
            Logical minimum: 1
        Logical Maximum (652)
            Header
                .... ..10 = bSize: 2 bytes (2)
                .... 01.. = bType: Global (1)
                0010 .... = bTag: Logical Maximum (0x2)
            Logical maximum: 652
        Usage Minimum (0x01)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0001 .... = bTag: Usage Minimum (0x1)
            Usage minimum: 0x01
        Usage Maximum (0x28c)
            Header
                .... ..10 = bSize: 2 bytes (2)
                .... 10.. = bType: Local (2)
                0010 .... = bTag: Usage Maximum (0x2)
            Usage maximum: 0x28c
        Input (Data,Array,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        End Collection
            Header
                .... ..00 = bSize: 0 bytes (0)
                .... 00.. = bType: Main (0)
                1100 .... = bTag: End Collection (0xc)
    Usage Page (Generic Desktop Controls)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 01.. = bType: Global (1)
            0000 .... = bTag: Usage Page (0x0)
        Usage Page: Generic Desktop Controls (0x01)
    Usage (System Control)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 10.. = bType: Local (2)
            0000 .... = bTag: Usage (0x0)
        Usage: System Control (0x80)
    Collection (Application)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 00.. = bType: Main (0)
            1010 .... = bTag: Collection (0xa)
        Collection type: Application (0x01)
        Report ID (0x04)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1000 .... = bTag: Report ID (0x8)
            Report ID: 0x04
        Report Size (2)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 2
        Report Count (1)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1001 .... = bTag: Report Count (0x9)
            Report count: 1
        Logical Minimum (1)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0001 .... = bTag: Logical Minimum (0x1)
            Logical minimum: 1
        Logical Maximum (3)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0010 .... = bTag: Logical Maximum (0x2)
            Logical maximum: 3
        Usage (System Sleep)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: System Sleep (0x82)
        Usage (System Power Down)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: System Power Down (0x81)
        Usage (System Wake Up)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: System Wake Up (0x83)
        Input (Data,Array,Abs,NoPref,Null)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...1 .... . = Preferred state: No Preferred
            ..1. .... . = Has null position: Null state
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        Report Size (6)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 6
        Input (Const,Var,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 1 = Data/constant: Constant
            .... ...1 . = Data type: Variable
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        End Collection
            Header
                .... ..00 = bSize: 0 bytes (0)
                .... 00.. = bType: Main (0)
                1100 .... = bTag: End Collection (0xc)
    Usage Page (Vendor)
        Header
            .... ..10 = bSize: 2 bytes (2)
            .... 01.. = bType: Global (1)
            0000 .... = bTag: Usage Page (0x0)
        Usage Page: Vendor (0xff00)
    Usage (Vendor)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 10.. = bType: Local (2)
            0000 .... = bTag: Usage (0x0)
        Usage: Vendor (0x01)
    Collection (Application)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 00.. = bType: Main (0)
            1010 .... = bTag: Collection (0xa)
        Collection type: Application (0x01)
        Report ID (0x10)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1000 .... = bTag: Report ID (0x8)
            Report ID: 0x10
        Report Size (8)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 8
        Report Count (6)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1001 .... = bTag: Report Count (0x9)
            Report count: 6
        Logical Minimum (0)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0001 .... = bTag: Logical Minimum (0x1)
            Logical minimum: 0
        Logical Maximum (255)
            Header
                .... ..10 = bSize: 2 bytes (2)
                .... 01.. = bType: Global (1)
                0010 .... = bTag: Logical Maximum (0x2)
            Logical maximum: 255
        Usage (Vendor)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: Vendor (0x01)
        Input (Data,Array,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        Usage (Vendor)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: Vendor (0x01)
        Output (Data,Array,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1001 .... = bTag: Output (0x9)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = (Non)-volatile: Non Volatile
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        End Collection
            Header
                .... ..00 = bSize: 0 bytes (0)
                .... 00.. = bType: Main (0)
                1100 .... = bTag: End Collection (0xc)
    Usage Page (Vendor)
        Header
            .... ..10 = bSize: 2 bytes (2)
            .... 01.. = bType: Global (1)
            0000 .... = bTag: Usage Page (0x0)
        Usage Page: Vendor (0xff00)
    Usage (Vendor)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 10.. = bType: Local (2)
            0000 .... = bTag: Usage (0x0)
        Usage: Vendor (0x02)
    Collection (Application)
        Header
            .... ..01 = bSize: 1 byte (1)
            .... 00.. = bType: Main (0)
            1010 .... = bTag: Collection (0xa)
        Collection type: Application (0x01)
        Report ID (0x11)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1000 .... = bTag: Report ID (0x8)
            Report ID: 0x11
        Report Size (8)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0111 .... = bTag: Report Size (0x7)
            Report size: 8
        Report Count (19)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                1001 .... = bTag: Report Count (0x9)
            Report count: 19
        Logical Minimum (0)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 01.. = bType: Global (1)
                0001 .... = bTag: Logical Minimum (0x1)
            Logical minimum: 0
        Logical Maximum (255)
            Header
                .... ..10 = bSize: 2 bytes (2)
                .... 01.. = bType: Global (1)
                0010 .... = bTag: Logical Maximum (0x2)
            Logical maximum: 255
        Usage (Vendor)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: Vendor (0x02)
        Input (Data,Array,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1000 .... = bTag: Input (0x8)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = [Reserved]: False
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        Usage (Vendor)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 10.. = bType: Local (2)
                0000 .... = bTag: Usage (0x0)
            Usage: Vendor (0x02)
        Output (Data,Array,Abs)
            Header
                .... ..01 = bSize: 1 byte (1)
                .... 00.. = bType: Main (0)
                1001 .... = bTag: Output (0x9)
            .... .... 0 = Data/constant: Data
            .... ...0 . = Data type: Array
            .... ..0. . = Coordinates: Absolute
            .... .0.. . = Min/max wraparound: No Wrap
            .... 0... . = Physical relationship to data: Linear
            ...0 .... . = Preferred state: Preferred State
            ..0. .... . = Has null position: No Null position
            .0.. .... . = (Non)-volatile: Non Volatile
            0... .... . = Bits or bytes: Buffered bytes (default, no second byte present)
        End Collection
            Header
                .... ..00 = bSize: 0 bytes (0)
                .... 00.. = bType: Main (0)
                1100 .... = bTag: End Collection (0xc)
```
</details>

<details>
    <summary>String Descriptor (USBTreeViewer)</summary>

```

      -------------------- String Descriptors -------------------
             ------ String Descriptor 0 ------
bLength                  : 0x04 (4 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language ID[0]           : 0x0409 (English - United States)
             ------ String Descriptor 1 ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Logitech"
             ------ String Descriptor 2 ------
bLength                  : 0x24 (36 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Gaming Mouse G402"
             ------ String Descriptor 3 ------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "8D8B346B5455"
             ------ String Descriptor 4 ------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "U90.03_B0020            "  *!*CAUTION  trailing space characters
```

```
Manufacturer String      : "Logitech"
Product String           : "Gaming Mouse G402"
Serial                   : "8D8B346B5455"
```

</details>


## HID Data Pack

### Mouse Data Pack

滑鼠的滑動，左右鍵點擊，中鍵點擊，滾輪的滑動

```
HID Data: 00 00 0000 0000 00 00
    .......0 = Button: 1 (primary/trigger): UP (左鍵 UP: 0, DOWN: 1)
    ......0. = Button: 2 (secondary): UP (右鍵 UP: 0, DOWN: 1)
    .....0.. = Button: 3 (tertiary): UP (中鍵 UP: 0, DOWN: 1)
    ....0... = Button: 4: UP (側鍵後 UP: 0, DOWN: 1)
    ...0.... = Button: 5: UP (側鍵前 UP: 0, DOWN: 1)
    ..0..... = Button: 6: UP
    .0...... = Button: 7: UP
    0....... = Button: 8: UP 
    .......0 = Button: 9: UP
    ......0. = Button: 10: UP
    .....0.. = Button: 11: UP
    ....0... = Button: 12: UP
    ...0.... = Button: 13: UP
    ..0..... = Button: 14: UP
    .0...... = Button: 15: UP
    0....... = Button: 16: UP
    00000000  00000000 = X Axis: 0 (RIGHT: -1, LEFT: 1)
    00000000  00000000 = Y Axis: 0 (UP: -1, DOWN: 1)
    00000000 = Usage: Wheel: 0 (UP: 1, DOWN: -1)
    00000000 = Usage: AC Pan: 0
```

### Keyboard Data Pack

這裡就是 側鍵 以及控制 DPI 的功能
