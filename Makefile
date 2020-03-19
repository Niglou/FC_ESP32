
esp32-nonos:= /media/DATA/Espressif_project/esp32-nonos

all :
	@$(MAKE) --directory=$(esp32-nonos) build `pwd`

upload :
	@esptool.py -c esp32 write_flash -sc 6,17,8,11,16 0x1000 FC_ESP32.bin
