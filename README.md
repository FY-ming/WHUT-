# 武汉理工大学国旗仪仗队排班系统文件说明

## 作者的废话

~~由于技术力有限，这个程序并没有多么优秀，只能针对常规情况进行排表。~~

## 使用说明

文件打包后请找到同文件夹下"MemberInformation"文件编辑队员的可执勤时间段
例：
张三
1 1 1 1 1
1 1 1 1 0
李四
0 1 0 1 0
1 1 1 1 1

### 请务必按照这个格式填写，1表示可执勤，0表示不可执勤，十个位置上方对应上午，下方对应下午，五段时间分别对应周一到周五

编写结束记得保存
然后启动exe文件就可以出表了。
如果有执勤次数分配过于不平均或者说队员执勤情况极端没有给出表格，请再执行几次exe文件或人工调整。（技术有限，对不起！:sob:真的改了很久了）

表格结果依次为：
南鉴湖升旗
南鉴湖降旗
东西院升旗
东西院降旗

### 关于使用的保姆教程

因为见识到了可爱的队友不知道怎么使用这个文件，所以就有了这一段文字说明 🤔

第一！查找需要的文件"MemberInformation.txt"！如果你记得自己将该程序安装在哪里了，那直接去找安装地址即可。
如果！你不知道，那么，右键排班系统快捷方式（就是那个有whut校徽的图标），选择"属性"，查看文件的起始位置（或者选择"打开文件所在位置"），将其复制并在你的电脑资源管理中心查找（查找时注意不需要双引号）。然后，能找到安装地址啦！
如果查看快捷方式后跳转的地址是桌面(即desk)，那么请在desk的界面再右键排班系统快捷方式，选择"属性"，查看文件的起始位置。理论上这次就是安装地址。
要还不行，建议使用搜索或者重新安装，装软件要记住安装地址哦。

第二！关于最后的出表结果。可以直接复制粘贴到Excel中，然后选定有文字的四行单元格，在工具区选择"数据"-"分列"，选择用分隔符分列，分隔符选择"|"（可能没有，要自定义）；然后就可以直接出最终表嘞！

注：卸载请前往：控制面板-卸载程序。

程序作者：F-MMMing
