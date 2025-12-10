//grundplatte : system.cpp
#include <_system.hpp>
#include <string.h>

_system*S=0;
//******************************************************************************************************************************************************************************************************
//                                                              S Y S T E M 
//******************************************************************************************************************************************************************************************************
_system::_system(){
};
_system::~_system(){
};
bool IsLittleEndian(){
                                                                //  Returns if we are running on a little-endian-machine
                                                                bcUInt8   test;
                                                                bcUInt16  value = 0xABCD;
                                                                // -----------------------------------------------

                                                                test = *((bcUInt8 *)&value);
                                                                return(0xcd == test);
}

//**************************************************************************************************************************************************************************************************
//                                                              T I M E
//**************************************************************************************************************************************************************************************************
_zeit::_zeit(){
                                                                s=0;
                                                                t=0;
                                                                tord[0]=0;
                                                                tord[1]=0;
                                                                a=1;
};
_zeit::~_zeit(){
};
void _zeit::anfang(){
                                                                t=0;
                                                                tord[0]=tord[1]=0;
                                                                a=1;
                                                                animieren();
                                                                animieren();
};
double _zeit::holen(){
                                                                return(animieren());
};
double _zeit::animieren(){
                                                                double dtms;
                                                                s=system();
                                                                tord[1]=tord[0];
                                                                tord[0]=double(s);
                                                                dtms=(tord[0]-tord[1]);
                                                                a=dtms/double(16.666666667f);
                                                                t+=a;
                                                                if(a>5)a=5;
                                                                return(t);
};
void _zeit::delay(int ms){
                                                                int so;
                                                                //-------
                                                                so=system();
                                                                while((int(system())-int(so))<ms);
};
/*
double _zeit::animation(){
                                                                animieren();
                                                                return(t);
};
*/
//****************************************************************************************************************************************************************************************************
//                                                              D A T E
//****************************************************************************************************************************************************************************************************
_datum::_datum(int y,int m,int d){
                                                                daycount[0]=31;
                                                                daycount[1]=28;
                                                                daycount[2]=31;
                                                                daycount[3]=30;
                                                                daycount[4]=31;
                                                                daycount[5]=30;
                                                                daycount[6]=31;
                                                                daycount[7]=31;
                                                                daycount[8]=30;
                                                                daycount[9]=31;
                                                                daycount[10]=30;
                                                                daycount[11]=31;
                                                                year=y;
                                                                month=m;
                                                                day=d;
                                                                holenzeichenkette();
                                                                holenindex();
};
_datum::~_datum(){
};
void _datum::setzen(int y,int m,int d){
                                                                year=y;
                                                                month=m;
                                                                day=d;
                                                                holenzeichenkette();
                                                                holenindex();
};
char _datum::zerlegen(char*s,int&d,int&m,int&y){
                                                                char day[256];
                                                                char month[256];
                                                                char year[256];
                                                                int i,j;
                                                                char r;
                                                                //-----------------
                                                                r=1;
                                                                i=0;
                                                                j=0;
                                                                while((s[j]!='.')&&(s[j]!=0)) day[i++]=s[j++];
                                                                if(s[j]==0) r=0;
                                                                day[i]=0;
                                                                i=0;
                                                                j++;
                                                                while((s[j]!='.')&&(s[j]!=0)) month[i++]=s[j++];
                                                                if(s[j]==0) r=0;
                                                                month[i]=0;
                                                                i=0;
                                                                j++;
                                                                while(s[j]!=0) year[i++]=s[j++];
                                                                year[i]=0;
                                                                d=atoi(day);
                                                                m=atoi(month);
                                                                y=atoi(year);
                                                                return(r);

};
void _datum::holenzeichenkette(){
                                                                char t[256];
                                                                char st[1024];
                                                                //------------
                                                                _itoa(day,t,10);
                                                                strcpy(st,t);
                                                                strcat(st,".");
                                                                _itoa(month,t,10);
                                                                strcat(st,t);
                                                                strcat(st,".");
                                                                _itoa(year,t,10);
                                                                strcat(st,t);
                                                                string=st;
};
char _datum::holenindex(){
                                                                int in;
                                                                int y=2000;
                                                                int m=1;
                                                                int d=1;
                                                                int dc;
                                                                int anzahl;
                                                                int emax=5000000;
                                                                //---------
                                                                anzahl=0;
                                                                in=0;
                                                                if(year>=y){
                                                                 dc=daycount[m-1];if(m==2) if((y%4)==0) dc=29; else dc=28;
                                                                 while( ((year!=y)||(month!=m)||(day!=d)) &&  (anzahl<emax) ){
                                                                  d++;
                                                                  in++;
                                                                  if(d>dc){
                                                                   d=1;
                                                                   m++;
                                                                   if(m>12){
                                                                    m=1;
                                                                    y++;
                                                                   };
                                                                   dc=daycount[m-1];if(m==2) if((y%4)==0) dc=29; else dc=28;
                                                                  };
                                                                  anzahl++;
                                                                 };
                                                                }else{
                                                                 while( ((year!=y)||(month!=m)||(day!=d)) &&  (anzahl<emax) ){
                                                                  d--;
                                                                  in--;
                                                                  if(d==0){
                                                                   m--;
                                                                   if(m==0){
                                                                    m=12;
                                                                    y--;
                                                                   };
                                                                   d=daycount[m-1];if(m==2) if((y%4)==0) d=29; else d=28;
                                                                  };
                                                                  anzahl++;
                                                                 };
                                                                };

                                                                index=in;
                                                                if(anzahl>=emax) return(0); else return(1);

};
int _datum::differenz(_datum*d){
                                                                int i;
                                                                //-----------
                                                                i=index-d->index;
                                                                return(i);
};
//******************************************************************************************************************************************************************************************************
//                                                              S P E A K E R 
//******************************************************************************************************************************************************************************************************
_pclautsprecher::_pclautsprecher(){
};
_pclautsprecher::~_pclautsprecher(){
};
//******************************************************************************************************************************************************************************************************
//                                                              K E Y B O A R D 
//******************************************************************************************************************************************************************************************************
_tastatur::_tastatur(/*_listebasis<_tastatur>*l*/){//:_listenknotenbasis<_tastatur>(l){
                                                                //clearkey();
};
_tastatur::~_tastatur(){
};
/*
void _tastatur::clearkey(){
                                                                unsigned int i;
                                                                //-----
                                                                for(i=0;i<1024;i++) pkey[i]=false;
};
*/
/*
bool _tastatur::taste(const unsigned int i)const{
                                                                if(i<1024){
                                                                 return(pkey[i]);
                                                                }else{
                                                                 //error
                                                                 return(false);
                                                                };
};
void _tastatur::taste(const unsigned int i,bool val){
                                                                if(i<1024){
                                                                 pkey[i]=val;
                                                                }else{
                                                                 //error
                                                                };
};
*/












