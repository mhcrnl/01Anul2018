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
#include <stdlib.h>
#include <unistd.h>

int BEEP=0;
char SWAP1[100],SWAP2[100],SWAP3[100],CFG[100],COMPILEFILE[100];

#include "keys.h"
#include "edlist.cpp"
#include "edmenu.cpp"
#include "edconfig.cpp"
#include "edlogo.cpp"
#include "edmulti.cpp"

main(int argc,char **argv)
{
        strcpy(SWAP1,".ed.sw1.");
        strcpy(SWAP2,".ed.sw2.");
        strcpy(SWAP3,".ed.sw3.");
        strcpy(CFG,"ed.cfg.");
        strcpy(COMPILEFILE,"ed.");
        strcat(COMPILEFILE,getlogin());
        strcat(COMPILEFILE,".cpp");
        strcat(SWAP1,getlogin());
        strcat(SWAP2,getlogin());
        strcat(SWAP3,getlogin());
        strcat(CFG,getlogin());

        char *temp;             //used for temporaray prposes, eg while opening a file using open in menu
        int tempno;
        question edq;
        input edi;
        message edm;
        edconfig edc;
        char string[255]="";                         //blank string used for searching
        char lastcom[100]="";
        char filename[255]="noname.txt";    //the default file opened
        char tempstring[255];                   //as the name suggests
        void initial(),final();                           //starting and ending program
        initial();
        curs_set(0);
        printw("Loading... ");
        refresh();
        void edlogo(),edhelp(),edclean();
        char *edopen(WINDOW *,WINDOW*,char*);
        char *edsave(char *,doc &);
        void edcompile(doc&),edrun();
        int edshudisave(char*,doc&);
        int menuhandler(WINDOW*,WINDOW*);
        int edsethmargins(),edsetvmargins();
        WINDOW *edit,*help,*status;             //the main windows
        WINDOW *B=newwin(23,80,1,0);
        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);             //editscreen
        help=newwin(1,80,24,0);        //helpbar
        status=newwin(1,80,0,0);       //statusbar
        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
        wbkgd(help,COLOR_PAIR(8)|WA_BOLD);
        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);

        if(argc>1)
        strcpy(filename,argv[1]);

        int locx=0+LMARGIN,locy=TMARGIN,i;                          //screen cursor position
        doc *block=new doc;                                       //the document object named block - the editor does all functions on block
        dochandler dc;

        tempno=block->load(filename,status);       //loading blank file
        dc.adddoc(&block,filename,&locx,&locy);
        if(!strcmp(filename+strlen(filename)-2,".c")||!strcmp(filename+strlen(filename)-2,".C")||!strcmp(filename+strlen(filename)-4,".cpp")||!strcmp(filename+strlen(filename)-2,".cxx"))
        {
                HIGHLIGHT=1;
                AUTOINDENT=1;
        }
        else
        {
                HIGHLIGHT=0;
                AUTOINDENT=0;
        }

        tempno=2;
        if(argc>2)
        while(tempno<=argc-1&&tempno<=8)
        {
                dc.update(&block,filename,locx,locy);
                strcpy(filename,argv[tempno]);
                if(!strcmp(filename+strlen(filename)-2,".c")||!strcmp(filename+strlen(filename)-2,".C")||!strcmp(filename+strlen(filename)-4,".cpp")||!strcmp(filename+strlen(filename)-2,".cxx"))
                {
                        HIGHLIGHT=1;
                        AUTOINDENT=1;
                }
                else
                {
                        HIGHLIGHT=0;
                        AUTOINDENT=0;
                }
                tempno++;
                block=0;
                block=new doc;
                block->load(filename,status);
                dc.adddoc(&block,filename,&locx,&locy);
                locy=TMARGIN;
        }
        if(argc>2)
        {
                dc.activate(0,&block,filename,&locx,&locy);
                delwin(edit);
                edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                dc.refreshbak(&block);
        }
                                          /*status bar initial update*/
        wattron(status,COLOR_PAIR(2));
        werase(status);
        wprintw(status,"ed! : ");
        wattroff(status,COLOR_PAIR(2));
        wprintw(status,"Hello %s, Welcome to ed! V1.0.",getlogin());
        wrefresh(status);
                                        /******************************/

        wattron(help,COLOR_PAIR(2));
        wprintw(help,"ed! Help>>  ");
        wattroff(help,COLOR_PAIR(2));
        wprintw(help,"F1-Help  F2-Save  F5-Menu  F6-Shell  F9-Compile  F10-Run  F12-Quit");
        wrefresh(edit);
        wrefresh(help);
        curs_set(0);
        edlogo();
        curs_set(2);
        block->editscreen(edit);
        wbkgd(B,COLOR_PAIR(0));
        wrefresh(B);
        if(TILE)
        dc.refreshbak(&block);
        wrefresh(edit);
        wrefresh(help);

        move(locy,locx);
        refresh();
        while(1)
        {
                int ch=getch();

                if(ch==ESC || MODE>1)             //QUICK COMMAND MODE
                {
                        curs_set(0);

                        switch(ch)
                        {
                                case 'b':
                                ch=CTRLB;
                                break;
                                case 'e':
                                ch=CTRLE;
                                break;
                                case 'v':
                                ch=CTRLV;
                                break;
                                case 'x':
                                ch=CTRLX;
                                break;
                                case 'h':
                                ch=CTRLH;
                                break;
                                case 'y':
                                ch=DEL;
                                break;
                                case 'a':
                                wtimeout(help,500);
                                ch=wgetch(help);
                                wtimeout(help,-1);
                                if(ch>='0'&&ch<='7')
                                block->gbufcopy(ch-'0');
                                else
                                edm.show("ed! has only 8 buffers. They are numbered from 0 to 7.");
                                ch=0;
                                break;
                                case 'z':
                                wtimeout(help,500);
                                ch=wgetch(help);
                                wtimeout(help,-1);
                                if(ch>='0'&&ch<='7')
                                {
                                        if(!block->gbufpaste(ch-'0'))
                                        edm.show("Buffer is empty.");
                                        else
                                        SAVE=1;
                                }
                                else
                                edm.show("ed! has only 8 buffers. They are numbered from 0 to 7.");
                                ch=0;
                                break;
                                case 'd':
                                wtimeout(help,500);
                                ch=wgetch(help);
                                if(ch=='d')
                                ch=CTRLY;
                                else if(ch=='w')
                                ch=CTRLW;
                                else
                                ch=0;
                                wtimeout(help,-1);
                                break;
                                case SPACE :
                                ch=RIGHT;
                                break;
                                case BACKSPACE :
                                ch=LEFT;
                                break;
                                case 'k' :
                                ch=UP;
                                break;
                                case 'j' :
                                ch=DOWN;
                                break;
                                case CTRLF:
                                ch=PGDOWN;
                                break;
                                case CTRLB:
                                ch=PGUP;
                                break;
                                case CTRLD :
                                for(int l=0;l<=(BMARGIN-TMARGIN-2)/2;l++)
                                {
                                        if(block->gotonl())
                                        {
                                                locy++;
                                        }
                                        else
                                        break;

                                }
                                break;
                                case CTRLU :
                                for(int l=0;l<=(BMARGIN-TMARGIN-2)/2;l++)
                                {
                                        if(block->gotopl())
                                        locy--;
                                        else
                                        break;
                                }
                                break;

                                case 'l':
                                for(int i=strlen(lastcom)-1;i>=0;i--)
                                ungetch(lastcom[i]);
                                ch=0;

                                case ':':
                                echo();
                                curs_set(1);
                                werase(help);
                                wattron(help,COLOR_PAIR(2));
                                wprintw(help,"Enter command : ");
                                wattroff(help,COLOR_PAIR(2));
                                wrefresh(help);
                                wscanw(help," %[^\n]",tempstring);
                                noecho();
                                if(!strcmp(tempstring,"l"))
                                strcpy(tempstring,lastcom);
                                else
                                strcpy(lastcom,tempstring);

                                if(!strcmp(tempstring,"w"))
                                ch=F2;
                                else if(!strncmp(tempstring,"w ",2))
                                {
                                        if(strlen(tempstring)>2)
                                        strcpy(filename,edsave(tempstring+2,*block));
                                }
                                else if(!strcmp(tempstring,"Q"))
                                ch=F12;
                                else if(!strcmp(tempstring,"Q!"))
                                {
                                        endwin();
                                        while(dc.closedoc(&block,filename,&locy,&locx));
                                        edclean();
                                        delwin(edit);
                                        delwin(help);
                                        delwin(status);
                                        delwin(B);
                                        return 0;
                                }
                                else if(!strcmp(tempstring,"o"))
                                ch=CTRLO;
                                else if(!strncmp(tempstring,"o ",2))
                                {
                                                dc.update(&block,filename,locx,locy);
                                                block=0;
                                                block=new doc;
                                                strcpy(filename,tempstring+2);
                                                if(!strcmp(filename+strlen(filename)-2,".c")||!strcmp(filename+strlen(filename)-2,".C")||!strcmp(filename+strlen(filename)-4,".cpp")||!strcmp(filename+strlen(filename)-2,".cxx"))
                                                {
                                                        HIGHLIGHT=1;
                                                        AUTOINDENT=1;
                                                }
                                                else
                                                {
                                                        HIGHLIGHT=0;
                                                        AUTOINDENT=0;
                                                }
                                                dc.adddoc(&block,filename,&locx,&locy);
                                                if(TILE)
                                                {
                                                        delwin(edit);
                                                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                                        wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                                }
                                                tempno=block->load(filename,status);
                                                if(!tempno)
                                                edm.show("Some errors were encountered while opening this file.");
                                                else if(tempno==-1)
                                                edm.show("File not found. Opening new blank file.");
                                                SAVE=0;
                                                locy=TMARGIN;
                                }
                                else if(!strcmp(tempstring,"n"))
                                ch=CTRLN;
                                else if(!strcmp(tempstring,"wq"))
                                {
                                        edsave(filename,*block);
                                        SAVE=0;
                                        ch=CTRLL;
                                }
                                else if(!strcmp(tempstring,"q!"))
                                {
                                        SAVE=0;
                                        ch=CTRLL;
                                }
                                else if(!strcmp(tempstring,"q"))
                                {
                                        ch=CTRLL;
                                }
                                else if(!strcmp(tempstring,"f"))
                                {
                                        curs_set(2);
                                        ch=CTRLF;
                                }
                                else if(!strcmp(tempstring,"fn"))
                                ch=F3;
                                else if(!strcmp(tempstring,"r"))
                                ch=CTRLR;
                                else if(!strncmp(tempstring,"f ",2))
                                {
                                        strcpy(string,tempstring+2);
                                        if(block->find(string,0))
                                        {
                                                locy=TMARGIN;
                                        }
                                        else
                                        {
                                                curs_set(0);
                                                edm.show("Search string not found.");
                                                curs_set(1);
                                        }
                                }
                                else if(!strncmp(tempstring,"fn ",3))
                                {
                                        strcpy(string,tempstring+3);
                                        if(block->find(string,1))
                                        {
                                                locy=TMARGIN;
                                        }
                                        else
                                        {
                                                curs_set(0);
                                                edm.show("Search string not found.");
                                                curs_set(1);
                                        }
                                }
                                else if(!strcmp(tempstring,"spell"))
                                {
                                        block->spellready();
                                        if(HIGHLIGHT<2)
                                                HIGHLIGHT+=2;
                                }
                                else if(!strcmp(tempstring,"spell off"))
                                {
                                        if(HIGHLIGHT>=2)
                                        HIGHLIGHT-=2;
                                }
                                else if(!strcmp(tempstring,"compile"))
                                ch=F9;
                                else if(!strcmp(tempstring,"run"))
                                ch=F10;
                                else if(!strcmp(tempstring,"shell"))
                                ch=F6;
                                else if(!strcmp(tempstring,"h")||!strcmp(tempstring,"help"))
                                ch=F1;
                                else if(!strcmp(tempstring,"set h"))
                                {
                                        if(HIGHLIGHT==0)
                                        HIGHLIGHT=1;
                                        else
                                        HIGHLIGHT=0;
                                }
                                else if(!strcmp(tempstring,"set ai"))
                                {
                                        if(AUTOINDENT==0)
                                        AUTOINDENT=1;
                                        else
                                        AUTOINDENT=0;
                                }
                                else if(!strcmp(tempstring,"set color"))
                                {
                                        curs_set(2);
                                        edc.select(edit);
                                        curs_set(1);
                                }
                                else if(!strcmp(tempstring,"set beep"))
                                {
                                        if(BEEP==0)
                                        BEEP=1;
                                        else
                                        BEEP=0;
                                }
                                else if(!strcmp(tempstring,"set hmargin"))
                                ch=3001;
                                else if(!strcmp(tempstring,"set vmargin"))
                                ch=3002;
                                else if(!strcmp(tempstring,"tile"))
                                {
                                        if(!TILE)
                                        ch=3003;
                                }
                                else if(!strcmp(tempstring,"untile"))
                                {
                                        if(TILE)
                                        ch=3003;
                                }
                                else if(!strncmp(tempstring,"!",1))
                                {
                                        endwin();
                                        system(tempstring+1);
                                        system("echo Press any key to continue...");
                                        getch();
                                        initial();
                                        wbkgd(B,COLOR_PAIR(0));
                                        wrefresh(B);
                                        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
                                        wbkgd(help,COLOR_PAIR(8)|WA_BOLD);
                                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                                }
                                else
                                {
                                        werase(help);
                                        wattron(help,COLOR_PAIR(2));
                                        if(BEEP)
                                        beep();
                                        wprintw(help,"Command Not Found. Press any key to continue...");
                                        wattroff(help,COLOR_PAIR(2));
                                        wrefresh(help);
                                        noecho();
                                        getch();
                                }
                                curs_set(0);
                                if(ch==':')
                                ch=0;
                                break;

                                case ESC:
                                if(MODE<2)
                                MODE+=2;
                                break;

                                case 'i' :
                                case INS :
                                MODE-=2;
                                wattron(help,COLOR_PAIR(2));
                                curs_set(2);
                                ch=0;
                                break;

                                default:
                                if(isdigit(ch))
                                {
                                        tempno=ch-'0';
                                        while(1)
                                        {
                                                wtimeout(help,500);
                                                ch=wgetch(help);
                                                wtimeout(help,-1);
                                                if(isdigit(ch))
                                                        tempno=tempno*10+(ch-'0');
                                                else if(ch!=ERR)
                                                {
                                                        if(ch=='d')
                                                        tempno*=2;
                                                        if(tempno>100)
                                                        tempno=100;
                                                        for(;tempno>0;tempno--)
                                                        ungetch(ch);
                                                        break;
                                                }
                                                else
                                                {
                                                        block->gotol(tempno);
                                                        ch=0;
                                                        break;
                                                }
                                        }
                                        ch=0;
                                        break;
                                }
                                if(isascii(ch))
                                {
                                        if(BEEP)
                                        beep();
                                        ch=0;
                                }
                                break;
                        }
                }
                else if(ch==F5)                //has the menu been called  -- GRAPHICAL MENU
            {
                        wattron(status,A_BLINK|COLOR_PAIR(2));
                        wmove(status,0,65);
                        wprintw(status," -COM-");
                        wattroff(status,A_BLINK|COLOR_PAIR(2));
                        wrefresh(status);
                        wattron(help,COLOR_PAIR(2));
                        werase(help);
                        wprintw(help,"ed! Help>>  ");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help,"Use numbers or the first letters to select and ENTER to execute.");
                        wrefresh(help);

                        curs_set(0);
                        ch=menuhandler(edit,B);
                        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
                        wrefresh(status);
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        wrefresh(edit);
                        curs_set(2);
                        switch(ch)           //switch case converting menucalls to shortcut calls
                        {
                                case 0:
                                ch=CTRLN;
                                break;
                                case 1:                 //open
                                ch=CTRLO;
                                break;
                                case 2:                //save
                                ch=F2;
                                break;
                                case 3:                //save as
                                ch=F4;
                                break;
                                case 4:                 //shell
                                ch=F6;
                                break;
                                case 5:                 //close
                                ch=CTRLL;
                                break;

                                case 6:                 //quit
                                ch=F12;
                                break;

                                case 1000:            //insert line
                                block->home();
                                block->enter(1);
                                block->gotopl();
                                break;
                                case 1001:
                                ch=CTRLY;
                                break;
                                case 1002:          //del word
                                ch=CTRLW;
                                break;
                                case 1003:          //start sel
                                ch=CTRLB;
                                break;
                                case 1004:          //end sel
                                ch=CTRLE;
                                break;
                                case 1005:          //hide sel
                                ch=CTRLH;
                                break;
                                case 1006:          //copy sel
                                ch=CTRLV;
                                break;
                                case 1007:          //cut sel
                                ch=CTRLX;
                                break;

                                case 2000:        //goto line
                                ch=CTRLG;
                                break;
                                case 2001:          //find
                                ch=CTRLF;
                                break;
                                case 2002:          //find next
                                ch=F3;
                                break;
                                case 2003:           //replace
                                ch=CTRLR;
                                break;
                                case 2004:          //compile
                                ch=F9;
                                break;
                                case 2005:          //run
                                ch=F10;
                                break;
                                case 2006:          //highlight
                                if(HIGHLIGHT==1)
                                HIGHLIGHT=0;
                                else
                                HIGHLIGHT=1;
                                break;
                                case 2007:          //autoindent
                                if(AUTOINDENT==1)
                                AUTOINDENT=0;
                                else
                                AUTOINDENT=1;
                                break;
                                case 2008:           //spell
                                if(HIGHLIGHT<2)
                                {
                                        block->spellready();
                                        HIGHLIGHT+=2;
                                }
                                else if(HIGHLIGHT>1)
                                HIGHLIGHT-=2;
                                break;

                                case 3000:          //colors edit
                                edc.select(edit);
                                break;
                                case 3001:          //pg width
                                break;
                                case 3002:         //pg height
                                break;
                                case 3003:          //tile - untile
                                break;
                                case 3004:          //beep setting
                                if(BEEP)
                                BEEP=0;
                                else
                                BEEP=1;
                                break;

                                case 4000:             //help
                                ch=F1;
                                break;

                                case 4001:              //about
                                curs_set(0);
                                edlogo();
                                curs_set(2);
                                break;
                        }
                        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
                        wrefresh(status);
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        wrefresh(edit);
                }

                switch(ch)               //this loop handles most funtions - uses shortcut values for case
                {
                        case 277:        //multiple docs //shift+F1,F2,F3,F4,F5,F6,F7,F8
                        case 278:
                        case 279:
                        case 280:
                        case 281:
                        case 282:
                        case 283:
                        case 284:
                        dc.update(&block,filename,locx,locy);
                        delwin(edit);
                        dc.activate(ch-277,&block,filename,&locx,&locy);
                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                        wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                        break;

                        case CTRLL :          //close current window
                        if(edshudisave(filename,*block))
                        {
                                if(!dc.closedoc(&block,filename,&locx,&locy))
                                {
                                        endwin();
                                        delwin(edit);
                                        delwin(help);
                                        delwin(status);
                                        delwin(B);
                                        edclean();
                                        return 0;
                                }
                                else
                                {
                                        delwin(edit);
                                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                        wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                }
                        }
                        break;

                        case CTRLN :           //open new file - new window
                        dc.update(&block,filename,locx,locy);
                        block=0;
                        block=new doc;
                        strcpy(filename,"noname.txt");
                        if(!dc.adddoc(&block,filename,&locx,&locy))
                        {
                                if(TILE)
                                {
                                        delwin(edit);
                                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                        wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                }
                                curs_set(0);
                                edm.show("Sorry! Cannot open more than 8 files at a time.");
                                curs_set(2);
                                break;
                        }
                        if(TILE)
                        {
                                delwin(edit);
                                edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                        }
                        block->load(filename);
                        SAVE=0;
                        locy=TMARGIN;
                        break;

                        case 3001 :             //pg width adjustment
                        werase(help);
                        wattron(help,COLOR_PAIR(2));
                        wprintw(help,"ed! Help>>  ");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help,"Use + & - to adjust left margin, / & * to adjust right margin.");
                        wrefresh(help);
                        tempno=block->findlno();
                        curs_set(2);
                        edsethmargins();
                        curs_set(1);
                        block->print(SWAP3);
                        block->restart();
                        maxindex=RMARGIN-LMARGIN;
                        block->restart();
                        block->load(SWAP3);
                        delwin(edit);
                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        block->gotol(tempno);
                        block->editscreen(edit);
                        locy=TMARGIN;
                        break;

                        case 3002 :              //pg height adjustment
                        werase(help);
                        wattron(help,COLOR_PAIR(2));
                        wprintw(help,"ed! Help>>  ");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help,"Use + & - to adjust top margin, / & * to adjust bottom margin.");
                        wrefresh(help);
                        curs_set(2);
                        edsetvmargins();
                        curs_set(1);
                        delwin(edit);
                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        block->resetscreen();
                        block->editscreen(edit);
                        locy=TMARGIN;
                        break;

                        case 3003 :           //tile - untile
                        if(!TILE)
                        {
                                dc.autotile(&block,filename,&locy,&locx);
                                delwin(edit);
                                edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                wbkgd(B,COLOR_PAIR(0)|A_BOLD);
                                wrefresh(B);
                        }
                        else
                        {
                                dc.untile(&block,filename,&locy,&locx);
                                delwin(edit);
                                edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                wbkgd(B,COLOR_PAIR(0)|A_BOLD);
                                wrefresh(B);
                        }
                        break;

                        case INS :             // INS<->OVR
                        if(MODE==0)
                        MODE=1;
                        else
                        MODE=0;
                        break;

                        case ENTER :
                        block->enter(MODE,1);
                        locy++;
                        SAVE=1;
                        break;

                        case TAB :
                        if(block->inschar(' ')>1)
                        locy++;
                        while(block->getindex()%8!=0)
                        if(block->inschar(' ')>1)
                        locy++;
                        SAVE=1;
                        break;

                        case END :
                        block->end();
                        while(block->getindex()==maxindex)
                        {
                                locy++;
                                block->gotonl();
                                block->end();
                        }
                        break;

                        case HOME :
                        if(block->getindex()==0)
                        while(block->isstring(" ",block->getcurrent(),block->getindex())&&block->incindex());
                        else
                        {
                                block->home();
                                while(block->gotopl())
                                {
                                        if(block->getlength()<=maxindex)
                                        {
                                                block->gotonl();
                                                block->home();
                                                break;
                                        }
                                        locy--;
                                }
                        }
                        break;

                        case DEL :
                        block->delchar(1);
                        SAVE=1;
                        break;

                        case BACKSPACE :
                        i=block->delchar(2);
                        if(i==2&&locy!=TMARGIN)
                        locy--;
                        SAVE=1;
                        break;

                        case PGDOWN :
                        for(int l=0;l<=BMARGIN-TMARGIN-2;l++)
                        {
                                if(block->gotonl())
                                {
                                        locy++;
                                }
                                else
                                {
                                        if(BEEP)
                                        beep();
                                        break;
                                }

                        }
                        break;

                        case PGUP :
                        for(int l=0;l<=BMARGIN-TMARGIN-2;l++)
                        {
                                if(block->gotopl())
                                locy--;
                                else
                                {
                                        if(BEEP)
                                        beep();
                                        break;
                                }
                        }
                        break;

                        case CTRLB :                 //begin selection
                        block->setcbegin();
                        break;

                        case CTRLE :                 //end selection
                        block->setcend();
                        break;

                        case CTRLV :                //copy
                        block->copy();
                        SAVE=1;
                        break;

                        case CTRLX :                    //cut
                        i=block->cut();
                        locy-=i;
                        SAVE=1;
                        break;

                        case CTRLH :               //discard selection
                        block->resetc();
                        break;

                        case CTRLO:                 //open file
                        curs_set(0);
                        werase(help);
                        wattron(help,COLOR_PAIR(2));
                        wprintw(help,"ed! Help>>  ");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help,"Use UP & DOWN to select, LEFT & RIGHT to skip page, ENTER to open.");
                        wrefresh(help);

                        temp=edopen(edit,B,0);
                        if(temp)
                        {
                                dc.update(&block,filename,locx,locy);
                                strcpy(filename,temp);
                                block=0;
                                block=new doc;
                                if(!dc.adddoc(&block,filename,&locx,&locy))
                                edm.show("Sorry! Cannot open more than 8 files at a time.");
                                else
                                {
                                        if(!strcmp(filename+strlen(filename)-2,".c")||!strcmp(filename+strlen(filename)-2,".C")||!strcmp(filename+strlen(filename)-4,".cpp")||!strcmp(filename+strlen(filename)-2,".cxx"))
                                        {
                                                HIGHLIGHT=1;
                                                AUTOINDENT=1;
                                        }
                                        else
                                        {
                                                HIGHLIGHT=0;
                                                AUTOINDENT=0;
                                        }
                                        tempno=block->load(filename,status);
                                        if(!tempno)
                                        edm.show("Some errors were encountered while opening this file.");
                                        else if(tempno==-1)
                                        edm.show("File not found. Opening new blank file.");
                                        SAVE=0;
                                        block->editscreen(edit);
                                        wclear(status);
                                        wprintw(status,"ed! : [%s]",filename);
                                        locy=TMARGIN;
                                }
                                if(TILE)
                                {
                                        delwin(edit);
                                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                        wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                }
                        }

                        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
                        wrefresh(status);
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        wrefresh(edit);
                        curs_set(2);
                        break;

                        case CTRLY:                         //delete line
                        i=block->delline(block->getcurrent(),1);
                        if(i==3)
                           locy--;
                        SAVE=1;
                        break;

                        case CTRLW:           //delete word
                        while(block->getlength()!=block->getindex()&&!block->isstring(" ",block->getcurrent(),block->getindex()))
                        block->delchar(1);
                        SAVE=1;
                        break;

                        case CTRLG :            //goto line
                        edi.getnum("Enter the line number :",&i);
                        block->gotol(i);
                        locy=TMARGIN;
                        break;

                        case RIGHT :
                        i=block->incindex();
                        if((!i)&&BEEP)
                        beep();
                        if(i==2)
                        locy++;
                        break;

                        case LEFT :
                        i=block->decindex();
                        if((!i)&&BEEP)
                        beep();
                        if(i==2)
                        locy--;
                        break;

                        case UP :
                        i=block->gotopl();
                        if(i)
                        {
                                locy--;
                        }
                        else if(BEEP)
                        beep();
                        break;

                        case DOWN :
                        if(block->gotonl())
                                block->gotopl();
                        i=block->gotonl();
                        if(i)
                        {
                                locy++;
                        }
                        else if(BEEP)
                        beep();
                        break;

                        case F2 :                   //save
                        curs_set(0);
                        edsave(filename,*block);
                        curs_set(2);
                        if(strcmp(filename,"noname.txt"))
                        SAVE=0;
                        break;

                        case F4 :                  //save as
                        strcpy(tempstring,"noname.txt");
                        curs_set(0);
                        if(strcmp(filename,"noname.txt"))
                        for(tempno=strlen(filename)-1;tempno>=0;tempno--)
                        ungetch(filename[tempno]);
                        edsave(tempstring,*block);
                        curs_set(2);
                        if(strcmp(tempstring,"noname.txt"))
                        {
                                strcpy(filename,tempstring);
                                SAVE=0;
                        }
                        break;

                        case F1 :               //help
                        curs_set(0);
                        werase(status);
                        wattron(status,COLOR_PAIR(2));
                        wprintw(status,"ed! : ");
                        wattroff(status,COLOR_PAIR(2));
                        mvwprintw(status,0,3," -Accessing Help...");
                        wrefresh(status);
                        werase(help);
                        wattron(help,COLOR_PAIR(2));
                        wprintw(help,"ed! Help>>  ");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help,"UP,DOWN,ESC,ENTER - All the keys that you need to access help ;-)");
                        wrefresh(help);
                        edhelp();
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        curs_set(2);
                        break;

                        case F7 :        //repaint
                        endwin();
                        initial();
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
                        wbkgd(help,COLOR_PAIR(8)|WA_BOLD);
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        curs_set(2);
                        break;


                        case F6 :                 //shell
                        endwin();
                        system("clear");
                        system("echo Type exit to return to ed!");
                        system("bash");

                        initial();
                        wbkgd(edit,COLOR_PAIR(1)|WA_BOLD);
                        wbkgd(status,COLOR_PAIR(8)|WA_BOLD);
                        wbkgd(help,COLOR_PAIR(8)|WA_BOLD);
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        break;

                        case F9 :                   //compile
                        edcompile(*block);
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        break;

                        case F10 :                //run
                        edrun();
                        wbkgd(B,COLOR_PAIR(0));
                        wrefresh(B);
                        break;

                        case F12 :                      //QUIT
                        curs_set(0);
                        while(1)
                        if(edshudisave(filename,*block))
                        {
                                if(!dc.closedoc(&block,filename,&locx,&locy))
                                {
                                        endwin();
                                        delwin(edit);
                                        delwin(help);
                                        delwin(status);
                                        delwin(B);
                                        edclean();
                                        return 0;
                                }
                                else
                                {
                                        delwin(edit);
                                        edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                        wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                }
                        }
                        else
                        {
                                delwin(edit);
                                edit=newwin(BMARGIN-TMARGIN,maxindex+1,TMARGIN,LMARGIN);
                                wbkgd(edit,COLOR_PAIR(1)|A_BOLD);
                                break;
                        }
                        curs_set(2);
                        break;

                        case CTRLF :       //find
                        curs_set(2);
                        for(int j=strlen(string)-1;j>=0;j--)
                        ungetch(string[j]);
                        edi.getinput("Input the pattern to be matched.",string);
                        if(block->find(string,0))
                        {
                                locy=TMARGIN;
                        }
                        else
                        {
                                curs_set(0);
                                edm.show("Search hit EOF. Search pattern not found.");
                                curs_set(2);
                        }
                        break;

                        case F3 :            //find next
                        curs_set(2);
                        for(int j=strlen(string)-1;j>=0;j--)
                        ungetch(string[j]);
                        edi.getinput("Input the pattern to be matched.",string);
                        if(block->find(string,1))
                        {
                                locy=TMARGIN;
                        }
                        else
                        {
                                curs_set(0);
                                edm.show("Search hit EOF. Search pattern not found.");
                                curs_set(1);
                        }
                        break;

                        case CTRLR :       //find and replace next
                        curs_set(2);
                        for(int j=strlen(string)-1;j>=0;j--)
                        ungetch(string[j]);
                        edi.getinput("Input the pattern to be replaced.",string);
                        if(block->find(string,1))
                        {
                                locy=TMARGIN;
                                block->editscreen(edit,&locx,&locy);
                                wrefresh(edit);
                                curs_set(0);
                                if(edq.ask("Replace??",2)==0)
                                {
                                        curs_set(1);
                                        SAVE=1;
                                        for(int j=strlen(tempstring)-1;j>=0;j--)
                                        ungetch(tempstring[j]);
                                        edi.getinput("Input replace pattern.",tempstring);
                                        for(int j=strlen(string)-1;j>=0;j--)
                                        block->delchar();
                                        for(int j=0;j<strlen(tempstring);j++)
                                        block->inschar(tempstring[j]);
                                }
                                curs_set(2);
                        }
                        else
                        {
                                curs_set(0);
                                edm.show("Search hit EOF. Search pattern not found.");
                                curs_set(2);
                        }
                        break;

                        default :                 //insert character
                        i=0;
                        if(isascii(ch)&&isprint(ch))
                        {
                                if(MODE==1)
                                i=block->inschar(ch);
                                else
                                i=block->ovrchar(ch);
                                if(i==1)
                                {
                                        SAVE=1;
                                }
                                else if(i==2||i==3)
                                {
                                        locy++;
                                        SAVE=1;
                                }
                                break;
                        }
                        else if(BEEP)
                        beep();
                        break;

                }

                while(locy>BMARGIN-1)                //required  for pg up and down
                {
                        locy--;
                        block->scrolldown(1);
                }
                while(locy<TMARGIN)
                {
                        locy++;

                        block->scrollup(1);
                }

                if(MODE<2)
                curs_set(0);
                block->editscreen(edit,&locx,&locy);
                werase(status);
                wattron(status,COLOR_PAIR(2));
                wprintw(status,"ed! ");
                wattroff(status,COLOR_PAIR(2));
                int tmpno,j;
                for(tmpno=strlen(filename)-1,j=0;tmpno>0&&j<16;tmpno--,j++);
                wprintw(status,"[%14s][%0.1lf%] W[%d/8] C[%2d/%2d] L[%d/%d]",filename+tmpno,block->getpercent(),WIN+1,locx-LMARGIN+1,maxindex+1,block->getcurline(),block->getmaxline());
                wattron(status,COLOR_PAIR(2));
                wmove(status,0,60);
                if(SAVE)
                wprintw(status,"-MFD-");
                else
                wprintw(status,"-SVD-");
                if(MODE==1)
                wprintw(status," -INS-");
                else if(MODE==0)
                wprintw(status," -OVR-");
                else
                wprintw(status," -QCM-");
                wattron(status,A_BLINK);
                if(AUTOINDENT==1)
                wprintw(status," -AI-");
                if(HIGHLIGHT==1)
                wprintw(status," -H-");
                wattroff(status,A_BLINK|COLOR_PAIR(2));
                wrefresh(status);
                werase(help);
                if(MODE<2)
                {
                        wattron(help,COLOR_PAIR(2));
                        wprintw(help,"ed! Help>>  ");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help,"F1-Help  F2-Save  F5-Menu  F6-Shell  F9-Compile  F10-Run  F12-Quit");
                }
                else
                {
                        wattron(help,COLOR_PAIR(2));
                        wprintw(help,"You are in Quick Command Mode.");
                        wattroff(help,COLOR_PAIR(2));
                        wprintw(help," [i/INS] Insert mode  [:] Extended commands");
                }
                wrefresh(help);
                if(TILE)
                dc.refreshbak(&block);
                curs_set(2);
                wmove(edit,locy-TMARGIN,locx-LMARGIN);
                wrefresh(edit);
        }
}

void initial()
{
        edconfig ec;
        initscr();
        start_color();
        keypad(stdscr,1);
        ec.loadcolors();
        /*init_pair(1,COLOR_YELLOW,COLOR_BLUE);   //edit screen
        init_pair(2,COLOR_BLUE,COLOR_YELLOW);   //selected       --not used
        init_pair(3,COLOR_BLUE,COLOR_WHITE);   //menus
        init_pair(4,COLOR_RED,COLOR_GREEN);   //selected menu
        init_pair(5,COLOR_WHITE,COLOR_RED);    //errors &&reminders
        init_pair(6,COLOR_GREEN,COLOR_BLACK);  //other windows
        init_pair(7,COLOR_BLACK,COLOR_BLACK);   //shadow effects
        init_pair(8,COLOR_GREEN,COLOR_BLACK);    //status bar and help bar
        init_pair(9,COLOR_RED,COLOR_BLUE);    //highlight for keywords
        init_pair(10,COLOR_WHITE,COLOR_BLUE);   //string
        init_pair(11,COLOR_MAGENTA,COLOR_BLUE);   //include        */
        wbkgd(stdscr,COLOR_PAIR(1));
        refresh();
        noecho();
        curs_set(2);
        ESCDELAY=0;
        //nonl();
}

void final()
{
        endwin();
        exit(0);
}

int menuhandler(WINDOW *W,WINDOW *B)
{

        char toolbar_arr[7][10]={"File","Edit","Tools","Settings","Help"};      //the toolbar
        hmenu toolbar(toolbar_arr,0,5,0,3);
        char file_arr[10][10]={"New","Open","Save","Save as","OS Shell","Close","Quit"};
        vmenu file(file_arr,"file",0,7,1,3);
        char edit_arr[10][10]={"Ins Line","Del Line","Del Word","Begin sel","End sel","Hide Sel","Copy","Cut","Replace"};
        vmenu edit(edit_arr,"edit",0,9,1,15);
        char tools_arr[10][10]={"Go to","Find","Find next","Replace","Compile","Run","Highlight","Auto Ind","Spell on"};
        if(HIGHLIGHT>1)
        strcpy(tools_arr[8],"Spell Off");
        vmenu tools(tools_arr,"tools",0,9,1,27);
        char setup_arr[10][10]={"Colors","Pg Width","Pg Height","Tile","On Beep"};
        if(TILE)
        strcpy(setup_arr[3],"Untile");
        if(BEEP)
        strcpy(setup_arr[4],"Off Beep");
        vmenu setup(setup_arr,"setup",0,5,1,39);
        char help_arr[10][10]={"Help","About"};
        if(strlen(getlogin())<10)
        strcpy(help_arr[1],getlogin());
        vmenu help(help_arr,"help",0,2,1,51);

        int option=toolbar.select();
        int flag;
        if(option!=-3)
        toolbar.press();
        while(1)
        {
          switch(option)
          {
                case 0:
                flag=file.select();
                break;

                case 1:
                flag=edit.select();
                break;

                case 2:
                flag=tools.select();
                break;

                case 3:
                flag=setup.select();
                break;

                case 4:
                flag=help.select();
                break;

                default:
                return -1;
          }
          if(flag>=0&&flag<=10)
          break;
          else
          {
                   wbkgd(B,COLOR_PAIR(0));
                   wrefresh(B);
                   wbkgd(W,COLOR_PAIR(1)|WA_BOLD);
                   wrefresh(W);
                   option=toolbar.select();
                   if(option!=-3)
                   toolbar.press();
          }
        }
        return option*1000+flag;
}


char *edopen(WINDOW *W,WINDOW *B,char* dir)
{
        WINDOW *where=newwin(3,80,21,0);
        wbkgd(where,COLOR_PAIR(8));
        char *filename=new char[255];
        char string[200];
        strcpy(string,"pwd>");
        strcat(string,SWAP1);
        system(string);
        FILE*ptr=fopen(SWAP1,"rb");
        fscanf(ptr,"%s",filename);
        wprintw(where,"Directory:- %s/%s",filename,dir);
        wrefresh(where);

        if(dir)
        strcpy(filename,dir);
        else
        strcpy(filename,"");

        char files[100][10][30];
        fmenu file[100];

        int i=0,j=0,k=0;
        char com[255];

        strcpy(com,"ls ");
        if(dir)
        strcat(com,dir);
        strcat(com," -Ff >");
        strcat(com,SWAP1);

        system(com);
        ptr=fopen(SWAP1,"rb");

        while(!feof(ptr))
        {
                char ch=getc(ptr);
                if(k==29)
                {
                        while(ch!='\n')
                        ch=getc(ptr);
                        files[i][j][k]='\0';
                        j++;
                        k=0;
                        continue;
                }
                if(ch=='\n'||ch=='*')
                {
                        if(ch=='*')
                        while(ch!='\n')
                        ch=getc(ptr);
                        files[i][j][k]='\0';
                        j++;
                        k=0;
                }
                else
                {
                        files[i][j][k]=ch;
                        k++;
                }
                if(j==9)
                {
                        files[i][j][0]='>';
                        files[i][j][1]='>';
                        files[i][j][2]='>';
                        files[i][j][3]='\0';
                        file[i].set(files[i],"SELECT THE FILE TO OPEN",0,j+1,5,5);
                        i++;
                        j=0;
                        k=0;
                        files[i][j][0]='<';
                        files[i][j][1]='<';
                        files[i][j][2]='<';
                        files[i][j][3]='\0';
                        j++;
                }
        }
        fclose(ptr);
        file[i].set(files[i],"SELECT THE FILE TO OPEN",0,j,5,5);
        i=0;
        int sel;
        while(1)
        {
                sel=file[i].select();
                if(sel==9)
                i++;
                else if(sel==0&&i!=0)
                i--;
                else if(sel==-1&&i>0)
                i--;
                else if(sel==-2&&files[i][9][0]=='>')
                i++;
                else if(sel==-1||sel==-2)
                return 0;
                else if(sel!=-3)
                {
                        if(files[i][sel][strlen(files[i][sel])-1]=='/')
                        {
                                strcat(filename,files[i][sel]);
                                wbkgd(B,COLOR_PAIR(0));
                                wrefresh(B);
                                wbkgd(W,COLOR_PAIR(1)|WA_BOLD);
                                wrefresh(W);
                                char *ptr=edopen(W,B,filename);
                                if(ptr)
                                {
                                        strcpy(filename,ptr);
                                        delete ptr;
                                        delwin(where);
                                        return filename;
                                }
                                else
                                {
                                        delwin(where);
                                        return 0;
                                }
                        }
                        else        //ie if selected
                        {
                                strcat(filename,files[i][sel]);
                                delwin(where);
                                return filename;
                        }
                }
                else
                {
                        delwin(where);
                        return 0;
                }
                wbkgd(B,COLOR_PAIR(0));
                wrefresh(B);
                wbkgd(W,COLOR_PAIR(1)|WA_BOLD);
                wrefresh(W);
                wbkgd(where,COLOR_PAIR(8));
                wrefresh(where);
        }
}

char *edsave(char *filename,doc &block)
{
        FILE *ptr=0;
        WINDOW *win=newwin(1,80,0,0);
        wbkgd(win,COLOR_PAIR(8));
        char fname[30];
        message saved;
        input ipbox;
        question q;
        int i;
        char string[100];
        if(strcmp(filename,"noname.txt"))
         {
                block.print(filename,win);
                delwin(win);
                return filename;
         }
         curs_set(2);
         ipbox.getinput("Enter the name of the file.",fname);
         curs_set(0);
         ptr=fopen(fname,"rb");
         if(!ptr)
         {
                strcpy(string,"Save the file as \"");
                strcat(string,fname);
                strcat(string,"\"  ?");
                i=q.ask(string,2);
                if(i==1)
                {
                        delwin(win);
                        return filename;
                }
         }
         else
         {
                fclose(ptr);
                strcpy(string,"The file \"");
                strcat(string,fname);
                strcat(string,"\"  already exists. Overwrite?");
                i=q.ask(string,2);
                if(i==1)
                {
                        delwin(win);
                        return filename;
                }
         }
         strcpy(filename,fname);
         block.print(filename);
         delwin(win);
         return filename;
}

void edcompile(doc &block)
{
        input box;
        question box2;
        char string[200];
        char com[200];
        block.print(COMPILEFILE);
        curs_set(0);
        if(box2.ask("Are there any command line parameters to be entered?",2)==0)
        {
                curs_set(2);
                box.getinput("Enter the command line parameters :",string);
                strcpy(com,"gcc ");
                strcat(com,string);
                strcat(com," ");
                strcat(com,COMPILEFILE);
                curs_set(0);
        }
        else
        {
                strcpy(com,"gcc ");
                strcat(com,COMPILEFILE);
        }
        strcat(com," -o edcompiled.exe");
        endwin();
        system("clear");
        system("echo Compiling..");
        system(com);
        system("echo \"Compilation done.\"");
        getch();
        initial();
}

void edrun()
{
        endwin();
        system("clear");
        system("./edcompiled.exe");
        system("echo \"\nProgram has completed execution. Press any key to continue...\"");
        getch();
        initial();
}

int edshudisave(char *filename,doc &block)
{
        question edq;
        if(!SAVE)
        return 1;
        WINDOW *file=newwin(1,60,14,10);
        WINDOW *sfile=newwin(1,1,15,70);
        wbkgd(file,COLOR_PAIR(5));
        wbkgd(sfile,COLOR_PAIR(7));
        curs_set(0);
        wprintw(file," Filename : %s",filename);
        wrefresh(file);
        wrefresh(sfile);
        int i=edq.ask("This file has been changed. Save? ");
        curs_set(2);
        if(i==0)
        edsave(filename,block);
        delwin(file);
        delwin(sfile);
        if(i==0||i==1)
        return 1;
        else
        return 0;
}

int edsethmargins()
{
        TILE=0;
        curs_set(0);
        WINDOW *bar=newwin(1,80,15,0);
        WINDOW *L=newwin(1,1,15,LMARGIN);
        WINDOW *R=newwin(1,1,15,RMARGIN);
        wbkgd(bar,COLOR_PAIR(3));
        wbkgd(L,COLOR_PAIR(4));
        wbkgd(R,COLOR_PAIR(4));
        wrefresh(bar);
        wrefresh(L);
        wrefresh(R);
        delwin(L);
        delwin(R);
        while(1)
        {
                char ch=getch();
                switch(ch)
                {
                        case '+' :
                        if(LMARGIN<79&&LMARGIN<RMARGIN-1)
                        LMARGIN++;
                        break;
                        case '-' :
                        if(LMARGIN>0)
                        LMARGIN--;
                        break;
                        case '*' :
                        if(RMARGIN<79)
                        RMARGIN++;
                        break;
                        case '/' :
                        if(RMARGIN>0&&LMARGIN<RMARGIN-1)
                        RMARGIN--;
                        break;
                        case ENTER :
                        delwin(bar);
                        bar=newwin(23,80,1,0);
                        wbkgd(bar,COLOR_PAIR(0));
                        wrefresh(bar);
                        delwin(bar);
                        curs_set(2);
                        return 1;
                }
                L=newwin(1,1,15,LMARGIN);
                R=newwin(1,1,15,RMARGIN);
                wbkgd(bar,COLOR_PAIR(3));
                wbkgd(L,COLOR_PAIR(4));
                wbkgd(R,COLOR_PAIR(4));
                wrefresh(bar);
                wrefresh(L);
                wrefresh(R);
        }
}

int edsetvmargins()
{
        TILE=0;
        curs_set(0);
        WINDOW *bar=newwin(23,1,1,40);
        WINDOW *T=newwin(1,1,TMARGIN,40);
        WINDOW *B=newwin(1,1,BMARGIN-1,40);
        wbkgd(bar,COLOR_PAIR(3));
        wbkgd(T,COLOR_PAIR(4));
        wbkgd(B,COLOR_PAIR(4));
        wrefresh(bar);
        wrefresh(T);
        wrefresh(B);
        delwin(T);
        delwin(B);
        while(1)
        {
                char ch=getch();
                switch(ch)
                {
                        case '+' :
                        if(TMARGIN<24&&TMARGIN<BMARGIN-1)
                        TMARGIN++;
                        break;
                        case '-' :
                        if(TMARGIN>1)
                        TMARGIN--;
                        break;
                        case '*' :
                        if(BMARGIN<24)
                        BMARGIN++;
                        break;
                        case '/' :
                        if(BMARGIN>1&&TMARGIN<BMARGIN-1)
                        BMARGIN--;
                        break;
                        case ENTER :
                        delwin(bar);
                        bar=newwin(23,80,1,0);
                        wbkgd(bar,COLOR_PAIR(8));
                        wrefresh(bar);
                        delwin(bar);
                        curs_set(2);
                        return 1;
                }
                T=newwin(1,1,TMARGIN,40);
                B=newwin(1,1,BMARGIN-1,40);
                wbkgd(bar,COLOR_PAIR(3));
                wbkgd(T,COLOR_PAIR(4));
                wbkgd(B,COLOR_PAIR(4));
                wrefresh(bar);
                wrefresh(T);
                wrefresh(B);
        }
}

void edclean()
{
        system("echo Freeing Buffers");
        for(int i=0;i<=7;i++)
        if(BUF[i])
        delete [] BUF[i];
        system("echo Removing all swap files");
        char string[200];
        strcpy(string,"rm ");
        strcat(string,SWAP1);
        system(string);
        strcpy(string,"rm ");
        strcat(string,SWAP2);
        system(string);
        strcpy(string,"rm ");
        strcat(string,SWAP3);
        system(string);
        strcpy(string,"rm ");
        strcat(string,COMPILEFILE);
        system(string);
        system("stty sane");
        system("clear");
        system("echo ThankYou for using Virtualage ed! V1.0.");
}


