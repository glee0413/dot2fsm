/*
 * main.cpp
 *
 *  Created on: 2016年6月21日
 *      Author: light
 *      Mail: glee-0413@163.com
 */
#include <dotparse/Dot2Fsm.h>
int
main(int argc,char* argv[]){
	Dot2Fsm dot2fsm;
	dot2fsm.parseDotFile("./fsm.dot");
	return 0;
}


