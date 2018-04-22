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

#include <string.h>
#include <ctype.h>
char KEYWORDS[][10]={"bool","catch","class","delete","friend","inline","new","namespace","operator","private","protected","public","tempate","this","throw","try","template","auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};

int MAXKEYS=49;


////////////////////////////////////////////////////////////////////////////////
//////////////the line class////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class doc;
class clip;

int LMARGIN=0;       //min =0 max=79
int RMARGIN=79;
int TMARGIN=1;
int BMARGIN=24;
int maxindex=RMARGIN-LMARGIN;
int HIGHLIGHT=0;          //0 none 1 c++ 2 spelling  3 spelling
int AUTOINDENT=0;
int MODE=1;     //1=insert  0-OVR   2,3-COM  QCM does not change MODE
int SAVE =0;     //0-dont save 1-save
char SPELLING[1000][100];     //spelling buffer
int MAXMIS=0;
int WIN =0;
char *BUF[8];

class line
{

        char *arr;
        int index, length;       //length is the final index in line \0, index if at
                                //end points to a \0 it jumps to next line if it reaches
                                //index number maxindex
        line *next,*prev;
        public:
        friend doc;
        friend clip;
        line();
        ~line();
};

line :: line()
{
        arr=new char[maxindex+2];
        next=prev=0;            //next and prev line ptrs are set to null
        index=length=0;         //index and length are initially NULL
        arr[0]='\0';            //initialising the string
        arr[maxindex+1]='\0';
        for(int i=1;i<maxindex;i++)
        arr[i]=' ';
}

line :: ~line()
{
        delete [] arr;
}

///////////////////////////////////////////////////////////////////////////////
///////////clip class for cut copy paste/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class clip
{
        line *begin;
        line *end;
        int bindex,endex;       //begin index and end index
        public:
        friend doc;
        clip();
};

clip :: clip()
{
        begin=end=0;
}



////////////////////////////////////////////////////////////////////////////////
//////////////the document class////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class doc
{
        line *first,*current,*screen;
        unsigned long curline,maxline;
        clip buffer;
        int movx;
        public:
        doc();
        ~doc();
        void restart(),resetscreen();         //to reload doc object
        int gotonl(),gotopl(),scrolldown(int),scrollup(int);    //moving current location and screen ptr
        void gotol(int);
        int findlno();
        line *getcurrent();
        int inschar(char), delchar(int),ovrchar(char);                      //inserting,deleting
        int load(char *,WINDOW*);                                     //loading file
        void spellready();
        void editscreen(WINDOW*,int*,int*);                   //display
        int print(char *,WINDOW *);                                   //printing to file
        void insertl(line*);                                //inserting line
        int delline(line *,int);                                 //deleting line
        int getcurline(),getmaxline();
        double getpercent();
        //following are specific funcs to carry out special jobs
        int enter(int,int=0),end(),home();
        int setcbegin(line*),setcend(line*),copy(),cut();     //funcs to set the beginning ending of a selection and to copy
        int gbufcopy(int),gbufpaste(int);
        void resetc();                                               //funt to reset selection to nothing
        int find(char*,int);
        int isstring(char *,line*,int);
        int iskeyword(char *,line*,int);
        //functions to let main interact with the line class
        int getindex(),getlength(),incindex(),decindex();
};

//constructor destructor
doc :: doc()
{
        first=new line;
        current=screen=first;
        curline=1;
        maxline=1;
        movx=0;
}

void doc :: restart()
{
        this->~doc();
        first=new line;
        current=screen=first;
        curline=1;
        maxline=1;
        movx=0;
}

void doc ::resetscreen()
{
        current=screen;
}

doc :: ~doc()
{
        while(first)
        {
                current=first;
                first=first->next;
                delete current;
        }
}

//getting current line
int doc :: getcurline()
{
        return curline;
}
int doc :: getmaxline()
{
        return maxline;
}
double doc :: getpercent()
{
        return ((double)curline/(double)maxline)*100.0;
}
//moving the current location and getting it
int doc :: gotonl()
{
        if(!current->next)
        return 0;
        if(current->length<=maxindex)
        curline++;
        current=current->next;
        if(movx<=current->length)
        current->index=movx;
        else
        current->index=current->length;
        return 1;
}

int doc :: gotopl()
{
        if(!current->prev)
        return 0;
        if(current->prev->length<=maxindex)
        curline--;
        current=current->prev;
        if(movx<=current->length)
        current->index=movx;
        else
        current->index=current->length;
        return 1;
}

void doc :: gotol(int n)
{
        int i=1;
        line *temp;
        for(temp=first;temp->next;temp=temp->next)
        if(i>=n)
        break;
        else if(temp->length<=maxindex)
        i++;
        if(n<=0)
        curline=1;
        else if(i<n)
        curline=i;
        else
        curline=n;
        screen=temp;
        current=temp;
        temp->index=0;
        movx=0;
}

int doc :: findlno()
{
        int i=1;
        line *temp;
        for(temp=first;temp!=current;temp=temp->next)
        if(temp->length<=maxindex)
        i++;
        return i;
}

line * doc :: getcurrent()
{
        return current;
}

//inserting and deleting a line
void doc :: insertl(line *ptr)          //inserts a line at the location of ptr shifting ptr down
{
        line *temp=new line;
        if(ptr==0)
        {
                line* temp2;
                for(temp2=first;temp2->next;temp2=temp2->next);
                temp2->next=temp;
                temp->prev=temp2;
                temp->next=0;
        }
        else
        {
                temp->next=ptr;
                temp->prev=ptr->prev;
                if(ptr->prev)
                ptr->prev->next=temp;
                else
                first=temp;
                ptr->prev=temp;
        }
}

int doc :: delline(line *ptr,int mode=0)   //mode is to check if fucctions is beig called by when called from outside mode shud be 1
{
        int retvalue=1;
        if(buffer.begin==ptr||buffer.end==ptr)        //hiding clip is one set pt is deleted
        {
                buffer.begin=buffer.end=0;
        }
        if(ptr->length<=maxindex&&mode) //check if mode is 1 to decrement maxline
        maxline--;
        if(ptr==first&&!first->next)
        maxline++;
        if(ptr==first)
        {
                if(first->next)
                first=first->next;
                else
                {
                        first->index=first->length=0;
                        *(first->arr)='\0';
                        current=first;
                        return 2;
                }
        }
        if(ptr==current&&ptr->next)
        current=current->next;
        else if(ptr==current&&ptr->prev)
        {
                if(ptr->prev->length<=maxindex)
                curline--;
                current=current->prev;
                retvalue=3;
        }
        if(ptr==screen&&ptr->next)             //updating screen ptr FINALLy found out what caused th seg dumps
        screen=screen->next;
        else if(ptr==screen&&ptr->prev)
        screen=screen->prev;
        if(ptr->prev)
        ptr->prev->next=ptr->next;
        if(ptr->next)
        ptr->next->prev=ptr->prev;
        delete ptr;
        return retvalue;
}


//scrolling the screen -- via the screen ptr of doc
int doc :: scrolldown(int n)
{       int i=0;
        while(1)
        {
                i++;
                if(i>n)
                break;
                if(screen->next)
                screen=screen->next;
                else
                        return i;
        }
        return i-1;
}


int doc :: scrollup(int n)
{
        int i=0;
        while(1)
        {
                i++;
                if(i>n)
                break;
                if(screen!=first)
                screen=screen->prev;
                else
                        return i;
        }
        return i-1;
}

//display

void doc :: editscreen(WINDOW *W,int *locx=0,int *locy=0)
{
        line* temp;

        int turnoffcolor=0;
        werase(W);
        int i=0,j;
        wattroff(W,A_REVERSE);
        for(temp=first;temp!=screen;temp=temp->next)
        {
                if(temp==buffer.begin)       //to check if begin of selection is before scrren
                {
                        wattron(W,A_REVERSE);
                }
                if(temp==buffer.end)
                {
                        wattroff(W,A_REVERSE);
                }
        }
        temp=screen;
        if(HIGHLIGHT==1)
        {
                temp=screen;
                while(1)
                if(temp->prev&&temp->prev->length==maxindex+1)
                temp=temp->prev;
                else
                break;
                while(temp!=screen)
                {
                        int tmp;
                        for(int k=0;k<=temp->length;k++)
                        if(turnoffcolor==-7)
                        turnoffcolor=tmp;
                        else if(turnoffcolor==-6)
                        turnoffcolor--;
                        else if(isstring("\\\"",temp,k))        //spl chars are not spl chars eg \"
                        {
                                tmp=turnoffcolor;
                                turnoffcolor=-6;
                        }
                        else if(isstring("//",temp,k)&&turnoffcolor==0)
                        {
                                        turnoffcolor=-3;
                                        wattron(W,COLOR_PAIR(10));
                        }
                        else if(turnoffcolor==0&&*(temp->arr+k)=='\"')
                        {
                                wattron(W,COLOR_PAIR(10));
                                turnoffcolor=-4;
                        }
                        else if(turnoffcolor==-4&&*(temp->arr+k)=='\"')
                        {
                                wattroff(W,COLOR_PAIR(10));
                                turnoffcolor=0;
                        }
                        temp=temp->next;
                }
        }

        temp=screen;     //initialising temp to screen
        while(1)
        {
                /*
                -2 encountered a /*
                -3 encountered a //
                -4 string
                -5 string
                -6,-7 consider next character as a normal char eg \"
                */
                for(j=0;j<=temp->length;j++)
                {
                        int tmp;
                        if(HIGHLIGHT==1)   //turnoffcolor=0 or greater means it is open for highlighting
                        {
                                if(turnoffcolor>0)
                                turnoffcolor--;

                                 if(turnoffcolor==-7)
                                        turnoffcolor=tmp;
                                else if(turnoffcolor==-6)
                                        turnoffcolor-=1;
                                else if(isstring("\\\"",temp,j))
                                {
                                tmp=turnoffcolor;
                                turnoffcolor=-6;
                                }

                                if(turnoffcolor==-3&&j==0&&temp->prev->length<=maxindex)
                                {
                                        wattroff(W,COLOR_PAIR(10));
                                        turnoffcolor=0;
                                }
                                if(turnoffcolor==0)
                                {
                                        if(isstring("#",temp,j))
                                        {
                                                wattron(W,COLOR_PAIR(11));
                                                turnoffcolor=-3;
                                        }
                                }
                                if(turnoffcolor>=0)
                                {
                                        if(turnoffcolor==0)     //HIGHLIGHTING KEYWORDS
                                        wattroff(W,COLOR_PAIR(9));
                                        for(int i=0;i<MAXKEYS;i++)
                                        if(iskeyword(KEYWORDS[i],temp,j))
                                        {
                                                wattron(W,COLOR_PAIR(9));
                                                turnoffcolor=strlen(KEYWORDS[i]);
                                                break;
                                        }
                                        if(isstring("//",temp,j))
                                        {
                                                turnoffcolor=-3;
                                                wattron(W,COLOR_PAIR(10));
                                        }
                                        if(isstring("/*",temp,j))
                                        turnoffcolor=-2;

                                        if(turnoffcolor==0&&*(temp->arr+j)=='\"')
                                        {
                                                wattron(W,COLOR_PAIR(10));
                                                turnoffcolor=-4;
                                        }
                                }
                                else if(turnoffcolor==-2)
                                {
                                        if(isstring("*/",temp,j))
                                        turnoffcolor=0;
                                }
                                else if(turnoffcolor==-4&&*(temp->arr+j)=='\"')
                                turnoffcolor=-5;
                                else if(turnoffcolor==-5)
                                {
                                        wattroff(W,COLOR_PAIR(10));
                                        turnoffcolor=0;
                                }
                        }
                        if(HIGHLIGHT==2||HIGHLIGHT==3)
                        {
                                if(turnoffcolor==0)
                                {
                                        wattroff(W,COLOR_PAIR(9));
                                        for(int i=0;i<MAXMIS;i++)
                                        {
                                                if(iskeyword(SPELLING[i],temp,j))
                                                {
                                                        turnoffcolor=strlen(SPELLING[i])-1;
                                                        wattron(W,COLOR_PAIR(9));
                                                        break;
                                                }
                                        }
                                }
                                else if(turnoffcolor>0)
                                turnoffcolor--;
                        }
                        if(temp==buffer.begin&&j==buffer.bindex)
                                wattron(W,A_REVERSE);
                        if(temp==buffer.end&&j==buffer.endex)
                                wattroff(W,A_REVERSE);
                        if(*(temp->arr+j)=='\0'&&temp->length<=maxindex)
                        waddch(W,'\n');
                        else  if(*(temp->arr+j)!='\0')
                        waddch(W,*(temp->arr+j));
                }
                temp=temp->next;

                i++;
                if(i==BMARGIN-TMARGIN||temp==0)
                break;          //return
        }
        while(i<BMARGIN-TMARGIN)
        {
                wprintw(W,"~");
                for(j=0;j<maxindex-1;j++)
                wprintw(W," ");
                wprintw(W,"~");
                i++;
        }
        if(locy)
        {
                *locy=0;
                i=0;
                for(temp=screen;temp!=current;temp=temp->next)
                i++;
                *locy=i+TMARGIN;
        }
        if(locx)
        *locx=LMARGIN+current->index;


}

void doc :: spellready()
{
        line *temp;
        char string[200];
        MAXMIS=0;
        FILE *fptr=fopen(SWAP1,"wb");
        int i=0,j=-1;
        for(temp=first;temp;temp=temp->next)
        {
                fprintf(fptr,"%s",temp->arr);
                if(temp->length<=maxindex&&temp->next)
                fprintf(fptr,"\n");
        }
        fclose(fptr);
        strcpy(string,"spell ");
        strcat(string,SWAP1);
        strcat(string,">");
        strcat(string,SWAP2);
        system(string);
        fptr=fopen(SWAP2,"rb");
        i=0,j=-1;
        while(1)
        {
                char ch=fgetc(fptr);
                if(ch==EOF||i==999)
                break;
                else if(ch=='\n')
                {
                        SPELLING[i][++j]='\0';
                        i++;
                        j=-1;
                        MAXMIS++;
                }                        else
                SPELLING[i][++j]=ch;
        }
        fclose(fptr);
}

//printing to file
int doc :: print(char *filename,WINDOW *status=0)
{
        FILE *ptr;
        unsigned long i=0;
        ptr=fopen(filename,"wb");
        if(!ptr)
        return 0;
        line *temp;
        for(temp=first;temp;temp=temp->next)
        {
                fprintf(ptr,"%s",temp->arr);
                if(temp->length<=maxindex&&temp->next)
                {
                        i++;
                        fprintf(ptr,"\n");
                        if(status)
                        {
                                werase(status);
                                wprintw(status,"Saving... %0.0lf percent completed.",(double)i/(double)maxline*100.0);
                                wrefresh(status);
                        }
                }
        }
        fclose(ptr);
        return 1;
}


int doc :: load(char *filename,WINDOW *status=0)
{
        FILE *ptr;
        line *temp;
        int retvalue =1;
        ptr=fopen(filename,"rb");
        if(!ptr)
        return -1;
        werase(status);
        wprintw(status,"Loading...");
        wrefresh(status);

        while(1)
        {
            char ch=fgetc(ptr);
            if(ch==EOF)
            break;
            else if(ch=='\n')
            {
                temp=new line;
                temp->prev=current;
                current->next=temp;
                temp->next=0;
                *(current->arr+current->index)='\0';
                current=temp;
                maxline++;
            }
            else if(ch=='\t')
            {
                inschar(' ');
                while(current->index%8!=0)
                inschar(' ');
            }
            else if(isprint(ch))
            {
                if(current->length==maxindex)          //get a new line if overflow!
                {
                        temp=new line;
                        temp->prev=current;
                        current->next=temp;
                        temp->next=0;
                }
                *(current->arr+current->index)=ch;
                current->length+=1;
                if(current->length==maxindex+1)
                        current=current->next;                             //update current
                else
                        current->index+=1;
            }
            else
            retvalue=0;
        }
        *(current->arr+current->index)='\0';
        current=first;
        current->index=0;
        fclose(ptr);
        curs_set(2);
        return retvalue;
}


//inserting and deleting characters from current line
int doc ::inschar(char ch)              //the insert function finally made it on 23-10-2001 half past two!!
{
        int i,retvalue=1;
        line *ptr=current;
        char tempch1,tempch2;
        tempch2=ch;

        /////////////////condition 1/////////////////////////////////////////////////////////////
        if(current->length==current->index)                         //if current index is at end of line
        {
                if(current->length==maxindex)          //get a new line if overflow!
                insertl(current->next);

                *(current->arr+current->index)=tempch2;
                current->length+=1;                                         //update length
                if(current->length==maxindex+1)
                {
                        current=current->next;                             //update current
                        movx=current->index;
                        return 2;
                }
                else
                {
                        current->index+=1;
                        *(current->arr+current->index)='\0';            //making the end point
                        movx=current->index;
                        return 1;
                }
        }

        /////////////////condition 2////////////////////////////////////////////////////////////////
        for(i=ptr->index;i<ptr->length;i++)                            //if index is not  at end of a PARA (not line of 80)
        {
                tempch1=*(ptr->arr+i);
                *(ptr->arr+i)=tempch2;
                tempch2=tempch1;
                if(i==ptr->length-1)                                         //check if ptr an i shud be updated - should be done only once when you are in the second last position
                {
                        if(ptr->length==maxindex)
                        insertl(ptr->next);

                        if(ptr->length==maxindex+1)
                        {
                                ptr=ptr->next;
                                i=-1;
                                continue;
                        }
                }
        }
        if(current->index==maxindex)
        {
                current=current->next;
                current->index=0;   //update index
                 retvalue =2;           //if current is changed to next line retvalue shud be 2
        }
        else
        current->index+=1;       //update index

        ptr->length+=1;              //updating ptr length
        *(ptr->arr+i)=tempch2;  //entering the last character
        *(ptr->arr+i+1)='\0';       //\0 for the last point

        movx=current->index;
        return retvalue;
}

int doc :: ovrchar(char ch)
{
        if(current->index!=current->length)
        delchar(1);
        return inschar(ch);
}

int doc ::delchar(int mode=1)             //the delete function depends on the completeness of the insert function
{
        int s=1,ind,retvalue=1;

        if((buffer.begin==current&&buffer.bindex==current->index)||(buffer.end==current&&buffer.endex==current->index))
        {
                buffer.begin=buffer.end=0;
        }

        if(mode==2)             //1-DEL 2-BKSPACE
        {
                if(current==first&&current->index==0)
                return 0;
                if(current->index>0)
                current->index-=1;
                else
                {
                        current=current->prev;
                        if(current->length==maxindex+1)
                        current->index=current->length-1;       /////check
                        else
                        current->index=current->length;
                        retvalue=2;
                }
        }

        line *ptr,*temp;

        ptr=current;
        ind=current->index;

        if(current->length==current->index)      //check if i am at the end of a line (PARA) so that i can
        {                                                              //join with the next if del is pressed
                s=0;
                if(current->next)
                {
                        current=current->next;
                        if(mode==2)
                                curline--;
                        maxline--;
                }
                else                                              //nothing to delete or join
                return 0;
        }
        else if(current->length!=current->index)        //if i am not at the end, do enter, then insert from the next line till i
                                                                        //ts end, then delete the next line till end by line, (i mean PARA)
        enter(1);
        temp= current;

        current=ptr;
        while(1)
        {
                for(int i=s;i<temp->length;i++)
                inschar(*(temp->arr+i));
                if(temp->length<=maxindex)
                {
                        delline(temp);
                        break;
                }
                else
                {
                        temp=temp->next;
                        delline(temp->prev);
                }
                s=0;
        }
        current=ptr;
        current->index=ind;
        movx=current->index;
        return retvalue;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//special functions
int  doc :: enter(int mode,int indentpermission=0)
{
        int autoindent=0;
        if(AUTOINDENT==1&&indentpermission==1)
        {
                line*temp=current;
                int i=0;
                while(1)
                if(temp->prev&&temp->prev->length==maxindex+1)
                temp=temp->prev;
                else
                break;
                while(1)
                if(temp->prev&&temp->prev->length==maxindex+1)
                temp=temp->prev;
                else
                break;
                for(int i=0;i<temp->length;i++)
                if(*(temp->arr+i)==' ')
                autoindent++;
                else
                break;

                int flag=0;             //avoiding white spaces
                temp=current;
                if(temp->prev&&temp->prev->length<=maxindex)
                for(int i=0;i<temp->index;i++)
                if(*(temp->arr+i)!=' ')
                {
                        flag=1;
                        break;
                }
                if(flag==0)
                for(int i=temp->index;i<temp->length;i++)
                if(*(temp->arr+i)==' ')
                temp->index++;
                else
                break;
        }
        line *ptr;
        if(mode==1)
        {
                if(indentpermission==1)
                {
                        curline++;
                        maxline++;
                }
                if(current->length<=maxindex)
                insertl(current->next);
                ptr=current;
                current=current->next;
                current->index=0;
                for(int i=ptr->index;i<ptr->length;i++)
                {
                        inschar(*(ptr->arr+i));
                }

                *(ptr->arr+ptr->index)='\0';
                ptr->length=ptr->index;
                current=ptr->next;
                current->index=0;
                if(AUTOINDENT==1&&indentpermission==1)
                for(int i=0;i<autoindent;i++)
                inschar(' ');
                movx=current->index;
                return 1;
        }
        else if(mode==0)
        if(current->next)
        {
                if(current->length<=maxindex&&indentpermission==1)
                curline++;
                current=current->next;
                current->index=0;
                movx=current->index;
                return 1;
        }
        return 0;
}

int doc :: end()
{
        if(current->index==maxindex)
        return 0;
        if(current->length==maxindex+1)
        {
                current->index=maxindex;
                movx=current->index;
                return 1;
        }
        current->index=current->length;
        movx=current->index;
        return 1;
}

int doc ::  home()
{
        if(current->index==0)
        return 0;
        current->index=0;
        movx=current->index;
        return 1;
}

int doc ::  setcbegin(line *ptr=0)
{
        if(ptr==0)
        ptr=current;
        buffer.begin=ptr;
        buffer.bindex=ptr->index;

        buffer.end=buffer.begin;
        buffer.endex=ptr->length;
        return 1;
}

int doc :: setcend(line *ptr=0)
{
        if(ptr==0)
        ptr=current;
        buffer.end=ptr;
        buffer.endex=ptr->index;
        return 1;
}

void doc :: resetc()
{
        buffer.begin=0;
        buffer.end=0;
}


int doc :: copy()
{
        char *buf;
        line *temp1;
        unsigned long i=1;
        if(buffer.begin==0||buffer.end==0)
        return 0;

        for(temp1=  buffer.begin;temp1!=buffer.end;temp1=temp1->next)
        i++;
        buf=new char[i*(maxindex+1)];        //finding how much memory is needed

        line *temp2=current;
        int temp=current->index;
        if(buffer.begin==0)
        return 0;
        int s,e,count=-1;
        for(temp1=  buffer.begin;;)
        {
                if(temp1==buffer.begin)                         //setting start and end points at each line
                {                                                               //depending on the conditions
                        s=buffer.bindex;
                        if(buffer.begin==buffer.end)
                        e=buffer.endex;
                        else
                        e=temp1->length;
                }
                else if(temp1==buffer.end)
                {
                        s=0;
                        e=buffer.endex;
                }
                else
                {
                        s=0;
                        e=temp1->length;
                }


                if(temp1!=buffer.begin&&temp1->prev)                 //loading the buffer
                if(temp1->prev->length<=maxindex)
                buf[++count]='\n';
                for(i=s;i<e;i++)
                {
                        buf[++count]=*(temp1->arr+i);
                }

                if(buffer.begin==buffer.end)            ///the boundary checking ->if begin==end ,execute loop only once
                break;
                else if(temp1==buffer.end) //temp1->prev WILL exist if first condition is not satisfied
                break;
                else
                temp1=temp1->next;                    //else move on to next line
        }
        buf[++count]='\0';
        for(i=0;buf[i]!='\0';i++)
        if(buf[i]=='\n')
        {
                maxline++;
                enter(1);
        }
        else
        inschar(buf[i]);
        current=temp2;
        current->index=temp;
        return 1;
}

int doc :: cut()
{
        char *buf;
        int Line=curline;
        line *temp1;
        unsigned long i=1;
        if(buffer.begin==0||buffer.end==0)
        return 0;

        for(temp1=  buffer.begin;temp1&&temp1!=buffer.end;temp1=temp1->next) //finding how much memory is needed
        i++;
        int retvalue=i-1;
        if(!temp1)       //if buffer.end does not lie after begin
        return 0;
        buf=new char[i*(maxindex+1)+1];             //generating buffer
        int count=-1;
        for(temp1=buffer.begin;temp1!=buffer.end->next;temp1=temp1->next)
        {
                int start,limit;
                if(temp1==buffer.end)
                limit=buffer.endex-1;    //will work even if it becomes -1
                else
                limit=temp1->length;
                if(temp1==buffer.begin)
                start=buffer.bindex;
                else
                start=0;
                for(int j=start;j<=limit;j++)
                if(j==temp1->length&&temp1->length<=maxindex)
                buf[++count]='\n';
                else if(j==temp1->length&&temp1->length==maxindex+1)
                break;
                else
                buf[++count]=*(temp1->arr+j);
        }

        temp1=current;                  //delete the section
        int tmp=current->index;
        current=buffer.begin;
        current->index=buffer.bindex;
        for(i=0;i<=count;i++)
        delchar();
        current=temp1;
        current->index=tmp;

         buffer.begin=current;
         buffer.bindex=current->index;
         for(i=0;i<=count;i++)
         {
                if(buf[i]=='\n')
                enter(1);
                else
                inschar(buf[i]);
         }
        buffer.end=current;
        buffer.endex=current->index;
        current=temp1;
        current->index=tmp;
        buffer.begin=current;
        buffer.bindex=current->index;
        curline=Line;
        return retvalue;
}


int doc :: gbufcopy(int handle)
{
        line *temp1;
        unsigned long i=1;
        if(buffer.begin==0||buffer.end==0)
        return 0;

        for(temp1=  buffer.begin;temp1!=buffer.end;temp1=temp1->next)
        i++;
        if(BUF[handle])
        delete BUF[handle];
        BUF[handle]=new char[i*(maxindex+1)];        //finding how much memory is needed
        line *temp2=current;
        int temp=current->index;
        if(buffer.begin==0)
        return 0;
        int s,e,count=-1;
        for(temp1=  buffer.begin;;)
        {
                if(temp1==buffer.begin)                         //setting start and end points at each line
                {                                                               //depending on the conditions
                        s=buffer.bindex;
                        if(buffer.begin==buffer.end)
                        e=buffer.endex;
                        else
                        e=temp1->length;
                }
                else if(temp1==buffer.end)
                {
                        s=0;
                        e=buffer.endex;
                }
                else
                {
                        s=0;
                        e=temp1->length;
                }


                if(temp1!=buffer.begin&&temp1->prev)                 //loading the buffer char array??change it to dynamic
                if(temp1->prev->length<=maxindex)
                BUF[handle][++count]='\n';
                for(i=s;i<e;i++)
                {
                        BUF[handle][++count]=*(temp1->arr+i);
                }

                if(buffer.begin==buffer.end)            ///the boundary checking ->if begin==end ,execute loop only once
                break;
                else if(temp1==buffer.end) //temp1->prev WILL exist if first condition is not satisfied
                break;
                else
                temp1=temp1->next;                    //else move on to next line
        }
        BUF[handle][++count]='\0';
        current=temp2;
        current->index=temp;
        return 1;
}

int doc :: gbufpaste(int handle)
{
        unsigned long i;
        if(!BUF[handle])
        return 0;
        line *temp=current;
        int ind=current->index;
        for(i=0;BUF[handle][i]!='\0';i++)
        if(BUF[handle][i]=='\n')
        {
                maxline++;
                enter(1);
        }
        else
        inschar(BUF[handle][i]);
        current=temp;
        current->index=ind;
        return 1;
}


int doc :: find(char * str,int mode)
{
        line *temp1;
        int Line=curline;
        int i;
        if(mode==0)                                       //0-from beginning 1-current
        {
                temp1=first;
                curline=1;
                i=0;
        }
        else
        {
                temp1=current;
                i=temp1->index+1;
                if(i==temp1->length)
                {
                        if(temp1->next)
                        {
                                temp1=temp1->next;
                                i=0;
                        }
                        else
                        return 0;
                }
        }

        for(;temp1;temp1=temp1->next)
        {
                for(;i<temp1->length;i++)
                if(isstring(str,temp1,i))
                {
                        screen=temp1;
                        current=temp1;
                        current->index=i;
                        return 1;
                }
                i=-1;
                if(temp1->length<=maxindex)
                curline++;
        }
        curline=Line;
        return 0;
}



int doc :: isstring(char * str,line *temp1,int index)
{
        int i,j;
        for(i=0,j=index;i<strlen(str);i++,j++)
        {
                if(j==temp1->length)
                {
                        if(temp1->length!=maxindex+1)
                        return 0;
                        j=0;
                        if(temp1->next)
                        temp1=temp1->next;
                        else
                        return 0;
                        if(str[i]!=*(temp1->arr+j))
                        return 0;
                }
                else
                if(str[i]!=*(temp1->arr+j))
                return 0;
        }
        return 1;
}

int doc :: iskeyword(char * str,line *temp1,int index)
{
        int i=0,j=index;
        if(j==0&&temp1->prev)
        {
                if(temp1->prev->length==maxindex+1)
                if(isalnum(*(temp1->prev->arr+maxindex)))
                return 0;
        }
        else
        {
                j--;
                if(isalnum(*(temp1->arr+j)))
                return 0;
        }
        for(i=0,j=index;i<strlen(str);i++,j++)
        {
                if(j==temp1->length)
                {
                        if(temp1->length!=maxindex+1)
                        return 0;
                        j=0;
                        if(temp1->next)
                        temp1=temp1->next;
                        else
                        return 0;
                        if(str[i]!=*(temp1->arr+j))
                        return 0;
                }
                else
                if(str[i]!=*(temp1->arr+j))
                return 0;
        }
        if(j==temp1->length&&temp1->length<maxindex+1)
        return 1;
        else if(j>=maxindex+1)
        {
                j=0;
                temp1=temp1->next;
        }
        if(!isalnum(*(temp1->arr+j)))
        return 1;
        return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//line class interaction thru doc

int doc :: getindex()
{
        return current->index;
}

int doc :: getlength()
{
        return current->length;
}

int doc :: incindex()
{
        if(current->index<maxindex)
        {
                if(current->index<current->length)
                {
                        current->index+=1;
                        movx=current->index;
                        return 1;
                }
                else
                return 0;
        }
        else if(current->index==maxindex)
        {
                if(current->next)
                current=current->next;
                else
                return 0;
                current->index=0;
                movx=current->index;
                return 2;
        }
}

int doc :: decindex()
{
        if(current->index>0)
        {
                current->index-=1;
                movx=current->index;
                return 1;
        }
        else if(current->prev)
        if(current->prev->length>maxindex)
        {
                current=current->prev;
                current->index=maxindex;
                movx=current->index;
                return 2;
        }
        else
        return 0;
}


