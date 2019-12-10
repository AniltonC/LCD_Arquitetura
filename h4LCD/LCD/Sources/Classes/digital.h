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
            time_out[i] = 32;
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
        cook_out = "        ";
    }
    void setInput(cookOption cook_in)
    {
        switch (cook_in)
        {
        case e:
            cook_out = " EDICAO ";
            return;
        case pp:
            cook_out = " PIPOCA ";
            return;
        case pz:
            cook_out = " PIZZA  ";
            return;
        case la:
            cook_out = "LASANHA ";
            return;
        case i3:
            cook_out = " INC+3  ";
            return;
        case i5:
            cook_out = " INC+5  ";
            return;
        case i7:
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
private:
    operationType oper_out;

public:
    OperDecoder()
    {
        oper_out.porta = "   ";
        oper_out.valvula = "   ";
        oper_out.giro = "   ";
    }
    void setInput(bool oper_in[3])
    {
        if (oper_in[0])
            oper_out.porta = "ON ";
        else
            oper_out.porta = "OFF";
        if (oper_in[1])
            oper_out.valvula = "ON ";
        else
            oper_out.valvula = "OFF";
        if (oper_in[2])
            oper_out.giro = "ON ";
        else
            oper_out.giro = "OFF";
    }

    operationType getOutput()
    {
        return oper_out;
    }
};

typedef enum
{
    play,
    pause
} enableType;
class Timer
{
private:
    uint8_t time[4];
    bool enableDecrement;
    uint8_t vaiUm[3] = {0, 0, 0};
    bool fimTemp;

public:
    Timer()
    {
        enableDecrement = 0;
        fimTemp = 0;
        for (uint8_t i = 0; i < 4; i++)
            time[i] = 0;
    }

    void enableTimer(enableType en)
    {
        if (en == play)
            enableDecrement = 1;
        else
            enableDecrement = 0;
    }

    void setTime(uint8_t time_in[4])
    {
        if (!enableDecrement)
            for (uint8_t i = 0; i < 4; i++)
                time[i] = time_in[i];
    }

    uint8_t *getTime()
    {
        return time;
    }

    void increment(uint8_t input)
    {
        time[3] += input;
        if (time[3] > 9)
        {
            vaiUm[2] = time[3] / 10;
            time[3] -= 10 * vaiUm[2];
            time[2] += vaiUm[2];

            if (time[2] > 5)
            {
                vaiUm[1] = time[2] / 6;
                time[2] -= 6 * vaiUm[1];
                time[1] += vaiUm[1];

                if (time[1] > 9)
                {
                    vaiUm[0] = time[1] / 10;
                    time[1] -= 10 * vaiUm[0];
                    time[0] += vaiUm[0];

                    if (time[0] > 9)
                        time[0] -= 10;
                }
            }
        }
    }

    void decrement()
    {
        if (enableDecrement)
        {
            if (time[0] == 0 && time[1] == 0 && time[2] == 0 && time[3] == 0)
            {
                enableDecrement = 0;
                fimTemp = 1;
            }
            else
            {
                time[3] -= 1;
                if (time[3] == 255)
                {
                    time[2] -= 1;
                    time[3] = 9;
                    if (time[2] == 255)
                    {
                        time[1] -= 1;
                        time[2] = 5;
                        if (time[1] == 255)
                        {
                            time[0] -= 1;
                            time[1] = 9;
                            if (time[0] == 255)
                            {
                                time[0] = 5;
                            }
                        }
                    }
                }
            }
        }
    }

    bool endTimer()
    {
        return fimTemp;
    }
};
#endif /* SOURCES_CLASSES_DIGITAL_H_ */
