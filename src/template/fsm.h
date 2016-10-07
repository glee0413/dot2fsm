/*
 * fsm.h
 *
 *  Created on: Mar 8, 2016
 *      Author: root
 */

#ifndef FSM_FSM_H_
#define FSM_FSM_H_

enum FSM_ACTION_STATUS{
	FAS_ERROR = -1,
	FAS_OK = 0,
	FAS_NEXT_STATE,
	FAS_IGNORE,
	FAS_MAX,
};

typedef struct ge_fsm_event{
	int event_id;
	void* data;
	int len;
	void* result;
} fsm_event_st;

typedef struct ge_fsm_state{
	int state_id;
	char* name;
	struct ge_fsm_state* (*get_next_status)(int event_id);
	int (*do_action)(fsm_event_st* event);
	int (*entry_action)(const struct ge_fsm_state* pre_status);
	int (*exit_action)(fsm_event_st* event);
	int timeout;
}ge_fsm_state_st;

typedef struct ge_fsm{
	ge_fsm_state_st pre_state;
	ge_fsm_state_st cur_state;

}ge_fsm_st;

#endif /* FSM_FSM_H_ */
