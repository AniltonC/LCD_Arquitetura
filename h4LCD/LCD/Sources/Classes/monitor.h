/*
 * monitor.h
 *
 *  Created on: Dec 12, 2019
 *      Author: anilton
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include "services.h"

class MonitorLCD
{
private:
    DigitalFactory monDigiFact = DigitalFactory();
    EditorService monEditorServ;
    TimerService monTimerServ;
    PrintService monPrintServ;
    sId monServSId, mStateSId, atualState, nextState;

public:
    Memoria monMemory = Memoria();
    MonitorLCD() : monEditorServ(&monMemory, monDigiFact.getPtrTimer(), monDigiFact.getPtrTimeDecod(), monDigiFact.getPtrCookDecod(), monDigiFact.getPtrOperDecod()), monTimerServ(&monMemory, monDigiFact.getPtrTimer(), monDigiFact.getPtrTimeDecod()), monPrintServ(&monMemory, monDigiFact.getPtrTimeDecod(), monDigiFact.getPtrCookDecod(), monDigiFact.getPtrOperDecod())
    {
    }
    void selectService()
    {
        /*
        switch (nextState)
        {
        case timeServ:
            if (monMemory.servToDo.tempoGeral)
            {
                monMemory.servToDo.tempoGeral = 0;
                atualState = nextState;
            }
            nextState = editServ;
            return;

        case editServ:
            if (monMemory.servToDo.edit)
            {
                monMemory.servToDo.edit = 0;
                atualState = nextState;
            }
            nextState = actiServ;
            return;

        case actiServ:
            if (monMemory.servToDo.actionGeral)
            {
                monMemory.servToDo.actionGeral = 0;
                atualState = nextState;
            }
            nextState = fLedServ;
            return;

        case fLedServ:
            if (monMemory.servToDo.fimLed)
            {
                monMemory.servToDo.fimLed = 0;

                atualState = nextState;
            }
            nextState = prntServ;
            return;

        case prntServ:
            atualState = nextState;
            nextState = editServ;
            return;
        }
        */
    }

    void doService()
    {
        if (monMemory.servToDo.inputTime || monMemory.servToDo.upTimeR)
        {
            monEditorServ.doSetTimeServ();
            monMemory.servToDo.inputTime = 0;
            monMemory.servToDo.upTimeR = 0;
            monMemory.servToDo.upTimeD = 1;
        }

        if (monMemory.servToDo.upTimeD)
        {
            monEditorServ.doService(0);
            monMemory.servToDo.upTimeD = 0;
        }

        if (monMemory.servToDo.inputCook)
        {
            monEditorServ.doService(1);
            monMemory.servToDo.inputCook = 0;
        }

        if (monMemory.servToDo.inputOper)
        {
            monEditorServ.doService(2);
            monMemory.servToDo.inputOper = 0;
        }

        if (monMemory.servToDo.inputAct)
        {
            monTimerServ.doActionService();
            monMemory.servToDo.inputAct = 0;
        }

        if (monMemory.servToDo.cancelAct)
        {
            monTimerServ.doActionService();
            monMemory.servToDo.cancelAct = 0;
        }

        
        monPrintServ.doService();
    }

    void doServiceFromIRQ()
    {
        monTimerServ.doService();
        if (monMemory.servToDo.fimLed)
        {
            monTimerServ.doFimLedService();
            monMemory.servToDo.fimLed = 0;
        }
    }
};

#endif /* MONITOR_H_ */
