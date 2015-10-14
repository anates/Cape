/*
 * LED_control.h
 *
 * Created: 03.08.2015 14:05:26
 *  Author: Roland-User
 */ 


#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include <asf.h>
#include <delay.h>

#define BLU_LED IOPORT_CREATE_PIN(PORTA, 6)
#define RED_LED IOPORT_CREATE_PIN(PORTA, 3)
#define YEL_LED IOPORT_CREATE_PIN(PORTA, 4)
#define GRE_LED IOPORT_CREATE_PIN(PORTA, 5)

/*#define RXTX YEL_LED
#define BOOT BLU_LED
#define FAILURE RED_LED
#define RUNNING GRE_LED*/

typedef enum {RXTX, FAILURE, RUNNING, BOOT} led;

#ifndef F_CPU
#define F_CPU 16000000
#endif

bool init_led_pins(void);
bool switch_led_on(led Led);
bool switch_led_off(led Led);
bool blink_led(led LED, uint16_t time);
bool switch_led(led Led, bool state);
#endif /* LED_CONTROL_H_ */