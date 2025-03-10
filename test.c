#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<mysql.h>
typedef struct student//定义一个链表数据类型
{
	char* name;//姓名
	char* sex;//性别
	int testscore;//分数 
	double testrate;//正确率 
	struct student* next;//链表的下一个元素
}student;

int Pending(int s, int flag);//判断两个数是否相等
int Division(char b, double c);//判断被除数是否为零
int Srand1();//产生随机数1~9
int Srand2();//产生随机数1~9
int getint(int a,int c);//使输入的数字规范成整型 
double getfloat();//使输入的数字规范成字符型 
int StatisticScore(int c);//统计答题的分数
double StatisticRate(double c);//计算正确率

void init_db();//数据库初始化 
void sortmenu();//打印排序选择菜单
void menu();//打印选择菜单
void add(student* p);//增加一个学生
student* findend(student* head);//返回新链表的结尾元素
student* sort(int number, student* head, int(*com) (student* p));//排序函数
int compare_name(student* p);//比较相邻两个链表元素的姓名
int compare_sex(student* p);//比较相邻两个链表元素的性别
int compare_score1(student* p);//比较相邻两个链表元素的分数 
int compare_score2(student* p);//比较相邻两个链表元素的正确率 
void print(student* p);//打印数据表
void outlink(student* head);//输出为文件且将结果录入数据库 
void clearlist(student* head);//删除数据表

int one();//任务一
int two();//任务二 
int three(student* p);//任务三 
int four(student* p);//任务四 
int five(student* p);//任务五 
void test(student* p);//任务选项 

int rightCount = 0;//全局变量正确题目计数 

//数据库设置
MYSQL* conn; 
MYSQL_RES* res;
MYSQL_ROW row;
const char* server = "localhost";
const char* user = "root";
const char* password = "password";
const char* database = "student_db";

//函数功能：判断两个数是否相等
int Pending(int s, int flag)
{
    if(s == flag)
    {
        printf("Right\n");
        rightCount++;
    }
    else
        printf("Wrong\n");
    return 0;
}
//判断被除数是否为零
int Division(char b, double c)
{
    int temp;
    temp = 0;
    if(b == '/' && c == 0)
    {
        printf("被除数为零");
        temp = 1;
    }
    return temp;
}

int Srand1()//产生1~9随机数，且返回此数 
{
    int i;
    i= rand() % 9 + 1;
    return i;
}

int Srand2()//产生1~9随机数，且返回此数 
{
    int i;
    i = rand() % 9 + 1;
    return i;
}

int getint(int a,int c)//使输入的数字规范成整型 
{
	char s[100];
	int valid = 1, i, m, h;
	do
	{
		valid = 1;
        scanf("%s", s);
        h = strlen(s);
        for(i = 0; i < h; i++) 
		{
            if(!(s[i] >= '0' && s[i] <= '9')) 
			{
                valid = 0;
                break;
        	}
    	}
        if(!valid) 
		{
            printf("输入答案格式错误，请重新输入！\n");
            printf("%d*%d=", a, c);
        }
    }while(!valid);
    m = atoi(s);//字符串转化为整型 
    return m;
}

double getfloat()//使输入的数字规范成字符型 
{
    char s[100];
    int valid, i, h;
    double m;
    int count, sign;
    do 
	{
        valid = 1;
        count = 0;
        sign = 0;
        scanf("%99s", s);
        h = strlen(s);
        if(h == 0)//检查空字符串
		{
            valid = 0;
        }
        for(i = 0; i < h && valid; i++)
		{
            if(i == 0 && (s[i] == '+' || s[i] == '-'))//允许首字符为符号
			{
                sign = 1;
                continue;
            }
            
            if(s[i] == '.')//统计小数点数量
			{
                count++;
                if(count > 1)//禁止多个小数点
				{  
                    valid = 0;
                    break;
                }
            }
            else if(!(s[i] >= '0' && s[i] <= '9'))//检查是否为数字
			{
                valid = 0;
                break;
            }
        }
        if(valid)//检查无效格式（如 "-", ".", "123.", "-.5" 等）
		{
            if (sign && h == 1) valid = 0;                //只有符号（如 "-"）
            else if (count == 1 && h == 1) valid = 0;  //只有小数点（如 "."）
            else if (count == 1 && s[h-1] == '.') valid = 0; //结尾是小数点（如 "12."）
        }
        if(!valid)
		{
            printf("输入格式错误，请重新输入！\n");
        }
    }while(!valid);
    m = atof(s);//字符串转化为浮点数 
    return m;
}

int StatisticScore(int c)//统计并返回答题的分数
{
    int x;
    x = c * 10;
    return x;
}

double StatisticRate(double c)//计算并返回答题的正确率
{
    double y;
    y = c/10;
    return y;
}

void init_db()
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
	{
        fprintf(stderr, "数据库连接失败: %s\n", mysql_error(conn));
        exit(1);
    }
    printf("成功连接到MySQL数据库\n");
    //创建数据库和表
    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS student_db")) 
	{
        fprintf(stderr, "创建数据库失败: %s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn, "USE student_db")) 
	{
        fprintf(stderr, "选择数据库失败: %s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS students (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100), sex VARCHAR(10), score INT, rate FLOAT)")) 
	{
        fprintf(stderr, "创建表失败: %s\n", mysql_error(conn));
        exit(1);
    }
}

//打印排序选择菜单
void sortmenu()
{
	printf("请选择排序方式：\n");
	printf("1:姓名 ");
	printf("2:性别 ");
	printf("3:分数 ");
	printf("4:正确率 ");
	printf("在此输入：");
}

void menu()
{
	printf("请选择序号：\n");
	printf("1:增加一个学生\n");
	printf("2:排序\n");
	printf("3:打印数据表\n");
	printf("0:退出\n");
	printf("在此输入：");
}

//增加一个学生
void add(student* p)
{
	p->sex = (char*)malloc(10);
	p->name = (char*)malloc(100);
	printf("请输入姓名：\n");
	scanf("%s", p->name);
	printf("请输入性别：\n");
	scanf("%s", p->sex);
	while(!(strcasecmp(p->sex, "nan")==0||strcasecmp(p->sex, "nv")==0||strcasecmp(p->sex, "男")==0||strcasecmp(p->sex, "女")==0))
	{
			printf("性别输入错误，请重新输入！\n");
			printf("请输入性别：\n");
			scanf("%s", p->sex); 
	}
}

//返回新链表的结尾元素
student* findend(student* head)
{
	student* p = head;
	while(p!=NULL&&p->next!= NULL)//寻找新链表的结尾元素
	{
		p = p->next;
	}
	return p;//返回新链表的结尾元素
}

//按某关键字排序
student* sort(int number, student* head,int(* compare) (student* p))
//number 学生人数 * head链表头 int(* compare) (student* p) 排序的关键字，函数指针，指向比较两个相邻学生的函数
{
	student* p, * q, * temp;
	//* p是前面的指针（探路比较大小用） * q是后面的指针（存储p的前一个元素，链表元素交换用）* temp 中间商指针，交换元素用
	int i, j;//冒泡排序的两次循环参数
	for(i = 0; i < number - 1; i++)//冒泡排序的趟数
	{
		p = head;//p,q归位，指向链表头
		q = head;
		for(j = 0; j < number - 1 - i ; j++)//冒泡排序一趟的比较
		{   
			if(compare(p)<0)//调用compare指向的比较函数
			{
				//如果现在的元素的某项数据小于下一个元素的某项数据，则两个链表元素交换位置
				if(p == head)//如果现在的元素是链表头
				{
					head = p->next;//新链表头变为现在的元素的下一个元素
					q->next = p->next;
					temp = p->next->next;//中间变量暂存
					p->next->next = p;
					p->next = temp;
					p = head;
					q = head;
				}
				else
				{
				q->next = p->next;
				temp = p->next->next;
				p->next->next = p;
				p->next = temp;
				p = q->next;
				}
			}
			q = p;
			p = p->next;//p指向下一个元素
		}
	}
	return head;
}

//比较相邻两个链表元素的姓名
int compare_name(student* p)
{
	return -strcmp(p->name, p->next->name);
}

//比较相邻两个链表元素的性别
int compare_sex(student* p)
{
	return -strcmp(p->sex, p->next->sex);
}

//比较相邻两个链表元素的分数 
int compare_score1(student* p)
{
	return (p->testscore) - (p->next->testscore);
}

//比较相邻两个链表元素的正确率 
int compare_score2(student* p)
{
	return (p->testrate) - (p->next->testrate);
}

//打印数据表
void print(student* head)
{
	student* p = head;
	int count = 1;//排名序号
	printf("序号\t姓名\t性别\t分数\t正确率\n");
	while(p != NULL)
	{
		printf("%d\t%s\t%s\t%d\t%.2f\n",count,p->name,p->sex,p->testscore,p->testrate);
		p = p->next;//下一个学生
		count++;//序号加1
	}
	printf("\n");
}

void outlink(student* head) {
    FILE* w = fopen("output.txt", "w");
    if(w == NULL) 
	{
        printf("打开文件失败!\n");
        return;
    }
    init_db();//初始化数据库
    student* p = head;
    int count = 1;
    fprintf(w, "序号\t姓名\t性别\t分数\t正确率\n");
    while(p != NULL)
	{
		//输出为文件 
        fprintf(w, "%d\t%s\t%s\t%d\t%.2f\n", count, p->name, p->sex, p->testscore, p->testrate);
        //插入数据库
        char query[256];
        snprintf(query, 256, "INSERT INTO students (name, sex, score, rate) VALUES ('%s', '%s', %d, %.2f)",
                 p->name, p->sex, p->testscore, p->testrate);
        if(mysql_query(conn, query)) 
		{
            fprintf(stderr, "插入数据失败: %s\n", mysql_error(conn));
        }

        p = p->next;
        count++;
    }
    fclose(w);
    //关闭数据库连接
    mysql_close(conn);
    printf("数据已保存到数据库\n");
}

void clearlist(student* head)//删除数据表
{
	student* p, * q;//* p当前要删除的链表元素  * q暂存p的下一个元素  
	p = head;//从链表头开始删除
	while (p != NULL)
	{
		q = p->next;//暂存p的下一个元素
		free(p);//释放内存
		p = q;//p指向下一个元素
	}
}

int one()//任务一 
{
    int a, c, d, m;
    do
    {
        a = Srand1();
        c = Srand2();
        d = a * c;
        printf("%d*%d=", a, c);
		m = getint(a,c);
        Pending(d, m);
    }while(m != d);
        return 0;
}
 
int two()//任务二
{
    int flag,count,temp;
    flag = 0;
    count = 0;
    double a, c, s, e;
    int b;
    char p;
    p = '/';
 
    do
    {
        a = Srand1();
        b = rand() % 4;
        c = Srand2();
        switch(b)
        {
        case 0:
            temp = Division(p, c);
            if (temp == 1)
                break;
            printf("%.2f/%.2f=", a, c);
            s = a / c;
            s = round(s * 100) / 100;//将除法计算值规范为保留两位小数位 
            break;
        case 1:
            printf("%.2f*%.2f=", a, c);
            s = a * c;
            break;
        case 2:
            s = a + c;
            printf("%.2f+%.2f=", a, c);
            break;
        default:
            printf("%.2f-%.2f=", a, c);
            s = a - c;
        }
		e = getfloat();
        if(s == e)
		{
            flag++;
            printf("Right\n");
        }
        else
		{
            count++;
            if (count != 4)
			{
                printf("Wrong! Please try again.You can try a total of three times,you have %d times\n",4-count);
        	}
			else
			{
                printf("Wrong! You have tried three times! Test over!\n");
                break;
            }
        }
    }while(flag != 1);
    flag = count = 0;
    return 0;
}
 
int three(student* p)//任务三
{
    int a, c, d, m, flag;
    flag = 0;
    rightCount = 0;
    do
	{
        flag++;
        a = Srand1();
        c = Srand2();
        d = a * c;
        printf("%d*%d=", a, c);
        m = getint(a,c);
        Pending(d, m);
    }while(flag != 10);
    p->testscore = StatisticScore(rightCount);
    p->testrate = StatisticRate(rightCount);
    printf("得分为: %d ,正确率为: %.2f ", p->testscore, p->testrate);
    return 0;
}

int four(student* p)//任务四
{
    int b, flag, parameter , x, temp;
    double y;
    double a, c, s;
    flag = 0;
    rightCount = 0;
    double m;
    char q;
    do
	{
        flag++;
        a = Srand1();
        a = a * 1.0;
        c = Srand2();
        c = c * 1.0;
        b = rand() % 4;
        switch(b)
		{
        case 0:
            q = '/';
            temp = Division(q, c);
            if (temp == 1)
                break;
            printf("%.2f/%.2f=", a, c);
            s = a / c;
            s = round(s * 100) / 100;
            break;
        case 1:
            printf("%.2f*%.2f=", a, c);
            s = a * c;
            break;
        case 2:
            s = a + c;
            printf("%.2f+%.2f=", a, c);
            break;
        default:
            printf("%.2f-%.2f=", a, c);
            s = a - c;
        }
        m = getfloat();
        Pending(s, m);
    }while(flag != 10);
    p->testscore = StatisticScore(rightCount);
    p->testrate = StatisticRate(rightCount);
    printf("得分为: %d ,正确率为: %.2f ", p->testscore, p->testrate);
    printf("\n");
    return 0;
}

int five(student* p)//任务五 
{
    int b, flag, x, temp;
    double a, c;
    rightCount = 0;
    double y, s;
    do 
	{
		rightCount = 0;
        flag = 0;
        double m;
        char q;
        do 
		{
            a = Srand1();
            a = (double)a;
            c = Srand2();
            c = (double)c;
            b = rand() % 4;
            switch(b) 
			{
            case 0:
                q = '/';
                temp = Division(q, c);
                if (temp == 1)
                {
                    continue;
                }
                printf("%.2f/%.2f=", a, c);
                s = a / c;
                s = round(s * 100) / 100;
                break;
            case 1:
                printf("%.2f*%.2f=", a, c);
                s = a * c;
                break;
            case 2:
                s = a + c;
                printf("%.2f+%.2f=", a, c);
                break;
            default:
                printf("%.2f-%.2f=", a, c);
                s = a - c;
            }
            m = getfloat();
            flag++;
            Pending(s, m);
        }while(flag % 10 != 0);
        p->testscore = StatisticScore(rightCount);
        p->testrate = StatisticRate(rightCount);
        printf("%d %.2f", p->testscore, p->testrate);
        printf("\n");
    }while(p->testrate <= 0.75);
    return 0;
}

void test(student *p)
{
	int a,flag;
    flag = 0;
    printf("******************************************************************************\n");
    printf(" * 1. 任务 1：随机产生 1 - 10 之间正整数，出乘法问题，直到学生答对为止(此为试用，不统计总分与正确率)。\n");
    printf(" * 2. 任务 2：在任务 1 基础上，随机产生 1 道四则运算题，当学生答错时，最多给三次机会(此为试用，不统计总分与正确率)。 \n");
    printf(" * 3. 任务 3：在任务 1 基础上，连做 10 道乘法题，不给机会重做，统计总分、正确率。\n");
    printf(" * 4. 任务 4：在任务 3 基础上，随机产生 10 道四则运算题，不给机会重做，统计总分、正确率。 \n");
    printf(" * 5. 任务 5：在任务 4 基础上，若回答正确率低于 75 % ，则再做 10 道题，直到正确率高于 75 % 为止。\n");
    printf(" * 6. 退出 \n");
    printf("***************************************************************************** \n");
    while(scanf("%d", &a) != EOF)
	{
        if (a == 6) 
		{
            printf("程序已结束\n");
            break;
        }
         
        switch(a)
		{
        case 1:
            one();
            break;
        case 2:
            two();
            break;
        case 3:
            three(p);
            break;
        case 4:
            four(p);
            break;
        case 5:
            five(p);
            break;
        default:
            printf("命令错误，程序已结束\n");
            break;
        }
        if (flag == 1)
            break;
        printf("*********************************************************************************\n");
        printf(" * 1. 任务 1：随机产生 1 - 10 之间正整数，出乘法问题，直到学生答对为止。\n");
        printf(" * 2. 任务 2：在任务 1 基础上，当学生答错时，最多给三次机会。 \n");
        printf(" * 3. 任务 3：在任务 1 基础上，连做 10 道乘法题，不给机会重做，统计总分、正确率。\n");
        printf(" * 4. 任务 4：在任务 3 基础上，随机产生 10 道四则运算题，不给机会重做，统计总分、正确率。 *\n");
        printf(" * 5. 任务 5：在任务 4 基础上，若回答正确率低于 75 % ，则再做 10 道题，直到正确率高于 75 % 为止。\n");
        printf(" * 6. 退出 *\n");
        printf("********************************************************************************** \n");
    }
} 

int main()
{
	srand((unsigned)time(NULL));
	init_db();
	int choose = 0, sortchoose = 0,number = 0;//choose选择的序号 sortchoose选择的排序序号 number统计现有学生人数
	student* now,* pre;//*now当前链表元素的指针 *pre前一个链表元素的指针
	student* head = NULL;//链表头
	do
	{
		menu();//打印选择菜单
		scanf("%d", &choose);//读入选项
		switch(choose)
		{
			case 1://增加一个学生
				now = (student *)malloc(sizeof(student));//为当前链表元素分配地址
				if (head == NULL)
					head = now;//如果链表头为空，则当前链表元素为链表头
				else 
					pre->next = now;//把上个链表元素的next指向现在的链表元素的地址，即把当前元素接入链表
				now->next = NULL;//当前元素的下一个元素定为空
				add(now);//增加一个元素
				test(now);
				pre = now;//为下一个元素增加做准备
			    number++;//链表元素增加，学生人数增加
				break;
			case 2://排序
				sortmenu();//打印排序选择菜单
				scanf("%d", &sortchoose);//读入选项
				switch (sortchoose)
				{
					case 1:
						head = sort(number, head, compare_name);
						pre = findend(head);
						printf("\n按姓名排序:\n");
						print(head);
						break;
					case 2:
						head = sort(number, head, compare_sex);
						pre = findend(head);
						printf("\n按性别排序:\n");
						print(head);
						break;
					case 3:
						head=sort(number, head, compare_score1);
						pre = findend(head);
						printf("\n按分数排序:\n");
						print(head);
						break;
					case 4:
						head = sort(number, head, compare_score2);
						pre = findend(head);
						printf("\n按正确率排序:\n");
						print(head);
						break;
					default:printf("请重新选择\n\n");
				}
				break;
			case 3:
				print(head);//打印信息表
				outlink(head); 
				break;
			case 0: break;
			default:printf("请重新选择\n\n"); break;
		}
	}while(choose);//当choose为真不为零（退出为零）
	printf("\n正在删除数据表...\n");
	clearlist(head);//删除数据表
	printf("删除成功\n");
	printf("已退出程序\n");
	return 0;
}
