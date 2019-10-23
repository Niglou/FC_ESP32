
#include <ESP32/registers/struct/rtc_cntl_struct.h>
#include <ESP32/registers/struct/timer_struct.h>
#include <ESP32/registers/struct/uart_struct.h>
#include <ESP32/registers/dport_reg.h>


extern "C" {
    extern int _init_start;
}

void disable_rtc_wdt() {

  /* Disable RTC Watchdog */
	RTCCNTL.wdt_feed.feed = 1;
	RTCCNTL.wdt_config0.stg0 = 0;
	RTCCNTL.wdt_config0.stg1 = 0;
	RTCCNTL.wdt_config0.stg2 = 0;
	RTCCNTL.wdt_config0.stg3 = 0;
	RTCCNTL.wdt_config0.flashboot_mod_en = 0;
	RTCCNTL.wdt_config0.en = 0;

}

void disable_procpu_wdt_flashboot() {

    TIMERG0.wdt_config0.flashboot_mod_en = 0;

}

void init_esp32() {

    disable_rtc_wdt();

    disable_procpu_wdt_flashboot();

    /* Set CPU on PLL clock */
    /* 0: XTAL, 1: PLL, 2: CK8M, 3: APLL */
    RTCCNTL.clk_conf.soc_clk_sel = 1;
    /* CPU Freq 0:80Mhz 1:160Mhz 2:240Mhz */
    //*((unsigned int*)DPORT_CPU_PER_CONF_REG) = 0;


	// Move exception vectors to IRAM
	asm volatile (
                  "wsr    %0, vecbase\n" \
                  ::"r"(&_init_start));

	/* UART divider to 694(80 000 000/115200) */
  /* UART divider to 138(80 000 000/576000) */
  UART0.clk_div.div_int = 694;
  //UART0.conf0.tick_ref_always_on = 0;


}
