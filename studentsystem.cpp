#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HEADER1"------------STUDENT----------\n"
#define HEADER2"|number|name|Comp|Math|Eng|sum|ave|mici|\n"
#define HEADER3"|-----|-----|-----|-----|-----|-----|-----|"
#define FORMAT "|%-10s|%-15s|%4d|%4d|%4d|%4d|%.2f|%4d|\n"
#define DATA p->data.num,p->data.name,p->data.cgrade,p->data.mgrade,p->data.egrade,p->data.total,p->data.ave,p->data.mingci
#define END"------------------------------------------------\n"
int saveflag=0;/*是否需要存盘的标志变量*/
/*定义与学生有关的数据结构*/
typedef struct student
{
	char num[10];
	char name[15];
	int cgrade;/*c语言成绩*/ 
	int mgrade;/*数学成绩*/ 
	int egrade;/*英语成绩*/ 
	int total;/*总分*/ 
	float ave;/*平均分*/ 
	int mingci;/*名次*/ 
 };
 /*定义每条记录或节点的数据结构*/ 
 
typedef struct node
{
	struct student data;
	struct node*next;
 } Node,*Link;
 /*主菜单*/
 void menu()
 {
 	system("cls");/*调用DOS命令，清屏，与clrscr（）功能相同*/
 	printf("The Students Grade Management System\n\n");
 	printf("****************Menu***************\n");
 	printf("*     1 input record            2 delete record* \n");
 	printf("*     3 search record           4 modify record* \n");
 	printf("*     5 insert record           6 count record* \n");
 	printf("*     7 sort record             8 save record* \n");
 	printf("*     9  display record         0 quit system* \n");
 	printf("***********************************\n");
 }
 void printheader()   /*格式化输出表头*/ 
 {
 	printf(HEADER1);
 	printf(HEADER2);
 	printf(HEADER3);
 }
 void printdata(Node*pp)    /*格式化输出表中数据*/ 
 {
 	Node*p;
 	p=pp;
 	printf(FORMAT,DATA);
  } 
void Wrong()         /*输出按键错误信息*/ 
{
	printf("\n\n\n\n\n*****Error:input as wrong!press any key to continue*****\n");
	getchar();
}
void Nofind()   /*输出未查找到此学生信息*/ 
{
	printf("\n=====>Not find this student! \n");
}
void Disp(Link l)/*显示单链表1中存储的学生记录，内容为student结构中定义的内容 */
{
	Node*p;
	p=l->next;/*1存储的是单链表中头节点的指针，该头节点没有存储学生信息，指针域指向的后继节点才有学生信息*/ 
	if(!p)
	{
		printf("\n=====>Not student record! \n");
		getchar();
		return;
	 } 
	 printf("\n\n");
	 printheader();/*输出 表格头部*/
	 while(p)
	 {
	 	printdata(p);
	 	p=p->next;
	 	printf("/n");
	  } 
}
	/*作用：用于定位链表中符合要求的节点，参数findmess[]保存要查找的具体内容；Locateofname按姓名在单链表1中查询；
	将符合条件的节点（可能不止一个）地址存入指针数组中 */
Node *Locateofnum(Link l,char findmess[])     /*按学号查询*/
{
	Node*r;
	r=l->next;
	while(r)
	{
		if(strcmp(r->data.num,findmess)==0)/*若找到findmess值的学号*/
		return r;
		r=r->next;
	}
	return 0;    /*若未找到，返回一个空指针*/ 
 } 
 void Locateofname(Link l,char findmess[],Node *n[])/*按姓名查询*/ 
 {
 	Node*r;
 	int i=0;
 	r=l->next;
 	while(r)
 	{
 		if(strcmp(r->data.name,findmess)==0)
 		n[i++]=r;/*将此符合查找条件的记录指针存入指针数组中*/
		r=r->next; 
	 }
  } 
  /*输入字符串，并进行长度验证（长度<lens)*/
  void stringinput(char *t,int lens,char*notice)
  {
  	char n[255];
  	printf(notice);
  	scanf("%s",n);
  	while(strlen(n)>lens)
  	{
  		printf("\n exceed the required length! \n");
  		/*进行长度校验，超过lens值重新输入*/
		  printf(notice);
		  scanf("%s",n); 
	  }
	  strcpy(t,n);   /*将输入的字符串拷贝到字符串t中*/ 
   } 
   /*输入分数，要求分数在0~100之间*/
   int numberinput(char *notice)
   {
   		int t=0;
   		printf(notice);
   		scanf("%d",&t);
   		while(t>100||t<0)
   		{
   			printf("\n score must in [0,100]!\n");    /*进行分数校验*/
			printf(notice);
			scanf("%d",&t); 
		}
	   	return t;
	} 
	/*增加学生的记录*/
	void Add(Link l)
	{
		Node *p,*r,*s;    /*实现添加操作的临时的结构体指针变量*/
		char ch,flag=0,num[10];
		r=l;
		s=l->next;
		system("cls");
		Disp(l);  /*先显示出已有的学生信息*/
		while(r->next!=NULL) 
		r=r->next;/*将指针移至链表最末尾，准备添加纪录*/
		while(l)    /*一次可输入多条记录，直至输入学号为零的记录结束添加操作*/
		{
		while(1)         /*输入学号，保证该学号没有被使用，若输入学号为0，则退出添加纪录操作*/
		{
			stringinput(num,10,"input number(press'0'return menu):");
			flag=0;
			if(strcmp(num,"0")==0)/*输入为零，则退出添加操作，返回主界面*/
			{return ;} 
			s=l->next;
			while(s)    /*查询该学号是否已经存在，若存在则要求重新输入一个未被占用的学号*/ 
			{
				if(strcmp(s->data.num,num)==0)
				{
					flag=1;
					break;
				}
				s=s->next;

			}
			if(flag==1)
			{
				getchar();
				printf("=====>The number %s is existing,try again?(y/n):",num);
				scanf("%c",&ch);
				if(ch=='y'||ch=='Y')
				continue;
				else
				return;
			}
			else
			break;
		 } 
		 p=(Node*)malloc(sizeof(Node));/*为新增记录申请内存空间*/
		 if(!p)
		 {
		 	printf("\n allocate memory failure");/*如没有申请到，打印提示信息*/
			 return; 
		  } 
		  strcpy(p->data.name,num);
		  stringinput(p->data.name,15,"Name:");
		  p->data.cgrade=numberinput("C language Score[0~100]:");
		  /*输入并校验分数，分数必须在0~100之间*/
		  p->data.mgrade=numberinput("Math Score[0~100]:");
		  p->data.egrade=numberinput("English Score[0~100]:"); 
		  p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade;
		  p->data.ave=(float)(p->data.total/3);
		  p->data.mingci=0;
		  p->next=NULL;          /*表明这是链表的尾部节点*/ 
		  r->next=p;         /*将新建的节点加入链表尾部中*/
		  r=p;
		  saveflag=1;
		}
			return;
		}
		/*按学号或姓名，查询学生记录*/
		void Qur(Link l)
		{
			int select;   /*select 值为1：按学号查，2：按姓名查，其他：返回主界面（菜单）*/
			char searchinput[20];    /*保存用户输入的查询内容*/
			Node*p;
			Node*n[5]={NULL};    /*用于存放按姓名查找到符合条件的节点的指针数组*/
			int i=0;
			if(!l->next)
			{
				system("cls");
				printf("\n=====>No student record!\n");
				getchar();
				return;
			 } 
			 system("cls");
			 printf("\n=====>1 Search by number =====>2 Search by name \n");
			 printf("      please choice[1,2]:");
			 scanf("%d",&select);
			 if(select==1)
			 {
			 	stringinput(searchinput,10,"input the existing student number:");
			 	p=Locateofnum(l,searchinput);
			 	/*在链表1中查找学号searchinput值的节点，并返回节点的指针*/
				 if(p)
				 {
				 	printheader();/*格式输出查找到的符合条件的记录*/
					 printdata(p);
					 printf(END);
					 printf("press any key to return");
					 getchar(); 
				  } 
				  else
				   	Nofind();
				   	getchar();
			 }
			 else if(select==2)
			 {
			 	stringinput(searchinput,15,"input the existing student name:");
			 	Locateofname(l,searchinput,n);
			 	/*在链表1中查找姓名为searchinput值的节点，并将节点的指针保存在数组n中*/
				 while((p=n[i++])!=NULL)/*显示已找到的符合姓名条件的记录直到指针为NULL*/
				 {
				 	printheader();
				 	printdata(p);
				 	printf(END);
				  } 
				  printf("press any key to return ");
				  getchar();
				  if(n[0]==NULL)
				  	Nofind();
				  getchar();
			 }
			 else
			 	Wrong();
			 getchar();
		 } 
		/*删除学生记录：先找到保存该学生记录的节点，然后删除该节点*/
		void Del(Link l)
		{
			Node*p,*r;
			char findmess[20],ch;
			if(!l->next)
			{
				system("class");
				printf("\n=====>NO student recond! \n");
				getchar();
				return;
			 } 
			 system("class");
			 Disp(l);
			 stringinput(findmess,10,"input the existing student number:");
			 /*输入要删除的学号*/
			 getchar();
			 p=Locateofnum(l,findmess);/*指针定位到要删除的位置*/
			 printf("Are you sure to delete %s(y/n)?",findmess);
			 
			 scanf("%c",&ch);
			 if(ch=='y'||ch=='Y')
			 {
			 	if(p)
			 	{
			 		r=l;
			 		while(r->next!=p)
					r=r->next;
					r->next=p->next;
					free(p);
					printf("\n===>deletesuccess!\n");
					getchar();
					saveflag=1;
				}
				else
				Nofind();
				getchar();
			}
		}
		/*修改学生的记录*/
		void Modify(Link l)
		{
			Node*p;
			char findmess[20];
			if(!l->next)
			{
				system("class");
				printf("\n=====>No student record!\n");
				getchar();
				return;
			}
			system("cls");
			printf("modify student recorder");
			Disp(l);
			stringinput(findmess,10,"input the existing student number:");
			p=Locateofnum(l,findmess);
			if(p)
			{
				printf("Number:%s,\n",p->data.num);
				printf("Name:%s",p->data.name);
				stringinput(p->data.name,15,"input new name:");
				printf("C language  score:%d,",p->data.cgrade);
				p->data.cgrade=numberinput("C language Score[0~100]:");
				printf("Math score:%d,",p->data.mgrade);
				p->data.mgrade=numberinput("Math Score[0~100]:");
				printf("English score :%d,",p->data.egrade);
				p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade;
				p->data.ave=(float)(p->data.total/3);
				p->data.mingci=0;
				printf("\n=====>modify sucess!\n");
				Disp(l);
				saveflag=1;
			}
			else Nofind();
			getchar();
			getchar();
		 } 
		 void Insert(Link l)
		 {
		 	Link p,v,newinfo;
		 	char ch,num[10],s[10];
		 	int flag=0;
		 	v=l->next;
		 	system("cls");
		 	Disp(l);
		 	while(1)
		 	{
		 		stringinput(s,10,"please input insert location after the Number:");
		 		flag=0;
		 		v=l->next;
		 		while(v)
		 		{
		 			if(strcmp(v->data.num,s)==0)
		 			{
		 				flag=1;
		 				break;
					 }
					 v=v->next;
					
				 }
				 if(flag==1)
					break;
					else
					{
						getchar();
						printf("\n=====>The number %s is not existing,try again?(y/n):",s);
						scanf("%c",&ch);
						if(ch=='y'||ch=='Y')
						{
							continue;
							
						}
						else
						{
							return;
						}
					}	
			 }
			 stringinput(num,10,"input new student Number:");
			 v=l->next;
			 while(v)
			 {
			 	if(strcmp(v->data.num,num)==0)
			 	{
			 		printf("=====>Sorry,the new number :'%s'is existing!\n",num);
			 		printheader();
			 		printdata(v);
			 		printf("\n");
			 		getchar();
			 		getchar();
			 		return;
				 }
				 v=v->next;
			 }
			 newinfo=(Node*)malloc(sizeof(Node));
			 if(!newinfo)
			 {
			 	printf("\n allocate memory failure");
			 	return;
			 }
			strcpy(newinfo->data.num,num);
			stringinput(newinfo->data.name,15,"Name:");
			newinfo->data.cgrade=numberinput("C language Score[0~100]:");
			newinfo->data.mgrade=numberinput("Math Score[0~100]");
			newinfo->data.egrade=numberinput("English Score[0~100]");
			newinfo->data.total=newinfo->data.egrade+newinfo->data.cgrade+newinfo->data.mgrade;
			newinfo->data.ave=(float)(newinfo->data.total/3);
			newinfo->data.mingci=0;
			newinfo->next=NULL;
			saveflag=1;/*在main中有对该全局变量的判断，若为1，则进行存盘操作*/
			p=l->next;
			while(l)
			{
				if(strcmp(p->data.num,s)==0)
				{
					newinfo->next=p->next;
					p->next=newinfo;
					break;
				}
				p=p->next;
			 } 
			 Disp(l);
			 printf("\n\n");
			 getchar();
		 }
		 
		 
		 
		 /*统计该班的总分第一名和单科第一名和各科0~59，60~69，70~79，80~89，90~100各个分数段的人数*/
		 void Count(Link l)
		 {
		 	Node *pm,*pe,*pc,*pt;
		 	Node* r=l->next;
		 	int countc[5]={0},countm[5]={0},counte[5]={0};
		 	if(!r)
		 	{
		 		system("cls");
		 		printf("\n=====>Not student record!\n");
		 		getchar();
		 		return;
			 }
			 system("cls");
			 Disp(l);
			 pm=pe=pc=pt=r;
			 while(r)
			 {
			 	if(r->data.cgrade<60)
			 	countc[0]++;
			 	if(r->data.mgrade<60)
			 	countm[0]++;
			 	if(r->data.egrade<60)
			 	counte[0]++;
			 	
			 	if(r->data.cgrade>=60&&r->data.cgrade<70)
			 	countc[1]++;
			 	if(r->data.mgrade>=60&&r->data.mgrade<70)
			 	countm[1]++;
			 	if(r->data.egrade>=60&&r->data.egrade<70)
			 	counte[1]++;
			 	
			 	if(r->data.cgrade>=70&&r->data.cgrade<80)
			 	countc[2]++;
			 	if(r->data.mgrade>=70&&r->data.mgrade<80)
			 	countm[2]++;
			 	if(r->data.egrade>=70&&r->data.egrade<80)
			 	counte[2]++;
			 	
			 	if(r->data.cgrade>=80&&r->data.cgrade<90)
			 	countc[3]++;
			 	if(r->data.mgrade>=80&&r->data.mgrade<90)
			 	countm[3]++;
			 	if(r->data.egrade>=80&&r->data.egrade<90)
			 	counte[3]++;
			 	
			 	if(r->data.cgrade>=90)
			 	countc[4]++;
			 	if(r->data.mgrade>=60)
			 	countm[4]++;
			 	if(r->data.egrade>=60)
			 	counte[4]++;
			 	r=r->next;
			 }
			 printf("\n-------the TongJi result-----------\n");
			 printf("C Language 0~59:%d(ren)\n",countc[0]);
			 printf("C Language 60~69:%d(ren)\n",countc[1]);
			 printf("C Language 70~79:%d(ren)\n",countc[2]);
			 printf("C Language 80~89:%d(ren)\n",countc[3]);
			 printf("C Language 90~100:%d(ren)\n",countc[4]);
			 printf("------------------------------------\n");
			printf("Math     0~59:%d(ren)\n",countm[0]);
			 printf("Math     60~69:%d(ren)\n",countm[1]);
			 printf("Math      70~79:%d(ren)\n",countm[2]);
			 printf("Math      80~89:%d(ren)\n",countm[3]);
			 printf("Math     90~100:%d(ren)\n",countm[4]);
			 printf("------------------------------------\n");
			 
			 printf("English     0~59:%d(ren)\n",counte[0]);
			 printf("English     60~69:%d(ren)\n",counte[1]);
			 printf("English     70~79:%d(ren)\n",counte[2]);
			 printf("English    80~89:%d(ren)\n",counte[3]);
			 printf("English    90~100:%d(ren)\n",counte[4]);
			 printf("------------------------------------\n");
			 printf("The highest student by total score num:%s total score:%d\n",pt->data.num,pt->data.total);
			 printf("The highest student by Engliah score num:%s total score :%d\n",pe->data.num,pe->data.egrade);
			 printf("The highest student by Math score num:%s total score :%d\n",pm->data.num,pm->data.mgrade);
			 printf("The highest by C score num:%s total score :%d\n",pc->data.num,pc->data.cgrade);
			 printf("\n\npress any key to return");
			 getchar();
		  } 
		  
		  void Sort(Link l)
		  {
		  	struct student temp;
		  	Node*p1,*p2,*p;
		  	int i=0;
		  	if(l->next==NULL)
		  	{
		  		system("cls");
		  		printf("\n=====>Not student record!\n");
		  		getchar();
			  	return;
			}
			system("cls");
			Disp(l);
			p1-l->next;
			while(p1)
			{
				p2=p1->next;
				p=p1;
				while(p2)
				{
					if(p2->data.total>=p->data.total)
					p=p2;
					p2=p2->next; 
				}
				temp=p->data;
				p->data=p1->data;
				p1->data=temp;
				p1=p1->next;
			}
			p=l->next;
			while(p!=NULL)
			{
				i++;
				p->data.mingci=i;
				p=p->next;
			}
			Disp(l);
			saveflag=1;
			printf("\n    =======>sort complete! \n");
			}
		 void Save(Link l)
		 {
		 	FILE *fp;
		 	Node*p;
		 	int count=0;
		 	fp=fopen("student","wb");
		 	if(fp==NULL)
		 	{
		 		printf("\n======> open file error!\n");
		 		getchar();
		 		return;
			 }
			 p=l->next;
			 while(p)
			 {
			 	if(fwrite(p,sizeof(Node),1,fp)==1)
			 	{
			 		p=p->next;
			 		count++;
				 }
				 else
				 { 
				 break;
			 	}
			 } 
			 if(count>0)
			 {
			 	getchar();
			 	printf("\n\n\n\n\n=======>save file complete,total saved's record number is:%d\n",count);
			 	getchar();
			 	saveflag=0;
			 }
			 else
			 {
			 	system("cls");
			 	printf("the current link is empty,no student record is saved!\n");
			 	getchar();
			 }
			 fclose(fp);
		}
		 
		int main()
		 {
		 	Link l;
		 	FILE *fp;
		 	int select;
		 	char ch;
		 	int count=0;
		 	Node *p,*r;
		 	
		 	l=(Node*)malloc(sizeof(Node));
		 	if(!l)
		 	{
		 		printf("\n allocate memory failure");
			 }
			 l->next=NULL;
			 r=l;
			 fp=fopen("student","ab+");
			 /*以追加方式打开一个二进制文件，可读可写，若此文件不存在，会创建此文件*/
			 if(fp==NULL)
			 {
			 	printf("\n======>can not open file! \n");
			 	exit(0);
			  } 
			  while(!feof(fp))
			{
				p=(Node*)malloc(sizeof(Node));
				if(!p)
				{
					printf("memory malloc failure!\n");
					exit(0);
				}
				if(fread(p,sizeof(Node),1,fp)==1)
				{
					p->next=NULL;
					r->next=p;
					r=p;
					count++;
				}
			}
			fclose(fp);
			printf("\n=======>open file sucess,the total records number is:%d.\n",count);
			printf("\n======>Press any key to enter the Menu!");
			getchar();
			while(1)
			{
				system("cls");
				menu();
				p=r;
				printf("\n              Please Enter your choice(0~9):");
				scanf("%d",&select);
				
				if(select==0)
				{
					if(saveflag==1)
					{
						getchar();
						printf("\n========>Whether save the modified record to file?(y/n):");
						scanf("%c",&ch);
						if(ch=='y'||ch=='Y')
						Save(l);
					}
					printf("=======>thank you for useness!");
					getchar();
					break;
				}
				switch(select)
				{
					case 1: Add(l);break;           /*增加学生记录*/ 
					case 2: Del(l);break;           /*删除学生记录*/ 
					case 3:Qur(l);break;			/*查询学生记录*/ 
					case 4:Modify(l);break;			/*修改学生记录*/ 
					case 5:Insert(l);break;			/*插入学生记录*/ 
					case 6:Count(l);break;			/*统计学生记录*/ 
					case 7:Sort(l);break;			/*排序学生记录*/ 
					case 8:Save(l);break;			/*保存学生记录*/ 
					case 9:system("cls");Disp(l);break;	/*显示学生记录*/ 
					default:Wrong();getchar();break;	/*按键有误，必须为数值0~9*/ 
				}
			}
			return 0;
		 }
		 
		  
		 
	
   
