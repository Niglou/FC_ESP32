
esp32-nonos:= /media/DATA/Espressif_project/esp32-nonos

all :
	@$(MAKE) --directory=$(esp32-nonos) build `pwd`
