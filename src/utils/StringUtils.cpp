/*
 * StringUtils.cpp
 *
 *  Created on: 2016年6月26日
 *      Author: light
 */

#include "StringUtils.h"
#include "stdio.h"
#include <cctype>
#include <algorithm>

namespace UTILS {

StringUtils::StringUtils() {
	// TODO Auto-generated constructor stub

}

StringUtils::~StringUtils() {
	// TODO Auto-generated destructor stub
}

void StringUtils::replaceAll( string& source, const string& from, const string& to){
	size_t start_pos = 0;
	while ((start_pos = source.find(from, start_pos)) != std::string::npos) {
		source.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}

void StringUtils::toUpper(string& source){
	transform(source.begin(), source.end(), source.begin(), ::toupper);
}

void StringUtils::toLower(string& source){
	transform(source.begin(), source.end(), source.begin(), ::tolower);
}

} /* namespace UTILS */


