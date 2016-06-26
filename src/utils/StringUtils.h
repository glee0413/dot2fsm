/*
 * StringUtils.h
 *
 *  Created on: 2016年6月26日
 *      Author: light
 */

#ifndef SRC_UTILS_STRINGUTILS_H_
#define SRC_UTILS_STRINGUTILS_H_
#include "macro.h"
#include <string>
using namespace std;

namespace UTILS {

class StringUtils {
public:
	enum ReplaceMode{
		ERM_NORMAL = 0,
		ERM_FILL, ///expand tostring the same length to the fromstring
	};
public:
	StringUtils();
	virtual ~StringUtils();

public:
	static void replaceAll( string& source, const string& from, const string& to);
	static void toUpper(string& source);
	static void toLower(string& source);
private:
		DISALLOW_COPY_AND_ASSIGN(StringUtils);
};

} /* namespace UTILS */

#endif /* SRC_UTILS_STRINGUTILS_H_ */
