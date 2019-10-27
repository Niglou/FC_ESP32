

EXEC= firmware.bin

SRC_DIR=	main \
					lib

OBJ_DIR=	build

LIB_DIR=	main lib

LD_DIR=		ld


BIN=$(HOME)/esp/xtensa-esp32-elf/bin/
CC=$(BIN)xtensa-esp32-elf-gcc
LD=$(BIN)xtensa-esp32-elf-ld
SIZE=$(BIN)xtensa-esp32-elf-size

EXT= .c .cpp .S

ALL_SRC_DIRS= $(foreach dir, $(SRC_DIR), $(shell find $(dir) -type d))

SRC=$(foreach ext, $(EXT), $(wildcard $(ALL_SRC_DIRS:=/*$(ext))))
OBJ=$(foreach src, $(SRC), $(OBJ_DIR)/$(src:.cpp=.o)) #$(patsubst .cpp,,$(src)))
LIB=$(addprefix -I, $(LIB_DIR))
LDF=$(wildcard $(LD_DIR:=/*.ld))

CFLAGS= $(LIB)
LDFLAGS= $(addprefix -T, $(LDF))

all : firmware.bin
	@echo
	@$(SIZE) -B -d firmware.elf
	@echo

upload : all
	@#esptool.py -c esp32 write_flash 0x1000 firmware.bin #esp32
	@esptool.py -c esp32 write_flash -sc 6,17,8,11,16 0x1000 firmware.bin #esp32-pico-d4
	@echo
	@$(SIZE) -B -d firmware.elf
	@echo

erase :
	@esptool.py -c esp32 erase_flash -sc 6,17,8,11,16

monitor :
	@screen /dev/ttyUSB0 115200

firmware.bin :	firmware.elf
	@#esptool.py -c esp32 elf2image -ff 80m -fm dio -fs 4MB $< #esp32
	@esptool.py -c esp32 elf2image -ff 80m -fm dio -fs 4MB -sc 6,17,8,11,16 $< #esp32-pico-d4

firmware.elf :	$(OBJ)
	@$(LD) -v -Llib/ESP32 -L$(HOME)/esp/xtensa-esp32-elf/lib/gcc/xtensa-esp32-elf/8.2.0 $(LDFLAGS) $^ -o $@ -lgcc -lm
	@#$(LD) -v -Llib/ESP32 $(LDFLAGS) $^ -o $@ -lm

$(OBJ) : $(SRC) | $(addprefix $(OBJ_DIR)/, $(ALL_SRC_DIRS))
	@$(foreach file, $(SRC), $(CC) $(CFLAGS) -c $(file) -o $(OBJ_DIR)/$(file:.cpp=.o) && \
		echo "$(file) --> $(OBJ_DIR)/$(file:.cpp=.o)"; )

$(addprefix $(OBJ_DIR)/, $(ALL_SRC_DIRS)) :
	@mkdir -p $(addprefix $(OBJ_DIR)/, $(ALL_SRC_DIRS))

rebuild : clean all


clean :
	@rm -f -R $(addprefix $(OBJ_DIR)/, $(ALL_SRC_DIRS:=/*))

test :
	@echo $(ALL_SRC_DIRS)
