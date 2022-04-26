#ifndef __MENU_H
#define __MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct _menu
{
    struct _menu * last;//父极菜单指针
    struct _menu * same_last;//同级菜单下一项指针
    struct _menu * same_next;//同级菜单上一项指针
    char * menu_name;//当前功能名称
    int id;//当前功能号
    void (*funsion)();//功能
    struct _menu*next;//子级菜单
  
}menu_t;

struct {
menu_t *now;//当前链表位置
int ctrl;
char input;
}sys_info;


menu_t * set_page(menu_t * head,int num);//输入为页的表头
menu_t*add_funsion(menu_t *head,void * fun,char * str);  //添加一个功能 head为该界面的第一项，自动在该界面后添加一项功能
menu_t * add_child(menu_t *head);//添加子级
void fun1();
void kong();//空函数
void set_fun(menu_t *menu,void * fun,char * str);//设置函数和功能
void switch_input();//判断输入
void *thread_menu(void *arg);//
void menu_init(void);//菜单初始化
int menu_create();//创建菜单


#endif
