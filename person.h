#pragma once
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person() 
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                time[i][j] ='1';
            }
        }
        times = 0;
    }
    Person(string name)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                time[i][j] ='1';
            }
        }
        this->name = name;
        times = 0;
    }
    ~Person(){}
    bool operator!=(Person person)
    {
        if (name != person.name)
        {
            return 1;
        }
        else
        {
            return 0;
        }

    }
    bool operator>(Person person)
    {
        return this->times > person.times;
    }
    bool operator<(Person person)
    {
        return this->times < person.times;
    }
    void operator=(const Person& person)
    {
        this->name = person.name;
        this->times = person.times;
        for (int i = 0; i < 2; i++)
        {
            for (int q = 0; q < 5; q++)
            {
                this->time[i][q] = person.time[i][q];
            }
        }
    }
    bool operator==(const Person& person)
    {
        if (this->name == person.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    string name; // 队员姓名
    char time[2][5]; // 对应10个任务时间点是否有时间
    int times; // 排班次数
};