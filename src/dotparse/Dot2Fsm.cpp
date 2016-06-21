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
		return 0;
	}
	g = agread(fp, 0);
	if (!g) {
		printf("parse file failed");
		return 0;
	}

	if (!agisdirected(g)) {
		printf("dot file must directed graph\n");
		agclose(g);
		return 0;
	}

	this->m_fsmName = agnameof(g);
	for (np = agfstnode (g); np; np = agnxtnode (g, np)) {
		this->m_stateList.push_back(agnameof(np));
		if(this->m_stateTransfer.find(agnameof(np)) != this->m_stateTransfer.end()){
			printf("Node is exist\n");
			agclose(g);
			return 0;
		}
		this->m_stateTransfer[agnameof(np)] = vector<StateTransfer>();
		for (ep = agfstedge(g, np); ep; ep = agnxtedge(g, ep, np)){
			Agnode_t *hp = aghead(ep);
			Agnode_t *tp = agtail(ep);
			if(hp == np && hp != tp){
				//NOTE: skip other status transfer to me
				continue;
			}
			if(!agget(ep,label_str)){
				printf("Node %s: has a noname event\n",agnameof(np));
				agclose(g);
				return -1;
			}
			this->m_stateTransfer[agnameof(np)].push_back(StateTransfer(agget(ep,label_str),agnameof(hp)));
		}
	}
	agclose(g);
	return 0;
}

