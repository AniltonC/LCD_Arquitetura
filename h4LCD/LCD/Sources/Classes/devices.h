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
#include "MKL25Z4.h"
#include "../Bibliotecas/I2C/mkl_LCD.h"
class Led
{
private:
    mkl_GPIOPort port;

public:
    Led(gpio_Pin pin) : port(pin)
    {
        port.setPortMode(gpio_output);
    };
    void turnOn()
    {
        port.writeBit(0);
    };
    void turnOff()
    {
        port.writeBit(1);
    };
    int getLed()
    {
        return port.readBit();
    }
};

class Visor
{
private:
    /*uint8_t adress;
    functionSetOption linhas, colunas, pixels;
    i2c_Pin_t SCL_pin, SDA_pin;
    mkl_LCD lcd(linhas, colunas, pixels, SCL_pin, SDA_pin, adress);*/
    mkl_LCD lcd;

public:
    /*Visor(functionSetOption numLines, functionSetOption numCols,
          functionSetOption numPixels, i2c_Pin_t SCLPin, i2c_Pin_t SDAPin,
          uint8_t I2CAddress)
    {
        linhas = numLines;
        colunas = numCols;
        pixels = numPixels;
        SCL_pin = SCLPin;
        SDA_pin = SDAPin;
        adress = I2CAddress;
    }*/
    Visor(functionSetOption numLines, functionSetOption numCols,
          functionSetOption numPixels, i2c_Pin_t SCLPin, i2c_Pin_t SDAPin,
          uint8_t I2CAddress) : lcd(numLines, numCols, numPixels, SCLPin, SDAPin, I2CAddress)
    {
        lcd.setCursor(1, 7);
        lcd.putString("LCD");
        lcd.setCursor(2, 3);
        lcd.putString("INICIALIZADO");
        lcd.delay(5000);
        lcd.clear();
        lcd.home();
    }
};

#endif /* SOURCES_DEVICES_DEVICES_H_ */