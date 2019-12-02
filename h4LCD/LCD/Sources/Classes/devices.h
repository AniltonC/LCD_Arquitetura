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
    mkl_LCD lcd;
    void init_printTime()
    {
        uint8_t minuto[4] = {32, 32, 32, 32};
        lcd.home();
        for (uint8_t i = 0; i < 4; i++)
        {
            lcd.putChar(minuto[i]);
            if (i == 1)
                lcd.putChar(':');
            lcd.delay(50);
        }
    }

    void init_printCook()
    {
        string cook = "          ";
        lcd.setCursor(1, 6);
        lcd.putChar(32);
        lcd.delay(50);
        for (uint8_t i = 0; i < cook.length(); i++)
        {
            lcd.putChar(cook[i]);
            lcd.delay(50);
        }
    }

    void init_printOper()
    {
        string porta = "P-    ";
        string valv = "V-    ";
        string giro = "G-   ";
        for (uint8_t i = 0; i < porta.length(); i++)
        {
            lcd.setCursor(2, 1 + i);
            lcd.putChar(porta[i]);
            lcd.setCursor(2, 7 + i);
            lcd.putChar(valv[i]);
            if (13 + i < 32)
            {
                lcd.setCursor(2, 13 + i);
                lcd.putChar(giro[i]);
            }
            lcd.delay(50);
        }
    }

public:
    Visor(functionSetOption numLines, functionSetOption numCols,
          functionSetOption numPixels, i2c_Pin_t SCLPin, i2c_Pin_t SDAPin,
          uint8_t I2CAddress) : lcd(numLines, numCols, numPixels, SCLPin, SDAPin, I2CAddress)
    {
        lcd.home();
        for (uint8_t i = 0; i < 32; i++)
        {
            lcd.putChar('.');
            if (i == 15)
                lcd.setCursor(2, 1);
            lcd.delay(50);
        }
        init_printTime();
        init_printCook();
        init_printOper();
    }
    void printTime(uint8_t minuto[4])
    {
        lcd.home();
        for (uint8_t i = 0; i < 4; i++)
        {
            lcd.putChar(minuto[i]);
            if (i == 1)
                lcd.putChar(':');
        }
    }

    void printCook(string cook)
    {
        lcd.setCursor(1, 9);
        lcd.putString(cook);
    }

    void printOper(string porta, string valv, string giro)
    {
        lcd.setCursor(2, 1);
        lcd.putString("P-" + porta);
        lcd.setCursor(2, 7);
        lcd.putString("V-" + valv);
        lcd.setCursor(2, 13);
        lcd.putString("G-" + giro);
    }
};

class Timer
{
};
#endif /* SOURCES_DEVICES_DEVICES_H_ */
