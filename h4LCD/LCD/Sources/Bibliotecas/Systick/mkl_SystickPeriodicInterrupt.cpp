/*!
 * @copyright   � 2019 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para  o System Tick Timer (MKL25Z).
 *
 * @file        mkl_SystickPeriodicInterrupt.cpp
 * @version     1.0
 * @date        31 Janeiro 2019
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   Systick - System Tick Timer.
 *              +compiler     Kinetis� Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Vers�o (data): Descri��o breve.
 *                             ++ 1.0 (31 Janeiro 2019): Vers�o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computa��o / Engenharia El�trica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Vers�o inicial:
 *                             ++ Victoria da Silva Leite <victoria.vl73@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa � um software livre; Voc� pode redistribu�-lo
 *              e/ou modific�-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              vers�o 3 da licen�a, ou qualquer vers�o posterior.
 *
 *              Este programa � distribu�do na esperan�a de que seja �til,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia impl�cita de
 *              COMERCIALIZA��O OU USO PARA UM DETERMINADO PROP�SITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */
#include "mkl_SystickPeriodicInterrupt.h"

/*!
 *   @fn		mkl_SystickPeriodicInterrupt
 *
 * 	 @brief		Construtor padr�o da classe.
 *   O construtor padr�o da classe obt�m o tempo de interrup��o periodica e
 *   o clock desejado, e configura o clock e tempo de interrup��o, habilita
 *   a interrup��o e limpa a contagem do systick.
 *
 *
 *	 @param[in] time_ms - Tempo em milisegundos para a interrup��o.
 *	 			clock - clock do sistema ou clock do sistema dividido por 16.
 */
mkl_SystickPeriodicInterrupt::mkl_SystickPeriodicInterrupt(uint32_t time_ms, systick_clockSource clock) {
	/*!
	 *  Clock pode ser setado em: clock12Mhz ou clock48Mhz.
	 */
    setClockSource(clock);

	/*!
	 * 	Habilita o systick.
	 */
    enableCounter();

	/*!
	 *  Seta o valor de recarga que ser� usado na contagem.
	 */
    setReload(reloadValue(time_ms, clock));

	/*!
	 *  Zera o contador.
	 */
    clearCounter();

	/*!
	 *  Habilita as requisi��es de interrup��o.
	 */
    enableInterruptRequest();
}

/*!
 *   @fn		enableInterruptRequest
 *
 * 	 @brief		Habilita a interrup��o do systick.
 */
void mkl_SystickPeriodicInterrupt::enableInterruptRequest() {
    __enable_irq();
    NVIC_EnableIRQ(SysTick_IRQn);
    enableInterrupt();
}
/*!
 *   @fn		disableInterruptRequest
 *
 * 	 @brief		Desabilita a interrup��o do systick.
 */
void mkl_SystickPeriodicInterrupt::disableInterruptRequest() {
    __disable_irq();
    NVIC_DisableIRQ(SysTick_IRQn);
    disableInterrupt();
}

/*!
 *   @fn		setPriority
 *
 * 	 @brief		Seta prioridade da interrup��o do systick
 *
 */
void mkl_SystickPeriodicInterrupt::setPriority(st_Priority_t priority) {
    NVIC_SetPriority(SysTick_IRQn, priority);
}

/*!
 *   @fn		getPriority
 *
 * 	 @brief		Retorna a prioridade de interrup��o no vetor de interrup��es NVIC.
 *
 *	 @param[out] Prioridade da interrup��o do systick.
 */
st_Priority_t mkl_SystickPeriodicInterrupt::getPriority() {
    return (st_Priority_t) NVIC_GetPriority(SysTick_IRQn);
}

/*!
 *   @fn		reloadValue
 *
 * 	 @brief		M�todo interno para calcular o valor de reload relativo ao tempo em milisegundos.
 *
 *	 @param[in]	time_ms - Tempo em milisegundos para a interrup��o.
 *	 			clock - clock do sistema ou clock do sistema dividido por 16.
 *
 *	 @param[out] reloadValue - Valor da quantidade de ciclos no registrador.
 */
uint32_t mkl_SystickPeriodicInterrupt::reloadValue(uint32_t time_ms, systick_clockSource  clock ) {
    uint32_t sys_clock;
    uint32_t reload = 0;

    if (clock == 1) {
        sys_clock = 41940000;
        reload = time_ms*41940 - 1;
    } else {
        sys_clock = 2621250;
        reload = time_ms*2621.25 - 1;
    }
    return reload;
}
