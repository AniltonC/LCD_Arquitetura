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

//PrintService monPrintServ = PrintService(&monMemory, monDigiFact.getPtrTimeDecod(), monDigiFact.getPtrCookDecod(), monDigiFact.getPtrOperDecod());

/*
 * SYSTICK TIMER
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);
FreqDivisor clock1Hz = FreqDivisor(1);
enableType doIntService = pause;
extern "C"
{
    void SysTick_Handler(void)
    {
        clock1Hz.increment();
        if (doIntService == play)
            if (clock1Hz.getClock())
                monTimerServ.doService();
    }
}

int main(void)
{
    uint8_t tempo[4] = {0, 0, 1, 0};
    bool oper[3] = {1, 0, 0};
    bool isUpTempo = monMemory.setTempoGeral(tempo);
    bool isUpCook = monMemory.setCookGeral(pp);
    bool isUpOper = monMemory.setOperGeral(oper);
    if (isUpTempo || isUpCook || isUpOper)
        monEditorServ.doService();

    bool isUpAction = monMemory.setAction(play);
    if (isUpAction)
    {
        doIntService = monMemory.getAction();
        monTimerServ.doActionService();
    }
    while (1)
    {
        monEditorServ.doService();
        monTimerServ.doFimLedService();
        //monPrintServ.doService();
    }
}