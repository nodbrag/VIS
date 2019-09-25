/*
* date.h
*
*  Created on: 2016��6��7��
*      Author: havesnag
*/

#ifndef INCLUDE_EC_DATE_H_
#define INCLUDE_EC_DATE_H_

#include <time.h>
#include <string>

#if (defined _WIN32) || (defined WIN32) || (defined _WIN64) || (defined WIN64)
#define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#else
#include <sys/time.h>
#endif // PLATFORM_WINDOWS


#ifndef int64
#define int64 long long
#endif//int64

namespace ec
{

	class Time;
	class Date;
	class Duration;

	/**
	* @brief ��ʾʱ���
	*/
	class Duration
	{
	public:
		/** @brief ʱ�����ͣ������������������������½� */
		enum Period
		{
			/** @brief ΢�� 1/1000000�� */
			MicroSecond = 5,
			/** @brief ���� 1/1000�� */
			MilliSecond = 6,
			/** @brief �� */
			Second = 11,
			/** @brief �� 60�� */
			Minute = 12,
			/** @brief Сʱ 3600�� */
			Hour = 13,
			/** @brief �� 86400�� */
			Day = 14,
			/** @brief �� 604800�� */
			Week = 15,
			/** @brief �� �������໥ת������Ϊ1:4 */
			Month = 22,
			/** @brief �� */
			Year = 23,
		};

		Duration(int64 value = 1, Period period = Second);
		Duration(const Duration &duration);
		~Duration();

		/** @brief ��¡��ǰ���� */
		Duration clone() const;

		/** @brief ��ȡ��ֵ */
		inline int64 value() const
		{
			return _value;
		}

		/** @brief ��ȡ���� */
		inline Period period() const
		{
			return _period;
		}

		/** @brief ����ʱ��ε���ֵ������ */
		Duration & set(int64 value, Period period = Second);
		/** @brief ����ʱ��ε���ֵ */
		Duration & setValue(int64 value);
		/** @brief ����ʱ��ε����� */
		Duration & setPeriod(Period period);

		/** @brief �������𣬽��;��ȣ�����ת����ʽ������׼ȷ�ģ�������ת��ʱ��1:4���� */
		Duration & rase();
		/** @brief ���ͼ����������ȣ�����ת����ʽ������׼ȷ�ģ�������ת��ʱ��1:4���� */
		Duration & down();
		/** @brief ת����ָ�����͵�ʱ��� */
		Duration & as(Period period);
		/** @brief ��ȡֵת����ĳ�����ͺ��ֵ */
		int64 valueAs(Period period) const;

		Duration operator + (const Duration &other);
		Duration operator + (int64 value);
		Duration operator - (const Duration &other);
		Duration operator - (int64 value);
		Duration & operator += (const Duration &other);
		Duration & operator += (int64 value);
		Duration & operator -= (const Duration &other);
		Duration & operator -= (int64 value);
		bool operator > (const Duration & other);
		bool operator >= (const Duration & other);
		bool operator == (const Duration & other);
		bool operator != (const Duration & other);
		bool operator < (const Duration & other);
		bool operator <= (const Duration & other);
	private:
		int64 _value;
		Period _period;
	};

	/**
	* @brief ������
	* @details ��ȷ���룬Windows�½��ܱ�ʾ1970-01-01 00:00:00֮ǰ�����ڣ�Linux���ܴ����ơ�
	*/
	class Date
	{
	public:
		/** @brief ���ص�ǰϵͳʱ��������UTC+8��ʱ��Ϊ8 */
		static int localTimeZone();
		/** @brief ���ص�ǰϵͳʱ��ƫ�ƣ�����Ϊ��λ������UTC+8��ʱ��Ϊ-28800 */
		static time_t localTimeZoneOffset();
		/** @brief �ж��Ƿ������� */
		static bool isLeapYear(int year);
		/** @brief ĳ��ĳ��һ���ж����� */
		static int yearMonthDays(int year, int month);

	public:
		/** @brief �Ե�ǰʱ�乹�� */
		Date();
		/**
		* @brief ��ʱ���(��)����
		* @param stamp ʱ���
		* @param utc �Ƿ�ΪUTC��׼ʱ�䣬Ϊfalse�򰴱�������ʱ�乹��
		*/
		Date(time_t stamp, bool utc = false);
		/** @brief ��Time������ */
		Date(const Time &time);
		/** @brief ��Date������ */
		Date(const Date &other);

		/**
		* @brief ��ָ��ʱ�乹��
		* @note Windows����СΪ1970-01-01 00:00:00
		* @param year �꣬ȡֵ��Χ[1970, )
		* @param month �£�ȡֵ��Χ[1,12]
		* @param day �գ�ȡֵ��Χ[1,31]
		* @param hour ʱ��ȡֵ��Χ[0,23]��Ĭ��Ϊ0
		* @param minute �֣�ȡֵ��Χ[0,59]��Ĭ��Ϊ0
		* @param second �룬ȡֵ��Χ[0,60]��Ĭ��Ϊ0
		*/
		Date(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

		~Date();

		/** @brief ��¡��ǰ���� */
		Date clone() const;

		/** @brief ת��ΪTime���� */
		Time toTime() const;
		/** @brief ת��Ϊ�ַ�������ʽΪ1970-01-01 00:00:00 */
		std::string toString() const;

		/**
		* @brief ��ʽ��Ϊ�ַ���
		* @param fmt ��ʽ
		* @details
		*     %Y ��CCYY��ʾ���꣨�磺2004��
		*     %m �·� (01-12)
		*     %d ���еĵڼ���(01-31)
		*     %H Сʱ, 24Сʱ��ʽ (00-23)
		*     %M ����(00-59)
		*     %S ����(00-59)
		*     %X��׼ʱ���ַ������磺23:01:59��
		*     %% �ٷֺ�
		*
		* @return ����������󷵻ؿ��ַ���
		*/
		std::string format(const char * fmt = "%Y-%m-%d %H:%M:%S") const;

		/** @brief �꣬[1970, ) */
		inline int year() const
		{
			return _tm.tm_year + 1900;
		}

		/** @brief �£�[1,12] */
		inline int month() const
		{
			return _tm.tm_mon + 1;
		}

		/** @brief �գ�[1,31] */
		inline int day() const
		{
			return _tm.tm_mday;
		}

		/** @brief ʱ��[0,23] */
		inline int hour() const
		{
			return _tm.tm_hour;
		}

		/** @brief �֣�[0,59] */
		inline int minute() const
		{
			return _tm.tm_min;
		}

		/** @brief �룬[0,60] */
		inline int second() const
		{
			return _tm.tm_sec;
		}

		/** @brief ���ڣ�[1,7] */
		inline int week() const
		{
			return (_tm.tm_wday > 0) ? _tm.tm_wday : 7;
		}

		/** @brief �Ƿ���UTC��׼ʱ�� */
		inline bool isUTC() const
		{
			return _isUTC;
		}

		/** @brief ת��Ϊʱ��� @note ������ʱ�䣨ʱ����ת���������ڶ�8��(UTC+8)ʱ1970-01-01 00:00:00Ϊ-28800 */
		time_t stamp() const;
		/** @brief ת��ΪUTCʱ��� @note ����1970-01-01 00:00:00Ϊ0 */
		time_t utcStamp() const;
		/** @brief ʱ��������UTC+8��ʱ��Ϊ8 */
		int timeZone() const;
		/** @brief ʱ��ƫ�ƣ�����Ϊ��λ������UTC+8��ʱ��Ϊ-28800 */
		time_t timeZoneOffset() const;

		/** @brief ͳһ���������� @note �ȵ���������/��/�ո���Ч */
		Date & setDate(int year, int month, int day);
		/** @brief �����꣬[1970, ) @note ����ʹ��setDateͳһ���������� @see setDate */
		Date & setYear(int year);
		/** @brief �����£�[1,12] @note ����ʹ��setDateͳһ���������� @see setDate */
		Date & setMonth(int month);
		/** @brief �����գ�[1,31] @note ����ʹ��setDateͳһ���������� @see setDate*/
		Date & setDay(int day);
		/** @brief ����ʱ��[0,23] */
		Date & setHour(int hour);
		/** @brief ���÷֣�[0,59] */
		Date & setMinute(int minute);
		/** @brief �����룬[0,60] */
		Date & setSecond(int second);

		/**
		* @brief ����Ϊĳ��ʱ��Ŀ�ʼ
		* @param period ʱ�����ͣ�
		* @details
		*      ΪYearʱ����Ϊһ��Ŀ�ʼ��
		*      ΪMonthʱ����Ϊһ�µĿ�ʼ��
		*      ΪDayʱ����Ϊһ��Ŀ�ʼ��
		*      ΪHourʱ����ΪһСʱ�Ŀ�ʼ��
		*      ΪMinuteʱ����Ϊһ���ӵĿ�ʼ��
		*      ΪSecond/MilliSecond/MicroSecondʱ��Ч����
		*/
		Date & zeroSet(Duration::Period period);

		/** @brief ��/�� һ��ʱ�� */
		Date & add(int64 value, Duration::Period period);
		/** @brief ��/�� һ��ʱ�� */
		Date & add(const Duration & duration);
		/** @brief ��/�� �� */
		Date & addYear(int value);
		/** @brief ��/�� �� */
		Date & addMonth(int value);

		/**
		* @brief �Ƚ���ʱ��֮��Ĳ���
		* @param period ���ʱ������
		* @param other Ҫ�ȽϵĶ���
		* @details
		*     ΪYear��ʾ���������ݣ����Ǿ��Բ�ֵ��2015-01-01��2014-12-30���1��
		*     ΪMonth��ʾ�������˵�������Ǿ��Բ�ֵ��2015-01-01��2014-12-30���1��
		*     ΪDay��ʾ����������������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1��
		*     ΪHour��ʾ�������Сʱ�������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1Сʱ
		*     ΪMinute��ʾ�����������������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1����
		*     ΪSecond��ʾ�����������
		*     ΪMilliSecond��ʾ��������������Date�ľ���Ϊ�룬����ֻ�ǽ��������*1000
		*     ΪMicroSecond��ʾ�������΢������Date�ľ���Ϊ�룬����ֻ�ǽ��������*1000000
		* @return ����this - other����Ӧ��ֵ
		*/
		int64 diff(const Date & other, Duration::Period period = Duration::Second);

		/** @brief ��ȡһ���е��죬[1,366] */
		int getYearDay() const;
		/** @brief ����1970-01-01 00:00:00������ */
		int getUTCFullMonths() const;
		/** @brief ����1970-01-01 00:00:00������ */
		int getUTCFullYears() const;

		/** @brief �Ƿ������� */
		bool isLeapYear() const;
		/** @brief �Ƿ���һ�µ����һ�� */
		bool isLastDayOfMonth() const;

		Date operator + (const Duration & duration);
		Date operator - (const Duration & duration);
		Duration operator - (const Date & other);
		Date & operator += (const Duration & duration);
		Date & operator -= (const Duration & duration);
		bool operator < (const Date & other);
		bool operator = (const Date & other);

	protected:
		void _set(time_t stamp);
		void _update();

	private:
		struct tm _tm;
		bool _isUTC;
	};

	/**
	* @brief ʱ����
	* @details ��ȷ��΢�룬����Date�໥ת����ת��ΪDate����ʧ���ȵ���
	* @see Date
	*/
	class Time
	{
	public:
		Time();
		/** @brief ��ʱ������� */
		Time(time_t stamp);
		/** @brief ��Date������ */
		Time(const Date &date);
		/** @brief ��Time������ */
		Time(const Time &time);
		~Time();

		/** @brief ��¡��ǰ���� */
		Time clone() const;

		/** @brief ת���ɱ�������ʱ���Date���� */
		Date toDate() const;
		/** @brief ת����UTC��׼ʱ���Date���� */
		Date utcDate() const;

		/** @brief ��ȡ��������ͬ��ʱ��� */
		inline time_t seconds() const
		{
			return _tv.tv_sec;
		}
		inline time_t tv_usec() const
		{
			return _tv.tv_usec;
		}
		/** @brief ��ȡ΢����, [0,1000000) @details ΢�벿��С��һ�� */
		inline long microSeconds() const
		{
			return _tv.tv_sec;
		}

		/** @brief ��ȡ����ʱ��� */
		inline int64 milliStamp() const
		{
			return _tv.tv_sec * 1000 + _tv.tv_usec / 1000;
		}

		/** @brief ��ȡ΢��ʱ��� */
		inline int64 microStamp() const
		{
			return _tv.tv_sec * 1000000 + _tv.tv_usec;
		}

		/** @brief ��ȡʱ��� */
		inline time_t stamp() const
		{
			return _tv.tv_sec;
		}

		/** @brief ��ȡUTCʱ��� */
		time_t utcStamp() const;

		/** @brief ����������΢���� */
		Time & set(time_t seconds, long microSeconds = 0);
		/** @brief ��ȡ΢����, [0,1000) */
		Time & setSeconds(time_t seconds);
		/** @brief ��ȡ΢����, [0,1000000) */
		Time & setMicroSeconds(long microSeconds);

		/**
		* @brief ����Ϊĳ��ʱ��Ŀ�ʼ
		* @param period ʱ�����ͣ�
		* @details
		*     ΪYearʱ����Ϊһ��Ŀ�ʼ��
		*	   ΪMonthʱ����Ϊһ�µĿ�ʼ��
		*	   ΪDayʱ����Ϊһ��Ŀ�ʼ��
		*	   ΪHourʱ����ΪһСʱ�Ŀ�ʼ��
		*	   ΪMinuteʱ����Ϊһ���ӵĿ�ʼ��
		*	   ΪSecondʱ����Ϊһ��Ŀ�ʼ��
		*	   ΪMilliSecondʱ����Ϊһ����Ŀ�ʼ��
		*	   ΪMicroSecondʱ����Ϊһ΢��Ŀ�ʼ
		*/
		Time & zeroSet(Duration::Period period);

		/** @brief ��/�� һ��ʱ�� */
		Time & add(int64 value, Duration::Period period);
		/** @brief ��/�� һ��ʱ�� */
		Time & add(const Duration & duration);
		/** @brief ��/�� �� */
		Time & addWeek(int value);
		/** @brief ��/�� �� */
		Time & addDay(int value);
		/** @brief ��/�� ʱ */
		Time & addHour(int value);
		/** @brief ��/�� �� */
		Time & addMinute(int value);
		/** @brief ��/�� �� */
		Time & addSecond(int value);
		/** @brief ��/�� ���� */
		Time & addMilliSecond(int value);
		/** @brief ��/�� ΢�� */
		Time & addMicroSecond(int value);

		/**
		* @brief �Ƚ���ʱ��֮��Ĳ���
		* @param period ���ʱ������
		* @param other Ҫ�ȽϵĶ���
		* @details
		*     ΪYear��ʾ���������ݣ����Ǿ��Բ�ֵ��2015-01-01��2014-12-30���1��
		*     ΪMonth��ʾ�������˵�������Ǿ��Բ�ֵ��2015-01-01��2014-12-30���1��
		*     ΪDay��ʾ����������������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1��
		*     ΪHour��ʾ�������Сʱ�������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1Сʱ
		*     ΪMinute��ʾ�����������������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1����
		*     ΪSecond��ʾ�����������
		*     ΪMilliSecond��ʾ������������
		*     ΪMicroSecond��ʾ�������΢����
		* @return ����this - other����Ӧ��ֵ
		*/
		int64 diff(const Time & other, Duration::Period period = Duration::Second);

		/** @brief ����1970-01-01 00:00:00��΢���� */
		int64 getUTCFullMicroSeconds() const;
		/** @brief ����1970-01-01 00:00:00�ĺ����� */
		int64 getUTCFullMilliSeconds() const;
		/** @brief ����1970-01-01 00:00:00������ @note ��getUTCStamp()������ͬ @see getUTCStamp */
		time_t getUTCFullSeconds() const;
		/** @brief ����1970-01-01 00:00:00�ķ��� */
		int getUTCFullMinutes() const;
		/** @brief ����1970-01-01 00:00:00��Сʱ */
		int getUTCFullHours() const;
		/** @brief ����1970-01-01 00:00:00������ */
		int getUTCFullDays() const;
		/** @brief ����1970-01-01 00:00:00������ @note ��0��ʼ��1970-01-01 00:00:00Ϊ��0������4 */
		int getUTCFullWeeks() const;

		Time operator + (const Duration & duration);
		Time operator - (const Duration & duration);
		Duration operator - (const Time & other);
		Time & operator += (const Duration & duration);
		Time & operator -= (const Duration & duration);
		bool operator < (const Time & other);
		bool operator = (const Time & other);

	private:
		struct timeval _tv;
	};

} /* namespace ec */

#endif /* INCLUDE_EC_DATE_H_ */