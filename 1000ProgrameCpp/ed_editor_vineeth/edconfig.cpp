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


class  edconfig
{
        int editbg,editfg;
        int menubg,menufg;
        int selmenubg,selmenufg;
        int errorbg,errorfg;
        int statusbg,statusfg;
        int highlightbg,highlightfg;
        int stringbg,stringfg;
        int includebg,includefg;
        int selectcolor();
        public:
        edconfig();
        int select(WINDOW*);
        void loaddefault();
        void writeconfig();
        void readconfig();
        void loadcolors();
};

edconfig :: edconfig()
{
        FILE *ptr=0;
        ptr=fopen(CFG,"r");
        if(ptr==NULL)
        {
                loaddefault();
                writeconfig();
        }
        else
        readconfig();
}

int edconfig :: select(WINDOW *W)
{
    int flag;
    char select_arr[10][30]={"Edit Window","Menu","Selected Menu","Status/Help Window","Message/Input Window","Keywords/Error Highlighting","String & comment Highlighting","Preprocessor Highlighting","Save Changes and Quit","Restore Default Colors"};
    fmenu select(select_arr,"COLOR EDITING OPTIONS",0,10,5,5);
    char fgbg_arr[10][10]={"Foregrnd","Backgrnd"};
    vmenu fgbg(fgbg_arr,"EDIT F/B",0,2,5,40);
    while(1)
    {
        wrefresh(W);
        switch(select.select())
        {
                case 0 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        editfg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        editbg=flag;
                }
                break;

                case 1 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        menufg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        menubg=flag;
                }
                break;

                case 2 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        selmenufg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        selmenubg=flag;
                }
                break;

                case 3 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        statusfg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        statusbg=flag;
                }
                break;

                case 4 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        errorfg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        errorbg=flag;
                }
                break;

                case 5 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        highlightfg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        highlightbg=flag;
                }
                break;

                case 6 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        stringfg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        stringbg=flag;
                }
                break;

                case 7 :
                flag=fgbg.select();
                if(flag==0)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        includefg=flag;
                }
                else if(flag==1)
                {
                        flag=selectcolor();
                        if(flag!=-1)
                        includebg=flag;
                }
                break;

                case 8 :
                loadcolors();
                writeconfig();
                return 1;

                case 9 :
                loaddefault();
                loadcolors();
                writeconfig();
                return 1;

                default:
                return 0;
        }
    }
}

int edconfig :: selectcolor()
{
        char fgbg_arr[10][10]={"Black","Blue","Red","Yellow","Green","Magenta","Cyan","White"};
        vmenu fgbg(fgbg_arr,"COLORS",0,8,5,60);
        int opt=fgbg.select();
        switch(opt)
        {
                case 0 :
                return COLOR_BLACK;
                case 1 :
                return COLOR_BLUE;
                case 2 :
                return COLOR_RED;
                case 3 :
                return COLOR_YELLOW;
                case 4 :
                return COLOR_GREEN;
                case 5 :
                return COLOR_MAGENTA;
                case 6 :
                return COLOR_CYAN;
                case 7 :
                return COLOR_WHITE;
                default :
                return -1;
        }
}

void edconfig :: loaddefault()
{
        editbg=COLOR_BLUE;
        editfg=COLOR_YELLOW;
        menubg=COLOR_WHITE;
        menufg=COLOR_BLUE;
        selmenubg=COLOR_GREEN;
        selmenufg=COLOR_RED;
        errorbg=COLOR_RED;
        errorfg=COLOR_WHITE;
        statusbg=COLOR_BLACK;
        statusfg=COLOR_GREEN;
        highlightbg=COLOR_BLUE;
        highlightfg=COLOR_RED;
        stringbg=COLOR_BLUE;
        stringfg=COLOR_WHITE;
        includebg=COLOR_BLUE;
        includefg=COLOR_MAGENTA;
}

void edconfig :: readconfig()
{
        FILE *ptr=fopen(CFG,"r");
        size_t size=sizeof(edconfig);
        fread(this,size,1,ptr);
        fclose(ptr);
}

void edconfig :: writeconfig()
{
        FILE *ptr=fopen(CFG,"w");
        size_t size=sizeof(edconfig);
        fwrite(this,size,1,ptr);
        fclose(ptr);
}

void edconfig :: loadcolors()
{
        init_pair(1,editfg,editbg);   //edit screen
        init_pair(2,statusbg+1,statusbg);   //mode specifier
        init_pair(3,menufg,menubg);   //menus
        init_pair(4,selmenufg,selmenubg);   //selected menu
        init_pair(5,errorfg,errorbg);    //errors &&reminders
        init_pair(6,statusfg,statusbg);  //other windows
        init_pair(7,COLOR_BLACK,COLOR_BLACK);   //shadow effects
        init_pair(8,statusfg,statusbg);    //status bar and help bar
        init_pair(9,highlightfg,highlightbg);    //highlight for keywords
        init_pair(10,stringfg,stringbg);   //string
        init_pair(11,includefg,includebg);   //include
}


