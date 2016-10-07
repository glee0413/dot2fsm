/*
 * main.cpp
 *
 *  Created on: 2016年6月21日
 *      Author: light
 *      Mail: glee-0413@163.com
 */
#include <dotparse/Dot2Fsm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils/macro.h>

int
main(int argc,char* argv[]){
	Dot2Fsm dot2fsm;
	int opt;
	int language = 0;
	string dot_file = "fsm.dot";
	string prefix;


	while ((opt = getopt(argc, argv, "d:t:p:")) != -1) {
		switch (opt) {
		case 'd':
			//strncpy(dot_file,optarg,sizeof(dot_file) - 1);
			dot_file = optarg;
			break;
		case 't':
			if(strcmp(optarg,"c")){
				language = FL_C_LANGUAGE;
			}else if(strcmp(optarg,"c++")){
				language = FL_CPP_LANGUAGE;
			}else{
				printf("support language: c,c++");
				return 0;
			}
			break;
		case 'p':
			prefix = optarg;
		default:
			break;
		}
	}

	if(dot2fsm.parseDotFile(dot_file.c_str()) == 0){
		dot2fsm.generalFSMCode(language);
	}


	return 0;
}


