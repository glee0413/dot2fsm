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
		StateTransfer(){

		}
	private:
		string m_eventName;
		string m_nextState;
	private:

	};
public:
	int parseDotFile(const char* dotFile);
private:
	int m_stateCount;
	string m_fsmName;
	vector<string> m_stateList;
	map<string,vector<StateTransfer> > m_stateTransfer;
};

#endif /* SRC_DOTPARSE_DOT2FSM_H_ */
