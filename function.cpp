#include<fstream>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<ctime>
#include "person.h"
#include "function.h"
#include"timescount.h"

//读文件操作
void readFile(vector<Person>& person)
{
    ifstream ifs("MemberInformation.txt");
    if (!ifs.is_open())
    {
        cout << "队员信息文件打开失败！" << endl;
        system("pause");
        exit(0);
    }
    Person tempPerson;
    string str;
    char c;//保存数字0/1
    while (ifs >> str)//ifstream直接读到空格会返回0
    {
        tempPerson.name = str;
        for (int q = 0; q < 2; q++)
        {
            for (int p = 0; p < 5; p++)
            {
                ifs >> c;//ifstream读取默认跳过空格与换行
                tempPerson.time[q][p] = c;
            }
        }
        person.push_back(tempPerson);
    }
    ifs.close();
}
void Show(const Person  worksheet[][5][3], const vector<Person> person)
{
    cout << endl << "全屏小黑窗以保证表格格式!" << endl << endl;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                switch (worksheet[x][y][z].name.size())//对齐工作，UTF-8中一个汉字占三字节即三个字符位(如果是GBK可能是两个字符位)（应该没有五个字的名字吧，如果有就抱歉了）
                {
                case 3://1字姓名
                    cout << left << setw(10) << worksheet[x][y][z].name;
                    break;
                case 6://2字姓名
                    cout << left << setw(11) << worksheet[x][y][z].name;
                    break;
                case 9://3字姓名
                    cout << left << setw(12) << worksheet[x][y][z].name;
                    break;
                case 12://4字姓名
                    cout << left << setw(13) << worksheet[x][y][z].name;
                    break;
                default://其他
                    cout << left << worksheet[x][y][z].name << ' ';
                    break;
                }
                
            }
            cout << '|';
        }
        cout << endl;
    }
    cout << endl << "所有队员执行任务次数：" << endl;
    for (int i = 0, q = 0; i < person.size(); i++)
    {
        switch (person[i].name.size())//对齐工作，UTF-8中一个汉字占三字节即三个字符位（应该没有五个字的名字吧，如果有就抱歉了）
        {
        case 3://1字姓名
            cout << right << setw(10) << person[i].name << ':' << person[i].times;
            break;
        case 6://2字姓名
            cout << right << setw(11) << person[i].name << ':' << person[i].times;
            break;
        case 9://3字姓名
            cout << right << setw(12) << person[i].name << ':' << person[i].times;
            break;
        case 12://4字姓名
            cout << right << setw(13) << person[i].name << ':' << person[i].times;
            break;
        default://其他
            cout << right << person[i].name << ':' << person[i].times << ' ';
            break;
        }
        if ((++q) == 7)
        {
            q = 0;
            cout << endl;
        }
    }
    cout << endl;
}

void WorksheetAll(Person  worksheet[][5][3])
{
    Person temp[4][5][3];//空数组，用于重置worksheet
    vector<TimesCount> improve;//辅助变量，用于优化任务分配次数
    srand((unsigned int)time(NULL));
    cout << "正在生成工作表,请耐心等待！（最晚为20s）" << endl;
    time_t tStart = time(NULL);//辅助变量，记录程序运行时间，用于终止死循环情况
    bool timeOut = 0;//辅助变量，判断程序是否超时，用于终止死循环情况
    bool restart = 0;//辅助变量，避免重跑时程序遇到极端情况卡死无法出结果
    bool onlyOnce = 0;
    TimesCount tempCount;
    vector<Person> tempPerson;//临时变量，储存队员信息 
    vector<Person> restartPerson;//临时变量，储存队员执勤次数
RESTART:
    vector<Person> person;
    readFile(person);  //读取队员信息
    for (int i = 0; i < 4; i++)//重置worksheet
    {
        for (int q = 0; q < 5; q++)
        {
            for (int p = 0; p < 3; p++)
            {
                worksheet[i][q][p] = temp[i][q][p];
            }
        }
    }
    if (!onlyOnce)
    {
        onlyOnce = 1;
        for (int i = 0; i < 2; i++)//录入辅助变量improve信息
        {
            for (int q = 0; q < 5; q++) {
                tempCount.sign = i * 5 + q + 1;
                tempCount.times = 0;
                for (int p = 0; p < person.size(); p++)
                {
                    tempCount.times += person[p].time[i][q];
                }
                improve.push_back(tempCount);
            }
        }
        sort(improve.begin(), improve.end(), TimesCount::cmp);//各时间段可执行次数升序排列
    }
    for (int i = 0; i < improve.size(); i++)//按照各时间段可执行次数从少到多的顺序排表
    {
        for (int z = 0; z < 3; z++)//某个时间段的南鉴湖任务
        {
            tempPerson = person;
        NJ:
            if ((time(NULL)-tStart)>20) //判断程序是否运行超过20秒，超过则退出程序
            {
                timeOut = 1;
                if(restart)//判断超时前是否存在已有的工作表，若有，直接输出
                {
                    goto restart;
                }
                goto OUT;
            }
            int test = rand() % tempPerson.size(); // 随机选取全部队员中的一人
            if (tempPerson[test].time[(improve[i].sign-1)/5][(improve[i].sign - 1) % 5] == '1' && tempPerson[test].times - min_element(tempPerson.begin(), tempPerson.end())->times < 1) //第一次筛选：南鉴湖任务；
            {
                switch (z)
                {
                case 1:
                    if (worksheet[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5][0] != tempPerson[test])
                    {
                        worksheet[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5][z] = tempPerson[test];
                        find(person.begin(), person.end(), tempPerson[test])->times++;
                    }
                    else
                    {
                        if (tempPerson.size() != 1)
                        {
                            tempPerson.erase(tempPerson.begin() + test);
                        }
                        else
                        {
                            goto RESTART;
                        }
                        
                        goto NJ;
                    }
                    break;
                case 2:
                    if (worksheet[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5][0] != tempPerson[test])
                    {
                        worksheet[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5][z] = tempPerson[test];
                        find(person.begin(), person.end(), tempPerson[test])->times++;
                    }
                    else
                    {
                        if (tempPerson.size() != 1)
                        {
                            tempPerson.erase(tempPerson.begin() + test);
                        }
                        else
                        {
                            goto RESTART;
                        }
                        goto NJ;
                    }
                    break;
                default:
                    worksheet[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5][z] = tempPerson[test];
                    find(person.begin(), person.end(), tempPerson[test])->times++;
                    break;
                }
                find(person.begin(), person.end(), tempPerson[test])->time[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5] = '0';//做出标记，避免东西院排表时与同一时间段的南鉴湖任务冲突
            }
            else
            {
                if (tempPerson.size() != 1)
                {
                    tempPerson.erase(tempPerson.begin() + test);
                }
                else
                {
                    goto RESTART;
                }
                goto NJ;
            }
        }

        for (int z = 0; z < 3; z++)//某个时间段的东西院任务
        {
            tempPerson = person;
        DX:
            if ((time(NULL) - tStart) > 20) //判断程序是否运行超过20秒，超过则退出程序
            {
                timeOut = 1;
                if (restart)//判断超时前是否存在已有的工作表，若有，直接输出
                {
                    goto restart;
                }
                goto OUT;
            }
            int test = rand() % tempPerson.size(); // 随机选取队员中的一人
            if (tempPerson[test].time[(improve[i].sign - 1) / 5][(improve[i].sign - 1) % 5] == '1' && tempPerson[test].times - min_element(tempPerson.begin(), tempPerson.end())->times < 2) //第二次筛选：东西院任务（筛选标准：不与同一时间段的南鉴湖任务冲突）
            {
                switch (z)
                {
                case 1:
                    if (worksheet[(improve[i].sign - 1) / 5 + 2][(improve[i].sign - 1) % 5][0] != tempPerson[test])
                    {
                        worksheet[(improve[i].sign - 1) / 5 + 2][(improve[i].sign - 1) % 5][z] = tempPerson[test];
                        find(person.begin(), person.end(), tempPerson[test])->times++;
                    }
                    else
                    {
                        if (tempPerson.size() != 1)
                        {
                            tempPerson.erase(tempPerson.begin() + test);
                        }
                        else
                        {
                            goto RESTART;
                        }
                        goto DX;
                    }
                    break;
                case 2:
                    if (worksheet[(improve[i].sign - 1) / 5 + 2][(improve[i].sign - 1) % 5][0] != tempPerson[test] && worksheet[(improve[i].sign - 1) / 5 + 2][(improve[i].sign - 1) % 5][1] != tempPerson[test])
                    {
                        worksheet[(improve[i].sign - 1) / 5 + 2][(improve[i].sign - 1) % 5][z] = tempPerson[test];
                        find(person.begin(), person.end(), tempPerson[test])->times++;
                    }
                    else
                    {
                        if (tempPerson.size() != 1)
                        {
                            tempPerson.erase(tempPerson.begin() + test);
                        }
                        else
                        {
                            goto RESTART;
                        }
                        goto DX;
                    }
                    break;
                default:
                    worksheet[(improve[i].sign - 1) / 5 + 2][(improve[i].sign - 1) % 5][z] = tempPerson[test];
                    find(person.begin(), person.end(),tempPerson[test])->times++;
                    break;

                }
            }
            else
            {
                if (tempPerson.size() != 1)
                {
                    tempPerson.erase(tempPerson.begin() + test);
                }
                else
                {
                    goto RESTART;
                }
                goto DX;
            }
        }
    }
    
    if ((max_element(person.begin(), person.end())->times - min_element(person.begin(), person.end())->times) > 1)//判断执勤次数最大值与最小值，用以平均任务次数(原理：max - min > 1则重新运行程序)
    {
        if (!restart)
        {
            restart = 1;
            restartPerson = person;
            for (int i = 0; i < 4; i++)//记录worksheet结果，避免重跑无法得到结果
            {
                for (int q = 0; q < 5; q++)
                {
                    for (int p = 0; p < 3; p++)
                    {
                        temp[i][q][p] = worksheet[i][q][p];
                    }
                }
            }
        }       
        if ((time(NULL) - tStart) > 15)//25秒内未能平均任务次数，输出次解
        {
            restart:
            Show(temp, restartPerson);
            cout << "未能平均任务次数，请人工调整！" << endl << endl;
            return;
        }
        goto RESTART;
    }
    else
    {
        Show(worksheet, person);//若找到更优解则输出更优解
    }

    if (timeOut)//超时30s且无结果才会进入
    {
        OUT:
        cout << "队员可升降旗情况极端，无法提供结果！" << endl;
    }

    system("pause");
}