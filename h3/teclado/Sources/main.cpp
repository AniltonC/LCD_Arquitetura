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

//SystemKeyService motor(gpio_PTD7, gpio_PTD6, tpm_PTD4, gpio_PTA1, gpio_PTA2, gpio_PTA17, gpio_PTC17, gpio_PTC12, gpio_PTC13, gpio_PTC6);

MonitorLCD LCDTimerMonitor = MonitorLCD();
uint8_t tempo[4] = {1, 0, 0, 0};
cookOption cookOpt = pp;

mkl_HC06BluetoothSlave bt(uart0_PTD7, uart0_PTD6);
char buf[20];
int pos=0;


mkl_KeyboardParallelPort keyboard(gpio_PTA13, gpio_PTD5, gpio_PTD0, gpio_PTD2,
								  gpio_PTC12, gpio_PTC13, gpio_PTC16, gpio_PTC17);


mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);
//
registrador Us(0);
registrador Ds(0);
registrador Um(0);
registrador Dm(0);
//
Switch botao3(gpio_PTC7), botao7(gpio_PTC0);

//Switch permission(gpio_PTC3);

controlador service_edit;

IncrementService service_inc;

CozimentoService service_coz;

char key;
int valor = 0;

extern "C"{
	void UART0_IRQHandler(){
		if(pos<20){
			buf[pos] = bt.receive8Bits();
			pos++;
		}
		else{
			pos=0;
			buf[pos] = bt.receive8Bits();
			pos++;
		}
	}
	void SysTick_Handler(void){
		keyboard.update();
		key = keyboard.getKey();
		if (keyboard.keyIsPressed())
		{
			valor = key;
		}
		LCDTimerMonitor.doServiceFromIRQ();
	}
}

void setup(){
	bt.setInterruptMode(uart_Rx);
	bt.setPriority(uart_Priority0);
	bt.enableInterrupt();

	LCDTimerMonitor.monMemory.setTempoGeral(tempo);
	tempo[3] = 0;
	tempo[2] = 0;
	tempo[1] = 0;
	tempo[0] = 0;
	LCDTimerMonitor.monMemory.setTempoGeral(tempo);
}

int main(){
	int contador=0;
	bool cont_blut=false;
	setup(); //! Configura o periférico bluetooth
	while (1){
		if(cont_blut){
			LCDTimerMonitor.monMemory.setAction(play);
		}
		else{
			LCDTimerMonitor.monMemory.setAction(pause);
		}


		Us.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[3]);
		Ds.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[2]);
		Um.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[1]);
		Dm.atualiza(LCDTimerMonitor.monMemory.getTempoGeral()[0]);

		service_edit.maq_est(keyboard.keyIsPressed(), 1);
		service_edit.select_service();
		service_edit.do_service(&Dm, &Um, &Ds, &Us, valor,&cookOpt);

		service_inc.machineState(botao3.isOn(), botao7.isOn(), 1);
		service_inc.selectService();
		service_inc.doService(&Dm, &Um, &Ds, &Us,&cookOpt);
		//LCDTimerMonitor.monMemory.setIncrement(incTime);
		//


		while(contador<=pos){
			if(buf[contador]!=service_coz.memoria){
				if(buf[contador]=='5'){
					cont_blut=!cont_blut;
				}
				service_coz.machineState(buf[contador], 1);
				service_coz.selectService();
				service_coz.doService(&Dm, &Um, &Ds, &Us,&cookOpt);
				contador=pos;
			}
			contador++;
		}
		contador=0;
		pos=0;




		tempo[3] = Us.leValor();
		tempo[2] = Ds.leValor();
		tempo[1] = Um.leValor();
		tempo[0] = Dm.leValor();
		LCDTimerMonitor.monMemory.setTempoGeral(tempo);
		//		LCDTimerMonitor.monMemory.setOperGeral(oper);
		LCDTimerMonitor.monMemory.setCookGeral(cookOpt);

//
//		motor.readAllInput();
//		motor.doService();
		LCDTimerMonitor.doService();


	}
	return 0;
}
