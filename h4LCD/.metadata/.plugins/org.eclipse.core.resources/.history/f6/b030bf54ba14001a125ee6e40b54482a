/*
 * main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */

#include "./Bibliotecas/I2C/mkl_LCD.h"
#include "MKL25Z4.h"
#include "./Classes/devices.h"

int main(void)
{
	Visor LCD(mode2Lines, mode16Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
	uint8_t tempo[4] = {57, 52, 53, 54};
	LCD.printTime(tempo);
	LCD.printCook("EDICAO");
	LCD.printOper("ON", "OFF", "ON");
}
