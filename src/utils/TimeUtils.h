/*
 * TimeUtils.h
 *
 *  Created on: 2016年5月11日
 *      Author: light
 */

#ifndef SRC_UTILS_TIMEUTILS_H_
#define SRC_UTILS_TIMEUTILS_H_

namespace UTILS {

	class TimeUtils {
		public:
			TimeUtils();
			virtual ~TimeUtils();
		public:
			static const char* getLocalTime(char* time_str);
			static const char* getTimeOfDay(char* time_str);

	};

} /* namespace UTILS */

#endif /* SRC_UTILS_TIMEUTILS_H_ */
