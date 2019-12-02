/*!
 * @copyright   � 2019 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para  o System Tick Timer (MKL25Z).
 *
 * @file        mkl_Systick.cpp
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

#include "mkl_Systick.h"

/*!
 *   @fn			setClockSource
 *
 * 	 @brief 		configura o clocl a ser usado.
 *
 * 	 Clock pode ser setado em: clock2Mhz ou clock48Mhz.Para valor de clock em 2Mhz(0)
 * 	 o valor do Clock utilizado no algoritmo ser� o valor do Clock do N�cleo (42Mhz)
 * 	 dividido por 16. Caso contr�rio, o Clock utilizado ser� o mesmo do n�cleo.
 *
 *	 @param[in]	clock - clock do sistema ou clock do sistema dividido por 16
 *
 *	 @remarks	Siglas
 *				- addrSTCSR: SYSTick Control and Status Register.
 */
void mkl_Systick::setClockSource(systick_clockSource clock) {
    setRegister();
    if (clock)
        *addrSTCSR |= 0x00000004;
    else
        *addrSTCSR &= ~0x00000004;
}

/*!
 *   @fn		setReload
 *
 * 	 @brief 	Seta a quantidade de ciclos no registrador
 *
 *	 @param[in]	- reloadValue: Valor da quantidade de ciclos no registrador (Valores entre 1 e 0x00FFFFFF).
 *
 *	 @remarks	Siglas
 *			    - addrSTCSR: SYSTick Reload Value Register.
 */
void mkl_Systick::setReload(uint32_t reloadValue) {
    *addrSTRVR = reloadValue;
}

/*!
 *   @fn		enableCounter
 *
 * 	 @brief 	Habilita o systick.
 *
 *	 @remarks	Siglas
 *				- addrSTCSR: SYSTick Control and Status Register.
 */
void mkl_Systick::enableCounter() {
    *addrSTCSR |= 0x00000001;
}

/*!
 *   @fn		disableCounter
 *
 * 	 @brief 	Desabilita o systick.
 *
 *	 @remarks	Siglas
 *				- addrSTCSR: SYSTick Control and Status Register.
 */
void mkl_Systick::disableCounter() {
    *addrSTCSR &= ~0x00000001;
}

/*!
 *   @fn		clearCounter
 *
 * 	 @brief 	Limpa o contador do systick.

 *	 @remarks	Siglas
 *				- addrSTCVR: SYSTick Current Value Register.
 */
void mkl_Systick::clearCounter() {
    *addrSTCVR = 0;
}

/*!
 *   @fn		enableInterrupt
 *
 * 	 @brief 	Habilita interrup��o do systick.
 *
 *	 @remarks	Siglas
 *				- addrSTCSR: SYSTick Control and Status Register.
 */
void mkl_Systick::enableInterrupt() {
    *addrSTCSR |= 0x00000002;
}

/*!
 *   @fn		disableInterrupt
 *
 * 	 @brief 	Desabilita a interrup��o do systick.
 *
 *	 @remarks	Siglas
 *				- addrSTCSR: SYSTick Control and Status Register.
 */
void mkl_Systick::disableInterrupt() {
    *addrSTCSR &= ~0x00000002;
}

/*!
 *   @fn		setRegister
 *
 * 	 @brief 	Endere�a os registradores do systick.
 *
 *	 @remarks	Siglas
 *				- addrSTCSR: SYSTick Control and Status Register.
 *				- addrSTCSR: SYSTick Reload Value Register.
 *				- addrSTCVR: SYSTick Current Value Register.
 *				- addrSTCALIB: SYSTick Calibration Value Register.
 *
 */
void mkl_Systick::setRegister() {
    addrSTCSR = (volatile unsigned int *)(0xE000E010);
    addrSTRVR = (volatile unsigned int *)(0xE000E014);
    addrSTCVR = (volatile unsigned int *)(0xE000E018);
    addrSTCALIB = (volatile unsigned int *)(0xE000E01C);
}
