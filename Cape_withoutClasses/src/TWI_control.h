/*
 * TWI_control.h
 *
 * Created: 12.08.2015 14:33:39
 *  Author: Roland-User
 */ 


#ifndef TWI_CONTROL_H_
#define TWI_CONTROL_H_

twi_master_options_t opt;
void receive_data(uint32_t *data, uint8_t data_size);
void send_data(uint32_t *data, uint8_t data_size);


#endif /* TWI_CONTROL_H_ */