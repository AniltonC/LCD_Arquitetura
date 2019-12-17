/*
 * switch.h
 *
 *  Created on: Dec 17, 2019
 *      Author: anilton
 */

#ifndef SOURCES_DISPOSITIVOS_SWITCH_H_
#define SOURCES_DISPOSITIVOS_SWITCH_H_

#include "../Bibliotecas/GPIO/mkl_GPIOPort.h"

typedef enum
{
	wait_for_press = 0,
	while_pressed = 1,
	send_data = 2
} estados;

class Switch
{
public:
	explicit Switch(gpio_Pin pino)
	{
		chave = mkl_GPIOPort(pino);
		chave.setPortMode(gpio_input);
		chave.setPullResistor(gpio_pullUpResistor);

		atualState = wait_for_press;
	}
	int read()
	{
		return chave.readBit();
	}
	int isOn()
	{
		switch (atualState)
		{
		case wait_for_press:
			if (read() == 0)
			{
				atualState = while_pressed;
			}
			break;
		case while_pressed:
			if (read() == 1)
			{
				atualState = send_data;
			}
			break;
		case send_data:
			atualState = wait_for_press;
			break;
		}

		if (atualState == wait_for_press || atualState == while_pressed)
		{
			return 0;
		}
		else if (atualState == send_data)
		{
			return 1;
		}
	}

private:
	mkl_GPIOPort chave;
	int atualState;
};

#endif /* SOURCES_DISPOSITIVOS_SWITCH_H_ */
