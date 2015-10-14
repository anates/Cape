/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <avr/io.h>
#include <usart_driver.h>
#include <SPI_control.h>
#include <LED_control.h>

#ifndef USART_CONTROL_H_
#define USART_SERIAL &USARTD0
#define USART_SERIAL_BAUDRATE 9600
#define USART_SERIAL_CHAR_LENGTH USART_CHSIZE_9BIT_gc
#define USART_SERIAL_PARITY USART_PMODE_EVEN_gc
#define USART_SERIAL_STOP_BIT true
#endif

#ifndef EEPROM_CONTROL_H_
#define POSITION_ADDR 0x0 //EEPROM_PAGE_SIZE
#define SPEED_ADDR 0x20 //2*EEPROM_PAGE_SIZE

#define NUMBER_CTRL_BYTES 4

uint8_t receiveArray[NUMBER_CTRL_BYTES];
uint8_t sendArray[NUMBER_CTRL_BYTES + 1];
#endif

USART_data_t USART_data_Stepper;
USART_data_t USART_data_PreAmp;

void init_usart_driver(register8_t dirset, register8_t dirclr, USART_data_t *data, USART_t *module)
{
	PORTD.DIRSET = dirset;
	PORTD.DIRCLR = dirclr;
	USART_InterruptDriver_Initialize(data, module, USART_DREINTLVL_LO_gc);
	USART_Format_Set(data->usart, USART_CHSIZE_8BIT_gc, USART_PMODE_EVEN_gc, false);
	USART_RxdInterruptLevel_Set(data->usart, USART_RXCINTLVL_LO_gc);
	
	USART_Baudrate_Set(module, 207, 0);
	USART_Rx_Enable(data->usart);
	USART_Tx_Enable(data->usart);
	
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
}

ISR(USARTD0_RXC_vect)
{
	USART_RXComplete(&USART_data_Stepper);
}

ISR(USARTD0_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_Stepper);
}

ISR(USARTC0_RXC_vect)
{
	USART_RXComplete(&USART_data_PreAmp);
}

ISR(USARTC0_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_PreAmp);
}

//C0 is preamp, D0 is stepper

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	sysclk_init();
	ioport_init();
	/* Insert application code here, after the board has been initialized. */
	//Own variables
	bool running = true;
	bool error = false;
	uint8_t spi_counter = 0;
	//Testdata
	uint32_t testdata = 0;
	//Create command & data storage
	uint8_t commandUSART[NUMBER_CTRL_BYTES];
	uint8_t commandSPI[NUMBER_CTRL_BYTES];
	//Memory
	uint8_t write_page[EEPROM_PAGE_SIZE];
	uint8_t read_page[EEPROM_PAGE_SIZE];
	//Own inits
	init_led_pins();
	//Boot sequence initiated
	switch_led(BOOT, true);
	init_usart_driver(PIN3_bm, PIN2_bm, &USART_data_Stepper, &USARTD0);
	init_usart_driver(PIN3_bm, PIN2_bm, &USART_data_PreAmp, &USARTC0);
	//Test blinking
	for(int i = 0; i < 10; i++)
	{
		blink_led(BOOT, 100);
		blink_led(RUNNING, 50);
		blink_led(RXTX, 50);
		blink_led(FAILURE, 100);
		blink_led(RXTX, 50);
		blink_led(RUNNING, 50);
	}
	//Load Stuff from memory, no clue what I should load
	memset(read_page, 0x0, EEPROM_PAGE_SIZE);
	nvm_eeprom_read_buffer(POSITION_ADDR, read_page, EEPROM_PAGE_SIZE);
	testdata = ((uint32_t)read_page[3] << 24) | ((uint32_t)read_page[2] << 16) | ((uint32_t)read_page[1] << 8) | read_page[0];
	memset(read_page, 0x0, EEPROM_PAGE_SIZE);
	nvm_eeprom_read_buffer(SPEED_ADDR, read_page, EEPROM_PAGE_SIZE);
	//currentSpeed = ((uint32_t)read_page[0] << 24) | ((uint32_t)read_page[1] << 16) | ((uint32_t)read_page[2] << 8) | read_page[3];
	memset(read_page, 0x0, EEPROM_PAGE_SIZE);
	//Boot sequence finished
	switch_led(BOOT, false);
	//Test of data
	if(testdata != 3)
	{
		switch_led(RXTX, true);
		//testdata = 10;
	}
	else
		switch_led(RUNNING, true);	
	delay_ms(1000);
	testdata = 3;
	//End of test data;	
	if(error != true)
	{
		memset(write_page, 0x0, EEPROM_PAGE_SIZE);
		write_page[3] = testdata >> 24;
		write_page[2] = testdata >> 16;
		write_page[1] = testdata >> 8;
		write_page[0] = testdata;
		nvm_eeprom_load_page_to_buffer(write_page);
		nvm_eeprom_atomic_write_page(POSITION_ADDR);
		memset(write_page, 0x0, EEPROM_PAGE_SIZE);
		write_page[3] = testdata >> 24;
		write_page[2] = testdata >> 16;
		write_page[1] = testdata >> 8;
		write_page[0] = testdata;
		nvm_eeprom_load_page_to_buffer(write_page);
		nvm_eeprom_atomic_write_page(POSITION_ADDR);
		memset(write_page, 0x0, EEPROM_PAGE_SIZE);
		switch_led(RUNNING, false);
		switch_led(RXTX, true);
		switch_led(BOOT, true);
		//Shutdown procedure can be executed
	}
	else
	{
		cli();
		while(1)
		{
			blink_led(FAILURE, 100);
		}
	}
	return 0;
}
