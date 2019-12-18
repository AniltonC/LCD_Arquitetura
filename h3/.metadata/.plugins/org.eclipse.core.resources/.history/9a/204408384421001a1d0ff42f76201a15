/*
 * incrementService.h
 *
 *  Created on: Dec 17, 2019
 *      Author: anilton
 */

#ifndef SOURCES_SERVICOS_INCREMENTSERVICE_H_
#define SOURCES_SERVICOS_INCREMENTSERVICE_H_

#include "../Digitais/registrador.h"

typedef enum
{
    wait_for_full2 = 0,
    ask_permission = 1,
    wait_permission2 = 2,
    load_value = 3,
    end_state = 4
} estados2;

class IncrementService
{
private:
    bool endService;
    bool permission;
    estados2 stateService;
    int valueIncrement;
    int servico;

public:
    explicit IncrementService()
    {
        stateService = wait_for_full2;
        valueIncrement = 0;
        servico = 0;
    }

    void recebeIncremento(registrador *reg4, registrador *reg3, registrador *reg2, registrador *reg1)
    {
        //Debater a questao da permissao do digito para o usuario
        if (reg1->leValor() + valueIncrement > 9)
        {
            if (reg2->leValor() + 1 > 5)
            {
                if (reg3->leValor() + 1 > 9)
                {
                    if (reg4->leValor() + 1 < 6)
                    {
                        reg1->atualiza(reg1->leValor() + valueIncrement - 10);
                        reg2->atualiza(0);
                        reg3->atualiza(0);
                        reg4->atualiza(reg4->leValor() + 1);
                    }
                }
                else
                {
                    reg1->atualiza(reg1->leValor() + valueIncrement - 10);
                    reg2->atualiza(0);
                    reg3->atualiza(reg3->leValor() + 1);
                }
            }
            else
            {
                reg1->atualiza(reg1->leValor() + valueIncrement - 10);
                reg2->atualiza(reg2->leValor() + 1);
            }
        }
        else
        {
            reg1->atualiza(reg1->leValor() + valueIncrement);
        }
    }

    void machineState(bool b3, bool b7, bool permission)
    {
        switch (stateService)
        {
        case wait_for_full2:
            if (b3)
            {
                valueIncrement = 3;
                stateService = ask_permission;
            }
            else if (b7)
            {
                valueIncrement = 7;
                stateService = ask_permission;
            }
            else
            {
                stateService = wait_for_full2;
            }
            break;
        case ask_permission:
            stateService = wait_permission2;
            break;
        case wait_permission2:
            if (b3)
            {
                valueIncrement = 3;
            }
            if (b7)
            {
                valueIncrement = 7;
            }
            if (permission)
            {
                stateService = load_value;
            }
            else
            {
                stateService = wait_permission2;
            }
            break;
        case load_value:
            stateService = end_state;
            break;
        case end_state:
            stateService = wait_for_full2;
            break;
        }
    }
    void selectService()
    {
        if (stateService == wait_for_full2)
        {
            servico = 0;
        }
        else if (stateService == ask_permission || stateService == wait_permission2)
        {
            servico = 1;
        }
        else if (stateService == load_value)
        {
            servico = 2;
        }
        else
        {
            servico = 3;
        }
    }

    void doService(registrador *reg4, registrador *reg3, registrador *reg2, registrador *reg1)
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
            recebeIncremento(reg4, reg3, reg2, reg1);
        }
        else
        {
            endService = true;
            permission = false;
        }
    }
};

#endif /* SOURCES_SERVICOS_INCREMENTSERVICE_H_ */
