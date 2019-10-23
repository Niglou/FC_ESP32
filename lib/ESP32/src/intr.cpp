#include "ESP32/include/intr.h"

void intr_enable(unsigned int interrupt) {
    asm volatile (
		"wsr %0, intenable \n"
		"rsync"
		::"r"(interrupt));
}
