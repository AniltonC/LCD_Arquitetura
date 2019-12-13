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
        bool getOut = 0;
        while (!getOut)
        {
            switch (nextState)
            {
            case editServ:
                if (monMemory.servToDo.editGeral)
                {
                    getOut = 1;
                    atualState = nextState;
                }
                nextState = actiServ;

            case actiServ:
                if (monMemory.servToDo.actionGeral)
                {
                    getOut = 1;
                    atualState = nextState;
                }
                nextState = fLedServ;

            case fLedServ:
                if (monMemory.servToDo.fimLed)
                {
                    getOut = 1;
                    atualState = nextState;
                }
                nextState = prntServ;

            case prntServ:
                getOut = 1;
                atualState = nextState;
                nextState = editServ;
            }
        }
    }
};

#endif /* MONITOR_H_ */
