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

enum FSM_LANGUAGE{
	FL_C_LANGUAGE = 0,
	FL_CPP_LANGUAGE,
	FL_MAX
};

int
main(int argc,char* argv[]){
	Dot2Fsm dot2fsm;
	int opt;
	int language = 0;
	char dot_file[56] = {0};



	while ((opt = getopt(argc, argv, "d:t:")) != -1) {
		switch (opt) {
		case 'd':
			strncpy(dot_file,optarg,sizeof(dot_file) - 1);
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
		}
	}

	dot2fsm.parseDotFile(dot_file);

	return 0;
}


