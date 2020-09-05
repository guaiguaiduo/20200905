#include "widget.h"
#include "ui_widget.h"
using namespace std;
#include <iostream>
#include <bits/stdc++.h>
#include <QDebug>
#define random(a,b) (rand()%(b-a+1))+a
int divarea;
int samount,bwamount,bamount;
int saleamount;
double sumprice;
int psm,pdm;
double pwm;
int alldate[13];
int allweight[16];
int allspiece[4];
struct pig{
    int spiece;
    double weight;
    int days;
    pig *next;
};
class pigcircle{
    private:
        int sum;
        int ifblack;
        int number;
        pig *head;
    public:
        pigcircle();
        int getnumber();
        int getsum();
        int getifblack();
        pig *gethead();
        void sendnumber(int i);
        void sendsum(int i);
        void sendifblack(int i);
        void sendhead(pig *p);
        int  searchspiece(int i);
        int  searchdays(int i);
        double searchweight(int i);
        int pigcirclestatistics();
        void upping() ;
        void sale();
        void insert(pig *p);
};
pigcircle pc[101];
pigcircle::pigcircle()
{
    sum=0;
    ifblack=0;
}
int pigcircle::getsum()
{
    return sum;
 }
int pigcircle::getnumber()
{
    return number;
}
pig* pigcircle::gethead()
{
    return head;
}
int pigcircle::getifblack()
{
    return ifblack;
}
void pigcircle::sendnumber(int i)
{
    number=i;
}
void pigcircle::sendifblack(int i)
{
    ifblack=i;
}
void pigcircle::sendsum(int i)
{
    sum=i;
}
void pigcircle::sendhead(pig *p)
{
    head=p;
}
int pigcircle::searchspiece(int i)
{
    if(i>sum) return -1;
    int j;
    pig *p=head;
    for(j=1;j<i;j++)
    p=p->next;
    return p->spiece;
}
double pigcircle::searchweight(int i)
{
    if(i>sum) return -1;
    int j;
    pig *p=head;
    for(j=1;j<i;j++)
    p=p->next;
    return p->weight;
}
int pigcircle::searchdays(int i)
{
    if(i>sum) return -1;
    int j;
    pig *p=head;
    for(j=1;j<i;j++)
    p=p->next;
    return p->days;
}
int pigcirclestatistics(int t,int i,pigcircle pc[])
{
    int j;
    pig *p=pc[t].gethead();
    int ifblack1=pc[t].getifblack();
    samount=bwamount=bamount=0;
    if(ifblack1==1)
    {
        bamount=pc[t].getsum();
        return 1;
    }
    else
    {
        while(p!=NULL)
        {
            if(p->spiece==2)
            samount+=1;
            else
            bwamount+=1;
            p=p->next;
        }
        return 2;
    }
}
void pigcircle::upping()
{
    pig *p=head;
    for(int i=1;i<=sum;i++)
    {
        p->weight=p->weight+(random(0,12))/10.0;
        p->days++;
        p=p->next;
    }
}
void allupping(pigcircle pc[])
{
    int i;
    for(i=1;i<=100;i++)
    pc[i].upping();
}
void pigcircle::sale()
{
    int i=1;
    pig *p=head,*p1,*p2;
    p1=head;
    for(;i<=sum;i++)
    {
        if(p->weight>75||p->days>360)
        {
          if(p->spiece==1)
            sumprice+=p->weight*15;
           else if(p->spiece==2)
           sumprice+=p->weight*7;
           else
           sumprice+=p->weight*6;
           saleamount++;
           if(p==head)
           {
            p=p->next;
            head=p1=p;
           }
           else if(p1==p&&p!=head)
           {
            p=p->next;
            p1=p;
           }
           if(p1!=p)
           {
            p2=p;
            p1->next=p->next;
            p=p->next;
           }
        }
        else
        {
         p1=p;
         p=p->next;
        }
    }
}
void saleall(pigcircle pc[])
{
    int i;
    saleamount=sumprice=0;
    for(i=1;i<=100;i++)
    pc[i].sale();
    ofstream destFile("buyandsale.txt",ios::app);
    destFile<<"sale"<<endl<<' '<<saleamount<<' '<<sumprice<<endl;
    destFile.close();
}
void initial(pigcircle pc[])
{
    int i,j;
    pig *p,*p1;
    for(i=1;i<=100;i++)
    {
        pc[i].sendsum(2);
        pc[i].sendnumber(i);
        if(i<=30)
        {
            pc[i].sendifblack(1);
            p=new pig;
            p->spiece=1;
            p->weight=(random(200,500))/10.0;
            p->days=0;
            for(j=1;j<=2;j++)
            {
               if(j==1) p1=p;
               else     p1->next=p;
            }
        }
        else
        {
            pc[i].sendifblack(0);
            p=new pig;
            p->spiece=random(2,3);
            p->weight=(random(200,500))/10.0;
            p->days=0;
            for(j=1;j<=2;j++)
            {
            if(j==1) p1=p;
               else  p1->next=p;
            }
        }
        pc[i].sendhead(p1);
    }
    divarea=31;
}
void outFile(pigcircle pc[])
{
    ofstream destFile("pigsmessage.txt",ios::out);
    int i,j,sum;
    pig *p,*p1;
    for(i=1;i<=100;i++)
    {
        p=pc[i].gethead();
        sum=pc[i].getsum();
        destFile<<pc[i].getnumber()<<endl;
        for(j=1;j<=sum;j++)
        {
            destFile<<p->spiece<<' '<<p->weight<<' '<<p->days<<endl;
            p1=p;
            p=p->next;
        }
    }
     destFile.close();
}
void inFile(pigcircle pc[])
{
    ifstream srcFile("pigsmessage.txt",ios::in);
    pig *p,*p1;
    int i,j,sum,t;
    for(i=1;i<=100;i++)
    {
        sum=pc[i].getsum();
        srcFile>>t;
        pc[i].sendnumber(t);
        for(j=1;j<=sum;j++)
        {
            p1=new pig;
            srcFile>>p1->spiece>>p1->weight>>p1->days;
            if(j==1) p=p1;
            else
            {
                p->next=p1;
                p=p1;
            }
        }
    }
    srcFile.close();
}
void allmember(pigcircle pc[])
{
    int i,sum,j,t;
    for(i=1;i<=100;i++)
    {
        sum=pc[i].getsum();
        for(j=1;j<=sum;j++)
        {
            allspiece[pc[i].searchspiece(j)]++;
            alldate[pc[i].searchdays(j)/31]++;
            allweight[int(pc[i].searchweight(j)/11.0)]++;
        }
    }
}
int buypigs(pigcircle pc[],int bp,int wp,int sp)
{
    ofstream destFile("buyandsale.txt",ios::app);
    destFile<<"buy"<<endl<<"black pig"<<' '<<bp<<endl<<"big white big"<<' '<<wp<<endl<<"samll white pig"<<' '<<sp<<endl;
    destFile.close();
    int i,sum=0,ave,gs,fg,j;
    pig *p,*np,*p1;
    for(i=1;i<divarea;i++)
    sum+=pc[i].getsum();
    sum+=bp;
    if(sum>divarea*10-10) return 0;
    ave=(sum/(divarea-1))+1;
    for(i=1;i<divarea&&bp!=0;i++)
    {
        gs=pc[i].getsum();
        if(gs>=ave) continue;
        p=pc[i].gethead();
        pc[i].sendsum(ave);
        for(j=1;j<gs;j++)
        p=p->next;
         for(j=gs+1;j<=ave&&bp!=0;j++)
         {
            np=new pig;
            np->spiece=1;
            np->weight=(random(200,500))/10.0;
            np->days=0;
            p->next=np;
            bp--;
         }
     }

    for(i=divarea;i<=100;i++)
    sum+=pc[i].getsum();
    sum+=wp+sp;
    int ap=wp+sp;
    if(sum>(101-divarea)*10) return 0;
    ave=sum/(101-divarea)+1;
    for(i=divarea;i<=100&&ap!=0;i++)
    {
        gs=pc[i].getsum();
        if(gs>=ave) continue;
        p=pc[i].gethead();
        pc[i].sendsum(ave);
        for(j=1;j<gs;j++)
        p=p->next;
         for(j=gs;j<=ave&&ap!=0;j++)
         {
            np=new pig;
            np->spiece=random(2,3);
            np->weight=(random(200,500))/10.0;
            np->days=0;
            p->next=np;
            ap--;
         }
     }
     return 1;
}
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->b1,QPushButton::clicked,
            [=]()
    {
        initial(pc);
    }
            );
    connect(ui->b,QPushButton::clicked,
            [=]()
    {
        allupping(pc);
        qDebug()<<pc[2].searchweight(1)<<' '<<pc[2].searchdays(1);
    }
            );
}

Widget::~Widget()
{
    delete ui;
}
