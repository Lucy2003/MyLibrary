/* C/C++ ����̨�˵���(Windows)

�˿�ʵ�ֿ���̨�˵�ѡ��ʹ�ü������ϡ����¼�ѡ��
û��ʹ��system(...)�������������¼��Կ�������ȡ��

ʹ�÷�����

int main(){
    SetTitle("�˵�����");  //���ÿ���̨���ڱ��⣬��ѡ��
    InitMenu();//ֻ��ִ��һ�Σ���ȡ����̨OUT���
    ReInitMenu(unsigned int �˵�����,unsigned int Ĭ����ID,char* �˵�����,int �Ƿ�����ػ�ѡ�񣬷����ʾ����);
    SetMenuSize(unsigned int �˵����,unsigned int �˵��߶�,unsigned int ѡ�и������,��Ϊ0);  //���ò˵���С,��ѡ��
    SetMenuColor(unsigned short ����ɫ,unsigned short ǰ��ɫ,unsigned short ��������ɫ,unsigned short ����ǰ��ɫ);  //���ò˵���ɫ����ѡ��
    SetMenuPos(unsigned int X,unsigned int Y); //���ò˵�λ�ã�
    AddMenu(unsigned int �˵�ID,char* �˵�����,char* �˵�����,unsigned short �˵��飬�밴˳����,��С��0); //��Ӳ˵���
    unsigned int ret=ListenMenu(); //�����˵�����ѡ���򷵻ز˵�ID,��ESC����255
    return 0;
}

ע��1.�ٴ�ִ��ReInitMenu,֮ǰ�Ĳ˵����������
    2.ListenMenu���غ����λ��Ĭ��Ϊ�˵������Ͻǣ���Ҫ���ص���ǰ���꣬�����
            RestoneCursorPos();
    3.������ò˵���ʾ�ڵ�ǰ�е���һ�У���ʹ�� SetMenuPos(-1,-1);
    4.SetMenuPos , SetMenuSize , SetMenuColor ������ȫ�ֵġ�
*/

#ifndef __CMMSW_H__
#define __CMMSW_H__

#ifdef __cplusplus
extern "C"{
#endif
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

unsigned int MenuSize = 0;
unsigned int MenuIndex = 0;
unsigned int MenuFGSize=0;
unsigned int MenuMaxWidth=79;
unsigned int MenuMaxHeight=24;
unsigned short MenuBGColor=0;
unsigned short MenuFColor=7;
unsigned short MenuHBColor=7;
unsigned short MenuHFColor=0;
unsigned int MenuHeightLightLen=0;
unsigned int MenuX,MenuY=0;
short MenuLoop =1;
short MenuGetCPos=1;
short MenuPosNext=0; //��ǰ����������ʾ�˵���־λ

COORD BeforePos = {0,0};
HANDLE hOut;

struct MenuItem_t {
    unsigned int StartX;
    unsigned int StartY;
    char *MenuTitle;
    char *MenuDesc;
    unsigned short MenuGroup;
};

struct MenuItem_t MenuItems[64];
short defaultIndex[64];
char *MenuHTitle="MainMenu";

enum
{
	UP = 72,
	DOWN = 80 ,
	ENTER = 13 ,
	ESC = 27 ,
};


int  GetUserInput(){
	int ch ;
	ch = getch();
	switch(ch)
	{
		case UP : if(MenuIndex > 0){MenuIndex -= 1;}else{if(MenuLoop!=0) MenuIndex=MenuSize-1;}break;
		case DOWN :if(MenuIndex < MenuSize -1){MenuIndex += 1;}else{if(MenuLoop!=0) MenuIndex=0;}break;
		case '1':if (MenuSize>=1) MenuIndex=0;break;
		case '2':if (MenuSize>=2) MenuIndex=1;break;
		case '3':if (MenuSize>=3) MenuIndex=2;break;
		case '4':if (MenuSize>=4) MenuIndex=3;break;
		case '5':if (MenuSize>=5) MenuIndex=4;break;
		case '6':if (MenuSize>=6) MenuIndex=5;break;
		case '7':if (MenuSize>=7) MenuIndex=6;break;
		case '8':if (MenuSize>=8) MenuIndex=7;break;
		case '9':if (MenuSize>=9) MenuIndex=8;break;
		//case '0':if (MenuSize>=0) MenuIndex=9;break;
		case ENTER: return ENTER ; //Enter
		case ESC: return ESC ;  //ESC
	}
	return 0 ;
}

void CleanMenu(){
    MenuIndex=0;
    MenuSize=0;
    for (int i=0;i<64;i++){
        MenuItems[i].MenuTitle="";
        MenuItems[i].MenuDesc="";
        defaultIndex[i]=0;
        MenuItems[i].MenuGroup=0;
    }
}

void SetMenuSize(unsigned int MaxWidth,unsigned int MaxHeight,unsigned int HighLightLen){
    MenuMaxWidth=MaxWidth;
    MenuMaxHeight=MaxHeight;
    MenuHeightLightLen=HighLightLen;
}

void SetMenuColor(unsigned short BGColor,unsigned short FColor,unsigned short HBColor,unsigned short HFColor){
    MenuBGColor=BGColor;
    MenuFColor=FColor;
    MenuHBColor=HBColor;
    MenuHFColor=HFColor;
}

void SetMenuPos(int X, int Y){
    MenuPosNext=0;
    MenuX=X;
    MenuY=Y;
    if (X<0||Y<0){MenuPosNext=1;MenuX=0;}
}

void SetTitle(char *Title){
    SetConsoleTitleA(Title);
}

void InitMenu(){ //Don't Run twice!
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ReInitMenu(unsigned int MenuCount,unsigned int DefaultIndex,char *MenuTitle,short Loop){
    CleanMenu();
    MenuHTitle=MenuTitle;
    MenuSize=MenuCount;
    MenuIndex=DefaultIndex;
    defaultIndex[DefaultIndex]=1;
    MenuLoop=Loop;
}

void AddMenu(unsigned int MenuID,char *MenuTitle,char *MenuDesc,unsigned short MenuGroup){
    MenuItems[MenuID].StartY=MenuY+MenuID+2+MenuGroup;
    MenuItems[MenuID].StartX=MenuX+(MenuMaxWidth-strlen(MenuTitle))/2;
    MenuItems[MenuID].MenuTitle=MenuTitle;
    MenuItems[MenuID].MenuDesc=MenuDesc;
    MenuItems[MenuID].MenuGroup=MenuGroup;
}

void SetCurPos(unsigned int x,unsigned int y){
    COORD pos={x,y};
    SetConsoleCursorPosition(hOut,pos);
}

void RestoneCursorPos(){
    SetCurPos(BeforePos.X,BeforePos.Y);
    MenuGetCPos=1;
}

void SetCurEnabled(int Enabled){
    if(Enabled==0 && MenuGetCPos==1){
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hOut, &csbi);
        BeforePos.X=csbi.dwCursorPosition.X;
        BeforePos.Y=csbi.dwCursorPosition.Y;
        MenuGetCPos=0;
    }
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);//��ȡ����̨�����Ϣ
    cci.bVisible = Enabled;
    //cci.dwSize = sizeof(cci);
    SetConsoleCursorInfo(hOut, &cci);

}

void FillMenuArea(int ISCLS){
    SetCurPos(MenuX,MenuY);DWORD temp;
    WORD color=(MenuFColor%16)|(MenuBGColor%16*16);
    DWORD length=MenuMaxWidth;
    for (int y=0;y<MenuMaxHeight;y++){
        for (int x=MenuX;x<MenuMaxWidth+MenuX;x++){
            SetCurPos(x,y+MenuY);
            if (ISCLS==0 && (y==1 || y==MenuMaxHeight -3)){
                printf("-");
            }else{
                printf(" ");
            }
            COORD wpos={MenuX,MenuY+y};
            if (ISCLS==0)
                FillConsoleOutputAttribute(hOut,color,length,wpos,&temp);
        }
    }
    SetCurPos(MenuX,MenuY);
}

void PrintMenuDesc(unsigned int MenuID){
    WORD color=(MenuFColor%16)|(MenuBGColor%16*16);
    DWORD temp;
    char *Descs=MenuItems[MenuID].MenuDesc;
    char Desc[MenuMaxWidth*2 +1];
    unsigned int Dsize=strlen(Descs);
    strncpy(Desc,Descs,2*MenuMaxWidth);
    for(unsigned int i=Dsize;i<2*MenuMaxWidth;i++){
        Desc[i]=' ';
    }
    Desc[2*MenuMaxWidth]='\0';
        char OutStr[MenuMaxWidth+2];
        strncpy(OutStr,Desc+0,MenuMaxWidth);
        OutStr[MenuMaxWidth]='\0';
        SetCurPos(MenuX,MenuY+MenuMaxHeight-2);
        printf("%s",OutStr);
        COORD wpos={MenuX,MenuY+MenuMaxHeight-2};
        DWORD length=strlen(OutStr);
        FillConsoleOutputAttribute(hOut,color,length,wpos,&temp);
        //Line2
        char OutStr2[MenuMaxWidth+2];
        strncpy(OutStr2,Desc+MenuMaxWidth,MenuMaxWidth);
        OutStr2[MenuMaxWidth]='\0';
        SetCurPos(MenuX,MenuY+MenuMaxHeight-1);
        printf("%s",OutStr2);
        COORD wpos2={MenuX,MenuY+MenuMaxHeight-1};
        DWORD length2=strlen(OutStr2);
        FillConsoleOutputAttribute(hOut,color,length2,wpos2,&temp);

    SetCurPos(MenuX,MenuY);
}


void PrintMenu(unsigned int MenuID,short HightLight){
    WORD color;
    if (HightLight==0){
        color=(MenuFColor%16)|(MenuBGColor%16*16);
    }else{
        color=(MenuHFColor%16)|(MenuHBColor%16*16);
    }
    unsigned int MenuIX=MenuItems[MenuID].StartX;
    unsigned int MenuIY=MenuItems[MenuID].StartY;
    short MenuIG=MenuItems[MenuID].MenuGroup;
    if (MenuPosNext==1) MenuIY= BeforePos.Y+MenuID+3+MenuIG; //����Y����
    SetCurPos(MenuIX,MenuIY);
    printf("%s",MenuItems[MenuID].MenuTitle);
    COORD wpos={0,MenuIY};
    DWORD length;
    if (MenuHeightLightLen==0){
        length=strlen(MenuItems[MenuID].MenuTitle);
        wpos.X=MenuItems[MenuID].StartX;
    }else{
        length=MenuHeightLightLen;
        wpos.X=MenuX+(MenuMaxWidth-MenuHeightLightLen)/2;
    }
    DWORD temp;
    FillConsoleOutputAttribute(hOut,color,length,wpos,&temp);
    SetCurPos(MenuX,MenuY);
}


void DrawMenu(){
    FillMenuArea(0);
    SetCurPos(MenuX+(MenuMaxWidth-strlen(MenuHTitle))/2,MenuY);
    printf("%s",MenuHTitle);
    WORD color=(MenuFColor%16)|(MenuBGColor%16*16);
    COORD wpos={MenuX+(MenuMaxWidth-strlen(MenuHTitle))/2,MenuY};
    DWORD length=strlen(MenuHTitle);
    DWORD temp;
    FillConsoleOutputAttribute(hOut,color,length,wpos,&temp);
    for (int i=0;i<MenuSize;i++){
        PrintMenu(i,defaultIndex[i]);
    }
    PrintMenuDesc(MenuIndex);
}

unsigned int ListenMenu(){
    SetCurEnabled(0);
    if (MenuPosNext==1){
        MenuX=0;
        MenuY=BeforePos.Y+1;
    }
    DrawMenu();
    unsigned int LastIndex=MenuIndex;
    for(;;){
        int ret = GetUserInput();
        if (ret==0){
            if (LastIndex!=MenuIndex){
                PrintMenu(MenuIndex,1);
                PrintMenu(LastIndex,0);
                PrintMenuDesc(MenuIndex);
                LastIndex=MenuIndex;
            }
        }else if (ret==ESC){
            FillMenuArea(1);
            if (MenuPosNext==1) RestoneCursorPos();
            SetCurEnabled(1);
            return 255;
        }else if (ret==ENTER){
            FillMenuArea(1);
            if (MenuPosNext==1) RestoneCursorPos();
            SetCurEnabled(1);
            return MenuIndex;
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif // __CMMSW_H__
