/*
Copyright (C) 2002 Vineeth Kaimal
email: edeater2001@yahoo.com

This program is free software; you can redistribute it and/or modify it under the terms of 
the GNU General Public License as published by the Free Software Foundation; either version 2 
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; 
if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <ncurses.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

#include "keys.h"

int DELAY=600;          //for the press button

class hmenu
{
        int opt,totopt;
        char options[7][10];
        int x,y;
        public:
        hmenu(char [7][10],int,int,int,int);
        void display(),press(int);
        int select();
};

hmenu :: hmenu(char ptr[7][10],int o,int to,int yy,int xx)
{
        opt=o;
        totopt=to;
         for(int i=0;i<totopt;i++)
         strcpy(options[i],ptr[i]);
         x=xx;
         y=yy;
}

void hmenu :: display()
{
        WINDOW *main=newwin(1,totopt*12,y,x);
        WINDOW *smain=newwin(1,totopt*12,y+1,x+1);
        WINDOW *selected=newwin(1,12,y,x+opt*12);

        for(int i=0;i<totopt;i++)
        wprintw(main," %-11s",options[i]);
        wprintw(selected," %s",options[opt]);
        wbkgd(main,COLOR_PAIR(3));
        wbkgd(smain,COLOR_PAIR(7));
        wbkgd(selected,COLOR_PAIR(4));
        wrefresh(smain);
        wrefresh(main);
        wrefresh(selected);
        delwin(main);
        delwin(smain);
        delwin(selected);
}

void hmenu :: press(int delay=300)
{
        WINDOW *selected=newwin(1,12,y,x+opt*12);
        wbkgd(selected,COLOR_PAIR(7));
        wrefresh(selected);
        delwin(selected);
        selected=newwin(1,12,y+1,x+opt*12+1);
        wprintw(selected," %s",options[opt]);
        wbkgd(selected,COLOR_PAIR(4));
        wrefresh(selected);
        delwin(selected);
        for(int i=0;i<delay;i++)        //delay
        for(int j=0;j<=30000;j++);
        display();
}

int hmenu :: select()
{
        while(1)
        {
                display();
                int ch =getch();
                if(isalpha(ch))
                {
                        int j=0;
                        for(int i=0;i<=totopt;i++)
                        if(i==totopt)
                        {
                                i=-1; j++;
                        }
                        else if(j==10)
                        break;
                        else if(options[i][j]==ch)
                        {
                                opt=i;
                                break;
                        }
                }
                else if(isdigit(ch))
                opt=(ch-1)-'0';
                else if(ch==RIGHT)
                opt++;
                else if(ch==LEFT)
                opt--;
                else if(ch==UP)
                return -1;
                else if(ch==ENTER||ch==DOWN)  //preferred to returning -2 for down
                return opt;
                else
                return -3;
                if(opt>=totopt)
                opt=0;
                if(opt<0)
                opt=totopt-1;
        }
}

class vmenu
{
        int opt,totopt;
        char options[10][10];
        char name[10];
        int x,y;
        public:
        vmenu(char [10][10],char *,int,int,int,int);
        void display(),set(char [10][10],char *,int,int,int,int);
        int select();
};


vmenu :: vmenu(char ptr[10][10],char *nm,int o,int to,int yy,int xx)
{
        opt=o;
        totopt=to;
        strcpy(name,nm);
         for(int i=0;i<totopt;i++)
         strcpy(options[i],ptr[i]);
         x=xx;
         y=yy;
}

void vmenu :: set(char ptr[10][10],char *nm,int o,int to,int yy,int xx)
{
        opt=o;
        totopt=to;
        strcpy(name,nm);
         for(int i=0;i<totopt;i++)
         strcpy(options[i],ptr[i]);
         x=xx;
         y=yy;
}

void vmenu :: display()
{
        WINDOW *main=newwin(totopt+1,12,y,x);
        WINDOW *smain=newwin(totopt+1,12,y+1,x+1);
        WINDOW *selected=newwin(1,12,y+opt+1,x);

        wbkgd(main,COLOR_PAIR(3));
        wbkgd(smain,COLOR_PAIR(7));
        wbkgd(selected,COLOR_PAIR(4));

        wprintw(main," -%s-\n",name);
        for(int i=0;i<totopt;i++)
        wprintw(main," %s\n",options[i]);
        wprintw(selected," %s",options[opt]);
        
        wrefresh(smain);
        wrefresh(main);
        wrefresh(selected);
        delwin(main);
        delwin(smain);
        delwin(selected);
}

int vmenu :: select()
{
        while(1)
        {
                display();
                int ch =getch();

                if(isalpha(ch))
                {
                        int j=0;
                        for(int i=0;i<=totopt;i++)
                        if(i==totopt)
                        {
                                i=-1; j++;
                        }
                        else if(j==10)
                        break;
                        else if(options[i][j]==ch)
                        {
                                opt=i;
                                break;
                        }
                }
                else if(isdigit(ch))
                opt=(ch-1)-'0';
                else if(ch==DOWN)
                opt++;
                else if(ch==UP)
                opt--;
                else if(ch==LEFT)
                return -1;
                else if(ch==RIGHT)
                return -2;
                else if(ch==ENTER)
                return opt;
                else
                return -3;
                if(opt>=totopt)
                opt=0;
                if(opt<0)
                opt=totopt-1;
        }
}

class fmenu
{
        int opt,totopt;
        char options[10][30];
        char name[30];
        int x,y;
        public:
        fmenu(char [10][30],char *,int,int,int,int);
        fmenu();
        void display(),set(char [10][30],char *,int,int,int,int);
        int select();
};

fmenu :: fmenu()
{
}

fmenu :: fmenu(char ptr[10][30],char *nm,int o,int to,int yy,int xx)
{
        opt=o;
        totopt=to;
        strcpy(name,nm);
         for(int i=0;i<totopt;i++)
         strcpy(options[i],ptr[i]);
         x=xx;
         y=yy;
}

void fmenu :: set(char ptr[10][30],char *nm,int o,int to,int yy,int xx)
{
        opt=o;
        totopt=to;
        strcpy(name,nm);
         for(int i=0;i<totopt;i++)
         strcpy(options[i],ptr[i]);
         x=xx;
         y=yy;
}

void fmenu :: display()
{
        WINDOW *main=newwin(totopt+1,32,y,x);
        WINDOW *smain=newwin(totopt+1,32,y+1,x+1);
        WINDOW *selected=newwin(1,32,y+opt+1,x);

        wprintw(main," -%s-\n",name);
        for(int i=0;i<totopt;i++)
        wprintw(main," %s\n",options[i]);
        wprintw(selected," %s",options[opt]);
        wbkgd(main,COLOR_PAIR(3));
        wbkgd(smain,COLOR_PAIR(7));
        wbkgd(selected,COLOR_PAIR(4));
        wrefresh(smain);
        wrefresh(main);
        wrefresh(selected);
        delwin(main);
        delwin(smain);
        delwin(selected);
}

int fmenu :: select()
{
        while(1)
        {
                display();
                int ch =getch();

                if(isalpha(ch))
                {
                        int j=0;
                        for(int i=0;i<=totopt;i++)
                        if(i==totopt)
                        {
                                i=-1; j++;
                        }
                        else if(j==10)
                        break;
                        else if(options[i][j]==ch)
                        {
                                opt=i;
                                break;
                        }
                }
                else if(isdigit(ch))
                opt=(ch-1)-'0';
                else if(ch==DOWN)
                opt++;
                else if(ch==UP)
                opt--;
                else if(ch==LEFT)
                return -1;
                else if(ch==RIGHT)
                return -2;
                else if(ch==ENTER)
                return opt;
                else
                return -3;
                if(opt>=totopt)
                opt=0;
                if(opt<0)
                opt=totopt-1;
        }
}

class question
{
        int x,y;
        public:
        question(int,int);
        int ask(char *,int,int,int);
};

question :: question(int yy=15,int xx=10)
{
        y=yy;
        x=xx;
}

int question :: ask(char *q,int opt=3,int yy=-1,int xx=-1)
{
        if(xx!=-1)
        x=xx;
        if(yy!=-1)
        y=yy;
        WINDOW *main=newwin(6,60,y,x);
        WINDOW *smain=newwin(6,60,y+1,x+1);
        wprintw(main,"\n %s",q);
        wbkgd(main,COLOR_PAIR(5));
        wbkgd(smain,COLOR_PAIR(7));
        wrefresh(smain);
        wrefresh(main);
        delwin(smain);
        char bar_arr[7][10]={"Yes","No","Cancel"};
        int j;
        if(opt==3)
                j=3;
        else
                j=2;
        hmenu bar(bar_arr,0,j,y+3,x+15);
        j=bar.select();
        if(j>=0)
        bar.press(DELAY);
        wbkgd(main,COLOR_PAIR(7));
        wrefresh(main);
        delwin(main);
        return j;
}


class input
{
        int x,y;
        public:
        input(int,int);
        char* getinput(char*,char *,int,int);
        int getnum(char*,int*,int,int);
};

input :: input(int yy=15,int xx=10)
{
        y=yy;
        x=xx;
}

char * input :: getinput(char *q,char *ip,int yy=-1,int xx=-1)
{
        if(xx!=-1)
        x=xx;
        if(yy!=-1)
        y=yy;
        WINDOW *main=newwin(6,60,y,x);
        WINDOW *smain=newwin(6,60,y+1,x+1);
        WINDOW *ipwin=newwin(1,50,y+3,x+4);
        wprintw(main,"\n %s",q);
        wbkgd(main,COLOR_PAIR(5));
        wbkgd(smain,COLOR_PAIR(7));
        wbkgd(ipwin,COLOR_PAIR(8));
        wmove(ipwin,0,0);
        wrefresh(smain);
        wrefresh(main);
        wrefresh(ipwin);
        echo();
        wscanw(ipwin," %[^\n]",ip);
        noecho();
        wbkgd(main,COLOR_PAIR(7));
        wrefresh(main);
        delwin(main);
        delwin(smain);
        delwin(ipwin);
        return ip;
}

int input :: getnum(char *q,int *ip,int yy=-1,int xx=-1)
{
        if(xx!=-1)
        x=xx;
        if(yy!=-1)
        y=yy;
        WINDOW *main=newwin(6,60,y,x);
        WINDOW *smain=newwin(6,60,y+1,x+1);
        WINDOW *ipwin=newwin(1,20,y+3,x+4);
        wprintw(main,"\n %s",q);
        wbkgd(main,COLOR_PAIR(5));
        wbkgd(smain,COLOR_PAIR(7));
        wbkgd(ipwin,COLOR_PAIR(8));
        wmove(ipwin,0,0);
        wrefresh(smain);
        wrefresh(main);
        wrefresh(ipwin);
        echo();
        wscanw(ipwin," %d",ip);
        noecho();
        wbkgd(main,COLOR_PAIR(7));
        wrefresh(main);
        delwin(main);
        delwin(smain);
        delwin(ipwin);
        return *ip;
}

class message
{
        int x,y;
        public:
        message(int,int);
        void show(char *,int,int);
};

message :: message(int yy=15,int xx=10)
{
        y=yy;
        x=xx;
}

void message :: show(char *q,int yy=-1,int xx=-1)
{
        if(xx!=-1)
        x=xx;
        if(yy!=-1)
        y=yy;
        WINDOW *main=newwin(6,60,y,x);
        WINDOW *smain=newwin(6,60,y+1,x+1);
        wprintw(main,"\n %s",q);
        wbkgd(main,COLOR_PAIR(5));
        wbkgd(smain,COLOR_PAIR(7));
        wrefresh(smain);
        wrefresh(main);
        delwin(smain);
        char bar_arr[7][10]={"OK"};
        hmenu bar(bar_arr,0,1,y+3,x+15);
        bar.select();
        bar.press(DELAY);
        wbkgd(main,COLOR_PAIR(7));
        wrefresh(main);
        delwin(main);
}
