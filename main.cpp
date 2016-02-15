#include<iostream>
#include<fstream>
#include<cmath>
#include"pixelcnt.cpp"
#include"diff.cpp"
#define pi 3.142857143;
using namespace std;
class coordinates
{
    public:
    double ra;
    double dec;
    void newcor(double*,double*,double);
};
class star:public coordinates
{
    public:
    long int id;
    double ra;
    double dec;
    double mag;
    double pixelx;
    double pixely;
    int quadrant;
    int flag;

    void check(coordinates,coordinates,coordinates,coordinates);
    void display();
    void dynamic(int);
};


double RA=0,DEC=0,ROLL=0,count=0,f=0,q=0,e=0,g=0,l=0,m=0;
 double v=0,ac=0,T=0;
int n=0,c=0;

int main()
{
    double x,y;
    coordinates A,B,C,D;
    star a[10000];
    int i=0;
    ifstream z;
    z.open("test.txt",ios::in);
   while(!z.eof())
    {
        z>>a[i].id;
        z>>a[i].ra;
        z>>a[i].dec;
        z>>a[i].mag;
        i++;
        count++;
    }

   for(i=0;i<count;i++)
    {
        a[i].ra=a[i].ra*15;
    }
    cout<<"Enter the RA and DEC in degree"<<endl;
    cin>>RA>>DEC;
    cout<<"Enter camera ROLL in degree"<<endl;
    cin>>ROLL;
    q=ROLL*(3.142857143/180);
    g=DEC*(3.142857143/180);
    e=sin(f)*5;
    if(RA<5 && RA>=0)
    {
        x=5-RA;
        y=360-x;
        A.ra=RA+5+e;
        A.dec=DEC+5;
        B.ra=y+e;
        B.dec=DEC+5;
        C.ra=y+e;
        C.dec=DEC-5;
        D.ra=RA+5+e;
        D.dec=DEC-5;
    }
    else if(RA>355 && RA<=360)
    {
        x=360-RA;
        y=5-x;
        A.ra=y+e;
        A.dec=DEC+5;
        B.ra=RA-5+e;
        B.dec=DEC+5;
        C.ra=RA-5+e;
        C.dec=DEC-5;
        D.ra=y+e;
        D.dec=DEC-5;
    }
    else
    {   cout<<"h";
        A.ra=RA+5+e;
        A.dec=DEC+5;
        B.ra=RA-5+e;
        B.dec=DEC+5;
        C.ra=RA-5+e;
        C.dec=DEC-5;
        D.ra=RA+5+e;
        D.dec=DEC-5;
    }
    cout<<"A "<<A.ra<<"\t"<<A.dec<<endl;
    cout<<"B "<<B.ra<<"\t"<<B.dec<<endl;
    cout<<"C "<<C.ra<<"\t"<<C.dec<<endl;
    cout<<"D "<<D.ra<<"\t"<<D.dec<<endl;
    if(ROLL==0 || ROLL==360)
    {
        for(i=0;i<count;i++)
        {
            a[i].check(A,C,D,B);
        }
    }
    else
    {
        A.newcor(&A.ra,&A.dec,q);
        B.newcor(&B.ra,&B.dec,q);
        C.newcor(&C.ra,&C.dec,q);
        D.newcor(&D.ra,&D.dec,q);
        cout<<"\nnew coordiantes\n";
        cout<<"A "<<A.ra<<"\t"<<A.dec<<endl;
        cout<<"B "<<B.ra<<"\t"<<B.dec<<endl;
        cout<<"C "<<C.ra<<"\t"<<C.dec<<endl;
        cout<<"D "<<D.ra<<"\t"<<D.dec<<endl;
        if(ROLL>0 && ROLL<=90)
        {

            for(i=0;i<count;i++)
            {
                a[i].check(A,C,D,B);
            }
        }
        else if(ROLL>90 && ROLL<=180)
        {
             for(i=0;i<count;i++)
             {
                 a[i].check(D,B,C,A);
             }
        }
        else if(ROLL>180 && ROLL<=270)
        {
             for(i=0;i<count;i++)
             {
                a[i].check(C,A,B,D);
             }
        }
        else if(ROLL>270 && ROLL<=360)
        {
            for(i=0;i<count;i++)
            {
                a[i].check(B,D,A,C);
            }
        }
    }

    for(i=0;i<count;i++)
    {
        if(a[i].flag==1)
            f++;
    }
    cout<<"total stars "<<f<<endl;

   cout<<"ID\tRA   \t   \tDEC   \t\tMAG   \tPIXEL\tLINE"<<endl;
    for(i=0;i<count;i++)
    {
        if(a[i].flag==1)
            {
                a[i].display();

            }
    }

    for(i=0;i<count;i++)
    {
        if(a[i].flag==1)
            {
                cout<<a[i].id<<"\t"<<a[i].ra<<"   \t"<<a[i].dec<<"   \t"<<a[i].mag<<"   \t"<<abs(a[i].pixelx)<<"\t"<<abs(a[i].pixely)<<endl;

            }
    }


    cout<<"\n------------dynamic-------------\n";

    cout<<"1.roll\n2.direction\n";
    cin>>c;
    if(c==1)
    {
        cout<<"enter the number of exposures\n";
        cin>>n;
        cout<<"enter the angular acceleration in degree/sec square and angular velocity in degree/sec\n";
        cin>>ac>>v;
        cout<<"enter the time interval between exposures in milli seconds\n";
        cin>>T;

    for(int l=1;l<=n;l++)
    {
        cout<<"\nexposure "<<l<<endl;
        cout<<"\nbefore roll\t\t\tafter roll"<<endl;
        cout<<"ID\tPIXEL\tLINE\t\tPIXEL\tLINE"<<endl;
        for(i=0;i<count;i++)
        {
            if(a[i].flag==1)
                a[i].dynamic(l);
        }
    }
    }else
    {
       a[0].dynamic(0);
    }

    return 0;
}
void coordinates::newcor(double *ra,double *dec,double b)
{
    double z;

    if(RA<6)
    {
        RA=RA+12;
        *ra=*ra+12;
        if(*ra>360)
            *ra=*ra-360;
        z=((*ra-RA)*cos(b))-((*dec-DEC)*sin(b))+RA;
        *dec=(((*ra-RA)*sin(b))+((*dec-DEC)*cos(b))+DEC);
        *ra=z;

        RA=RA-12;
        *ra=*ra-12;
        if(*ra<0)
            *ra=*ra+360;
    }
    else if(RA>354)
    {

        RA=RA-12;
        *ra=*ra-12;
        if(*ra<0)
            *ra=*ra+360;
        z=((*ra-RA)*cos(b))-((*dec-DEC)*sin(b))+RA;
        *dec=(((*ra-RA)*sin(b))+((*dec-DEC)*cos(b))+DEC);
        *ra=z;
        RA=RA+12;
        *ra=*ra+12;
        if(*ra>360)
            *ra=*ra-360;
    }
    else
    {

        z=((*ra-RA)*cos(b))-((*dec-DEC)*sin(b))+RA;
        *dec=((*ra-RA)*sin(b))+((*dec-DEC)*cos(b))+DEC;
        *ra=z;
    }

    return;

}
void star::check(coordinates p,coordinates q,coordinates r,coordinates s)
{
    int c=0;

    if(RA<5 && (dec<=p.dec && dec>=q.dec && ((ra>=0 && ra<=r.ra)||(ra>=s.ra && ra<=360))))
    {
        goto p;
    }
    else if(RA>355 && (dec<=p.dec && dec>=q.dec && ((ra>=s.ra && ra<=360)||(ra>=0 && ra<=r.ra))))
    {
        goto p;
    }

    if(dec<=p.dec && dec>=q.dec && ra<=r.ra && ra>=s.ra)
    {   p:;


        RA=RA+12;
        ra=ra+12;
        if(ra>360)
            ra=ra-360;
        if(ra>=RA)
        {

            if(dec>DEC)
                quadrant=2;
            else if(dec<DEC)
                quadrant=3;
        }
        else if(ra<=RA)
        {

            if(dec>DEC)
                quadrant=1;
            else if(dec<DEC)
                quadrant=4;

        }
         RA=RA-12;
        ra=ra-12;
        if(ra<0)
            ra=ra+360;
    }

    if(quadrant==1 || quadrant==2)
    {
        if((((dec-p.dec-((abs((p.dec-r.dec)/(p.ra-r.ra)))*(ra-p.ra)))<=0) || ((dec-p.dec-((abs((p.dec-s.dec)/(p.ra-s.ra)))*(ra-p.ra)))<=0)))//divide zero problem
            flag=1;


    }
    else if(quadrant==3 || quadrant==4)
    {
        if((((dec-q.dec-((abs((q.dec-r.dec)/(q.ra-r.ra)))*(ra-q.ra)))>=0) || ((dec-q.dec-((abs((q.dec-s.dec)/(q.ra-s.ra)))*(ra-q.ra)))>=0)))//divide zero problem
            flag=1;

    }

    return;
}
void star::display()
{

        pixelx=pixelcnt(difference(RA,ra));
        pixely=pixelcnt(abs(DEC-dec));

        if(quadrant==1)
        {
            pixelx=500+pixelx;
            pixely=500-pixely;
        }
        else if(quadrant==2)
        {
            pixelx=500-pixelx;
            pixely=500-pixely;
        }
        else if(quadrant==3)
        {
            pixelx=500-pixelx;
            pixely=500+pixely;
        }
        else if(quadrant==4)
        {
            pixelx=500+pixelx;
            pixely=500+pixely;
        }

       // cout<<id<<"\t"<<ra<<"   \t"<<dec<<"   \t"<<mag<<"   \t"<<abs(pixelx)<<"\t"<<abs(pixely)<<endl;

        return;
}

void star::dynamic(int l)
{
    double x=0,y=0,t=0.1,roll=0,s=0,r=0,dist=0,time=0,p=0,r1=0;
    double theta=0;
    int direction;


    if(c==1)
    {



                    roll=(v*t)+((ac*t*t)/2);
                    roll=roll*(3.1428571428/180);
                    display();
                    cout<<id<<"\t"<<abs(pixelx)<<"\t"<<abs(pixely)<<"\t\t";
                    newcor(&ra,&dec,roll);
                    display();
                    cout<<abs(pixelx)<<"\t"<<abs(pixely)<<endl;
                  /*  x=abs(pixelcnt(difference(RA,ra)));
                    r1=abs(pixelcnt(abs(DEC-dec)));
        if(quadrant==1)
        {
            x=500+x;
            r1=500-r1;
        }
        else if(quadrant==2)
        {
            x=500-x;
            r1=500-r1;
        }
        else if(quadrant==3)
        {
            x=500-x;
            r1=500+r1;
        }
        else if(quadrant==4)
        {
            x=500+x;
            r1=500+r1;
        }
                    cout<<id<<"\t"<<x<<"\t"<<r1<<"\t\t";
                    newcor(&ra,&dec,roll);
                    x=abs(pixelcnt(difference(RA,ra)));
                    r1=abs(pixelcnt(abs(DEC-dec)));
        if(quadrant==1)
        {
            x=500+x;
            r1=500-r1;
        }
        else if(quadrant==2)
        {
            x=500-x;
            r1=500-r1;
        }
        else if(quadrant==3)
        {
            x=500-x;
            r1=500+r1;
        }
        else if(quadrant==4)
        {
            x=500+x;
            r1=500+r1;
        }
                    cout<<x<<"\t"<<r1<<endl;*/



                    T=T*l;
                    v=v+(ac*T);



    }
    else
    {
        cout<<"enter the direction"<<endl;
        cout<<"1.up\n2.down\n3.right\n4.left\n5.diagonal upper right(dur)\n6.diagonal upper left(dul)\n7.diagonal bottom right(dbr)\n8.diagonal bottom left(dbl)\n";
        cin>>direction;
        cout<<"enter the angle in degree\n";
        cin>>theta;
        cout<<"enter the number of exposures\n";
        cin>>n;
        cout<<"enter the acceleration in degree/sec square and velocity in degree/sec\n";
        cin>>ac>>v;
        cout<<"enter the time interval between exposures in milli seconds\n";
        cin>>T;
        for(int i=1;i<=n;i++)
        {
            s=(v*t)+((ac*t*t)/2);
            cout<<"pixel length for exposure "<<i<<"="<<pixelcnt(s)<<endl;
            T=T*i;
            v=v+(ac*T);

        }

            time=(n*0.1)+((n-1)*T);
            dist=(v*time)+((ac*time*time)/2);
        switch(direction)
        {
            case 1 : DEC=DEC+dist;
                            break;
            case 2 : DEC=DEC-dist;
                            break;
            case 3 : RA=RA+dist;
                            if(RA>360)
                                RA=RA-360;
                            break;
            case 4 : RA=RA-dist;
                            if(RA<0)
                                RA=RA+360;
                            break;
            case 5 : x=sin(theta)*dist;
                          y=cos(theta)*dist;
                          RA=RA-x;
                          if(RA<0)
                                RA=RA+360;
                          DEC=DEC+y;
                          break;
            case 6 : theta=90-theta;
                          theta=theta*(3.1428571428/180);
                          x=sin(theta)*dist;
                          y=cos(theta)*dist;
                          RA=RA+x;
                          if(RA>360)
                                RA=RA-360;
                          DEC=DEC+y;
                          break;
            case 7 : theta=180-theta;
                          theta=theta*(3.1428571428/180);
                          x=sin(theta)*dist;
                          y=cos(theta)*dist;
                          RA=RA+x;
                          if(RA>360)
                                RA=RA-360;
                          DEC=DEC-y;
                          break;
            case 8 : theta=270-theta;
                          theta=theta*(3.1428571428/180);
                          x=sin(theta)*dist;
                          y=cos(theta)*dist;
                          RA=RA-x;
                          if(RA<0)
                                RA=RA+360;
                          DEC=DEC-y;
                          break;
        }
        cout<<"\nnew coordinates is\n";
        cout<<RA<<" "<<DEC<<endl;
    }
        return;
}
