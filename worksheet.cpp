#include <string>
#include "person.h"
#include "function.h"

Person worksheet[4][5][3]; // 工作表变量：用于记录最后的排班结果 （4：两升两降  5：一周五天  3：一次三人）


int main()
{    
    cout << "使用前请先阅读文件夹内README文件！" << endl
        << "若已阅读，请输入0，否则先去看一下吧~" << endl;
    int read;
    cin >> read;
    if (!read)
    {
        WorksheetAll(worksheet);
    }
    cout << "程序由万明制作，任何问题，他背锅:)" << endl;
    return 0;
}