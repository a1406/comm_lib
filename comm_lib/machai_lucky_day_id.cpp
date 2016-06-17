#include "machai_lucky_day_id.h"
#include "time_helper.h"
#include <time.h>

unsigned int get_machai_lucky_day_id(unsigned int year, unsigned int month, unsigned int day, unsigned int maxKey)
{
	if (maxKey == 0)
		return (0);
	uint32_t now = time(NULL) - 5*3600;
	static uint32_t start_ts = 0;	
	if (0 == start_ts) {
		start_ts = time_helper::get_time(year, month, day);
	}

	uint32_t cur_day_start_ts = time_helper::get_day_hour(0, now);
	uint32_t num = ((cur_day_start_ts-start_ts)/86400)%maxKey + 1;	
	return num;	

}

