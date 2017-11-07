#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HEADER1"------------STUDENT----------\n"
#define HEADER2"|number|name|Comp|Math|Eng|sum|ave|mici|\n"
#define HEADER3"|-----|-----|-----|-----|-----|-----|-----|"
#define FORMAT "|%-10s|%-15s|%4d|%4d|%4d|%4d|%.2f|%4d|\n"
#define DATA p->data.num,p->data.name,p->data.cgrade,p->data.mgrade,p->data.egrade,p->data.total,p->data.ave,p->data.mingci
#define END"------------------------------------------------\n"
int saveflag=0;/*�Ƿ���Ҫ���̵ı�־����*/
/*������ѧ���йص����ݽṹ*/
typedef struct student
{
	char num[10];
	char name[15];
	int cgrade;/*c���Գɼ�*/ 
	int mgrade;/*��ѧ�ɼ�*/ 
	int egrade;/*Ӣ��ɼ�*/ 
	int total;/*�ܷ�*/ 
	float ave;/*ƽ����*/ 
	int mingci;/*����*/ 
 };
 /*����ÿ����¼��ڵ�����ݽṹ*/ 
 
typedef struct node
{
	struct student data;
	struct node*next;
 } Node,*Link;
 /*���˵�*/
 void menu()
 {
 	system("cls");/*����DOS�����������clrscr����������ͬ*/
 	printf("The Students Grade Management System\n\n");
 	printf("****************Menu***************\n");
 	printf("*     1 input record            2 delete record* \n");
 	printf("*     3 search record           4 modify record* \n");
 	printf("*     5 insert record           6 count record* \n");
 	printf("*     7 sort record             8 save record* \n");
 	printf("*     9  display record         0 quit system* \n");
 	printf("***********************************\n");
 }
 void printheader()   /*��ʽ�������ͷ*/ 
 {
 	printf(HEADER1);
 	printf(HEADER2);
 	printf(HEADER3);
 }
 void printdata(Node*pp)    /*��ʽ�������������*/ 
 {
 	Node*p;
 	p=pp;
 	printf(FORMAT,DATA);
  } 
void Wrong()         /*�������������Ϣ*/ 
{
	printf("\n\n\n\n\n*****Error:input as wrong!press any key to continue*****\n");
	getchar();
}
void Nofind()   /*���δ���ҵ���ѧ����Ϣ*/ 
{
	printf("\n=====>Not find this student! \n");
}
void Disp(Link l)/*��ʾ������1�д洢��ѧ����¼������Ϊstudent�ṹ�ж�������� */
{
	Node*p;
	p=l->next;/*1�洢���ǵ�������ͷ�ڵ��ָ�룬��ͷ�ڵ�û�д洢ѧ����Ϣ��ָ����ָ��ĺ�̽ڵ����ѧ����Ϣ*/ 
	if(!p)
	{
		printf("\n=====>Not student record! \n");
		getchar();
		return;
	 } 
	 printf("\n\n");
	 printheader();/*��� ���ͷ��*/
	 while(p)
	 {
	 	printdata(p);
	 	p=p->next;
	 	printf("/n");
	  } 
}
	/*���ã����ڶ�λ�����з���Ҫ��Ľڵ㣬����findmess[]����Ҫ���ҵľ������ݣ�Locateofname�������ڵ�����1�в�ѯ��
	�����������Ľڵ㣨���ܲ�ֹһ������ַ����ָ�������� */
Node *Locateofnum(Link l,char findmess[])     /*��ѧ�Ų�ѯ*/
{
	Node*r;
	r=l->next;
	while(r)
	{
		if(strcmp(r->data.num,findmess)==0)/*���ҵ�findmessֵ��ѧ��*/
		return r;
		r=r->next;
	}
	return 0;    /*��δ�ҵ�������һ����ָ��*/ 
 } 
 void Locateofname(Link l,char findmess[],Node *n[])/*��������ѯ*/ 
 {
 	Node*r;
 	int i=0;
 	r=l->next;
 	while(r)
 	{
 		if(strcmp(r->data.name,findmess)==0)
 		n[i++]=r;/*���˷��ϲ��������ļ�¼ָ�����ָ��������*/
		r=r->next; 
	 }
  } 
  /*�����ַ����������г�����֤������<lens)*/
  void stringinput(char *t,int lens,char*notice)
  {
  	char n[255];
  	printf(notice);
  	scanf("%s",n);
  	while(strlen(n)>lens)
  	{
  		printf("\n exceed the required length! \n");
  		/*���г���У�飬����lensֵ��������*/
		  printf(notice);
		  scanf("%s",n); 
	  }
	  strcpy(t,n);   /*��������ַ����������ַ���t��*/ 
   } 
   /*���������Ҫ�������0~100֮��*/
   int numberinput(char *notice)
   {
   		int t=0;
   		printf(notice);
   		scanf("%d",&t);
   		while(t>100||t<0)
   		{
   			printf("\n score must in [0,100]!\n");    /*���з���У��*/
			printf(notice);
			scanf("%d",&t); 
		}
	   	return t;
	} 
	/*����ѧ���ļ�¼*/
	void Add(Link l)
	{
		Node *p,*r,*s;    /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
		char ch,flag=0,num[10];
		r=l;
		s=l->next;
		system("cls");
		Disp(l);  /*����ʾ�����е�ѧ����Ϣ*/
		while(r->next!=NULL) 
		r=r->next;/*��ָ������������ĩβ��׼����Ӽ�¼*/
		while(l)    /*һ�ο����������¼��ֱ������ѧ��Ϊ��ļ�¼������Ӳ���*/
		{
		while(1)         /*����ѧ�ţ���֤��ѧ��û�б�ʹ�ã�������ѧ��Ϊ0�����˳���Ӽ�¼����*/
		{
			stringinput(num,10,"input number(press'0'return menu):");
			flag=0;
			if(strcmp(num,"0")==0)/*����Ϊ�㣬���˳���Ӳ���������������*/
			{return ;} 
			s=l->next;
			while(s)    /*��ѯ��ѧ���Ƿ��Ѿ����ڣ���������Ҫ����������һ��δ��ռ�õ�ѧ��*/ 
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
		 p=(Node*)malloc(sizeof(Node));/*Ϊ������¼�����ڴ�ռ�*/
		 if(!p)
		 {
		 	printf("\n allocate memory failure");/*��û�����뵽����ӡ��ʾ��Ϣ*/
			 return; 
		  } 
		  strcpy(p->data.name,num);
		  stringinput(p->data.name,15,"Name:");
		  p->data.cgrade=numberinput("C language Score[0~100]:");
		  /*���벢У�����������������0~100֮��*/
		  p->data.mgrade=numberinput("Math Score[0~100]:");
		  p->data.egrade=numberinput("English Score[0~100]:"); 
		  p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade;
		  p->data.ave=(float)(p->data.total/3);
		  p->data.mingci=0;
		  p->next=NULL;          /*�������������β���ڵ�*/ 
		  r->next=p;         /*���½��Ľڵ��������β����*/
		  r=p;
		  saveflag=1;
		}
			return;
		}
		/*��ѧ�Ż���������ѯѧ����¼*/
		void Qur(Link l)
		{
			int select;   /*select ֵΪ1����ѧ�Ų飬2���������飬���������������棨�˵���*/
			char searchinput[20];    /*�����û�����Ĳ�ѯ����*/
			Node*p;
			Node*n[5]={NULL};    /*���ڴ�Ű��������ҵ����������Ľڵ��ָ������*/
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
			 	/*������1�в���ѧ��searchinputֵ�Ľڵ㣬�����ؽڵ��ָ��*/
				 if(p)
				 {
				 	printheader();/*��ʽ������ҵ��ķ��������ļ�¼*/
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
			 	/*������1�в�������Ϊsearchinputֵ�Ľڵ㣬�����ڵ��ָ�뱣��������n��*/
				 while((p=n[i++])!=NULL)/*��ʾ���ҵ��ķ������������ļ�¼ֱ��ָ��ΪNULL*/
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
		/*ɾ��ѧ����¼�����ҵ������ѧ����¼�Ľڵ㣬Ȼ��ɾ���ýڵ�*/
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
			 /*����Ҫɾ����ѧ��*/
			 getchar();
			 p=Locateofnum(l,findmess);/*ָ�붨λ��Ҫɾ����λ��*/
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
		/*�޸�ѧ���ļ�¼*/
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
			saveflag=1;/*��main���жԸ�ȫ�ֱ������жϣ���Ϊ1������д��̲���*/
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
		 
		 
		 
		 /*ͳ�Ƹð���ֵܷ�һ���͵��Ƶ�һ���͸���0~59��60~69��70~79��80~89��90~100���������ε�����*/
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
			 /*��׷�ӷ�ʽ��һ���������ļ����ɶ���д�������ļ������ڣ��ᴴ�����ļ�*/
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
					case 1: Add(l);break;           /*����ѧ����¼*/ 
					case 2: Del(l);break;           /*ɾ��ѧ����¼*/ 
					case 3:Qur(l);break;			/*��ѯѧ����¼*/ 
					case 4:Modify(l);break;			/*�޸�ѧ����¼*/ 
					case 5:Insert(l);break;			/*����ѧ����¼*/ 
					case 6:Count(l);break;			/*ͳ��ѧ����¼*/ 
					case 7:Sort(l);break;			/*����ѧ����¼*/ 
					case 8:Save(l);break;			/*����ѧ����¼*/ 
					case 9:system("cls");Disp(l);break;	/*��ʾѧ����¼*/ 
					default:Wrong();getchar();break;	/*�������󣬱���Ϊ��ֵ0~9*/ 
				}
			}
			return 0;
		 }
		 
		  
		 
	
   
