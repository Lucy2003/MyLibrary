#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "CMmsw.h"

int menu=1;

void Menu1(){
    ReInitMenu(4,0,"C/C++�����в˵�����",1);
    SetMenuPos(-1,9);
    SetMenuSize(40,10,20);
    SetMenuColor(1,15,4,15);
    AddMenu(0,"[01]   ˢ�²˵�! ","ɶҲ����",0);
    AddMenu(1,"[02] ת���¼��˵�","�¼��˵���ѡ�����",0);
    AddMenu(2,"[03]     ����    ","��ʾ�����Ϣ",1);
    AddMenu(3,"[04]     �˳�    ","�˳����Գ���",1);
    menu=1;
}

void Menu2(){
    ReInitMenu(2,1,"�����˵�",0);
    SetMenuPos(25,9);
    SetMenuSize(30,9,25);
    AddMenu(0,"[01]   �����ϼ��˵�  ","�����ϼ��˵�",0);
    AddMenu(1,"[02] ��ӡ Hello World","��ӡ Hello World ��֮ǰ��괦�������ش˲˵�",0);
    menu=2;
}
int main()
{
    //for (int i=0;i<80*50;i++) printf("A");
    SetTitle("C/C++�����в˵�����");
    InitMenu();
    for(;;){
        if (menu==1) Menu1();
        if (menu==2) Menu2();
        unsigned int ret=ListenMenu();
        if (menu==1){
            switch(ret){
                case 0:break;
                case 1:menu=2;break;
                case 2:/*RestoneCursorPos();*/printf("\nC/C++ Console Menu Library V1.0.0\n�����������...\n");getch();break;
                case 3:return 0;
                case 255:printf("ESC.Exit...");Sleep(800);return 0;
            }
        }else{
            switch(ret){
                case 0:menu=1;break;
                case 1:RestoneCursorPos();printf("Hello World!");break;
                case 255:menu=1;break;
            }
        }
    }
    return 0;
}
