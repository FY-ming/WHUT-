#pragma once
class TimesCount//用于优化任务分配次数
{
public:
	int sign;//标记队员10个时间段
	int times;//全部队员总计可执勤次数
	TimesCount()
	{
		sign = 0;
		times = 0;
	}
	static bool cmp(const TimesCount& one, const TimesCount& other)
	{
		return one.times < other.times;
	}
};