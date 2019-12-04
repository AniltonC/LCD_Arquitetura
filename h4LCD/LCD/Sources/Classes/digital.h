/*
 * digital.h
 *
 *  Created on: Dec 3, 2019
 *      Author: anilton
 */

#ifndef SOURCES_CLASSES_DIGITAL_H_
#define SOURCES_CLASSES_DIGITAL_H_

#include "stdint.h"
#include "devices.h"

class TimeDecoder
{
private:
    uint8_t time_out[4];

public:
    TimeDecoder()
    {
        for (uint8_t i; i < 4; i++)
        {
            time_out[i] = 32;
        }
    }

    void setInput(uint8_t time_in[4])
    {
        if (time_in[0] == 0)
        {
            time_out[0] = 32;
            if (time_in[1] == 0)
                time_out[1] = 32;
            else
                time_out[1] = time_in[1] + 48;
        }
        else
        {
            time_out[0] = time_in[0] + 48;
            time_out[1] = time_in[1] + 48;
        }
        time_out[2] = time_in[2] + 48;
        time_out[3] = time_in[3] + 48;
    }

    uint8_t *getOutput()
    {
        return time_out;
    }
};

typedef enum
{
    e,
    pp,
    pz,
    la,
    i3,
    i5,
    i7
} cookOption;
class CookDecoder
{
private:
    string cook_out;

public:
    CookDecoder()
    {
        cook_out = " ";
    }
    void setInput(uint8_t cook_in)
    {
        switch (cook_in)
        {
        case 0:
            cook_out = " EDICAO ";
            return;
        case 1:
            cook_out = " PIPOCA ";
            return;
        case 2:
            cook_out = " PIZZA  ";
            return;
        case 3:
            cook_out = "LASANHA ";
            return;
        case 4:
            cook_out = " INC+3  ";
            return;
        case 5:
            cook_out = " INC+5  ";
            return;
        case 6:
            cook_out = " INC+7  ";
            return;
        default:
            cook_out = "        ";
            return;
        }
        cook_out = cook_in;
    }
    string getOutput()
    {
        return cook_out;
    }
};

class OperDecoder
{
};

class Timer
{
};

#endif /* SOURCES_CLASSES_DIGITAL_H_ */
