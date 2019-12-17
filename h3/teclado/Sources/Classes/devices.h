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

class Button
{
private:
    mkl_GPIOPort port;

public:
    Button(gpio_Pin pin) : port(pin)
    {
        port.setPortMode(gpio_input);
        port.setPullResistor(gpio_pullUpResistor);
    }

    bool readButton()
    {
        return port.readBit();
    }
};

class Led
{
private:
    mkl_GPIOPort port;

public:
    Led(gpio_Pin pin) : port(pin)
    {
        port.setPortMode(gpio_output);
        turnOff();
    };
    void turnOn()
    {
        port.writeBit(0);
    };
    void turnOff()
    {
        port.writeBit(1);
    };
    bool getLed()
    {
        return port.readBit();
    }
};

typedef struct
{
    string porta, valvula, giro;
} operationType;
class Visor
{
private:
    mkl_LCD lcd;

public:
    Visor(functionSetOption numLines, functionSetOption numCols,
          functionSetOption numPixels, i2c_Pin_t SCLPin, i2c_Pin_t SDAPin,
          uint8_t I2CAddress) : lcd(numLines, numCols, numPixels, SCLPin, SDAPin, I2CAddress)
    {
        lcd.home();
        uint8_t minuto[4] = {32, 32, 32, 32};
        printTime(minuto);
        printCook("          ");
        operationType construtor;
        construtor.giro = "   ";
        construtor.porta = "   ";
        construtor.valvula = "   ";
        printOper(construtor);

        lcd.home();
        for (uint8_t i = 1; i < 41; i++)
        {
            if (i == 21)
                lcd.setCursor(4, 1);
            lcd.putChar(255);
        }
    }
    void printTime(uint8_t minuto[4])
    {
        lcd.setCursor(2, 1);
        for (uint8_t i = 0; i < 4; i++)
        {
            lcd.putChar(minuto[i]);
            if (i == 1)
                lcd.putChar(':');
        }
    }

    void printCook(string cook)
    {
        lcd.setCursor(2, 10);
        lcd.putString(cook);
    }

    void printOper(operationType oper_in)
    {
        lcd.setCursor(3, 1);
        lcd.putString("P-" + oper_in.porta);
        lcd.setCursor(3, 8);
        lcd.putString("V-" + oper_in.valvula);
        lcd.setCursor(3, 15);
        lcd.putString("G-" + oper_in.giro);
    }
};

class FreqDivisor
{
private:
    //mkl_SystickPeriodicInterrupt clockMaq;
    uint8_t freqCounter, counterLim;
    bool newClock,
        en;

public:
    FreqDivisor(uint8_t newFreq)
    {
        freqCounter = 0;
        newClock = 0;
        counterLim = 50 / newFreq;
    }

    void enable(bool in)
    {
        en = in;
    }

    void reset()
    {
        freqCounter = 0;
        en = 0;
    }

    void increment()
    {
        if (en)
        {
            freqCounter++;
            if (freqCounter == (counterLim))
            {
                newClock = 1;
                freqCounter = 0;
            }
            else
                newClock = 0;
        }
    }
    bool getClock()
    {
        return newClock;
    }
};

#endif /* SOURCES_DEVICES_DEVICES_H_ */
