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

class dochandler;
int TILE=1;

class delem
{
        doc *document;
        int dLMARGIN;
        int dRMARGIN;
        int dTMARGIN;
        int dBMARGIN;
        int dmaxindex;
        int dHIGHLIGHT;
        int dAUTOINDENT;
        int dMODE;
        int dSAVE;
        int dMAXMIS;
        char filename[255];
        int dx,dy;
        public:
        friend dochandler;
};

class dochandler
{
        delem docs[8];
        int inuse[8];
        public:
        dochandler();
        int adddoc(doc **,char*,int*,int*);
        doc* activate(int,doc**,char*,int*,int*);
        doc* closedoc(doc**,char*,int*,int*);
        void update(doc**,char *,int,int);
        void autotile(doc**,char*,int *,int*),untile(doc**,char*,int *,int*);;
        void refreshbak(doc**);
};

dochandler::dochandler()
{
        for(int i=0;i<8;i++)
        inuse[i]=0;
}

int dochandler :: adddoc(doc **ptr,char *filename,int *locx,int *locy)
{
        int i;
        for(i=0;i<8;i++)
        if(inuse[i]==0)
        break;
        if(i==8)
        {
                delete *ptr;            //////////////////////////////////////////////////////////////////////////////
                i=0;
                LMARGIN=docs[i].dLMARGIN;
                RMARGIN=docs[i].dRMARGIN;
                TMARGIN=docs[i].dTMARGIN;
                BMARGIN=docs[i].dBMARGIN;
                maxindex=docs[i].dmaxindex;
                HIGHLIGHT=docs[i].dHIGHLIGHT;
                AUTOINDENT=docs[i].dAUTOINDENT;
                MODE=docs[i].dMODE;
                SAVE=docs[i].dSAVE;
                MAXMIS=docs[i].dMAXMIS;
                strcpy(filename,docs[i].filename);
                *ptr=docs[i].document;
                WIN=i;
                *locy=docs[i].dy;
                *locx=docs[i].dx;
                return 0;
        }
        docs[i].document=*ptr;
        docs[i].dLMARGIN=LMARGIN;
        docs[i].dRMARGIN=RMARGIN;
        docs[i].dTMARGIN=TMARGIN;
        docs[i].dBMARGIN=BMARGIN;
        docs[i].dmaxindex=maxindex;
        docs[i].dHIGHLIGHT=HIGHLIGHT;
        docs[i].dAUTOINDENT=AUTOINDENT;
        docs[i].dMODE=MODE;
        docs[i].dSAVE=SAVE;
        docs[i].dMAXMIS=MAXMIS;
        docs[i].dy=TMARGIN;
        docs[i].dx=LMARGIN;
        strcpy(docs[i].filename,filename);
        inuse[i]=1;
        WIN=i;
        if(TILE)
        autotile(ptr,filename,locx,locy);
        WINDOW *B=newwin(0,0,0,0);
        wrefresh(B);
        delwin(B);
        return 1;
}

void dochandler :: update(doc **ptr,char *filename,int locx,int locy)       //very imporatnt to update before adding documents
{
        int i;
        for(i=0;i<8;i++)
        if(inuse[i]&&docs[i].document==*ptr)
        break;
        docs[i].dLMARGIN=LMARGIN;
        docs[i].dRMARGIN=RMARGIN;
        docs[i].dTMARGIN=TMARGIN;
        docs[i].dBMARGIN=BMARGIN;
        docs[i].dmaxindex=maxindex;
        docs[i].dHIGHLIGHT=HIGHLIGHT;
        docs[i].dAUTOINDENT=AUTOINDENT;
        docs[i].dMODE=MODE;
        docs[i].dSAVE=SAVE;
        docs[i].dMAXMIS=MAXMIS;
        strcpy(docs[i].filename,filename);
        docs[i].dy=locy;
        docs[i].dx=locx;
}


doc* dochandler::activate(int i,doc **ptr,char *filename,int *locx,int *locy)
{
        if(inuse[i]==0)
        return 0;
        LMARGIN=docs[i].dLMARGIN;
        RMARGIN=docs[i].dRMARGIN;
        TMARGIN=docs[i].dTMARGIN;
        BMARGIN=docs[i].dBMARGIN;
        maxindex=docs[i].dmaxindex;
        HIGHLIGHT=docs[i].dHIGHLIGHT;
        AUTOINDENT=docs[i].dAUTOINDENT;
        MODE=docs[i].dMODE;
        SAVE=docs[i].dSAVE;
        MAXMIS=docs[i].dMAXMIS;
        strcpy(filename,docs[i].filename);
        *locy=docs[i].dy;
        *locx=docs[i].dx;
        *ptr=docs[i].document;
        WIN=i;
        WINDOW *B=newwin(0,0,0,0);
        wrefresh(B);
        delwin(B);
        return docs[i].document;
}

doc* dochandler::closedoc(doc** ptr,char *filename,int *locx,int*locy)
{
        int i;
        for(i=0;i<8;i++)
        if(inuse[i])
        if(docs[i].document==*ptr)
        break;
        inuse[i]=0;
        delete docs[i].document;
        for(i=0;i<8;i++)
        if(inuse[i])
        break;
        if(i==8)
        return 0;
        LMARGIN=docs[i].dLMARGIN;
        RMARGIN=docs[i].dRMARGIN;
        TMARGIN=docs[i].dTMARGIN;
        BMARGIN=docs[i].dBMARGIN;
        maxindex=docs[i].dmaxindex;
        HIGHLIGHT=docs[i].dHIGHLIGHT;
        AUTOINDENT=docs[i].dAUTOINDENT;
        MODE=docs[i].dMODE;
        SAVE=docs[i].dSAVE;
        MAXMIS=docs[i].dMAXMIS;
        strcpy(filename,docs[i].filename);
        *locy=docs[i].dy;
        *locx=docs[i].dx;
        *ptr=docs[i].document;
        WIN=i;
        if(TILE)
        autotile(ptr,filename,locx,locy);
        WINDOW *B=newwin(0,0,0,0);
        wrefresh(B);
        delwin(B);
        return docs[i].document;
}


void dochandler::autotile(doc** ptr,char* filename,int *locx,int *locy)
{
        TILE=1;
        int i,num=0,count=0,tempno;
        for(i=0;i<8;i++)
        if(inuse[i])
        num++;

        int tm=1,bm=24/num;//1+23/num;

        for(i=0;i<8;i++)
        if(inuse[i])
        {
                count++;
                maxindex=docs[i].dmaxindex;
                tempno=docs[i].document->findlno();
                docs[i].document->print(SWAP3);
                docs[i].document->restart();
                docs[i].dLMARGIN=0;
                docs[i].dRMARGIN=79;
                docs[i].dTMARGIN=tm;
                docs[i].dBMARGIN=bm;
                docs[i].dmaxindex=docs[i].dRMARGIN-docs[i].dLMARGIN;
                maxindex=docs[i].dmaxindex;
                docs[i].document->restart();
                docs[i].document->load(SWAP3);
                docs[i].document->gotol(tempno);
                docs[i].document->home();
                docs[i].dy=tm;
                docs[i].dx=0;

                tm=bm+1;//tm+24/num;//23/num+1;
                bm=tm+24/num-1;//23/num;
        }

        for(i=0;i<8;i++)
        if(inuse[i])
        if(docs[i].document==*ptr)
        break;
        LMARGIN=docs[i].dLMARGIN;
        RMARGIN=docs[i].dRMARGIN;
        TMARGIN=docs[i].dTMARGIN;
        BMARGIN=docs[i].dBMARGIN;
        *locy=docs[i].dy;
        *locx=docs[i].dx;
        maxindex=docs[i].dmaxindex;

        WINDOW *B=newwin(0,0,0,0);
        wrefresh(B);
        delwin(B);
}

void dochandler::untile(doc** ptr,char* filename,int *locx,int *locy)
{
        TILE=0;
        int i,num=0,count=0,tempno;
        for(i=0;i<8;i++)
        if(inuse[i])
        num++;
        if(num%2)
        num++;

        int tm=1,bm=24;

        for(i=0;i<8;i++)
        if(inuse[i])
        {
                count++;
                maxindex=docs[i].dmaxindex;
                tempno=docs[i].document->findlno();
                docs[i].document->print(SWAP3);
                docs[i].document->restart();
                docs[i].dLMARGIN=0;
                docs[i].dRMARGIN=79;
                docs[i].dTMARGIN=tm;
                docs[i].dBMARGIN=bm;
                docs[i].dmaxindex=docs[i].dRMARGIN-docs[i].dLMARGIN;
                maxindex=docs[i].dmaxindex;
                docs[i].document->restart();
                docs[i].document->load(SWAP3);
                docs[i].document->gotol(tempno);
                docs[i].document->home();
                docs[i].dy=tm;
                docs[i].dx=0;
        }

        for(i=0;i<8;i++)
        if(inuse[i])
        if(docs[i].document==*ptr)
        break;
        LMARGIN=docs[i].dLMARGIN;
        RMARGIN=docs[i].dRMARGIN;
        TMARGIN=docs[i].dTMARGIN;
        BMARGIN=docs[i].dBMARGIN;
        *locy=docs[i].dy;
        *locx=docs[i].dx;
        maxindex=docs[i].dmaxindex;
}

void dochandler::refreshbak(doc **ptr)
{
        WINDOW *win;
        for(int i=0;i<8;i++)
        if(inuse[i]&&docs[i].document!=*ptr)
        {
                win=newwin(docs[i].dBMARGIN-docs[i].dTMARGIN,docs[i].dmaxindex+1,docs[i].dTMARGIN,docs[i].dLMARGIN);
                wbkgd(win,COLOR_PAIR(1));
                docs[i].document->editscreen(win);
                wattron(win,A_REVERSE|COLOR_PAIR(10));
                mvwprintw(win,0,0,"--Window : %d--file : %s--Activate Using <SHIFT+F%d>--",i+1,docs[i].filename,i+1);
                if(docs[i].dSAVE)
                wprintw(win," -MODIFIED-");
                else
                wprintw(win," -SAVED-");
                if(docs[i].dMODE==1)
                wprintw(win," -INS-");
                else if(docs[i].dMODE==0)
                wprintw(win," -OVR-");
                else
                wprintw(win," -QCM-");
                wattroff(win,A_REVERSE|COLOR_PAIR(10));
                wrefresh(win);
                delwin(win);
        }
}
