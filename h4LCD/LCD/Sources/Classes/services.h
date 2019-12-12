/*
 * services.h
 *
 *  Created on: Dec 10, 2019
 *      Author: anilton
 */

#ifndef SOURCES_CLASSES_SERVICES_H_
#define SOURCES_CLASSES_SERVICES_H_

#include "devices.h"
#include "digital.h"
#include "../Bibliotecas/GPIO/mkl_GPIOPort.h"

class DigitalFactory
{
private:
    Timer ptrTimer;
    TimeDecoder ptrTimeDec;
    CookDecoder ptrCookDec;
    OperDecoder ptrOperDec;

public:
    DigitalFactory()
    {
        ptrTimer = Timer();
        ptrTimeDec = TimeDecoder();
        ptrCookDec = CookDecoder();
        ptrOperDec = OperDecoder();
    }

    Timer *getPtrTimer()
    {
        return &ptrTimer;
    }

    TimeDecoder *getPtrTimeDecod()
    {
        return &ptrTimeDec;
    }

    CookDecoder *getPtrCookDecod()
    {
        return &ptrCookDec;
    }

    OperDecoder *getPtrOperDecod()
    {
        return &ptrOperDec;
    }
};

class Memoria
{
private:
    uint8_t tempo_geral[4] = {0, 0, 0, 0};
    cookOption cookGeral = ed;
    bool operGeral[3] = {0, 0, 0};
    bool tempo_novo = 0;
    Led redLed = Led(gpio_PTB18);

public:
    Memoria()
    {
    }

    bool setTempoGeral(uint8_t tempo[4])
    {
        bool saida = 0;
        for (uint8_t i = 0; i < 4; i++)
        {
            if (tempo_geral[i] != tempo[i])
            {
                tempo_geral[i] = tempo[i];
                saida = 1;
            }
        }
        return saida;
    }

    bool setCookGeral(cookOption cookIn)
    {
        if (cookIn != cookGeral)
        {
            cookGeral = cookIn;
            return 1;
        }
        else
            return 0;
    }

    bool setOperGeral(bool operIn[3])
    {
        bool saida = 0;
        for (uint8_t i = 0; i < 3; i++)
        {
            if (operIn[i] != operGeral[i])
            {
                operGeral[i] = operIn[i];
                saida = 1;
            }
        }
        return saida;
    }

    uint8_t *getTempoGeral()
    {
        return tempo_geral;
    }

    cookOption getCookGeral()
    {
        return cookGeral;
    }

    bool *getOperGeral()
    {
        return operGeral;
    }
};

class EditorService
{
private:
    Timer *Temporizador;
    TimeDecoder *TimeDecod;
    CookDecoder *CookDecod;
    OperDecoder *OperDecod;
    Memoria *MemoriaGeral;

public:
    EditorService(Memoria *memIn, Timer *temporIn, TimeDecoder *timeDIn, CookDecoder *cookIn, OperDecoder *operIn)
    {
        MemoriaGeral = memIn;
        Temporizador = temporIn;
        TimeDecod = timeDIn;
        CookDecod = cookIn;
        OperDecod = operIn;
    }
    void doService()
    {
        Temporizador->setTime(MemoriaGeral->getTempoGeral());
        CookDecod->setInput(MemoriaGeral->getCookGeral());
        OperDecod->setInput(MemoriaGeral->getOperGeral());
    }
};

class TimerService
{
};

class IncrementService
{
};

class PrintService
{
private:
    Visor LCD;
    Memoria *MemoriaGeral;
    TimeDecoder *TimeDecod;

public:
    PrintService(Memoria *memoria, TimeDecoder *tdecod) : LCD(mode4Lines, mode20Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27)
    {
        MemoriaGeral = memoria;
        TimeDecod = tdecod;
    }
    void UpdateLCD()
    {
        TimeDecod->setInput(MemoriaGeral->getTempoGeral());
        LCD.printTime(TimeDecod->getOutput());
    }
};

#endif /* SOURCES_CLASSES_SERVICES_H_ */
