#include "MKL25Z4.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "./Classes/services.h"

DigitalFactory monDigiFact = DigitalFactory();
Memoria monMemory = Memoria();
/*!
 * CLASSES DE SERVICO
 */
EditorService monEditorServ = EditorService(&monMemory, monDigiFact.getPtrTimer(), monDigiFact.getPtrTimeDecod(), monDigiFact.getPtrCookDecod(), monDigiFact.getPtrOperDecod());

TimerService monTimerServ = TimerService(&monMemory, monDigiFact.getPtrTimer(), monDigiFact.getPtrTimeDecod());

PrintService monPrintServ = PrintService(&monMemory, monDigiFact.getPtrTimeDecod(), monDigiFact.getPtrCookDecod(), monDigiFact.getPtrOperDecod());

/*
 * SYSTICK TIMER
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);
//FreqDivisor clock1Hz = FreqDivisor(1);
enableType doIntService = pause;
extern "C"
{
    void SysTick_Handler(void)
    {
        //clock1Hz.increment();
        //if (clock1Hz.getClock())
        monTimerServ.doService();
        monTimerServ.doFimLedService();
    }
}

int main(void)
{
    uint8_t tempo[4] = {0, 0, 1, 0};
    bool oper[3] = {1, 0, 0};
    monMemory.setTempoGeral(tempo);
    monMemory.setCookGeral(pp);
    monMemory.setOperGeral(oper);

    if (monMemory.servToDo.tempoGeral)
        monEditorServ.doSetTimeServ();

    if (monMemory.servToDo.editGeral)
        monEditorServ.doService();

    monMemory.setAction(play);
    if (monMemory.servToDo.actionGeral)
    {
        doIntService = monMemory.getAction();
        monTimerServ.doActionService();
    }
    while (1)
    {
        if (monMemory.servToDo.editGeral)
            monEditorServ.doService();
        monPrintServ.doService();
    }
}