/*
 * main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */


#include "./Bibliotecas/devices.h"

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
