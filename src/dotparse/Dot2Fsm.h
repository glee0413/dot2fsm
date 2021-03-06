/*
 * dotparse.h
 *
 *  Created on: 2016年6月21日
 *      Author: light
 *      Mail: glee-0413@163.com
 */

#ifndef SRC_DOTPARSE_DOT2FSM_H_
#define SRC_DOTPARSE_DOT2FSM_H_
#include <string>
#include <vector>
#include <map>
using namespace std;

class Dot2Fsm {
public:
	Dot2Fsm();
	virtual ~Dot2Fsm();
public:
	struct StateTransfer {
	public:
		StateTransfer(const char* event, const char* nextState) {
			this->m_eventName = event;
			this->m_nextState = nextState;
		}
		StateTransfer(const string& event, const string& nextState) {
			this->m_eventName = event;
			this->m_nextState = nextState;
		}
		StateTransfer(){}
		string EventName(){return this->m_eventName;}
		string NextState(){return this->m_nextState;}
	private:
		string m_eventName;
		string m_nextState;
	private:

	};
public:
	enum DotFsmEnumType{
		DFET_EVENT = 0,
		DFET_STATE
	};
public:
	int parseDotFile(const char* dotFile);
	int generalFSMCode(int language);
private:
	int generalFSMCode_C();
	int generalStateCode_C(map<int,string>& replace_str);
	int createFSMDir();
	int buildReplaceString(map<int,string>& replace_str);
	string GetFSMEnumName(string read_name,DotFsmEnumType type);
private:
	int m_stateCount;
	string m_fsmName;
	vector<string> m_stateList;
	vector<string> m_eventList;
	map<string,vector<StateTransfer> > m_stateTransfer;
	vector<string> m_stateFileName;
};

#endif /* SRC_DOTPARSE_DOT2FSM_H_ */
