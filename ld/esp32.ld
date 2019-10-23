
MEMORY {
	/*dport0_seg (RW) :			org = 0x3FF00000, len = 0x10*/
	/*irom_seg (RX) :			org = 0x40000000, len = 0x5FFFF*/
	/*iram_vector_seg (RX) :		org = 0x40080000, len = 0x400 */
	iram_seg (RWXA) :			org = 0x40080000, len = 0x2FFFF
	dram_seg (RWA) :			org = 0x3FFB0000, len = 0x2C200
	drom0_0_seg (R) :     org = 0x3F400018, len = 0x400000-0x18
}

ENTRY(main_cpu0);

SECTIONS {

	.vectors : {
		_init_start = ABSOLUTE(.);
		. = 0x0;
    	KEEP(*(.WindowVectors.text));
    	. = 0x180;
    	KEEP(*(.Level2InterruptVector.text));
    	. = 0x1c0;
    	KEEP(*(.Level3InterruptVector.text));
    	. = 0x200;
    	KEEP(*(.Level4InterruptVector.text));
    	. = 0x240;
    	KEEP(*(.Level5InterruptVector.text));
    	. = 0x280;
    	KEEP(*(.DebugExceptionVector.text));
    	. = 0x2c0;
    	KEEP(*(.NMIExceptionVector.text));
    	. = 0x300;
    	KEEP(*(.KernelExceptionVector.text));
    	. = 0x340;
    	KEEP(*(.UserExceptionVector.text));
    	. = 0x3C0;
    	KEEP(*(.DoubleExceptionVector.text));
    	. = 0x400;
		/* *(.*Vector.literal) */

		_init_end = ABSOLUTE(.);
	} > iram_seg

	.text : {
		. = ALIGN (16);
		_loader_text_start = ABSOLUTE(.);
		*(.literal .literal*)
		*(.text .text*)
		*(.iram1 .iram1*)

	} > iram_seg


	.data : {
    _data_start = ABSOLUTE(.);
		*(.rodata .rodata*)
		*(.data .data*)
		*(.bss .bss*)
    	_data_end = ABSOLUTE(.);
		. = ALIGN(4);
	} > dram_seg

}
