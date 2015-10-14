/*
 * SPI_control.h
 *
 * Created: 07.08.2015 10:34:00
 *  Author: Roland-User
 */ 


#ifndef SPI_CONTROL_H_
#define SPI_CONTROL_H_

#include <asf.h>
#include <avr/io.h>

struct spi_device spi_device_conf;

void SPI_init_pins(void);
void SPI_init_module(void);
void SPI_test(void);
void SPI_write_data_8(uint8_t *data);
void SPI_write_data_32(uint32_t *data);
void SPI_rec_data(uint8_t *data, size_t len);

#endif /* SPI_CONTROL_H_ */