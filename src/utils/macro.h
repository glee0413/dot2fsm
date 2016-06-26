/*
 * macro.h
 *
 *  Created on: 2016年5月11日
 *      Author: light
 */

#ifndef SRC_UTILS_MACRO_H_
#define SRC_UTILS_MACRO_H_


#define    DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);                \
    TypeName& operator=(const TypeName&)

enum FSM_LANGUAGE{
	FL_C_LANGUAGE = 0,
	FL_CPP_LANGUAGE,
	FL_MAX
};

#endif /* SRC_UTILS_MACRO_H_ */
