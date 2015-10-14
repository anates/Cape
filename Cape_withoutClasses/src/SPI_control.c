/*
 * SPI_control.c
 *
 * Created: 07.08.2015 10:33:46
 *  Author: Roland-User
 */ 

#include <SPI_control.h>

void SPI_init_pins(void)
{
	ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);//SS
	ioport_configure_port_pin(&PORTC, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);//MOSI
	ioport_configure_port_pin(&PORTC, PIN6_bm, IOPORT_DIR_INPUT);//MISO
	ioport_configure_port_pin(&PORTC, PIN7_bm, IOPORT_DIR_OUTPUT | IOPORT_INIT_HIGH);//SCK
	
};

void SPI_init_module(void)
{
	spi_device_conf.id = IOPORT_CREATE_PIN(PORTC, 4);
	spi_master_init(&SPIC);
	spi_master_setup_device(&SPIC, &spi_device_conf, SPI_MODE_0, 1000000, 0);
	spi_enable(&SPIC);
}

void SPI_test(void)
{
	uint8_t data_buffer[1] = {0xAB};
	struct spi_device spi_device_conf = {.id = IOPORT_CREATE_PIN(PORTC, 4)};
	spi_select_device(&SPIC, &spi_device_conf);
	spi_write_packet(&SPIC, data_buffer, 1);
	spi_read_packet(&SPIC, data_buffer, 1);
	spi_deselect_device(&SPIC, &spi_device_conf);
}

void SPI_write_data_8(uint8_t *data)
{
	spi_write_packet(&SPIC, data, 8);
	delay_ms(10);
}

void SPI_write_data_32(uint32_t *data)
{
	uint8_t data8[4];
	const uint8_t * data8_ptr = &data8[0];
	data8[0] = *data;
	data8[1] = *data >> 8;
	data8[2] = *data >> 16;
	data8[3] = *data >> 24;
	spi_write_packet(&SPIC, data8_ptr, 32);
	delay_ms(10);
}

void SPI_rec_data(uint8_t *data, size_t len)//Could lead to risky overflow...
{
	spi_read_packet(&SPIC, data, (len < 32)?len:32);
}