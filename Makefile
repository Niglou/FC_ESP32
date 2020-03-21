
ESP32-NONOS:= /media/DATA/Espressif_project/esp32-nonos

include $(ESP32-NONOS)/Header.mk


LD_DIR:= $(ESP32-NONOS)/ld

CC:=	$(XTENSA)/bin/xtensa-esp32-elf-gcc
LD:=	$(XTENSA)/bin/xtensa-esp32-elf-ld
SIZE:=$(XTENSA)/bin/xtensa-esp32-elf-size

ESP32_OBJ:= $(wildcard $(ESP32-NONOS)/builds/*.o)

NAME:= $(shell basename `pwd`)
DIR_SRC:= $(shell find -type d -not -path './.*')
SRC:=	$(shell find -name '*.S' -o -name '*.c' -o -name '*.cpp')
OBJ:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(SRC))))
LD_FILES:= $(wildcard $(LD_DIR:=/*.ld))

ESP32_DIR_SRC:= $(shell find $(ESP32-NONOS) -type d -not -path './.*')

# Add include of ESP32-NONOS
CFLAG:= $(addprefix -I, $(ESP32_DIR_SRC))
LDFLAGS:= $(addprefix -T, $(LD_FILES)) \
	-L$(XTENSA)/xtensa-esp32-elf/lib \
	-L$(XTENSA)/lib/gcc/xtensa-esp32-elf/8.2.0

VPATH:= $(DIR_SRC)

build : $(NAME).bin
	@$(SIZE) -B -d $(NAME).elf
	@echo

upload :
	# ESP32-PICO-D4
	@esptool.py -c esp32 write_flash -sc 6,17,8,11,16 0x1000 $(NAME).bin
	# ESP32
	#@esptool.py -c esp32 write_flash 0x1000 $(NAME).bin

$(NAME).bin : $(NAME).elf
	@esptool.py -c esp32 elf2image -ff 80m -fm dio -fs 4MB $< #ESP32
	@#esptool.py -c esp32 elf2image -ff 80m -fm dio -fs 4MB -sc 6,17,8,11,16 $< #ESP32-PICO-D4
	@echo 'Binary "$(NAME).bin" created !'
	@echo

$(NAME).elf : ESP32-NONOS $(OBJ_DIR) $(OBJ)
	@$(LD) $(LDFLAGS) $(ESP32_OBJ) $(OBJ) -o $(NAME).elf -lm -lgcc
	@echo
	@echo $(NAME) 'compiled !'
	@echo

ESP32-NONOS :
	@$(MAKE) --directory=$(ESP32-NONOS) build

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo
	@echo '$(NAME) "$(OBJ_DIR)" folder created !'
	@echo

# Rules for each type of sources
$(OBJ_DIR)/%.c.o : %.c
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@

$(OBJ_DIR)/%.cpp.o : %.cpp
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@

$(OBJ_DIR)/%.S.o : %.S
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@
