/*
 * devices.h
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */

#ifndef SOURCES_DEVICES_DEVICES_H_
#define SOURCES_DEVICES_DEVICES_H_

#include "stdint.h"
#include "../Bibliotecas/GPIO/mkl_GPIOPort.h"

class Led{
    private:
        mkl_GPIOPort port;
    public:
        Led(gpio_Pin pin) : port(pin){
            port.setPortMode(gpio_output);
        };
        void turnOn(){
            port.writeBit(0);
        };
        void turnOff(){
            port.writeBit(1);
        };
        int getLed(){
        	return port.readBit();
        }
};




#endif /* SOURCES_DEVICES_DEVICES_H_ */
