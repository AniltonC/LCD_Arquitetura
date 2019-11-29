/*
 * main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */

/*
#include "./Classes/devices.h"

int main(){
	int valor;
	while(1){
		Led led1(gpio_PTB18);
		led1.turnOn();
		valor = led1.getLed();

		led1.turnOff();
		valor = led1.getLed();
	}
	return 0;
}
*/

#include "./Bibliotecas/I2C/mkl_LCD.h"
#include "MKL25Z4.h"
#include "./Classes/devices.h"

/*!
 *   EndereÃ§o do mÃ³dulo I2C utilizado
 */
uint8_t deviceAddress = 0x27;

/*!
 *   Configura o formato do display e os parametros do modulo I2C
 */
//mkl_LCD lcd(mode2Lines, mode16Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, deviceAddress);

/*!
 *   @brief      Pausa o programa
 *
 *   Interrompe o programa para o periodo de tempo (em milissegundos) especificado
 *   como parametro.
 *
 *   @param[in]  milliSeconds - o nÃºmero de milissegundos para fazer uma pausa
 */
void delay(uint32_t milliSeconds)
{
	uint32_t i;
	uint32_t j;

	for (i = 0; i < milliSeconds; i++)
	{
		for (j = 0; j < 1500; j++)
		{
		}
	}
}

//int i = 0x0;

/*!
 *   @brief      Imprime texto no display LCD.
 *
 *   Este programa realiza o teste da classe do periferico LCD. A palavra
 *   "Arquitetura" Ã© impressa em uma linha.
 */

int main(void) /*
{


	int valor;
	Led led1(gpio_PTB18);
	while(1){
		led1.turnOn();
		valor = led1.getLed();
		delay(200);
		led1.turnOff();
		valor = led1.getLed();
		delay(200);
	}

	string name = "Anilton";
	lcd.home();
	//lcd.setCursorOff();
	//lcd.setBlinkOff();
	uint8_t num = 0;
	while (1)
	{
		lcd.home();
		lcd.setCursorOff();
		lcd.putString("Cursor OFF!");
		delay(2000);

		lcd.clear();
		lcd.home();

		lcd.setBlinkOff();
		lcd.putString("Blink OFF!");
		delay(5000);
		//lcd.home();
		for (int i = 0; i < name.length(); i++)
		{
			lcd.putChar(name[i]);
			if (num == 15)
			{
				lcd.setCursor(2, 1);
				num++;
			}
			else if (num == 31)
			{
				num = 0;
				lcd.home();
			}
			else
				num++;

			delay(300);
		}

		lcd.clear();
		lcd.home();

		lcd.setCursorOn();
		lcd.putString("Cursor ON!");
		delay(2000);

		lcd.clear();
		lcd.home();

		lcd.setBlinkOn();
		lcd.putString("Blink ON!");
		delay(2000);
	}

	while (true)
	{
		delay(500);
		lcd.setCursor(1, 1);
		lcd.putString("Teste 1 2 3");
	}
}
*/
{
	Visor LCD(mode2Lines, mode16Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, deviceAddress);
}