#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"



menu_t * set_page(menu_t * head,int num)//输入为页的表头
{
    for(int i=0;i<num;i++)
    {
        if(head->same_next!=NULL)
        head=head->same_next;
        else
        {
            printf("超出当前功能号\n");
        }

    }
     if(head->next!=NULL)
    head=head->next;
    else
    {

        printf("创建子菜单\n");
    menu_t *p = NULL;
	p = (menu_t *)malloc(sizeof(menu_t)) ;
	if(p == NULL){
		printf("NO enough momery to allocate!\n");
		exit(0);
	}

		head->next=p;
        p->last=head;
        p->id=0;//当前功能号为0
        p->same_last=NULL;
        p->same_next=NULL;
        return p;
    }

    return head;
}

menu_t*add_funsion(menu_t *head,void * fun,char * str){    //添加一个功能 head为该界面的第一项，自动在该界面后添加一项功能
	menu_t *p = NULL,*pr = head;   
    
	p = (menu_t *)malloc(sizeof(menu_t)) ; 
	if(p == NULL){		
		printf("NO enough momery to allocate!\n");
		exit(0);
	}
	if(head == NULL){		
		head = p;	//head为空，创建头节点	
        printf("创建头节点\n");						
	}else{				//如果不是创建头节点	
        int i=1;					                       
		while(pr->same_next!= NULL){		//找到同级菜单最后的表
        {
            i++;
            pr = pr->same_next;
        }
			
		}
		pr->same_next = p;	//在同级菜单尾部创建一个功能
        p->same_last=pr;
        p->last=head->last;
       
       
        p->id=i;
	}
     p->funsion=fun;
	 p->menu_name=str;
	p->same_next = NULL;//下一个同级功能为空
    p->next=NULL;			//下一个子集功能为空
	return head;		
}
 menu_t * add_child(menu_t *head)//添加子级
{
    	menu_t *p = NULL;   
	p = (menu_t *)malloc(sizeof(menu_t)) ; 
	if(p == NULL){		
		printf("NO enough momery to allocate!\n");
		exit(0);
	}
	if(head == NULL){		
		printf("输入head错误，添加子级失败\n");							
	}else{										                       
		head->next=p;
        p->last=head;
        p->same_last=NULL;
        p->same_next=NULL;
	}
    return p;
}
void fun1()
{
   printf("%s","\033[1H\033[2J");//linux下的清屏函数,window下请用system("cls");
    printf("使用键盘选择以下功能\n");
    if(sys_info.now->last!=NULL)//如果父极不为空
    {
        menu_t * start=sys_info.now->last->next;//start指向同级第一个
        while(start!=NULL)//将所有功能打在屏幕上,如果功能和选中功能一样,变色
        {
            
            if(start->menu_name==sys_info.now->menu_name)//
            {
                printf(">>********%s*********<<\n",start->menu_name);
            }
            else
            {
                printf("    ****%s****\n",start->menu_name);
            }
            start=start->same_next;

        }
    }
    else
    {
        printf("父极为空");
    }


}
void kong()//空函数
{
    printf("%s","\033[1H\033[2J");//linux下的清屏函数,window下请用system("cls");
    printf("***多级菜单显示****");
}
void set_fun(menu_t *menu,void * fun,char * str)//设置函数和功能
{
        menu->funsion=fun;
        menu->menu_name=str;
}
void switch_input()//判断输入
{
  

    scanf("%c", & sys_info.input);//把a仍给系统，交给对应函数处理
    if (sys_info.ctrl)//按键控制链表
    {
        switch (sys_info.input)
    {
     case 'w'://上
     if(sys_info.now->same_last!=NULL)
     sys_info.now=sys_info.now->same_last;
     
        break;
         case 's'://下
         if(sys_info.now->same_next!=NULL)
         sys_info.now=sys_info.now->same_next;
      
        break;
         case 'a':// 左相当于返回
         if(sys_info.now->last!=NULL)
         sys_info.now=sys_info.now->last;
     
        break;
         case 'd'://右相当于确认
     if(sys_info.now->next!=NULL)
         sys_info.now=sys_info.now->next;
        break;
    
    default:
        break;
    }
        sys_info.now->funsion();
    }
}


void menu_init(void)
{
    sys_info.ctrl=1;

    menu_t *head=NULL;
    head=add_funsion(head,kong,"添加头节点");//添加头节点

    menu_t *first=set_page(head,0);//主页面
    set_fun(first,fun1,"第一页选项一");
    add_funsion(first,fun1,"第一页选项二");
    add_funsion(first,fun1,"第一页选项三");


    menu_t *second=set_page(first,0);//第一个功能的页面 二级菜单
    set_fun(second,fun1,"选项一的选项一");
    add_funsion(second,fun1,"选项一的选项二");
    add_funsion(second,fun1,"选项一的选项三");
    sys_info.now=first;

    menu_t *three=set_page(first,1);//第一个功能的页面 二级菜单
    set_fun(three,fun1,"选项二的选项一");
    add_funsion(three,fun1,"选项二的选项二");
    add_funsion(three,fun1,"选项二的选项三");

    menu_t *four=set_page(second,0);//第一个功能的页面的第一个页面  三级菜单
    set_fun(four,fun1,"选项一的选项一的选项一");
    add_funsion(four,fun1,"选项一的选项一选项二");
    add_funsion(four,fun1,"选项一的选项一选项三");
    fun1();
    sys_info.now=first;
}


void *thread_menu(void *arg)
{

   menu_init();
    while(1)
    {
        switch_input();
	if(sys_info.input == 'q')
	{
		break;
	}
    
    }
    printf("%s","\033[1H\033[2J");
    printf("%s: menu exit\n",__FUNCTION__);
    pthread_exit(NULL);

}

int menu_create()
{
	pthread_t id;
	if (pthread_create(&id,NULL,thread_menu,NULL))
	{
		printf("error creating thread.\n");
	}
	pthread_join(id,NULL);
	//pthread_detach(id);

}
#if 0 
int main()
{
	menu_create();
	printf("succus\n");
	
	while(1)
	{
		sleep(1);
	}
        //pthread_detach(id);

}
#endif


#if 0
int main()
{
	pthread_t id;
        if (pthread_create(&id,NULL,thread_menu,NULL))
        {
                printf("error creating thread.\n");
        }
        pthread_join(id,NULL);

}
#endif

