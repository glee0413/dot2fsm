/*
 * fsm.c
 *
 *  Created on: Mar 8, 2016
 *      Author: root
 */
#include <stdio.h>
#include <stdlib.h>
#include <fsm.h>

int
do_fsm_action(ge_fsm_st *fsm,int event_id,void* data,int len){
	fsm_event_st event;
	int action_type = 0;
	ge_fsm_state_st* next_state = NULL;

	if(!fsm)
		return -1;

	memset(&event,0,sizeof(fsm_event_st));
	event.event_id = event_id;
	event.data = data;
	event.len = len;

	action_type = fsm->cur_state.do_action(&event);

	while(FAS_NEXT_STATE == action_type){
		if(fsm->cur_state.exit_action)
			fsm->cur_state.exit_action(&event);
		next_state = fsm->cur_state.get_next_status(&event);
		if(!next_state){
			action_type = FAS_ERROR;
			break;
		}
		fsm->pre_state = fsm->cur_state;
		fsm->cur_state = next_state;
		if(fsm->cur_state.entry_action){
			action_type = fsm->cur_state.entry_action(&fsm->pre_state);
		}else{
			action_type = FAS_OK;
		}
	}

	return 0;
}

int init_fsm(ge_fsm_st *fsm){

	return 0;
}

