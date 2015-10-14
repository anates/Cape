/*
 * LED_control.c
 *
 * Created: 03.08.2015 14:13:52
 *  Author: Roland-User
 */ 
#include "LED_control.h"

bool init_led_pins(void)
{
	ioport_set_pin_dir(BLU_LED, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BLU_LED, IOPORT_MODE_PULLDOWN);
	ioport_set_pin_dir(RED_LED, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(RED_LED, IOPORT_MODE_PULLDOWN);
	ioport_set_pin_dir(GRE_LED, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(GRE_LED, IOPORT_MODE_PULLDOWN);
	ioport_set_pin_dir(YEL_LED, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(YEL_LED, IOPORT_MODE_PULLDOWN);
	return true;
}

bool switch_led_on(led Led)
{
	if(Led == RXTX)
	{
		ioport_set_pin_mode(YEL_LED, IOPORT_MODE_PULLUP);
		return true;
	};
	if(Led == FAILURE)
	{
		ioport_set_pin_mode(RED_LED, IOPORT_MODE_PULLUP);
		return true;
	};
	if(Led == RUNNING)
	{
		ioport_set_pin_mode(GRE_LED, IOPORT_MODE_PULLUP);
		return true;
	};
	if(Led == MOVING)
	{
		ioport_set_pin_mode(BLU_LED, IOPORT_MODE_PULLUP);
		return true;
	};
	return false;
}

bool switch_led(led Led, bool state)
{
	ioport_mode_t new_mode;
	if(state)
		new_mode = IOPORT_MODE_PULLUP;
	else
		new_mode = IOPORT_MODE_PULLDOWN;
	if(Led == RXTX)
	{
		ioport_set_pin_mode(YEL_LED, new_mode);
		return true;
	};
	if(Led == FAILURE)
	{
		ioport_set_pin_mode(RED_LED, new_mode);
		return true;
	};
	if(Led == RUNNING)
	{
		ioport_set_pin_mode(GRE_LED, new_mode);
		return true;
	};
	if(Led == MOVING)
	{
		ioport_set_pin_mode(BLU_LED, new_mode);
		return true;
	};
	return false;
}

bool switch_led_off(led Led)
{
	if(Led == RXTX)
	{
		ioport_set_pin_mode(YEL_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	if(Led == FAILURE)
	{
		ioport_set_pin_mode(RED_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	if(Led == RUNNING)
	{
		ioport_set_pin_mode(GRE_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	if(Led == MOVING)
	{
		ioport_set_pin_mode(BLU_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	return false;
}

bool blink_led(led LED, int time)
{
	if(LED == RXTX)
	{
		ioport_set_pin_mode(YEL_LED, IOPORT_MODE_PULLUP);
		delay_ms(time);
		ioport_set_pin_mode(YEL_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	if(LED == FAILURE)
	{
		ioport_set_pin_mode(RED_LED, IOPORT_MODE_PULLUP);
		delay_ms(time);
		ioport_set_pin_mode(RED_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	if(LED == RUNNING)
	{
		ioport_set_pin_mode(GRE_LED, IOPORT_MODE_PULLUP);
		delay_ms(time);
		ioport_set_pin_mode(GRE_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	if(LED == MOVING)
	{
		ioport_set_pin_mode(BLU_LED, IOPORT_MODE_PULLUP);
		delay_ms(time);
		ioport_set_pin_mode(BLU_LED, IOPORT_MODE_PULLDOWN);
		return true;
	};
	return false;
}