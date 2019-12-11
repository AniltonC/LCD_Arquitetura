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

/* Bluetooth */
#include <assert.h>
#include "./Bibliotecas/Bluetooth/mkl_HC06BluetoothSlave.h"

mkl_HC06BluetoothSlave bt(uart0_PTA2, uart0_PTA1);  //! Bluetooth na UART 0
mkl_GPIOPort ledVerde(gpio_PTB19);                  //! LED da placa
uint8_t buf = '0';                                        //! Armazenar dado recebido
uart_Exception_t exc;                               //! Armazenar exceÃ§Ã£o


/*!
 * 	Declara��o do led RGB interno da placa
 */
mkl_GPIOPort blueLed(gpio_PTD1);

/*!
 * 	Declara��o do led RGB interno da placa
 */
mkl_GPIOPort redLed(gpio_PTB18);

/*!
 * 	Declara��o do objeto systick e configura��o para acontecer uma interrup��o a cada 100ms
 * 	e usar o clock da placa de 42MHz
 */
// mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);
FreqDivisor clock1Hz = FreqDivisor(1);
FreqDivisor clock5Hz = FreqDivisor(2);
FreqDivisor clock10Hz = FreqDivisor(0.3);
/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */

uint8_t time[4] = {0, 1, 3, 0};
TimeDecoder timeDecod = TimeDecoder();
CookDecoder cookDecod = CookDecoder();
OperDecoder operDecod = OperDecoder();
Timer Temporizador = Timer();
uint8_t input = 40, option = 0;
bool operacoes[3] = {0, 1, 0};

// /*!
//  *   @brief    Realiza o blink dos leds vermelhor e azul.
//  */

// extern "C"
// {
// 	void SysTick_Handler(void)
// 	{
// 		clock1Hz.increment();

// 		if (clock1Hz.getClock())
// 			Temporizador.decrement();
// 			Temporizador.setTime(time);
// 			cookDecod.setInput(pp);
// 	}
// }


/*!
 *   @fn delayMs
 *
 *   @brief      Realiza um delay de n ms.
 */
void delayMs(uint16_t n) {
	for (uint16_t i = 0; i < n; i++)
		for (uint16_t j = 0; j < 7000; j++) {}
}

/*!
 *   @fn setupLedRGB
 *
 *   @brief      Realiza a configuraÃ§Ã£o do perifÃ©rico para a entrada e saÃ­da.
 *               Este procedimento realiza a configuraÃ§Ã£o do pino PTD1 para o
 *               modo saÃ­da (RGB)
 *
 *   @details    O led RGB Ã© do tipo anodo comum.
 */
void setupLedRGB() {
	ledVerde.setPortMode(gpio_output);
	ledVerde.writeBit(true);
}

/*!
 *   @fn setupBluetooth
 *
 *   @brief      Realiza a configuraÃ§Ã£o do perifÃ©rico Bluetooth.
 *
 *   @details    Prioridade 0 e modo de interrupÃ§Ã£o no RX.
 */
void setupBluetooth() {
	bt.setInterruptMode(uart_Rx);
	bt.setPriority(uart_Priority0);
	bt.enableInterrupt();
}

/*!
 *   @fn UART0_IRQHandler
 *
 *   @brief      Rotina de serviÃ§o de interrupÃ§Ã£o.
 *
 *   @details    Recebe os dados atravÃ©s da UART.
 */
extern "C" {
void UART0_IRQHandler() {
	buf = bt.receive8Bits();
}
}


/*!
 *   @brief    Realiza a configura��es das io's e espera pelas interrup��es.
 *
 *   Este programa realiza o teste da classe do perif�rico systick.
 *
 *   @return  sempre retorna o valor 0.
 */

Led fimTimer = Led(gpio_PTB18);
int main(void)
{
	__disable_irq();
	setupLedRGB();     //! Configura o LED RGB
	setupBluetooth();  //! Configura o perifÃ©rico bluetooth
	__enable_irq();

	bool newTime = false;



	Visor LCD(mode4Lines, mode20Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
	// Temporizador.setTime(time);
	Temporizador.enableTimer(play);
	while (1)
	{

		/*!
		* Caso o dado enviado seja igual ao recebido
		* o LED verde da placa acenderÃ¡.
		*/
		while (true) {
			if(buf == 'A'){
				ledVerde.writeBit(true);
				cookDecod.setInput(i3);
			}
			if(buf == 'B'){
				ledVerde.writeBit(true);
				cookDecod.setInput(i5);
			}
			if(buf == 'C'){
				ledVerde.writeBit(true);
				cookDecod.setInput(i7);
			}
			if(buf == 'D'){
				ledVerde.writeBit(true);
				cookDecod.setInput(la);

				time[0]=0;
				time[1]=2;
				time[2]=0;
				time[3]=2;
				newTime = true;
			}
			if(buf == 'E'){
				ledVerde.writeBit(false);
				cookDecod.setInput(pz);

				time[0]=0;
				time[1]=1;
				time[2]=0;
				time[3]=1;
				newTime = true;
			}
			if(buf == 'F'){
				ledVerde.writeBit(true);
				cookDecod.setInput(pp);

				time[0]=0;
				time[1]=0;
				time[2]=3;
				time[3]=0;
				newTime = true;
			}
			if(buf == 'G'){
				operacoes[1] = 1;
				operacoes[2] = 1;
			}
			if(buf == 'H'){
				operacoes[1] = 0;
				operacoes[2] = 0;
			}
			

			clock1Hz.increment();

			if (clock1Hz.getClock()){
				Temporizador.decrement();
				if(newTime){
					Temporizador.setTime(time);
					newTime = false;
				}
				operDecod.setInput(operacoes);
			}

			timeDecod.setInput(Temporizador.getTime());
			LCD.printTime(timeDecod.getOutput());
			LCD.printCook(cookDecod.getOutput());
			LCD.printOper(operDecod.getOutput());
			if (Temporizador.endTimer())
				fimTimer.turnOn();
			else
				fimTimer.turnOff();
		}
		}
}
