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

typedef struct
{
    bool inputTime = 0,
         upTimeR = 0,
         upTimeD = 0,
         inputCook = 0,
         inputOper = 0,
         inputAct = 0,
         cancelAct = 0,
         fimLed = 0,
         increment = 0;
} sId_doService;

typedef enum
{
    editServ,
    timeServ,
    incmServ,
    actiServ,
    fLedServ,
    prntServ

} sId;

class Memoria
{
private:
    uint8_t tempo_geral[4] = {0, 0, 0, 0};
    cookOption thisCookGeral = ed;
    bool operGeral[3] = {0, 0, 0};
    enableType thisAction = pause;
    bool thisCancelAction = 0;
    bool thisFimTimer = 0, doFimLedAct = 0;

public:
    sId_doService servToDo;

    Memoria()
    {
    }

    void setTempoGeral(uint8_t tempo[4])
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (tempo_geral[i] != tempo[i])
            {
                tempo_geral[i] = tempo[i];
                servToDo.inputTime = 1;
            }
        }
    }
    void TimerUpdate(uint8_t timer_up[4])
    {
        for (uint8_t i = 0; i < 4; i++)
            tempo_geral[i] = timer_up[i];
        servToDo.upTimeR = 1;
    }

    void setIsFimTimer(bool fim)
    {
        if (thisFimTimer != fim)
        {
            thisFimTimer = fim;
            servToDo.fimLed = 1;
        }
    }

    void setCookGeral(cookOption cookIn)
    {
        if (cookIn != thisCookGeral)
        {
            thisCookGeral = cookIn;
            servToDo.inputCook = 1;
        }
    }

    void setOperGeral(bool operIn[3])
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            if (operIn[i] != operGeral[i])
            {
                operGeral[i] = operIn[i];
                servToDo.inputOper = 1;
            }
        }
    }

    void setAction(enableType action)
    {
        if (thisAction != action)
        {
            thisAction = action;
            servToDo.inputAct = 1;
        }
    }

    void setCancelAction(bool cancel)
    {
        servToDo.cancelAct = 0;
        if (thisCancelAction != cancel)
        {
            thisCancelAction = cancel;
            servToDo.cancelAct = 1;
        }
    }

    bool setIncrement()
    {
        while (servToDo.inputTime == 1 && servToDo.upTimeD == 1)
        {
            servToDo.increment = 0;
        }
        servToDo.increment = 1;
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
    void doSetTimeServ()
    {
        thisTimer->setTime(thisMemoriaGeral->getTempoGeral());
    }
    void doService(uint8_t in)
    {
        if (in == 0)
            thisTimeDecod->setInput(thisTimer->getTime());
        else if (in == 1)
            thisCookDecod->setInput(thisMemoriaGeral->getCookGeral());
        else
            thisOperDecod->setInput(thisMemoriaGeral->getOperGeral());
    }
};

class TimerService
{
private:
    Memoria *thisMemoriaGeral;
    Timer *thisTimer;
    TimeDecoder *thisTimeDecod;
    Led fimLed = Led(gpio_PTB18);
    FreqDivisor clock = FreqDivisor(1);

public:
    TimerService(Memoria *memIn, Timer *timerIn, TimeDecoder *timeDIn)
    {
        thisMemoriaGeral = memIn;
        thisTimer = timerIn;
        thisTimeDecod = timeDIn;
    }

    void doActionService()
    {
        if (thisMemoriaGeral->getCancelAction())
        {
            thisTimer->cancelTimer();
            clock.reset();
            thisMemoriaGeral->setCancelAction(0);
        }
        else
        {
            thisTimer->enableTimer(thisMemoriaGeral->getAction());
            if (thisMemoriaGeral->getAction() == play)
                clock.enable(1);
            else
                clock.enable(0);
        }
    }

    void doFimLedService()
    {
        if (thisMemoriaGeral->getFimLedAction())
        {
            fimLed.turnOn();
            clock.reset();
        }
        else
            fimLed.turnOff();
    }

    void doService()
    {
        clock.increment();
        if (thisMemoriaGeral->getAction() == play)
        {
            if (clock.getClock())
            {
                thisTimer->decrement();
                thisMemoriaGeral->setIsFimTimer(thisTimer->endTimer());
            }
            thisMemoriaGeral->TimerUpdate(thisTimer->getTime());
        }
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
