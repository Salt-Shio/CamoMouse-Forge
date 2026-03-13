// #include "g402_pack_builder.h"
// #include "ch32v30x_usbfs_device.h"
// #include "string.h"
// #include <stdint.h>

// void Send_Mouse_Data_Pack(uint8_t button_code, int16_t delta_x, int16_t delta_y) {
//     struct Mouse_Data_Pack pack;
//     memset(&pack, 0, sizeof(pack));
//     pack.BUTTON_CODE = button_code;
//     pack.DELTA_X = delta_x;
//     pack.DELTA_Y = delta_y;
//     USBFS_Endp_DataUp(MOUSE_ENDPOINT, (uint8_t*)&pack, sizeof(pack), DEF_UEP_CPY_LOAD);
// }

// void Send_Keyboard_Data_Pack(uint8_t dpi_state) {
//     struct Keyboard_Data_Pack pack;
//     memset(&pack, 0, sizeof(pack));
//     pack.REPORT_ID = 0x11;
//     pack.FEATURE_CODE_1 = 0xff;
//     pack.FEATURE_CODE_2 = 0x0f;
//     pack.FEATURE_CODE_3 = 0x10;
//     pack.DPI_STATE = dpi_state;
//     USBFS_Endp_DataUp(KEYBOARD_ENDPOINT, (uint8_t*)&pack, sizeof(pack), DEF_UEP_CPY_LOAD);
// }

#include "g402_pack_builder.h"
#include "ch32v30x_usbfs_device.h"
#include "string.h"
#include <stdint.h>

void Send_Mouse_Data_Pack(uint8_t button_code, int16_t delta_x, int16_t delta_y) {
    struct Mouse_Data_Pack pack;
    memset(&pack, 0, sizeof(pack));
    
    pack.BUTTON_CODE = button_code;
    pack.DELTA_X = delta_x;
    pack.DELTA_Y = delta_y;
    
    uint8_t status;
    uint32_t timeout = 0xFFFF; 
    do {
        status = USBFS_Endp_DataUp(MOUSE_ENDPOINT, (uint8_t *)&pack, sizeof(pack), DEF_UEP_CPY_LOAD);
        timeout--;
    } while (status != READY && timeout > 0);
}

void Send_Keyboard_Data_Pack(uint8_t dpi_state) {
    struct Keyboard_Data_Pack pack;
    memset(&pack, 0, sizeof(pack));
    
    pack.REPORT_ID = 0x11;
    pack.FEATURE_CODE_1 = 0xff;
    pack.FEATURE_CODE_2 = 0x0f;
    pack.FEATURE_CODE_3 = 0x10;
    pack.DPI_STATE = dpi_state;
    
    uint8_t status;
    uint32_t timeout = 0xFFFF;
    do {
        status = USBFS_Endp_DataUp(KEYBOARD_ENDPOINT, (uint8_t *)&pack, sizeof(pack), DEF_UEP_CPY_LOAD);
        timeout--;
    } while (status != READY && timeout > 0);
}