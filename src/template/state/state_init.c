/*
 * state_init.c
 *
 *  Created on: Mar 13, 2016
 *      Author: root
 */

#include "../fsm.h"
#include "state.h"

static ge_fsm_state_st* state_init_get_next_status(int event_id){
	return NULL;
}

fsm_event_st state_init = {
		.state_id = ST_INIT,
		.name = "ST_INIT",
		.get_next_status = state_init_get_next_status,
};
