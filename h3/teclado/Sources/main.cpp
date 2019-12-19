#include "stdint.h"
#include "MKL25Z4.h"

#include "./Teclado/mkl_KeyboardParallelPort.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "./Dispositivos/led.h"
#include "./Dispositivos/switch.h"

#include "./Dispositivos/decoder.h"
#include "./Servicos/cozimento.h"
#include "./Servicos/editService.h"
#include "./Servicos/incrementService.h"

#include "./Classes/services.h"
#include "./Classes/monitor.h"
#include "./Classes/devices.h"
#include "../Includes/mkl_HC06BluetoothSlave.h"

#include "Motor/classesComunicao.h"

MonitorLCD LCDTimerMonitor = MonitorLCD();

MonitorMotor Motor(gpio_PTC7, gpio_PTC0, tpm_PTD4, gpio_PTA1, gpio_PTA2, gpio_PTC3, gpio_PTC4, gpio_PTC5, gpio_PTC6, &LCDTimerMonitor);

uint8_t tempo[4] = {1, 0, 0, 0};

mkl_HC06BluetoothSlave bt(uart0_PTD7, uart0_PTD6);
char buf[20];
int pos = 0;

mkl_KeyboardParallelPort keyboard(gpio_PTA13, gpio_PTD5, gpio_PTD0, gpio_PTD2, gpio_PTC12, gpio_PTC13, gpio_PTC16, gpio_PTC17);

mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);
//
registrador Us(0);
registrador Ds(0);
registrador Um(0);
registrador Dm(0);
//
Switch botao3(gpio_PTA12), botao7(gpio_PTA1);

//Switch permission(gpio_PTC3);

controlador service_edit(&LCDTimerMonitor);

IncrementService service_inc(&LCDTimerMonitor);

CozimentoService service_coz(&LCDTimerMonitor);

char key;
int valor = 0;

extern "C"
{
	void UART0_IRQHandler()
	{
		if (pos < 20)
		{
			buf[pos] = bt.receive8Bits();
			pos++;
		}
		else
		{
			pos = 0;
			buf[pos] = bt.receive8Bits();
			pos++;
		}
	}
	void SysTick_Handler(void)
	{
		keyboard.update();
		key = keyboard.getKey();
		if (keyboard.keyIsPressed())
		{
			valor = key;
		}

		LCDTimerMonitor.doServiceFromIRQ();
	}
}

void setup()
{
	bt.setInterruptMode(uart_Rx);
	bt.setPriority(uart_Priority0);
	bt.enableInterrupt();

	LCDTimerMonitor.monMemory.setTempoGeral(tempo);
	tempo[3] = 0;
	tempo[2] = 0;
	tempo[1] = 0;
	tempo[0] = 0;
	LCDTimerMonitor.monMemory.setTempoGeral(tempo);
	LCDTimerMonitor.monMemory.setCookGeral(i3);
	LCDTimerMonitor.monMemory.setCookGeral(ed);
}

int main()
{
	int contador = 0;
	bool cont_blut = false;
	setup(); //! Configura o periférico bluetooth
	while (1)
	{
		// if (cont_blut)
		// {
		// 	Motor.setActionMotor(true);
		// }
		// else
		// {
		// 	Motor.setActionMotor(false);
		// }

		Us.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[3]);
		Ds.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[2]);
		Um.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[1]);
		Dm.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[0]);

		Motor.readAllInput();

		service_edit.maq_est(keyboard.keyIsPressed(), 1);
		service_edit.select_service();
		service_edit.do_service(&Dm, &Um, &Ds, &Us, valor);

		service_inc.machineState(botao3.isOn(), botao7.isOn(), 1);
		service_inc.selectService();
		service_inc.doService(&Dm, &Um, &Ds, &Us);

		while (contador <= pos)
		{
			if (buf[contador] != service_coz.memoria)
			{
				if (buf[contador] == '5')
				{
					cont_blut = !cont_blut;
				}
				service_coz.machineState(buf[contador], 1);
				service_coz.selectService();
				service_coz.doService(&Dm, &Um, &Ds, &Us);
				contador = pos;
			}
			contador++;
		}
		contador = 0;
		pos = 0;

		//tempo[3] = Us.leValor();
		//tempo[2] = Ds.leValor();
		//tempo[1] = Um.leValor();
		//tempo[0] = Dm.leValor();
		//LCDTimerMonitor.monMemory.setTempoGeral(tempo);

		Motor.doService();
		LCDTimerMonitor.doService();
	}
	return 0;
}
