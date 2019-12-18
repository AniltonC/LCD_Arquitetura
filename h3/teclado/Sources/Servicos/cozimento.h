/*
 * cozimento.h
 *
 *  Created on: Dec 17, 2019
 *      Author: anilton
 */

#ifndef SOURCES_SERVICOS_COZIMENTO_H_
#define SOURCES_SERVICOS_COZIMENTO_H_
#include "stdint.h"
#include "../Digitais/registrador.h"
#include "../Classes/digital.h"
typedef enum
{
    H3_wait_for_full = 0,
    H3_ask_permission = 1,
    H3_wait_permission = 2,
    H3_load_value = 3,
    H3_end_state = 4
} estados_bluetooth;

class CozimentoService
{
private:
    bool endService;
    bool permission;
    estados_bluetooth stateService;
    int operacao;
    int servico;
public:
    char memoria;
    explicit CozimentoService()
    {
        stateService = H3_wait_for_full;
        servico = 0;
        operacao = 0;
        memoria='0';
    }

    void machineState(char chave, bool permission)
    {
        switch (stateService)
        {
        case H3_wait_for_full:
        	if(chave!=memoria){
        		memoria=chave;
        		stateService = H3_ask_permission;
        		if (memoria == '1'){
					operacao = 1;
				}
				else if (memoria == '2'){
					operacao = 2;
				}
				else if (memoria == '3'){
					operacao = 3;
				}
				else if (memoria == '4'){
					operacao = 4;
				}
				else if (memoria == '5'){
					operacao = 5;
				}
        	}
			else{
				stateService = H3_wait_for_full;
			}

            break;
        case H3_ask_permission:
            stateService = H3_wait_permission;
            break;
        case H3_wait_permission:
            if (permission)
            {
                stateService = H3_load_value;
            }
            else
            {
                stateService = H3_wait_permission;
            }
            break;
        case H3_load_value:
            stateService = H3_end_state;
            break;
        case H3_end_state:
            stateService = H3_wait_for_full;
            break;
        }
    }

    void selectService()
    {
        if (stateService == H3_wait_for_full)
        {
            servico = 0;
        }
        else if (stateService == H3_ask_permission || stateService == H3_wait_permission)
        {
            servico = 1;
        }
        else if (stateService == H3_load_value)
        {
            servico = 2;
        }
        else
        {
            servico = 3;
        }
    }

    void doService(registrador *reg4, registrador *reg3, registrador *reg2, registrador *reg1,cookOption *tipo)
    {
        if (servico == 0)
        {
            endService = false;
            permission = false;
        }
        else if (servico == 1)
        {
            endService = false;
            permission = true;
        }
        else if (servico == 2)
        {
            endService = false;
            permission = false;
            if (operacao == 1)
            {
                reg4->atualiza(0);
                reg3->atualiza(0);
                reg2->atualiza(3);
                reg1->atualiza(0);
                *tipo=pz;
            }
            else if (operacao == 2)
            {
                reg4->atualiza(0);
                reg3->atualiza(1);
                reg2->atualiza(0);
                reg1->atualiza(1);
                *tipo=pp;
            }
            else if (operacao == 3)
            {
                reg4->atualiza(0);
                reg3->atualiza(2);
                reg2->atualiza(0);
                reg1->atualiza(2);
                *tipo=la;
            }
            else if (operacao == 4)
            {
                reg4->atualiza(0);
                reg3->atualiza(0);
                reg2->atualiza(0);
                reg1->atualiza(0);
            }
        }
        else
        {
            endService = true;
            permission = false;
        }
    }
};

#endif /* SOURCES_SERVICOS_COZIMENTO_H_ */
