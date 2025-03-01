#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<mysql/mysql.h>
//用结构体封装图书信息
void ShowMainMeun()
{
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t**********欢迎进入**********\n");
	printf("\t\t**********图书馆管理系统**********\n");
	printf("\t\t**********主菜单**********\n");
	printf("\t\t**********1.图书管理**********\n");
	printf("\t\t**********2.读者管理**********\n");
	printf("\t\t**********3.借书还书登记**********\n");
	printf("\t\t**********0.退出系统**********\n");
	printf("\t\t**********请选择0-3**********\n");
	printf("\n");
}
void   ShowBookMeun()
{
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t***********欢迎进入**********\n");
	printf("\t\t***********图书馆管理系统**********\n");
	printf("\t\t***********子菜单**********\n");
	printf("\t\t***********1.显示图书信息**********\n");
	printf("\t\t***********2.增加图书信息**********\n");
	printf("\t\t***********3.查找图书信息**********\n");
	printf("\t\t***********4.删除图书信息**********\n");
	printf("\t\t***********5.修改图书信息**********\n");
	printf("\t\t***********0.退出系统**********\n");
}
void ShowBook()
{
 MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
MYSQL_RES*  result;
MYSQL_ROW row;
char *sql="select *from book";
if(mysql_query(mysql,sql)!=0)
{
    printf("query sql err:%s\n",mysql_error(mysql));
}
result=mysql_store_result(mysql);
if(result==NULL)
{
    printf("res err:%s\n",mysql_error(mysql));
    exit(1);
}
int num=mysql_num_rows(result);
int count=mysql_field_count(mysql);
printf("book有%d行%d列\n",num,count);
	for(int i=0;i<num;i++)
{
    row=mysql_fetch_row(result);
    for(int j=0;j<count;j++)
    {
        printf("%s  ",row[j]);
    }
    printf("\n");
}
mysql_close(mysql);
}
void  AddBook()
{
    MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }

	char dest[500]={" "};
    int iNum;
    char acName[15];
    char acAuthor[15];
    char acPress[15];
    int iAmout;
    char ch;
    while(1)
    {
        printf("现在开始往数据库db_book插入数据\n");
        printf("\t图书编号：");
        scanf("%d",&iNum);
        printf("\t图书名称：");
         scanf("%s",acName);
         printf("\t图书作者：");
         scanf("%s",acAuthor);
         printf("\t图书出版社：");
         scanf("%s",acPress);
         printf("\t图书库存量：");
         scanf("%d",&iAmout);
         getchar();
         sprintf(dest,"insert into book(iNum,acName,acAuthor,acPress,iAmout)values(%d,'%s','%s','%s',%d);",iNum,acName,acAuthor,acPress,iAmout);
    printf("dest==%s\n",dest);
    if(mysql_query(mysql,dest)!=0)
    {
        printf("query sql err:%s\n",mysql_error(mysql));
        exit(3);
    }
    else
    {
        printf("\t插入成功\n");
        memset(dest,0,500);
        printf("是否继续插入数据？y/n\n");
        char select;
        scanf("%c",&select);
        if(select=='n'||select=='N')
        {
            break;
        }
    }
    }
mysql_close(mysql); 
}
int SearchBook()
{
    MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    MYSQL_RES* result;
    MYSQL_ROW row;
    int iNum;
    printf("请输入图书编号");
    scanf("%d",&iNum);
    getchar();
    char dest1[500]={"  "};
    sprintf(dest1,"select *from book where iNum=%d",iNum);
    printf("dest1==%s\n",dest1);
    if(mysql_query(mysql,dest1)!=0)
    {
        printf("\n%d号图书不存在，查询失败！\n",iNum);
    }
    else
    {
        result=mysql_store_result(mysql);
        if(mysql_num_rows(result)!=0)
        {
            printf("\t          *****显示图书信息*****        \n");
            printf("\t图书编号  图书名  图书作者  图书出版社   图书库存量\n");
            printf("\t-----------------------------\n");
            while(row=mysql_fetch_row(result))
            {
                fprintf(stdout,"\t  %-7s %-7s %-7s %-7s %-7s \n",row[0] ,row[1],row[2],row[3],row[4]);
            }
        }
        else
        {
            printf("没有找到该记录信息");
        }
    }
	mysql_close(mysql);
}
void DeleteBook()//删除图书信息
{
	 MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    MYSQL_RES* result;
    MYSQL_ROW row;
    int iNum;
    printf("现在开始删除数据\n");
    printf("请输入图书编号");
    scanf("%d",&iNum);
    getchar();
    char dest1[500]={"  "};
    sprintf(dest1,"select *from book where iNum=%d",iNum);
    printf("dest1==%s\n",dest1);
    if(mysql_query(mysql,dest1)!=0)
    {
        printf("\n%d号图书不存在，查询失败！\n",iNum);
    }
    else
    {
        result=mysql_store_result(mysql);
        if(mysql_num_rows(result)!=0)
        {
            char ch;
            printf("发现记录信息是否显示？(y/n)");
            scanf("%c",&ch);
            getchar();
            if(ch=='y'||ch=='Y')
            {
            printf("\t          *****显示图书信息*****        \n");
            printf("\t图书编号  图书名  图书作者  图书出版社   图书库存量\n");
            printf("\t-----------------------------\n");
            while(row=mysql_fetch_row(result))
            {
                fprintf(stdout,"\t  %-7s %-7s %-7s %-7s %-7s \n",row[0] ,row[1],row[2],row[3],row[4]);
            }
            printf("\t是否删除？y/n");
            char dest2[500]={"  "};
            scanf("%c",&ch);
            getchar();
            if(ch=='y'||ch=='Y')
            {
                sprintf(dest2,"delete from book where iNum=%d",iNum);
                printf("dest2==%s\n",dest2);
                if(mysql_query(mysql,dest2)!=0)
                {
                    printf("\t删除失败\n");
                }
                else
                {
                    printf("\t %d号图书信息删除成功！\n",iNum);
                }
            }
            }
        }
        else
        {
                printf("没有找到相关记录\n");
        }
    }
	mysql_close(mysql);

}
void ShowModifyBookMenu()
{
	printf("\n\n\n\n");
	printf("\t      1.编号       \n");
	printf("\t      2.书名       \n");
	printf("\t      3.作者       \n");
	printf("\t      4.出版社       \n");
	printf("\t      5.库存量     \n");
	printf("\t请输入要修改的信息(1-5)");
}
void  ModifyBook()
{
	 MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    MYSQL_RES* result;
    MYSQL_ROW row;
    printf("现在开始修改记录\n");
    int iNum;
    printf("请输入图书编号");
    scanf("%d",&iNum);
    getchar();
    char dest3[500]={"  "};
    sprintf(dest3,"select *from book where iNum=%d",iNum);
    printf("dest3==%s\n",dest3);
    char ch;
    if(mysql_query(mysql,dest3)!=0)
    {
        printf("\n%d号图书不存在，查询失败！\n",iNum);
    }
    else
    {
        result=mysql_store_result(mysql);
        if(mysql_num_rows(result)!=0)
        {
            printf("发现记录信息是否显示？(y/n)\n");
            scanf("%c",&ch);
            getchar();
            if(ch=='Y'||ch=='y')
            {

            printf("\t          *****显示图书信息*****        \n");
            printf("\t图书编号  图书名  图书作者  图书出版社   图书库存量\n");
            printf("\t-----------------------------\n");
            while(row=mysql_fetch_row(result))
            {
                fprintf(stdout,"\t  %-7s %-7s %-7s %-7s %-7s \n",row[0] ,row[1],row[2],row[3],row[4]);
            }
            }
        }
        else
        {
            printf("没有找到该记录信息");
        }
    }
    printf("\t是否修改？(y/n)");
    scanf("%c",&ch);
    getchar();
    int iltem;
    if(ch=='y'||ch=='Y')
    {   
        ShowModifyBookMenu();
        scanf("%d",&iltem);
        getchar();
        switch(iltem)
        {
        case 1:
            printf("请输入修改后的图书编号");
            int iNum1;
            scanf("%d",&iNum1);
            getchar();
            char dest5[500]={" "};
            sprintf(dest5,"update book set iNum='%d' where iNum=%d",iNum1,iNum);
            printf("dest5==%s",dest5);
            if(mysql_query(mysql,dest5)!=0)
            {
            printf("\t修改记录失败\n");
            }
            else
            {
            printf("\t修改成功\n");
            }
            break;
        case 2:
        printf("请输入修改后的名字：\n");
        char acName[15];
        scanf("%s",acName);
        getchar();
        char dest4[500]={" "};
        sprintf(dest4,"update book set acName='%s'where iNum=%d",acName,iNum);
        printf("dest4==%s",dest4);
        if(mysql_query(mysql,dest4)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        case 3:
        printf("请输入修改后的作者：\n");
        char acAuthor[15];
        scanf("%s",acAuthor);
        getchar();
        char dest6[500]={" "};
        sprintf(dest6,"update book set acName='%s'where iNum=%d",acAuthor,iNum);
        printf("dest6==%s",dest6);
        if(mysql_query(mysql,dest6)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        case 4:
        printf("请输入修改后的出版社：\n");
        char acPress[15];
        scanf("%s",acPress);
        getchar();
        char dest7[500]={" "};
        sprintf(dest7,"update book set acPress='%s'where iNum=%d",acPress,iNum);
        printf("dest7==%s",dest7);
        if(mysql_query(mysql,dest7)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        case 5:
        printf("请输入修改后的库存量：\n");
        int iAmout;
        scanf("%d",&iAmout);
        getchar();
        char dest8[500]={" "};
        sprintf(dest8,"update book set iAmout='%d'where iNum=%d",iAmout,iNum);
        printf("dest8==%s",dest8);
        if(mysql_query(mysql,dest8)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        }
    }
	mysql_close(mysql);

}
void  MangerBook()
{
    MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
	int iltem;
	ShowBookMeun();
	scanf("%d", &iltem);
	getchar();
	while (iltem)
	{
		switch (iltem)
		{
		case 1:
			ShowBook();
			break;
		case 2:
			AddBook();
			break;
		case 3:
			
			SearchBook();
			break;
		case 4:
			DeleteBook();
			break;
		case 5:
			ModifyBook();
			break;
		default:
			printf("\t\t请输入正确的数字！\n\t\t");

		}

		printf("按任意键返回");
		getchar();
		ShowBookMeun();
		scanf("%d", &iltem);
		getchar();
	}
    mysql_close(mysql);
}
void   ShowReaderMeun()
{
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t***********欢迎进入**********\n");
	printf("\t\t***********图书馆管理系统**********\n");
	printf("\t\t***********子菜单**********\n");
	printf("\t\t***********1.显示读者信息**********\n");
	printf("\t\t***********2.增加读者信息**********\n");
	printf("\t\t***********3.查找读者信息**********\n");
	printf("\t\t***********4.删除读者信息**********\n");
	printf("\t\t***********5.修改读者信息**********\n");
	printf("\t\t***********0.退出系统**********\n");
}
void ShowReader()
{
	MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
MYSQL_RES*  result;
MYSQL_ROW row;
char *sql="select *from reader";
if(mysql_query(mysql,sql)!=0)
{
    printf("query sql err:%s\n",mysql_error(mysql));
}
result=mysql_store_result(mysql);
if(result==NULL)
{
    printf("res err:%s\n",mysql_error(mysql));
    exit(1);
}
int num=mysql_num_rows(result);
int count=mysql_field_count(mysql);
printf("reader有%d行%d列\n",num,count);
	for(int i=0;i<num;i++)
{
    row=mysql_fetch_row(result);
    for(int j=0;j<count;j++)
    {
        printf("%s  ",row[j]);
    }
    printf("\n");
}
mysql_close(mysql);
}
void  AddReader()
{
    MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }

	char dest[500]={" "};
    int iNum;
    char acName[15];
    char acSex[15];
    int iMax;
    int iAmout;
    char ch;
    while(1)
    {
        printf("现在开始往数据表reader插入数据\n");
        printf("\t读者编号：");
        scanf("%d",&iNum);
        printf("\t读者姓名：");
         scanf("%s",acName);
         printf("\t：读者性别");
         scanf("%s",acSex);
         printf("\t：最大可借阅数量");
         scanf("%d",&iMax);
         printf("\t：当前可借阅数量");
         scanf("%d",&iAmout);
         getchar();
         sprintf(dest,"insert into reader(iNum,acName,acSex,iMax,iAmout)values(%d,'%s','%s','%d',%d);",iNum,acName,acSex,iMax,iAmout);
    printf("dest==%s\n",dest);
    if(mysql_query(mysql,dest)!=0)
    {
        printf("query sql err:%s\n",mysql_error(mysql));
        exit(3);
    }
    else
    {
        printf("\t插入成功\n");
        memset(dest,0,500);
        printf("是否继续插入数据？y/n\n");
        char select;
        scanf("%c",&select);
        if(select=='n'||select=='N')
        {
            break;
        }
    }
    }
mysql_close(mysql); 
}
int SearchReader()
{
	MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    MYSQL_RES* result;
    MYSQL_ROW row;
    int iNum;
    printf("请输入读者编号");
    scanf("%d",&iNum);
    getchar();
    char dest1[500]={"  "};
    sprintf(dest1,"select *from reader where iNum=%d",iNum);
    printf("dest1==%s\n",dest1);
    if(mysql_query(mysql,dest1)!=0)
    {
        printf("\n%d号读者不存在，查询失败！\n",iNum);
    }
    else
    {
        result=mysql_store_result(mysql);
        if(mysql_num_rows(result)!=0)
        {
            printf("\t          *****显示读者信息*****        \n");
            printf("\t读者编号  读者姓名  读者性别  最大可借阅图书量   当前可借阅图书量\n");
            printf("\t-----------------------------\n");
            while(row=mysql_fetch_row(result))
            {
                fprintf(stdout,"\t  %-7s %-7s %-7s %-7s %-7s \n",row[0] ,row[1],row[2],row[3],row[4]);
            }
        }
        else
        {
            printf("没有找到该记录信息");
        }
    }
	mysql_close(mysql);
}
void DeleteReader()
{
	MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    MYSQL_RES* result;
    MYSQL_ROW row;
    int iNum;
    printf("现在开始删除数据\n");
    printf("请输入读者编号");
    scanf("%d",&iNum);
    getchar();
    char dest1[500]={"  "};
    sprintf(dest1,"select *from reader where iNum=%d",iNum);
    printf("dest1==%s\n",dest1);
    if(mysql_query(mysql,dest1)!=0)
    {
        printf("\n%d号读者不存在，查询失败！\n",iNum);
    }
    else
    {
        result=mysql_store_result(mysql);
        if(mysql_num_rows(result)!=0)
        {
            char ch;
            printf("发现记录信息是否显示？(y/n)");
            scanf("%c",&ch);
            getchar();
            if(ch=='y'||ch=='Y')
            {
            printf("\t          *****显示读者信息*****        \n");
            printf("\t读者编号  读者姓名  读者性别  最大可借阅图书量   当前可借阅图书量\n");
            printf("\t-----------------------------\n");
            while(row=mysql_fetch_row(result))
            {
                fprintf(stdout,"\t  %-7s %-7s %-7s %-7s %-7s \n",row[0] ,row[1],row[2],row[3],row[4]);
            }
            printf("\t是否删除？y/n");
            char dest2[500]={"  "};
            scanf("%c",&ch);
            getchar();
            if(ch=='y'||ch=='Y')
            {
                sprintf(dest2,"delete from reader where iNum=%d",iNum);
                printf("dest2==%s\n",dest2);
                if(mysql_query(mysql,dest2)!=0)
                {
                    printf("\t删除失败\n");
                }
                else
                {
                    printf("\t %d号读者信息删除成功！\n",iNum);
                }
            }
            }
        }
        else
        {
                printf("没有找到相关记录\n");
        }
    }
	mysql_close(mysql);
}
void ShowModifyReaderMenu()
{
	printf("\n\n\n\n");
	printf("\t      1.读者编号       \n");
	printf("\t      2.姓名       \n");
	printf("\t      3.性别       \n");
	printf("\t      4.最大可借阅数量       \n");
	printf("\t请输入要修改的信息(1-5)");
}
void ModifyReader()//5.修改读者信息;
{
	 MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    MYSQL_RES* result;
    MYSQL_ROW row;
    printf("现在开始修改记录\n");
    int iNum;
    printf("请输入读者编号");
    scanf("%d",&iNum);
    getchar();
    char dest3[500]={"  "};
    sprintf(dest3,"select *from reader where iNum=%d",iNum);
    printf("dest3==%s\n",dest3);
    char ch;
    if(mysql_query(mysql,dest3)!=0)
    {
        printf("\n%d号读者不存在，查询失败！\n",iNum);
    }
    else
    {
        result=mysql_store_result(mysql);
        if(mysql_num_rows(result)!=0)
        {
            printf("发现记录信息是否显示？(y/n)\n");
            scanf("%c",&ch);
            getchar();
            if(ch=='Y'||ch=='y')
            {

            printf("\t          *****显示读者信息*****        \n");
            printf("\t读者编号  读者姓名  读者性别  最大可借阅数量   当前可借阅数量\n");
            printf("\t-----------------------------\n");
            while(row=mysql_fetch_row(result))
            {
                fprintf(stdout,"\t  %-7s %-7s %-7s %-7s %-7s \n",row[0] ,row[1],row[2],row[3],row[4]);
            }
            }
        }
        else
        {
            printf("没有找到该记录信息");
        }
    }
    printf("\t是否修改？(y/n)");
    scanf("%c",&ch);
    getchar();
    int iltem;
    if(ch=='y'||ch=='Y')
    {   
        ShowModifyReaderMenu();
        scanf("%d",&iltem);
        getchar();
        switch(iltem)
        {
        case 1:
            printf("请输入修改后的读者编号");
            int iNum1;
            scanf("%d",&iNum1);
            getchar();
            char dest5[500]={" "};
            sprintf(dest5,"update reader set iNum='%d' where iNum=%d",iNum1,iNum);
            printf("dest5==%s",dest5);
            if(mysql_query(mysql,dest5)!=0)
            {
            printf("\t修改记录失败\n");
            }
            else
            {
            printf("\t修改成功\n");
            }
            break;
        case 2:
        printf("请输入修改后的姓名：\n");
        char acName[15];
        scanf("%s",acName);
        getchar();
        char dest4[500]={" "};
        sprintf(dest4,"update reader set acName='%s'where iNum=%d",acName,iNum);
        printf("dest4==%s",dest4);
        if(mysql_query(mysql,dest4)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        case 3:
        printf("请输入修改后的读者性别：\n");
        char acSex[15];
        scanf("%s",acSex);
        getchar();
        char dest6[500]={" "};
        sprintf(dest6,"update reader set acSex='%s'where iNum=%d",acSex,iNum);
        printf("dest6==%s",dest6);
        if(mysql_query(mysql,dest6)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        case 4:
        printf("请输入修改后的最大可借阅数量：\n");
        int iMax;
        scanf("%d",&iMax);
        getchar();
        char dest7[500]={" "};
        sprintf(dest7,"update reader set iMax='%d'where iNum=%d",iMax,iNum);
        printf("dest7==%s",dest7);
        if(mysql_query(mysql,dest7)!=0)
        {
            printf("\t修改记录失败\n");
        }
        else
        {
            printf("\t修改成功\n");
        }
        break;
        }
    }
	mysql_close(mysql);
}
void  MangerReader()
 {
      MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
	int rselect;
	ShowReaderMeun();
	scanf("%d", &rselect);
	getchar();
	while (rselect)
	{
		switch (rselect)
		{
		case 1:
			ShowReader();
			break;
		case 2:
			AddReader();
			break;
		case 3:
			SearchReader();
			break;
		case 4:
			DeleteReader();
			break;
		case 5:
			ModifyReader();
			break;
		default:
			printf("\t\t请输入正确的数字！\n\t\t");

		}
		printf("按任意键返回");
		getchar();
		ShowReaderMeun();
		scanf("%d", &rselect);
		getchar();
	}
    mysql_close(mysql);
 }
void BorrowBook()
{
     MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    ShowReader();
	char dest[500]={" "};
    int iReaderNum;
    char acReaderName[15];
    char acSex[15];
    int  iBookiNum;
    char  acBookName[15];
    char  data[15];
    ShowBook();
    while(1)
    {
        printf("现在开始往借阅表中插入数据\n");
        printf("\t读者编号：");
        scanf("%d",&iReaderNum);
        printf("\t读者姓名：");
         scanf("%s",acReaderName);
         printf("\t读者性别:");
         scanf("%s",acSex);
         printf("\t要借阅的图书编号:");
         scanf("%d",&iBookiNum);
         printf("\t要借阅的图书名:");
         scanf("%s",acBookName);
         printf("\t借阅日期：");
            scanf("%s",data);
         getchar();
         sprintf(dest,"insert into borrow(iReaderNum,acReaderName,acSex,iBookiNum,acBookName,data)values(%d,'%s','%s','%d','%s','%s');",iReaderNum,acReaderName,acSex,iBookiNum,acBookName,data);
    printf("dest==%s\n",dest);
    if(mysql_query(mysql,dest)!=0)
    {
        printf("query sql err:%s\n",mysql_error(mysql));
        exit(3);
    }
    else
    {
        printf("\t插入成功\n");
        memset(dest,0,500);
        printf("是否继续插入数据？y/n\n");
         char select;
        scanf("%c",&select);
        if(select=='n'||select=='N')
        {
            break;
        } 
    }
    }
    printf("\t以下是借阅信息：\n");
    MYSQL_RES*  result;
MYSQL_ROW row;
char *sql="select *from borrow";
if(mysql_query(mysql,sql)!=0)
{
    printf("query sql err:%s\n",mysql_error(mysql));
}
result=mysql_store_result(mysql);
if(result==NULL)
{
    printf("res err:%s\n",mysql_error(mysql));
    exit(1);
}
int num=mysql_num_rows(result);
int count=mysql_field_count(mysql);
printf("borrow有%d行%d列\n",num,count);
	for(int i=0;i<num;i++)
{
    row=mysql_fetch_row(result);
    for(int j=0;j<count;j++)
    {
        printf("%s  ",row[j]);
    }
    printf("\n");
}
mysql_close(mysql); 
}
void  ReturnBook()
{
 MYSQL  mydata;
    MYSQL *mysql=mysql_init(&mydata);
    if(mysql==NULL)
    {
        printf("数据库初始化失败\n");
        exit(1);
    }
    else
    {
        printf("数据库初始化成功\n");
    }
    mysql=mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",0,NULL,0);
    if(mysql==NULL)
    {
        printf("数据库连接失败\n");
        exit(2);
    }
    else
    {
        printf("数据库连接成功\n");
    }
    ShowReader();
	char dest[500]={" "};
    int iReaderNum;
    char acReaderName[15];
    char acSex[15];
    int  iBookiNum;
    char  acBookName[15];
    char  data[15];
    ShowBook();
    while(1)
    {
        printf("现在开始往归还记录表中插入数据\n");
        printf("\t读者编号：");
        scanf("%d",&iReaderNum);
        printf("\t读者姓名：");
         scanf("%s",acReaderName);
         printf("\t读者性别:");
         scanf("%s",acSex);
         printf("\t要归还的图书编号:");
         scanf("%d",&iBookiNum);
         printf("\t要归还的图书名:");
         scanf("%s",acBookName);
         printf("\t归还日期：");
            scanf("%s",data);
         getchar();
         sprintf(dest,"insert into return1(iReaderNum,acReaderName,acSex,iBookiNum,acBookName,data)values(%d,'%s','%s','%d','%s','%s');",iReaderNum,acReaderName,acSex,iBookiNum,acBookName,data);
    printf("dest==%s\n",dest);
    if(mysql_query(mysql,dest)!=0)
    {
        printf("query sql err:%s\n",mysql_error(mysql));
        exit(3);
    }
    else
    {
        printf("\t插入成功\n");
        memset(dest,0,500);
        printf("是否继续插入数据？y/n\n");
         char select;
        scanf("%c",&select);
        if(select=='n'||select=='N')
        {
            break;
        } 
    }
    }
    printf("\t以下是归还信息：\n");
    MYSQL_RES*  result;
MYSQL_ROW row;
char *sql="select *from return1";
if(mysql_query(mysql,sql)!=0)
{
    printf("query sql err:%s\n",mysql_error(mysql));
}
result=mysql_store_result(mysql);
if(result==NULL)
{
    printf("res err:%s\n",mysql_error(mysql));
    exit(1);
}
int num=mysql_num_rows(result);
int count=mysql_field_count(mysql);
printf("return1有%d行%d列\n",num,count);
	for(int i=0;i<num;i++)
{
    row=mysql_fetch_row(result);
    for(int j=0;j<count;j++)
    {
        printf("%s  ",row[j]);
    }
    printf("\n");
}
mysql_close(mysql); 

}
 void ShowBorrowReturnMenu()
 {
	 system("cls");
	 printf("\n\n\n\n\n\n");
	 printf("\t\t**********欢迎进入**********\n");
	 printf("\t\t**********借还书登记**********\n");
	 printf("\t\t**********子菜单**********\n");
	 printf("\t\t**********1.借书登记**********\n");
	 printf("\t\t**********2.还书登记**********\n");
	 printf("\t\t**********0.退出系统**********\n");
	 printf("\t\t**********请选择0-2**********\n");
	 printf("\n");
 }
void    BorrowReturnManger()
{
	ShowBorrowReturnMenu();
	int iltem;
	scanf("%d", &iltem);
	getchar();
	while (iltem)
	{
		switch (iltem)
		{
		case 1:
			BorrowBook();
			break;
		case 2:
			ReturnBook();
			break;
		default:
			printf("\t\t请输入正确的数字\n\t\t");
		}
		printf("请按任意键返回主菜单");
		getchar();
		ShowBorrowReturnMenu();
		scanf("%d", &iltem);
		getchar();
	}
}
int main()
{
	ShowMainMeun();
	int iltem;
	scanf("%d",&iltem);
	while (iltem)
	{
		switch (iltem)
		{
		case 1:
			MangerBook();//图书管理模块
			break;
		case 2:
			MangerReader();//读者管理模块
			break;
		case 3:
			BorrowReturnManger();//借书还书模块
			break;
			default:
				printf("\t\t请输入正确的数字!\n\t程序将在3秒后跳转到主菜单");
				sleep(3000);
		}
		ShowMainMeun();
		scanf("%d",&iltem);
		getchar();
		
	}
}
