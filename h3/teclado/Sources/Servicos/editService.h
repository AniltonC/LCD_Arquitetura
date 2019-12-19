/*
 * editService.h
 *
 *  Created on: Dec 17, 2019
 *      Author: anilton
 */

#ifndef SOURCES_SERVICOS_EDITSERVICE_H_
#define SOURCES_SERVICOS_EDITSERVICE_H_

#include "../Digitais/registrador.h"
#include "../Classes/digital.h"
#include "../Classes/monitor.h"
typedef enum
{
    wait_for_full = 0,
    wait_for_fim_full = 1,
    sent_permission = 2,
    wait_permission = 3,
    arrived_permission = 4,
    final = 5,
} estados_service;

class controlador
{
private:
    estados_service atual;
    int servico;
    bool pede_permissao;
    bool finish;
    bool contagem;
    MonitorLCD *LCD;

    uint8_t tempoUpdate[4] = {0, 0, 0, 0};

public:
    explicit controlador(MonitorLCD *param_lcd)
    {
        atual = wait_for_full;
        servico = 0;
        pede_permissao = 0;
        finish = 0;
        contagem = 0;
        LCD = param_lcd;
    }

    void maq_est(bool press, bool permission)
    {
        switch (atual)
        {
        case wait_for_full:
            if (press)
            {
                atual = wait_for_fim_full;
            }
            else
            {
                atual = wait_for_full;
            }
            break;
        case wait_for_fim_full:
            if (press)
            {
                atual = wait_for_fim_full;
            }
            else
            {
                atual = sent_permission;
            }
            break;
        case sent_permission:
            atual = wait_permission;
            break;
        case wait_permission:
            if (permission)
            {
                atual = arrived_permission;
            }
            else
            {
                atual = wait_permission;
            }
            break;
        case arrived_permission:
            atual = final;
            break;
        case final:
            atual = wait_for_full;
            break;
        }
    }

    void select_service()
    {
        if (atual == wait_for_full || atual == wait_for_fim_full)
        {
            servico = 0;
        }
        else if (atual == sent_permission || atual == wait_permission)
        {
            servico = 1;
        }
        else if (atual == arrived_permission)
        {
            servico = 2;
        }
        else
        {
            servico = 3;
        }
    }

    void do_service(registrador *four, registrador *three, registrador *two, registrador *one, int key)
    {
        if (servico == 0)
        {
            pede_permissao = 0;
            finish = 0;
        }
        else if (servico == 1)
        {
            pede_permissao = 1;
            finish = 0;
        }
        else if (servico == 2)
        {
            LCD->monMemory.setCookGeral(ed);
            pede_permissao = 0;
            finish = 0;
            four->atualiza(three->leValor());
            three->atualiza(two->leValor());
            two->atualiza(one->leValor());
            one->atualiza(key);

            tempoUpdate[3] = one->leValor();
            tempoUpdate[2] = two->leValor();
            tempoUpdate[1] = three->leValor();
            tempoUpdate[0] = four->leValor();

            LCD->monMemory.setTempoGeral(tempoUpdate);
            //*tipo=ed;
        }
        else if (servico == 3)
        {
            pede_permissao = 0;
            finish = 1;
        }
    }
};

#endif /* SOURCES_SERVICOS_EDITSERVICE_H_ */
