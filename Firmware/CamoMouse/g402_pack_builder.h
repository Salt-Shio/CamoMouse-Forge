#include "stdint.h"

#define MOUSE_ENDPOINT 0x01
#define KEYBOARD_ENDPOINT 0x02

enum MOUSE_BUTTON_CODE {
    BUTTON_ALLUP = 0x00,
    BUTTON_LEFT = 0x01,
    BUTTON_RIGHT = 0x02,
    BUTTON_MIDDLE = 0x04,
    BUTTON_SIDE_BACK = 0x08,
    BUTTON_SIDE_FORWARD = 0x10
};

typedef struct Mouse_Data_Pack {
    uint8_t BUTTON_CODE;
    uint8_t PAD;
    int16_t DELTA_X;
    int16_t DELTA_Y;
    uint8_t WHEEL;
    uint8_t WHEEL_PAD;
} __attribute__((packed));

enum KEYBOARD_DPI_STATE {
    DPI_K_STATE_0 = 0x00,
    DPI_K_STATE_1 = 0x01,
    DPI_K_STATE_2 = 0x02,
    DPI_K_STATE_3 = 0x03
};

typedef struct Keyboard_Data_Pack {
    uint8_t REPORT_ID;
    uint8_t FEATURE_CODE_1;
    uint8_t FEATURE_CODE_2;
    uint8_t FEATURE_CODE_3;
    uint8_t DPI_STATE;
    uint8_t PAD[15];
};

// 只用我想要的功能

void Send_Mouse_Data_Pack(uint8_t button_code, int16_t delta_x, int16_t delta_y);
void Send_Keyboard_Data_Pack(uint8_t dpi_state);

