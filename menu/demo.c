#include "menu.h"



void main()
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
    while(1)
    {
        switch_input();
    }

}

