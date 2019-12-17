//#include "digitalFactory.h"
#include "../digitais/registrador.h"


typedef enum{
	H3_wait_for_full=0,
	H3_ask_permission=1,
	H3_wait_permission=2,
	H3_load_value=3,
	H3_end_state=4
}estados_bluetooth;


class CozimentoService{

public:
	explicit CozimentoService();
	void machineState(char chave, bool permission);
	void selectService();
	void doService(registrador *reg4,registrador *reg3,registrador *reg2,registrador *reg1);
private:
	bool endService;
	bool permission;
	estados_bluetooth stateService;
	int operacao;
	int servico;
};
