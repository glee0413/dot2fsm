/*
 * dotparse.cpp
 *
 *  Created on: 2016年6月21日
 *      Author: light
 *      Mail: glee-0413@163.com
 */

#include "Dot2Fsm.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <utils/macro.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include<fstream>
#include <algorithm>
#include <utils/StringUtils.h>
#include <ctemplate/fsm_template_token.h>

extern const char fsm_c[];
extern const char fsm_h[];
extern const char state_c[];
extern const char state_func[];
extern const char state_h[];

using namespace UTILS;
using namespace std;

Dot2Fsm::Dot2Fsm() {
	// TODO Auto-generated constructor stub
	m_stateCount = 0;
}

Dot2Fsm::~Dot2Fsm() {
	// TODO Auto-generated destructor stub
}

int
Dot2Fsm::parseDotFile(const char* dotFile){
	//GVC_t *gvc;
	graph_t *g;
	FILE *fp;
	Agnode_t* np;
	Agedge_t *ep;
	char label_str[16] = "label";

	//gvc = gvContext();
	fp = fopen(dotFile, "r");
	if (!fp){
		printf("Open file %s failed: reason :%s\n",dotFile,strerror(errno));
		return -1;
	}
	g = agread(fp, 0);
	if (!g) {
		printf("parse file failed");
		return -1;
	}

	if (!agisdirected(g)) {
		printf("dot file must directed graph\n");
		agclose(g);
		return -1;
	}

	this->m_fsmName = agnameof(g);
	StringUtils::toLower(m_fsmName);

	for (np = agfstnode (g); np; np = agnxtnode (g, np)) {
		if(!agfstedge(g, np)){
			continue;
		}
		this->m_stateList.push_back(agnameof(np));
		if(this->m_stateTransfer.find(agnameof(np)) != this->m_stateTransfer.end()){
			printf("Node is exist\n");
			agclose(g);
			return -1;
		}
		this->m_stateTransfer[agnameof(np)] = vector<StateTransfer>();
		for (ep = agfstedge(g, np); ep; ep = agnxtedge(g, ep, np)){
			Agnode_t *hp = aghead(ep);
			Agnode_t *tp = agtail(ep);
			string event;
			string next_state;
			if(hp == np && hp != tp){
				//NOTE: skip other status transfer to me
				continue;
			}
			if(!agget(ep,label_str)){
				printf("Node %s: has a noname event\n",agnameof(np));
				agclose(g);
				return -1;
			}
			next_state = agnameof(hp);
			event = agget(ep,label_str);
			StringUtils::toLower(next_state);
			StringUtils::toLower(event);
			this->m_stateTransfer[agnameof(np)].push_back(StateTransfer(event,next_state));

			if(find(m_eventList.begin(), m_eventList.end(), event) == m_eventList.end()){
				m_eventList.push_back(agget(ep,label_str));
			}
		}
	}
	agclose(g);

	for(vector<string>::iterator it = this->m_stateList.begin();
					it != this->m_stateList.end() ;it++){
		StringUtils::toLower(*it);
	}

	for(vector<string>::iterator it = this->m_eventList.begin();
					it != this->m_eventList.end() ;it++){
		StringUtils::toLower(*it);
	}

	return 0;
}

int
Dot2Fsm::generalFSMCode(int language){
	int ret = 0;
	switch(language){
	case FL_C_LANGUAGE:
		ret = this->generalFSMCode_C();
		break;
	case FL_CPP_LANGUAGE:
		break;
	}
	return ret;
}

int Dot2Fsm::createFSMDir(){
	if(access(this->m_fsmName.c_str(),F_OK) == 0){
			struct stat filestat;
			if(stat(this->m_fsmName.c_str(),&filestat) == -1){
				perror("stat");
				return -1;
			}
			if(!S_ISDIR(filestat.st_mode)){
				printf("%s is not directory\n",this->m_fsmName.c_str());
				return -1;
			}
		}else{
			if(mkdir(this->m_fsmName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
				printf("mkdir %s failed:%s",this->m_fsmName.c_str(),strerror(errno));
				return -1;
			}
		}

		if(chdir(this->m_fsmName.c_str())){
			printf("change director %s failed: %s\n",this->m_fsmName.c_str(),strerror(errno));
			return -1;
		}

		printf("%s\n",get_current_dir_name());
		return 0;
}

int Dot2Fsm::buildReplaceString(map<int,string>& replace_str){
	replace_str[EFTT_FSM_H_FSMNAME] = this->m_fsmName;
	replace_str[EFTT_FSM_H_FSMUPNAME] = this->m_fsmName;
	StringUtils::toUpper(replace_str[EFTT_FSM_H_FSMUPNAME]);
	replace_str[EFTT_FSM_C_FSMNAME_STATE] = "s_" + this->m_fsmName + "_state";

	for (vector<string>::iterator it = this->m_stateList.begin();
			it != this->m_stateList.end(); it++) {
		string state_upcase = *it;
		string state_enum = replace_str[EFTT_FSM_H_FSMUPNAME] + "_" + state_upcase;

		StringUtils::toUpper(state_upcase);
		StringUtils::toUpper(state_enum);

		if (it == this->m_stateList.begin()) {
			replace_str[EFTT_FSM_H_STATE_LIST] = state_enum + " = 0,\n";
		} else {
			replace_str[EFTT_FSM_H_STATE_LIST] +=
					"\t" + state_enum + ",\n";
		}

		replace_str[EFTT_STATE_FSMNAME_INIT_STATE_FUNC] = this->m_fsmName
				+ "_int_" + *it;

		if (it != this->m_stateList.begin()) {
			replace_str[EFTT_FSM_C_STATE_INIT_FUNC_LIST] += "\t";
		}

		replace_str[EFTT_FSM_C_STATE_INIT_FUNC_LIST] +=
				replace_str[EFTT_STATE_FSMNAME_INIT_STATE_FUNC] + "(&"
						+ replace_str[EFTT_FSM_C_FSMNAME_STATE] + "["
						+ state_enum + "]);\n";

	}
	//replace_str[EFTT_FSM_C_STATE_LIST] = state_list;

	for (vector<string>::iterator it = this->m_eventList.begin();
			it != this->m_eventList.end(); it++) {
		string event_upcase = *it;
		StringUtils::toUpper(event_upcase);

		if (it == this->m_eventList.begin()) {
			replace_str[EFTT_FSM_H_EVENT_LIST] =
					replace_str[EFTT_FSM_H_FSMUPNAME] + "_" + event_upcase
							+ " = 0,\n";
		} else {
			replace_str[EFTT_FSM_H_EVENT_LIST] +=
					"\t" + replace_str[EFTT_FSM_H_FSMUPNAME] + "_" + event_upcase
							+ ",\n";
		}
	}

	for (vector<string>::iterator it = this->m_stateFileName.begin();
			it != this->m_stateFileName.end(); it++) {
		replace_str[EFTT_FSM_C_INCLUDE_STATE_HEADER_LIST] += "#include \"" + *it + ".h\"\n";
	}

	return 0;
}

int Dot2Fsm::generalStateCode_C(){
	map<int,string> replace_str;

	if(chdir(this->m_fsmName.c_str())){
		printf("change directory %s failed\n",this->m_fsmName.c_str());
		return -1;
	}



	for (vector<string>::iterator it = this->m_stateFileName.begin();
				it != this->m_stateFileName.end(); it++) {

		string filename = *it + "_state.h";
		fstream local_state_h(filename.c_str(), ios::out);

		filename = *it + "_state.c";
		fstream local_state_c(filename.c_str(), ios::out);

		filename = *it + "_state_func.c";
		fstream local_state_func_c(filename.c_str(), ios::out);

		string str_state_h = state_h;
		string str_state_c = state_c;
		string str_state_func = state_func;

		replace_str[EFTT_STATE_C_STATE_NAME] = *it;
		//this->m_stateTransfer
		vector<StateTransfer> stateTransfer = this->m_stateTransfer[*it];
		for(vector<StateTransfer>::iterator iter = stateTransfer.begin();
				iter != stateTransfer.end();iter++){
			//"case a: b; break;"
			replace_str[EFTT_STATE_C_SWITCH_NEXT_STATUS] = "\tcase ";
			replace_str[EFTT_STATE_C_SWITCH_NEXT_STATUS] += iter->EventName();
			replace_str[EFTT_STATE_C_SWITCH_NEXT_STATUS] += ":\n\t\treturn ";
			replace_str[EFTT_STATE_C_SWITCH_NEXT_STATUS] += iter->NextState();
			replace_str[EFTT_STATE_C_SWITCH_NEXT_STATUS] += ";";

			replace_str[EFTT_STATE_C_EVENT_HANDLER] = "\tcase ";
			replace_str[EFTT_STATE_C_EVENT_HANDLER] += iter->EventName() + ":\nt\treturn ";
			replace_str[EFTT_STATE_C_EVENT_HANDLER] += iter->EventName();
			replace_str[EFTT_STATE_C_EVENT_HANDLER] += "_handler(event);";
		}
		//TODO:change real timeout
		replace_str[EFTT_STATE_C_STATE_TIMEOUT] += "-1";

		for(int i = EFIT_STATE_START;i < EFIT_STATE_END; i++){
			StringUtils::replaceAll(str_state_h,fsm_template_token[i],replace_str[i]);
			StringUtils::replaceAll(str_state_c,fsm_template_token[i],replace_str[i]);
			StringUtils::replaceAll(str_state_func,fsm_template_token[i],replace_str[i]);

		}
	}

//	switch(i){
//	case 1:
//		break;
//	}
	return 0;
}

int Dot2Fsm::generalFSMCode_C(){

	if(createFSMDir()){
		return -1;
	}

	string filename = this->m_fsmName+"_fsm.h";
	fstream local_fsm_h(filename.c_str(),ios::out);

	filename = this->m_fsmName+"_fsm.c";
	fstream local_fsm_c(filename.c_str(),ios::out);

	string str_fsm_h = fsm_h;
	string str_fsm_c = fsm_c;

	if(!local_fsm_h.is_open() || !local_fsm_c.is_open()){
		printf("create %s_fsm.h file failed\n",this->m_fsmName.c_str());
		return -1;
	}

	for (vector<string>::iterator it = this->m_stateList.begin();
				it != this->m_stateList.end(); it++) {
		this->m_stateFileName.push_back(this->m_fsmName + "_" + *it);
	}

	map<int,string> replace_str;

	buildReplaceString(replace_str);

	for(int i = 0 ; i < EFTT_FSM_END ; i++){
		StringUtils::replaceAll(str_fsm_h,fsm_template_token[i],replace_str[i]);
		StringUtils::replaceAll(str_fsm_c,fsm_template_token[i],replace_str[i]);
	}

	local_fsm_h << str_fsm_h;
	local_fsm_c << str_fsm_c;
	local_fsm_h.close();
	local_fsm_c.close();

	this->generalStateCode_C();
	return 0;

	return 0;
}
