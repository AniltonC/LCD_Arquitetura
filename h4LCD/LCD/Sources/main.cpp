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
FreqDivisor divisorFreq = FreqDivisor(1);
FreqDivisor diviFreq2hz = FreqDivisor(50);
/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */

uint8_t divisor = 0;
uint16_t cont = 0;
uint8_t t[4] = {48, 48, 54, 48};

/*!
 *   @brief    Realiza o blink dos leds vermelhor e azul.
 */

extern "C"
{
	void SysTick_Handler(void)
	{
		divisorFreq.increment();
		if (divisorFreq.getClock())
		{
			t[3] -= 1;
			if (t[3] < 48)
			{
				t[2] -= 1;
				t[3] = 57;
				if (t[2] < 48)
				{
					t[1] -= 1;
					t[2] = 53;
					if (t[1] < 48)
					{
						//t[0] -= 1;
						t[1] = 57;
						/*
						if (t[0] < 48)
						{
							t[0] = 53;
						}
						*/
					}
				}
			}
			divisor = 0;
		}

		diviFreq2hz.increment();
		if (diviFreq2hz.getClock())
		{
			t[0]++;
			if (t[0] == 57)
				t[0] = 48;
		}
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
	Visor LCD(mode2Lines, mode16Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
	while (1)
	{
		//count = true;
		LCD.printTime(t);
		/* Espera aqui por uma interrupcao */
	}
}
