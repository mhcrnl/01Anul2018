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

int delay();

void edlogo()
{
        WINDOW*contents=newwin(20,40,2,20);
        WINDOW*scontents=newwin(20,40,3,21);
        wbkgd(contents,COLOR_PAIR(8));
        wbkgd(scontents,COLOR_PAIR(7));
        box(contents,ACS_CKBOARD,ACS_CKBOARD);
        char c=159;
        wattron(contents,A_BOLD);
        wrefresh(scontents);

        if(delay())
        return;
        if(delay())
        return;
        mvwprintw(contents,1,2,"                                 ");
        mvwprintw(contents,2,2,"                                 ");
        mvwprintw(contents,3,2,"                                 ");
        mvwprintw(contents,4,2,"                                 ");
        mvwprintw(contents,5,2,"                                 ");
        mvwprintw(contents,6,2,"                                 ");
        mvwprintw(contents,7,2,"                                 ");
        mvwprintw(contents,8,2,"                                 ");
        mvwprintw(contents,9,2,"       %c%c%c                       ",c,c,c);
        mvwprintw(contents,10,2,"     %c%c                          ",c,c);
        mvwprintw(contents,11,2,"    %c                            ",c);
        mvwprintw(contents,12,2,"                                 ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                                ");
        mvwprintw(contents,2,2,"                                ");
        mvwprintw(contents,3,2,"                                ");
        mvwprintw(contents,4,2,"       %c%c%c%c                     ",c,c,c,c);
        mvwprintw(contents,5,2,"        %c%c%c%c                    ",c,c,c,c);
        mvwprintw(contents,6,2,"          %c%c                    ",c,c);
        mvwprintw(contents,7,2,"          %c%c                    ",c,c);
        mvwprintw(contents,8,2,"         %c%c                     ",c,c);
        mvwprintw(contents,9,2,"       %c%c%c                      ",c,c,c);
        mvwprintw(contents,10,2,"     %c%c                         ",c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                               ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                                ");
        mvwprintw(contents,2,2,"                                ");
        mvwprintw(contents,3,2,"                                ");
        mvwprintw(contents,4,2,"       %c%c%c%c                     ",c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c                    ",c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c                    ",c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c                    ",c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c                     ",c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c                      ",c,c,c);
        mvwprintw(contents,10,2,"     %c%c                         ",c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                                ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                                ");
        mvwprintw(contents,2,2,"                                ");
        mvwprintw(contents,3,2,"                                ");
        mvwprintw(contents,4,2,"       %c%c%c%c                     ",c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c                    ",c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c               ",c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c                ",c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c                   ",c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c                    ",c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                                ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                                ");
        mvwprintw(contents,2,2,"                                ");
        mvwprintw(contents,3,2,"                                ");
        mvwprintw(contents,4,2,"       %c%c%c%c                     ",c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c                    ",c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c               ",c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c                ",c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c %c%c%c%c%c             ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c    %c%c%c             ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                               ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                                ");
        mvwprintw(contents,2,2,"                      %c         ",c);
        mvwprintw(contents,3,2,"                     %c          ",c);
        mvwprintw(contents,4,2,"       %c%c%c%c         %c           ",c,c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c       %c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c  %c            ",c,c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c   %c            ",c,c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c %c%c%c%c%c             ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c    %c%c%c             ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                                ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                                ");
        mvwprintw(contents,2,2,"                      %c         ",c);
        mvwprintw(contents,3,2,"                     %c          ",c);
        mvwprintw(contents,4,2,"       %c%c%c%c         %c%c          ",c,c,c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c       %c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c  %c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c   %c%c           ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c %c%c%c%c%c %c%c          ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c    %c%c%c             ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                                ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        mvwprintw(contents,1,2,"                             %c  ",c);
        mvwprintw(contents,2,2,"                      %c     %c%c%c ",c,c,c,c);
        mvwprintw(contents,3,2,"                     %c     %c%c%c%c%c",c,c,c,c,c,c);
        mvwprintw(contents,4,2,"       %c%c%c%c         %c%c     %c%c%c%c%c",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c       %c%c      %c%c%c%c%c",c,c,c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c       %c%c%c ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c  %c%c       %c%c%c ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c   %c%c        %c  ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c %c%c%c%c%c %c%c          ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c    %c%c%c             ",c,c,c,c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                           ",c);
        mvwprintw(contents,12,2,"                                ");
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;
        if(delay())
        return;
        if(delay())
        return;

        mvwprintw(contents,1,2,"                             %c  ",c);
        mvwprintw(contents,2,2,"                      %c     %c%c%c ",c,c,c,c);
        mvwprintw(contents,3,2,"                     %c     %c%c%c%c%c",c,c,c,c,c,c);
        mvwprintw(contents,4,2,"       %c%c%c%c         %c%c     %c%c%c%c%c",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c       %c%c      %c%c%c%c%c",c,c,c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c       %c%c%c ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c  %c%c       %c%c%c ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c   %c%c        %c  ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c %c%c%c%c%c %c%c          ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c    %c%c%c          %c  ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                       %c%c%c ",c,c,c,c);
        mvwprintw(contents,12,2,"                             %c ",c);
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wprintw(contents,"\n");
        wrefresh(contents);
        if(delay())
        return;

        wattron(contents,COLOR_PAIR(2)|A_BOLD);
        mvwprintw(contents,1,2,"                             %c  ",c);
        mvwprintw(contents,2,2,"                      %c     %c%c%c ",c,c,c,c);
        mvwprintw(contents,3,2,"                     %c     %c%c%c%c%c",c,c,c,c,c,c);
        mvwprintw(contents,4,2,"       %c%c%c%c         %c%c     %c%c%c%c%c",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,5,2,"      %c%c%c%c%c%c       %c%c      %c%c%c%c%c",c,c,c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,6,2,"      %c%c  %c%c     %c%c%c%c       %c%c%c ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,7,2,"      %c%c  %c%c   %c%c  %c%c       %c%c%c ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,8,2,"      %c%c %c%c   %c%c   %c%c        %c  ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,9,2,"       %c%c%c  %c %c%c%c%c%c %c%c          ",c,c,c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,10,2,"     %c%c  %c%c%c    %c%c%c          %c  ",c,c,c,c,c,c,c,c,c);
        mvwprintw(contents,11,2,"    %c                       %c%c%c ",c,c,c,c);
        mvwprintw(contents,12,2,"                             %c ",c);
        wattroff(contents,COLOR_PAIR(2));
        mvwprintw(contents,13,2,"      Virtualage (R) ed! V1.0");
        mvwprintw(contents,14,2,"      TEXT EDITOR BASED ON VI");
        mvwprintw(contents,15,2,"    Programmed by Vineeth Kaimal");
        mvwprintw(contents,16,2,"             1GV99CS059        ");
        wattron(contents,COLOR_PAIR(2));
        mvwprintw(contents,17,2,"       Visit ed!'s homepage at");
        mvwprintw(contents,18,2,"http://www.geocities.com/edeater2001");
        wattroff(contents,COLOR_PAIR(2));
        wattroff(contents,COLOR_PAIR(2)|A_BOLD);
        box(contents,ACS_CKBOARD,ACS_CKBOARD);
        wrefresh(scontents);
        wrefresh(contents);
        if(getch()=='a')
        {
               wattron(contents,A_BOLD);
               for(int i=18;i>2;i--)
               {
                        werase(contents);
                        box(contents,ACS_CKBOARD,ACS_CKBOARD);
                        wattron(contents,COLOR_PAIR(2));
                        mvwprintw(contents,i,2,"Programmer: ");
                        wattroff(contents,COLOR_PAIR(2));
                        mvwprintw(contents,i+1,2,"Vineeth Kaimal");
                        wattron(contents,COLOR_PAIR(2));
                        mvwprintw(contents,i+2,2,"Project Guide: ");
                        wattroff(contents,COLOR_PAIR(2));
                        mvwprintw(contents,i+3,2,"Jagadishwari");
                        wattron(contents,COLOR_PAIR(2));
                        mvwprintw(contents,i+4,2,"Head of the department: ");
                        wattroff(contents,COLOR_PAIR(2));
                        mvwprintw(contents,i+5,2,"S S Ahluwalia");
                        mvwprintw(contents,i+7,2,"This editor was made as project work");
                        mvwprintw(contents,i+8,2,"for  the  Vth  semester,  CST,  VTU.");
                        mvwprintw(contents,i+10,2,"I  thank  all  my  teachers who have");
                        mvwprintw(contents,i+11,2,"made  me  capable  of  making  this"); 
                        mvwprintw(contents,i+12,2,"project.");
                        wrefresh(contents);
                        delay();
               }
               wattroff(contents,A_BOLD);
               getch();               
        }
        delwin(contents);
        delwin(scontents);
}

int delay()
{
        int i,j;
        wtimeout(stdscr,100);
        if(getch()!=ERR)
        {
                wtimeout(stdscr,-1);
                return 1;
        }
        else
        {
                wtimeout(stdscr,-1);
                return 0;
        }
}

void edhelp()
{
        WINDOW *main=newwin(23,80,1,0);
        char arr[10][30]={"File Operations","Editing options","Tools offered","Modes","QCM Mode Functions","Multiple Files","Copy/Paste using buffers","Windows in ed!","Shortcut Listing"};
        fmenu help(arr,"Where do you need help?",0,9,5,20);
        wbkgd(main,COLOR_PAIR(1)|A_BOLD);
        wrefresh(main);
        switch(help.select())
        {
                case 0 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"FILE OPERATIONS:-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\ned! opens the default file noname.txt whenever no command line parameters   are given.");
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"\n\nShortcuts Provided :");
                wattroff(main,COLOR_PAIR(10));
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+n");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Open a new file, by default this is the file called noname.txt");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+o");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Open a file.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+l");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Close a file, if the current file is the only file opened, then this            option exits the editor.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nF2");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Save a file");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nF4");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Save file with a different name");
                wprintw(main,"\n\ned! accepts multiple command line arguments specifying multiple files to be opened.");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;

                case 1 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"EDITING OPERATIONS:-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\nThe editing features of ed! include copy,cut and replace.");
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"\n\nShortcuts Provided :");
                wattroff(main,COLOR_PAIR(10));
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+y");
                wattroff(main,COLOR_PAIR(10));
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Delete Row.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+w");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Delete Word.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+b");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Begin the selection. It automatically selects till end of the current           row.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+e");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- End the selection. It can be used to add or reduce the size of                  selection. Ctrl+e should be set only after setting Ctrl+b");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+v");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Copy the selection to the current cursor location.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+x");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Cut the selection and paste to the current cursor location.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+h");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Reset and hide the selection.");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;

                case 2 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"TOOLS :-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\ned! provides a number of tools... some of which may be very helpful to a programmer.");
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"\nShortcuts Provided :");
                wattroff(main,COLOR_PAIR(10));
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+f");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Find the first occurence of the search pattern.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nF3");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Find the next occurence of the search pattern.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+r");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Find the next occurence of the search pattern and replace it.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nF9");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Compile the file.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nF10");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\t- Execute the executable obtained after compilation.");
                wprintw(main,"\nThe file is saved as .ed01.comp.cpp before compilation and the executable is named as edcompiled.exe.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n\nHighlighting ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"and ");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"Autoindentation ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"options can be toggled from the Tools menu or executing commands \"set ai\" and \"set h\" and the command prompt in QCM. Highlighting highlights C/C++keywords, preprocessor statements and strings.\nHighlighting does not adequately support /* */ for commenting. ");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                getch();
                werase(main);
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nSpelling errors ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"can be highlighted by setting spell check on. This can be done at the prompt in QCM or through the menu. Only errors present during the time spell was set will be shown, new errors will not be shown as errors. Spell checking should be set again for new errors to be detected. A maximum of 1000 errors will be detected at a time.");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;

                case 3 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"MODES:-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\ned! has 4 basic modes. ");
                wprintw(main,"The modes are displayed on the right hand side of the status bar (on top) :");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n-INS-");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\tThe Insert mode");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n-OVR-");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\tThe Replace mode.");
                wattron(main,COLOR_PAIR(9)|A_BLINK);
                wprintw(main,"\n-COM-");
                wattroff(main,COLOR_PAIR(9)|A_BLINK);
                wprintw(main,"\tThe Menu mode.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n-QCM-");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\tThe Quick Command mode.");
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"\nUse INSERT key to toggle between INS and OVR. Menu mode can be activated by    pressing F5. QCM mode is activated using ESC. i/INS is used to togo back to insert mode.");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\nIn insert mode characters are inserted between existing characters, and they arewritten over existing characters in overwrite mode. In the Menu mode,arrow keys can be used to manipulate the menus. The starting  letters  of  the  options    provided (in CAPS) can be used as shortcuts to these options in the menu mode.  If this is not possible, they can be accessed by  the  respective  order  of    appearance. i.e. by pressing 0 through 9. 0 can be used to access the 10'th option. Menus are limited to 10 options.");
                wprintw(main,"The Quick command mode assigns various editing functions to  keyboard keys.The  status bar also displays if Highlight (");
                wattron(main,COLOR_PAIR(9)|A_BLINK);
                wprintw(main,"-H-");
                wattroff(main,COLOR_PAIR(9)|A_BLINK);
                wprintw(main,") and Autoindentation(");
                wattron(main,COLOR_PAIR(9)|A_BLINK);
                wprintw(main,"-AI-");
                wattroff(main,COLOR_PAIR(9)|A_BLINK);
                wprintw(main,") are switched on. ed! provides a shell (Shortcut:- F6) that allows you to execute UNIX commands without exiting the program.");
                wprintw(main,"\nPress any key to continue...");
                wrefresh(main);
                break;

                case 4 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"The Quick Command Mode:-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\nThe QCM allows you to use character keys to perform special funtions. These    keys are listed below.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n\n<b Begin Selection>\n<e Extend Selection>\n<h Hide Selection>\n<v Copy Selection>\n<x Cut Selection>\n<dd Delete Line>\n<dw Delete Word>\n<y Delete Character>\n<Number - Goto that line with the same line number>\n<Number followed by any command - Execute the command for that many times>\n<l Make available the last command keyed in at prompt.>");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\n\nThe Keys given above are to execute quick commands. Pressing \":\" will prompt    you to enter a command similar to Ex mode in Vi. The commands accepted in this  way are given below.");
                wprintw(main,"\n\nPress any key to see the commands...");
                wrefresh(main);
                getch();
                werase(main);
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nq,q!,wq   ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Similar to their functions in Vi - in ed! they are applicable to the            current Window.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nQ,Q!      ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Similar to q and q! but are applied to all Windows.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\no         ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Open a file, can be used with an argument specifying a filename to              directly   open a file. ");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nf,fn      ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Find and Find next. these commands can also be used with arguments.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nr         ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Replace the next occurence of find pattern with a new pattern.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nset ai    ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Toggles AI Mode.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nset h     ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Toggles Highlight mode.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nset hmargin");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"/");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"set vmargin ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Set up the horizontal and vertical page margins");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nset color ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Edit colors.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n!         ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Used with a Unix command as argument. This is used to execute Unix              commands without exiting the editor or invoking the shell.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nspell     ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Update highlighting of spelling errors.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nspell off ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Removes highlighting of errors");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nset beep  ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Toggles the sounding of bell");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nl         ");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"Executes the last command keyed in.");
                wprintw(main,"\n\nSome of the other commands are : ");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\ncompile  run  shell  help  tile  untile");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;

                case 5 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"Multiple Files :-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\ned! allows you to open multiple files, a maximum of 8 at a time. The          restriction being due to the limited number of toggle keys and the assumption   that it is seldom required to open more files.");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n\nUse SHIFT+(F1-F8) to toggle between the different windows.");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\n\nThe windows can be tiled or untiled as required by the user. These options can  be exercised through the Setup Menu or by typing the commands \"tile\" and        \"untile\" in QCM mode. Files take longer to load in the TILED mode. It is recommended not to open files exceeding 1Mb in tiled mode to sustain smooth operation.");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;
                
                case 6 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"How to make use of ed!'s buffers :-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\ned! provides you with 8 buffers which are numbered from 0 to 7. These buffers   can be used as clipboards holding sections of your documents. Buffers can  be   used only in the QCM mode. To load the buffer, select the text to be  loaded    using commands <b e> and then press \"a\" followed by the buffer number you       wish to load. Loading a buffer clears any data that may have been present in it.To  paste from a buffer take the cursor to the required location and press \"z\"  followed by the buffer number from which to load the data.");
                wprintw(main,"\n\nLoading the buffers with ExcessivE amounts of data and then attempting to paste from it can cause the editor to freeze. This can also occur when using the normal select/copy/cut facility.");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;
                
                case 7 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"Description of the windows :-");
                wattroff(main,COLOR_PAIR(10));
                wprintw(main,"\n\ned! has three main windows, the edit window, the status window and the help window. More than one edit windows may be open at a time. The active edit window is the one which has the brightest foreground color.");
                wprintw(main,"\n\nThe help window is the one seen at the bottom of the screen. It proided context sensitive help in all modes except the QCM mode. In the QCM mode the help windowturns into a command window that accepts extended commands.");
                wprintw(main,"\n\nThe status window is present at the top of the screen. It provides various information about the currently opened file and also displays the current mode. The  format is given below.");
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"\n\nStatus bar :-");
                wattroff(main,COLOR_PAIR(10));
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\ned!");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main," [filename] [percentage of file behind current line] W[Current Window no./8] C[Column number of cursor/total number of columns in window] L[Current line number/Total number of lines]"); 
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"-SVD/MFD- -INS/OVR/COM/QCM- -AI/ - -H/ -");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\n\n-SVD/MFD- tells you whether the file has been modified after the last save.\nINS,OVR,COM,QCM,AI & H  are mode specifiers.");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;
                
                case 8 :
                wbkgd(main,COLOR_PAIR(1)|A_BOLD);
                wattron(main,COLOR_PAIR(10));
                wprintw(main,"All shortcuts in ed! have been listed below :-");
                wattroff(main,COLOR_PAIR(10));
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\nFunction Keys :-");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\nF1  Help\nF2  Save\nF3  Find next occurence of the pattern\nF4  Save as..\nF5  Menu(Only in insert mode)\nF6  Shell\nF7  Repaint Screen\nF9  Compile\nF10 Run previous compiled program\nF12 Quit");
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"\n\nFollowing shortcut keys use the Ctrl Key, they are valid  only  in  the  Insert/Replace mode");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+b Begin Selection\nCtrl+c Terminate program (Interrupt) - Causes abnormal termination.\nCtrl+e Extend Selection\nCtrl+f Search for a from the beginning of the file\nCtrl+g Go to Line\nCtrl+l Close current window");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                getch();
                werase(main);
                wattron(main,COLOR_PAIR(9));
                wprintw(main,"Insert/Replace mode Ctrl keys contd.");
                wattroff(main,COLOR_PAIR(9));
                wprintw(main,"\nCtrl+n Open new Window\nCtrl+o Open a file\nCtrl+r Find and Replace\nCtrl+w Delete word\nCtrl+y Delete row\nCtrl+z Stop current job (Interrupt) - Causes abnormal termination.");
                wprintw(main,"\n\nShortcut keys and editing keys in QCM mode have already been discussed  in  the section dedicated to the same.");
                wprintw(main,"\n\nHandling on Menus has also been discussed  in  previous  sections.  Numbers   orletters or arrow keys can be used to select the required option.");
                wprintw(main,"\n\nThis does not belong here, but I don't feel like wasting all the space here...  Q> What is Virtualage?");
                wprintw(main,"\nVirtualage is the company that I own.  Unfortunately  it  exists  only   in  thevirtual hyperspace of my brain. Until  its  ultimate  realization  in  the  realworld which is inevitable, I've decided to mark all programs made my me with thetrademark. :-)");
                wprintw(main,"\n\nPress any key to continue...");
                wrefresh(main);
                break;

                default:
                return;

        }
        getch();
}

