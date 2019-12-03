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

    void setInput(uint8_t time_in[4]){
        if(0<=time_in[0]<10){
            time_out[0] = time_in[0] + 48;
        }
    }
};

class CookDecoder
{
};

class OperDecoder
{
};

class Timer
{
};

#endif /* SOURCES_CLASSES_DIGITAL_H_ */
