#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<mysql.h>
typedef struct student//����һ��������������
{
	char* name;//����
	char* sex;//�Ա�
	int testscore;//���� 
	double testrate;//��ȷ�� 
	struct student* next;//�������һ��Ԫ��
}student;

int Pending(int s, int flag);//�ж��������Ƿ����
int Division(char b, double c);//�жϱ������Ƿ�Ϊ��
int Srand1();//���������1~9
int Srand2();//���������1~9
int getint(int a,int c);//ʹ��������ֹ淶������ 
double getfloat();//ʹ��������ֹ淶���ַ��� 
int StatisticScore(int c);//ͳ�ƴ���ķ���
double StatisticRate(double c);//������ȷ��

void init_db();//���ݿ��ʼ�� 
void sortmenu();//��ӡ����ѡ��˵�
void menu();//��ӡѡ��˵�
void add(student* p);//����һ��ѧ��
student* findend(student* head);//����������Ľ�βԪ��
student* sort(int number, student* head, int(*com) (student* p));//������
int compare_name(student* p);//�Ƚ�������������Ԫ�ص�����
int compare_sex(student* p);//�Ƚ�������������Ԫ�ص��Ա�
int compare_score1(student* p);//�Ƚ�������������Ԫ�صķ��� 
int compare_score2(student* p);//�Ƚ�������������Ԫ�ص���ȷ�� 
void print(student* p);//��ӡ���ݱ�
void outlink(student* head);//���Ϊ�ļ��ҽ����¼�����ݿ� 
void clearlist(student* head);//ɾ�����ݱ�

int one();//����һ
int two();//����� 
int three(student* p);//������ 
int four(student* p);//������ 
int five(student* p);//������ 
void test(student* p);//����ѡ�� 

int rightCount = 0;//ȫ�ֱ�����ȷ��Ŀ���� 

//���ݿ�����
MYSQL* conn; 
MYSQL_RES* res;
MYSQL_ROW row;
const char* server = "localhost";
const char* user = "root";
const char* password = "password";
const char* database = "student_db";

//�������ܣ��ж��������Ƿ����
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
//�жϱ������Ƿ�Ϊ��
int Division(char b, double c)
{
    int temp;
    temp = 0;
    if(b == '/' && c == 0)
    {
        printf("������Ϊ��");
        temp = 1;
    }
    return temp;
}

int Srand1()//����1~9��������ҷ��ش��� 
{
    int i;
    i= rand() % 9 + 1;
    return i;
}

int Srand2()//����1~9��������ҷ��ش��� 
{
    int i;
    i = rand() % 9 + 1;
    return i;
}

int getint(int a,int c)//ʹ��������ֹ淶������ 
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
            printf("����𰸸�ʽ�������������룡\n");
            printf("%d*%d=", a, c);
        }
    }while(!valid);
    m = atoi(s);//�ַ���ת��Ϊ���� 
    return m;
}

double getfloat()//ʹ��������ֹ淶���ַ��� 
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
        if(h == 0)//�����ַ���
		{
            valid = 0;
        }
        for(i = 0; i < h && valid; i++)
		{
            if(i == 0 && (s[i] == '+' || s[i] == '-'))//�������ַ�Ϊ����
			{
                sign = 1;
                continue;
            }
            
            if(s[i] == '.')//ͳ��С��������
			{
                count++;
                if(count > 1)//��ֹ���С����
				{  
                    valid = 0;
                    break;
                }
            }
            else if(!(s[i] >= '0' && s[i] <= '9'))//����Ƿ�Ϊ����
			{
                valid = 0;
                break;
            }
        }
        if(valid)//�����Ч��ʽ���� "-", ".", "123.", "-.5" �ȣ�
		{
            if (sign && h == 1) valid = 0;                //ֻ�з��ţ��� "-"��
            else if (count == 1 && h == 1) valid = 0;  //ֻ��С���㣨�� "."��
            else if (count == 1 && s[h-1] == '.') valid = 0; //��β��С���㣨�� "12."��
        }
        if(!valid)
		{
            printf("�����ʽ�������������룡\n");
        }
    }while(!valid);
    m = atof(s);//�ַ���ת��Ϊ������ 
    return m;
}

int StatisticScore(int c)//ͳ�Ʋ����ش���ķ���
{
    int x;
    x = c * 10;
    return x;
}

double StatisticRate(double c)//���㲢���ش������ȷ��
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
        fprintf(stderr, "���ݿ�����ʧ��: %s\n", mysql_error(conn));
        exit(1);
    }
    printf("�ɹ����ӵ�MySQL���ݿ�\n");
    //�������ݿ�ͱ�
    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS student_db")) 
	{
        fprintf(stderr, "�������ݿ�ʧ��: %s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn, "USE student_db")) 
	{
        fprintf(stderr, "ѡ�����ݿ�ʧ��: %s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS students (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100), sex VARCHAR(10), score INT, rate FLOAT)")) 
	{
        fprintf(stderr, "������ʧ��: %s\n", mysql_error(conn));
        exit(1);
    }
}

//��ӡ����ѡ��˵�
void sortmenu()
{
	printf("��ѡ������ʽ��\n");
	printf("1:���� ");
	printf("2:�Ա� ");
	printf("3:���� ");
	printf("4:��ȷ�� ");
	printf("�ڴ����룺");
}

void menu()
{
	printf("��ѡ����ţ�\n");
	printf("1:����һ��ѧ��\n");
	printf("2:����\n");
	printf("3:��ӡ���ݱ�\n");
	printf("0:�˳�\n");
	printf("�ڴ����룺");
}

//����һ��ѧ��
void add(student* p)
{
	p->sex = (char*)malloc(10);
	p->name = (char*)malloc(100);
	printf("������������\n");
	scanf("%s", p->name);
	printf("�������Ա�\n");
	scanf("%s", p->sex);
	while(!(strcasecmp(p->sex, "nan")==0||strcasecmp(p->sex, "nv")==0||strcasecmp(p->sex, "��")==0||strcasecmp(p->sex, "Ů")==0))
	{
			printf("�Ա�����������������룡\n");
			printf("�������Ա�\n");
			scanf("%s", p->sex); 
	}
}

//����������Ľ�βԪ��
student* findend(student* head)
{
	student* p = head;
	while(p!=NULL&&p->next!= NULL)//Ѱ��������Ľ�βԪ��
	{
		p = p->next;
	}
	return p;//����������Ľ�βԪ��
}

//��ĳ�ؼ�������
student* sort(int number, student* head,int(* compare) (student* p))
//number ѧ������ * head����ͷ int(* compare) (student* p) ����Ĺؼ��֣�����ָ�룬ָ��Ƚ���������ѧ���ĺ���
{
	student* p, * q, * temp;
	//* p��ǰ���ָ�루̽·�Ƚϴ�С�ã� * q�Ǻ����ָ�루�洢p��ǰһ��Ԫ�أ�����Ԫ�ؽ����ã�* temp �м���ָ�룬����Ԫ����
	int i, j;//ð�����������ѭ������
	for(i = 0; i < number - 1; i++)//ð�����������
	{
		p = head;//p,q��λ��ָ������ͷ
		q = head;
		for(j = 0; j < number - 1 - i ; j++)//ð������һ�˵ıȽ�
		{   
			if(compare(p)<0)//����compareָ��ıȽϺ���
			{
				//������ڵ�Ԫ�ص�ĳ������С����һ��Ԫ�ص�ĳ�����ݣ�����������Ԫ�ؽ���λ��
				if(p == head)//������ڵ�Ԫ��������ͷ
				{
					head = p->next;//������ͷ��Ϊ���ڵ�Ԫ�ص���һ��Ԫ��
					q->next = p->next;
					temp = p->next->next;//�м�����ݴ�
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
			p = p->next;//pָ����һ��Ԫ��
		}
	}
	return head;
}

//�Ƚ�������������Ԫ�ص�����
int compare_name(student* p)
{
	return -strcmp(p->name, p->next->name);
}

//�Ƚ�������������Ԫ�ص��Ա�
int compare_sex(student* p)
{
	return -strcmp(p->sex, p->next->sex);
}

//�Ƚ�������������Ԫ�صķ��� 
int compare_score1(student* p)
{
	return (p->testscore) - (p->next->testscore);
}

//�Ƚ�������������Ԫ�ص���ȷ�� 
int compare_score2(student* p)
{
	return (p->testrate) - (p->next->testrate);
}

//��ӡ���ݱ�
void print(student* head)
{
	student* p = head;
	int count = 1;//�������
	printf("���\t����\t�Ա�\t����\t��ȷ��\n");
	while(p != NULL)
	{
		printf("%d\t%s\t%s\t%d\t%.2f\n",count,p->name,p->sex,p->testscore,p->testrate);
		p = p->next;//��һ��ѧ��
		count++;//��ż�1
	}
	printf("\n");
}

void outlink(student* head) {
    FILE* w = fopen("output.txt", "w");
    if(w == NULL) 
	{
        printf("���ļ�ʧ��!\n");
        return;
    }
    init_db();//��ʼ�����ݿ�
    student* p = head;
    int count = 1;
    fprintf(w, "���\t����\t�Ա�\t����\t��ȷ��\n");
    while(p != NULL)
	{
		//���Ϊ�ļ� 
        fprintf(w, "%d\t%s\t%s\t%d\t%.2f\n", count, p->name, p->sex, p->testscore, p->testrate);
        //�������ݿ�
        char query[256];
        snprintf(query, 256, "INSERT INTO students (name, sex, score, rate) VALUES ('%s', '%s', %d, %.2f)",
                 p->name, p->sex, p->testscore, p->testrate);
        if(mysql_query(conn, query)) 
		{
            fprintf(stderr, "��������ʧ��: %s\n", mysql_error(conn));
        }

        p = p->next;
        count++;
    }
    fclose(w);
    //�ر����ݿ�����
    mysql_close(conn);
    printf("�����ѱ��浽���ݿ�\n");
}

void clearlist(student* head)//ɾ�����ݱ�
{
	student* p, * q;//* p��ǰҪɾ��������Ԫ��  * q�ݴ�p����һ��Ԫ��  
	p = head;//������ͷ��ʼɾ��
	while (p != NULL)
	{
		q = p->next;//�ݴ�p����һ��Ԫ��
		free(p);//�ͷ��ڴ�
		p = q;//pָ����һ��Ԫ��
	}
}

int one()//����һ 
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
 
int two()//�����
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
            s = round(s * 100) / 100;//����������ֵ�淶Ϊ������λС��λ 
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
 
int three(student* p)//������
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
    printf("�÷�Ϊ: %d ,��ȷ��Ϊ: %.2f ", p->testscore, p->testrate);
    return 0;
}

int four(student* p)//������
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
    printf("�÷�Ϊ: %d ,��ȷ��Ϊ: %.2f ", p->testscore, p->testrate);
    printf("\n");
    return 0;
}

int five(student* p)//������ 
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
    printf(" * 1. ���� 1��������� 1 - 10 ֮�������������˷����⣬ֱ��ѧ�����Ϊֹ(��Ϊ���ã���ͳ���ܷ�����ȷ��)��\n");
    printf(" * 2. ���� 2�������� 1 �����ϣ�������� 1 �����������⣬��ѧ�����ʱ���������λ���(��Ϊ���ã���ͳ���ܷ�����ȷ��)�� \n");
    printf(" * 3. ���� 3�������� 1 �����ϣ����� 10 ���˷��⣬��������������ͳ���ܷ֡���ȷ�ʡ�\n");
    printf(" * 4. ���� 4�������� 3 �����ϣ�������� 10 �����������⣬��������������ͳ���ܷ֡���ȷ�ʡ� \n");
    printf(" * 5. ���� 5�������� 4 �����ϣ����ش���ȷ�ʵ��� 75 % �������� 10 ���⣬ֱ����ȷ�ʸ��� 75 % Ϊֹ��\n");
    printf(" * 6. �˳� \n");
    printf("***************************************************************************** \n");
    while(scanf("%d", &a) != EOF)
	{
        if (a == 6) 
		{
            printf("�����ѽ���\n");
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
            printf("������󣬳����ѽ���\n");
            break;
        }
        if (flag == 1)
            break;
        printf("*********************************************************************************\n");
        printf(" * 1. ���� 1��������� 1 - 10 ֮�������������˷����⣬ֱ��ѧ�����Ϊֹ��\n");
        printf(" * 2. ���� 2�������� 1 �����ϣ���ѧ�����ʱ���������λ��ᡣ \n");
        printf(" * 3. ���� 3�������� 1 �����ϣ����� 10 ���˷��⣬��������������ͳ���ܷ֡���ȷ�ʡ�\n");
        printf(" * 4. ���� 4�������� 3 �����ϣ�������� 10 �����������⣬��������������ͳ���ܷ֡���ȷ�ʡ� *\n");
        printf(" * 5. ���� 5�������� 4 �����ϣ����ش���ȷ�ʵ��� 75 % �������� 10 ���⣬ֱ����ȷ�ʸ��� 75 % Ϊֹ��\n");
        printf(" * 6. �˳� *\n");
        printf("********************************************************************************** \n");
    }
} 

int main()
{
	srand((unsigned)time(NULL));
	init_db();
	int choose = 0, sortchoose = 0,number = 0;//chooseѡ������ sortchooseѡ���������� numberͳ������ѧ������
	student* now,* pre;//*now��ǰ����Ԫ�ص�ָ�� *preǰһ������Ԫ�ص�ָ��
	student* head = NULL;//����ͷ
	do
	{
		menu();//��ӡѡ��˵�
		scanf("%d", &choose);//����ѡ��
		switch(choose)
		{
			case 1://����һ��ѧ��
				now = (student *)malloc(sizeof(student));//Ϊ��ǰ����Ԫ�ط����ַ
				if (head == NULL)
					head = now;//�������ͷΪ�գ���ǰ����Ԫ��Ϊ����ͷ
				else 
					pre->next = now;//���ϸ�����Ԫ�ص�nextָ�����ڵ�����Ԫ�صĵ�ַ�����ѵ�ǰԪ�ؽ�������
				now->next = NULL;//��ǰԪ�ص���һ��Ԫ�ض�Ϊ��
				add(now);//����һ��Ԫ��
				test(now);
				pre = now;//Ϊ��һ��Ԫ��������׼��
			    number++;//����Ԫ�����ӣ�ѧ����������
				break;
			case 2://����
				sortmenu();//��ӡ����ѡ��˵�
				scanf("%d", &sortchoose);//����ѡ��
				switch (sortchoose)
				{
					case 1:
						head = sort(number, head, compare_name);
						pre = findend(head);
						printf("\n����������:\n");
						print(head);
						break;
					case 2:
						head = sort(number, head, compare_sex);
						pre = findend(head);
						printf("\n���Ա�����:\n");
						print(head);
						break;
					case 3:
						head=sort(number, head, compare_score1);
						pre = findend(head);
						printf("\n����������:\n");
						print(head);
						break;
					case 4:
						head = sort(number, head, compare_score2);
						pre = findend(head);
						printf("\n����ȷ������:\n");
						print(head);
						break;
					default:printf("������ѡ��\n\n");
				}
				break;
			case 3:
				print(head);//��ӡ��Ϣ��
				outlink(head); 
				break;
			case 0: break;
			default:printf("������ѡ��\n\n"); break;
		}
	}while(choose);//��chooseΪ�治Ϊ�㣨�˳�Ϊ�㣩
	printf("\n����ɾ�����ݱ�...\n");
	clearlist(head);//ɾ�����ݱ�
	printf("ɾ���ɹ�\n");
	printf("���˳�����\n");
	return 0;
}
