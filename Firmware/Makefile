# ============================================================================
# Google Antigravity (MRS 2.0 轉換) 專用 Makefile for CH32V307
# ============================================================================

TARGET = CamoMouse-Forge
BUILD_DIR = build
USER_DIR ?= User # 如果要改成想偽裝的滑鼠要放 CamoMouse (因為這是修改後的專案)
WCH_LIB_DIR = SRC

TOOLCHAIN_PATH ?= 
# D:/MounRiver/MounRiver_Studio2/resources/app/resources/win32/components/WCH/Toolchain/RISC-V Embedded GCC/bin

ifeq ($(strip $(TOOLCHAIN_PATH)),)
$(error [CamoMouseForge 編譯錯誤] 需要編譯器路徑！請在終端機輸入: make TOOLCHAIN_PATH="你的/MRS/Toolchain/bin/路徑" ，或者直接編輯 Makefile 填寫 TOOLCHAIN_PATH 變數)
endif

CC      = "$(TOOLCHAIN_PATH)/riscv-none-embed-gcc.exe"
AS      = "$(TOOLCHAIN_PATH)/riscv-none-embed-gcc.exe" -x assembler-with-cpp
OBJCOPY = "$(TOOLCHAIN_PATH)/riscv-none-embed-objcopy.exe"
OBJDUMP = "$(TOOLCHAIN_PATH)/riscv-none-embed-objdump.exe"
SIZE    = "$(TOOLCHAIN_PATH)/riscv-none-embed-size.exe"

C_SOURCES = \
$(wildcard $(USER_DIR)/*.c) \
$(WCH_LIB_DIR)/Core/core_riscv.c \
$(WCH_LIB_DIR)/Debug/debug.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_rcc.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_gpio.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_misc.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_exti.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_tim.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_usart.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_pwr.c \
$(WCH_LIB_DIR)/Peripheral/src/ch32v30x_dbgmcu.c

ASM_SOURCES = \
$(WCH_LIB_DIR)/Startup/startup_ch32v30x_D8C.S

LDSCRIPT = $(WCH_LIB_DIR)/Ld/Link.ld

MCU = -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore
CFLAGS = $(MCU) -Os -Wall -fmessage-length=0 -fsigned-char \
-ffunction-sections -fdata-sections -Wunused -Wuninitialized -g

C_INCLUDES = \
-I$(USER_DIR) \
-I$(WCH_LIB_DIR)/Core \
-I$(WCH_LIB_DIR)/Peripheral/inc \
-I$(WCH_LIB_DIR)/Debug

CFLAGS += $(C_INCLUDES)

LDFLAGS = $(MCU) -T$(LDSCRIPT) -nostartfiles -Xlinker --gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map --specs=nano.specs --specs=nosys.specs

# ============================================================================
# 編譯規則 (Build Rules)
# ============================================================================

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary -S $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)

.PHONY: all clean