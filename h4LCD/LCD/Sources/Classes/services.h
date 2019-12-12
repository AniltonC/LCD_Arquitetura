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

    Timer *getPtrTimer() { return &ptrTimer; }

    TimeDecoder *getPtrTimeDecod() { return &ptrTimeDec; }

    CookDecoder *getPtrCookDecod() { return &ptrCookDec; }

    OperDecoder *getPtrOperDecod() { return &ptrOperDec; }
};

class Memoria
{
private:
    uint8_t tempo_geral[4] = {0, 0, 0, 0};
    cookOption thisCookGeral;
    bool operGeral[3] = {0, 0, 0};
    enableType thisAction;
    bool thisCancelAction;
    bool thisFimTimer, doFimLedAct;

public:
    Memoria()
    {
        thisCookGeral = ed;
        thisAction = pause;
        thisCancelAction = 0;
        thisFimTimer = 0;
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
    void TimerUpdate(uint8_t timer_up[4])
    {
        for (uint8_t i = 0; i < 4; i++)
            tempo_geral[i] = timer_up[i];
    }

    void setIsFimTimer(bool fim)
    {
        if (thisFimTimer != fim)
            thisFimTimer = fim;
    }

    bool setCookGeral(cookOption cookIn)
    {
        if (cookIn != thisCookGeral)
        {
            thisCookGeral = cookIn;
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

    bool setAction(enableType action)
    {
        if (thisAction != action)
        {
            thisAction = action;
            return 1;
        }
        else
            return 0;
    }

    bool setCancelAction(bool cancel)
    {
        if (thisCancelAction != cancel)
        {
            thisCancelAction = cancel;
            return 1;
        }
        return 0;
    }

    uint8_t *getTempoGeral() { return tempo_geral; }

    cookOption getCookGeral() { return thisCookGeral; }

    bool *getOperGeral() { return operGeral; }

    enableType getAction() { return thisAction; }

    bool getCancelAction() { return thisCancelAction; }

    bool getFimLedAction() { return thisFimTimer; }
};

class EditorService
{
private:
    Memoria *thisMemoriaGeral;
    Timer *thisTimer;
    TimeDecoder *thisTimeDecod;
    CookDecoder *thisCookDecod;
    OperDecoder *thisOperDecod;

public:
    EditorService(Memoria *memIn, Timer *timerIn, TimeDecoder *timeDIn, CookDecoder *cookIn, OperDecoder *operIn)
    {
        thisMemoriaGeral = memIn;
        thisTimer = timerIn;
        thisTimeDecod = timeDIn;
        thisCookDecod = cookIn;
        thisOperDecod = operIn;
    }
    void doService()
    {
        thisTimer->setTime(thisMemoriaGeral->getTempoGeral());
        thisCookDecod->setInput(thisMemoriaGeral->getCookGeral());
        thisOperDecod->setInput(thisMemoriaGeral->getOperGeral());
    }
};

class TimerService
{
private:
    Memoria *thisMemoriaGeral;
    Timer *thisTimer;
    TimeDecoder *thisTimeDecod;
    FreqDivisor timerClock1Hz = FreqDivisor(1);
    Led fimLed = Led(gpio_PTB18);

public:
    TimerService(Memoria *memIn, Timer *timerIn, TimeDecoder *timeDIn)
    {
        thisMemoriaGeral = memIn;
        thisTimer = timerIn;
        thisTimeDecod = timeDIn;
    }

    void doActionService()
    {
        thisTimer->enableTimer(thisMemoriaGeral->getAction());
        if (thisMemoriaGeral->getCancelAction())
        {
            thisTimer->cancelTimer();
            thisMemoriaGeral->setCancelAction(0);
        }
    }

    void doFimLedService()
    {
        if (thisMemoriaGeral->getFimLedAction())
            fimLed.turnOn();
        else
            fimLed.turnOff();
    }

    void doService()
    {
        //timerClock1Hz.increment();
        if (timerClock1Hz.getClock())
        {
            thisTimer->decrement();
            thisMemoriaGeral->TimerUpdate(thisTimer->getTime());
        }
        thisTimeDecod->setInput(thisTimer->getTime());
    }
};

class IncrementService
{
};

class PrintService
{
private:
    Visor LCD;
    TimeDecoder *thisTimeDecod;
    CookDecoder *thisCookDecod;
    OperDecoder *thisOperDecod;

public:
    PrintService(Memoria *memoria, TimeDecoder *timeDIn, CookDecoder *cookIn, OperDecoder *operIn) : LCD(mode4Lines, mode20Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27)
    {
        thisTimeDecod = timeDIn;
        thisCookDecod = cookIn;
        thisOperDecod = operIn;
    }
    void doService()
    {
        LCD.printTime(thisTimeDecod->getOutput());
        LCD.printCook(thisCookDecod->getOutput());
        LCD.printOper(thisOperDecod->getOutput());
    }
};

#endif /* SOURCES_CLASSES_SERVICES_H_ */
