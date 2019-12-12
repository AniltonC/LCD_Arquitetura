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
    bool tempoGeral = 0,
         cookGeral = 0,
         operGeral = 0,
         actionGeral = 0,
         cancelAct = 0,
         fimLed = 0;
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
    cookOption thisCookGeral;
    bool operGeral[3] = {0, 0, 0};
    enableType thisAction;
    bool thisCancelAction;
    bool thisFimTimer, doFimLedAct;

public:
    sId_doService servToDo;

    Memoria()
    {
        thisCookGeral = ed;
        thisAction = pause;
        thisCancelAction = 0;
        thisFimTimer = 0;
    }

    void setTempoGeral(uint8_t tempo[4])
    {
        servToDo.tempoGeral = 0;
        for (uint8_t i = 0; i < 4; i++)
        {
            if (tempo_geral[i] != tempo[i])
            {
                tempo_geral[i] = tempo[i];
                servToDo.tempoGeral = 1;
            }
        }
    }
    void TimerUpdate(uint8_t timer_up[4])
    {
        for (uint8_t i = 0; i < 4; i++)
            tempo_geral[i] = timer_up[i];
    }

    void setIsFimTimer(bool fim)
    {
        servToDo.fimLed = 0;
        if (thisFimTimer != fim)
        {
            thisFimTimer = fim;
            servToDo.fimLed = 1;
        }
    }

    void setCookGeral(cookOption cookIn)
    {
        servToDo.cookGeral = 0;
        if (cookIn != thisCookGeral)
        {
            thisCookGeral = cookIn;
            servToDo.cookGeral = 1;
        }
    }

    void setOperGeral(bool operIn[3])
    {
        servToDo.operGeral = 0;
        for (uint8_t i = 0; i < 3; i++)
        {
            if (operIn[i] != operGeral[i])
            {
                operGeral[i] = operIn[i];
                servToDo.operGeral = 0;
            }
        }
    }

    void setAction(enableType action)
    {
        servToDo.actionGeral = 0;
        if (thisAction != action)
        {
            thisAction = action;
            servToDo.actionGeral = 1;
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
        thisTimeDecod->setInput(thisTimer->getTime());
    }
};

class TimerService
{
private:
    Memoria *thisMemoriaGeral;
    Timer *thisTimer;
    TimeDecoder *thisTimeDecod;
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
        thisTimer->decrement();
        thisMemoriaGeral->setIsFimTimer(thisTimer->endTimer());
        thisMemoriaGeral->TimerUpdate(thisTimer->getTime());
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
