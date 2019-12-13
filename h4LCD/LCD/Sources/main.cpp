#include "MKL25Z4.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "./Classes/services.h"
#include "./Classes/monitor.h"

//MONITOR
MonitorLCD LCDTimerMonitor = MonitorLCD();

/*
 * SYSTICK TIMER
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

extern "C"
{
    void SysTick_Handler(void)
    {
        LCDTimerMonitor.doServiceFromIRQ();
    }
}

int main(void)
{
    uint8_t tempo[4] = {0, 2, 0, 0};
    bool oper[3] = {1, 0, 1};

    LCDTimerMonitor.monMemory.setTempoGeral(tempo);
    LCDTimerMonitor.monMemory.setOperGeral(oper);
    LCDTimerMonitor.monMemory.setCookGeral(la);
    LCDTimerMonitor.monMemory.setAction(play);
    while (1)
    {
        LCDTimerMonitor.doService();
    }
}
