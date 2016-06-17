#ifndef _TIME_HELPER_H__
#define _TIME_HELPER_H__

#include <time.h>
#include <string>
#include <stdint.h>

class time_helper
{
public:
	static void set_cached_time(time_t t);
	static time_t get_cached_time();	
	static std::string				print_time_string(time_t t,bool is_print = false);
	static int				get_current_time(timeval *t);
//	static unsigned                get_local_time(void);
	static unsigned				calc_time(time_t start_time,int hour,int min,int sec);
	static bool					get_duration_time(time_t time_start, time_t time_end, int& hour, int& min, int& sec);

//	static tm						localTime(time_t now);
//	static tm						localTime(void);
	static unsigned				get_day_hour(unsigned hour, time_t now = 0);	// ��ȡnow����Ӧ��������+hour��Ӧ��ʱ���
	static unsigned				get_day_timestamp(unsigned hour, unsigned minute, unsigned second, time_t now=0);
	static unsigned				get_cur_hour(time_t now = 0); /// result: 0~23
	static unsigned				thisDay(int offset = 0, time_t now = 0); //next offset time!	
	static unsigned				nextDay(int offset = 0, time_t now = 0); //next offset time!
	static unsigned				get_cur_day_by_month(time_t now=0);  /// ��ȡ��ǰʱ���Ǳ��µĵڼ���
	static bool                 is_same_month_by_year(time_t t1, time_t t2); /// �ж���ʱ����Ƿ�Ϊͬһ���е�ͬһ��
	static unsigned				nextHalfHour(time_t now = 0);
	static unsigned				nextHour(time_t now = 0);
	static unsigned				nextWeek(int offset = 0, time_t now = 0);
	static unsigned				next2Minute(time_t now = 0);
	static unsigned             getWeek(time_t now=0);
	static unsigned				get_timestamp_by_day(int hour, int minute, time_t now = 0);
	

	static void					showTime(time_t t = 0);
	static void					showTime(tm t);

//		int						timeZone(void);
	static int                     timezone_offset(void);
	static bool					is_same_day(unsigned int t1, unsigned int t2=0);
		//microsecond 
	static void					sleep(int micro_secs);

	static uint32_t             get_time(int year, int month, int day);
	static unsigned get_cur_month_by_year(time_t now);
	static int      get_date_by_time(int32_t* year, int32_t* month, int32_t* day, time_t now=0);  /// ����ʱ���������/��/��
	static bool		is_same_hour(time_t t1, time_t t2);
};

#endif
