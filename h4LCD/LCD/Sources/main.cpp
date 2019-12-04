/*
 * main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */

#include "stdint.h"
#include "./Bibliotecas/GPIO/mkl_GPIOPort.h"
#include "MKL25Z4.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "./Classes/devices.h"
#include "./Classes/digital.h"

/*!
 * 	Declara��o do led RGB interno da placa
 */
//mkl_GPIOPort blueLed(gpio_PTD1);

/*!
 * 	Declara��o do led RGB interno da placa
 */
//mkl_GPIOPort redLed(gpio_PTB18);

/*!
 * 	Declara��o do objeto systick e configura��o para acontecer uma interrup��o a cada 100ms
 * 	e usar o clock da placa de 42MHz
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);
FreqDivisor clock1Hz = FreqDivisor(1);
/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */

uint8_t t[4] = {6, 0, 0, 0};
TimeDecoder timeDecod = TimeDecoder();
CookDecoder cookDecod = CookDecoder();
uint8_t option = 0;

/*!
 *   @brief    Realiza o blink dos leds vermelhor e azul.
 */

extern "C"
{
	void SysTick_Handler(void)
	{
		clock1Hz.increment();
		if (clock1Hz.getClock())
		{
			t[3] -= 1;
			if (t[3] == 255)
			{
				t[2] -= 1;
				t[3] = 9;
				if (t[2] == 255)
				{
					t[1] -= 1;
					t[2] = 5;
					if (t[1] == 255)
					{
						t[0] -= 1;
						t[1] = 9;
						if (t[0] == 255)
						{
							t[0] = 5;
						}
					}
				}
			}
			option++;
			if (option == 7)
				option = 0;
			cookDecod.setInput(option);
		}

		timeDecod.setInput(t);
	}
}

/*!
 *   @brief    Realiza a configura��es das io's e espera pelas interrup��es.
 *
 *   Este programa realiza o teste da classe do perif�rico systick.
 *
 *   @return  sempre retorna o valor 0.
 */
int main(void)
{
	Visor LCD(mode4Lines, mode20Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
	while (1)
	{
		//count = true;
		//uint8_t tempo[4] = timeDecod.getOutput();
		LCD.printTime(timeDecod.getOutput());
		LCD.printCook(cookDecod.getOutput());
		/* Espera aqui por uma interrupcao */
	}
}
