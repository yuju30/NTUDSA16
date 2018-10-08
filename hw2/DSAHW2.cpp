#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <vector>
using namespace std;

#define INF 2147483647
typedef struct datas{
 int uu,ui,ur,ut;
  bool operator <(const struct datas &a) const {
    if(uu != a.uu) return uu < a.uu;
    if(ui != a.ui) return ui < a.ui;
    if(ut != a.ut) return ut < a.ut;
    return ur < a.ur;
  }
  bool operator !=(const struct datas &a) const {
    return uu!=a.uu||ui!=a.ui||ur!=a.ur||ut!=a.ut;
  }
  bool operator ==(const struct datas &a) const {
    return uu==a.uu&&ui==a.ui&&ur==a.ur&&ut==a.ut;
  } 
}Data;
typedef struct countusers{
 int uid,cou;
}Couuser;

bool cmpu(Data a,Data b)
{ if(a.uu!=b.uu) return a.uu < b.uu; 
  if(a.ui!=b.ui) return a.ui < b.ui;
  if(a.ut!=b.ut) return a.ut < b.ut;
  if(a.ur!=b.ur) return a.ur < b.ur;
  return 0;
}
bool cmpi(Data a,Data b)
{ if(a.ui!=b.ui) return a.ui < b.ui;
  if(a.uu!=b.uu) return a.uu < b.uu; 
  if(a.ut!=b.ut) return a.ut < b.ut;
  if(a.ur!=b.ur) return a.ur < b.ur;
  return 0;
}
vector<Data> rawdt,itemdt;
vector<Couuser> userap;
void ini(Data *a)
{a->uu=0;a->ui=0;a->ur=-2;a->ut=0; 
}

void Accept(int u,int i,int t)
{ Data acc;
  acc.uu=u;acc.ui=i;acc.ut=t;acc.ur=-2;
 vector<Data>::iterator key=lower_bound(rawdt.begin(),rawdt.end(),acc,cmpu);     
 if(key==rawdt.end())cout<<"0"<<endl;
 if(key->uu!=u||key->ui!=i||key->ut!=t)cout<<"0"<<endl;
 else cout<<key->ur<<endl;
 }//outputs the (Result) when user u is given item i at time t
void Items(int u1,int u2)
{ Data U1,U2;
  ini(&U1);ini(&U2);
  U1.uu=u1;U2.uu=u2;
  vector<Data>::iterator key1=lower_bound(rawdt.begin(),rawdt.end(),U1,cmpu);
  vector<Data>::iterator key2=lower_bound(rawdt.begin(),rawdt.end(),U2,cmpu);
  vector<int> i1,i2;
  int tempi1=0,tempi2=0; 
  if(key1!=rawdt.end()&&key1->uu==u1){
    for (vector<Data>::iterator vi1 = key1; vi1 != rawdt.end(); ++vi1){
    if(vi1->uu==key1->uu&&vi1->ui!=tempi1){i1.push_back(vi1->ui);tempi1=vi1->ui;} 
    if(vi1->uu!=key1->uu) break;
    } 
  }
  if(key2!=rawdt.end()&&key2->uu==u2){
    for (vector<Data>::iterator vi2 = key2; vi2 != rawdt.end(); ++vi2){
    if(vi2->uu==key2->uu&&vi2->ui!=tempi2){i2.push_back(vi2->ui);tempi2=vi2->ui;} 
    if(vi2->uu!=key2->uu) break;
    }
  } 
    int finditemp=0,jud=0;
    if(i1.size()==0||i2.size()==0){cout<<"EMPTY"<<endl; return;}
    else{
      int i1size=i1.size();
      for (int i = 0; i < i1size; ++i){
        if(i1[i]==finditemp) continue;
        vector<int>::iterator find=lower_bound(i2.begin(),i2.end(),i1[i]);
        if(find==i2.end())continue;
        if(i1[i]==*find){cout<<i1[i]<<endl;finditemp=i1[i];jud=1;}
       }
      } 
    if(jud==0)cout<<"EMPTY"<<endl;      
}//outputs the sorted (ItemId), line by line, 
 //that are recommended to both user u1 and user u2
void Users(int i1,int i2,int t1,int t2)
{ Data I1,I2;
  ini(&I1);ini(&I2);
  I1.ui=i1;I2.ui=i2;
  vector<Data>::iterator ikey1=lower_bound(itemdt.begin(),itemdt.end(),I1,cmpi);
  vector<Data>::iterator ikey2=lower_bound(itemdt.begin(),itemdt.end(),I2,cmpi);
  vector<int> u1,u2;
  if(ikey1!=itemdt.end()&&ikey1->ui==i1){
    for (vector<Data>::iterator vi1 = ikey1; vi1 != itemdt.end(); ++vi1){
    if(vi1->ui==ikey1->ui&&vi1->ut>=t1&&vi1->ut<=t2) u1.push_back(vi1->uu);
    if(vi1->ui!=ikey1->ui) break;
    } 
  }
  if(ikey2!=itemdt.end()&&ikey2->ui==i2){
    for (vector<Data>::iterator vi2 = ikey2; vi2 != itemdt.end(); ++vi2){
    if(vi2->ui==ikey2->ui&&vi2->ut>=t1&&vi2->ut<=t2) u2.push_back(vi2->uu);
    if(vi2->ui!=ikey2->ui) break;
    }
  } 
  if(u1.size()==0||u2.size()==0){cout<<"EMPTY"<<endl; return;}
    int findutemp=0,jud=0; 
    int u1size=u1.size();
  for (int i = 0; i < u1size; ++i){
    if(u1[i]==findutemp) continue;
    vector<int>::iterator find=lower_bound(u2.begin(),u2.end(),u1[i]);
    if(find==u2.end()) continue;
    if(u1[i]==*find){cout<<u1[i]<<endl;findutemp=u1[i];jud=1;}
    }
    if(jud==0)cout<<"EMPTY"<<endl;      
}//outputs the sorted (UserId), line by line, which corresponds to
//users who are given both item i1 and item i2 between the time interval [t1,t2]
void Ratio(int i,int thr)
{ int iacc=0,itot=0,jud;
  int userapsize=userap.size();
  for (int cui = 0; cui < userapsize; ++cui){
     if(userap[cui].cou>thr){
      itot++;jud=0;
     Data temp1;ini(&temp1);temp1.uu=userap[cui].uid;
     Data temp2;ini(&temp2);temp2.uu=userap[cui].uid;temp2.ui=INF;
     vector<Data>::iterator key1=lower_bound(rawdt.begin(),rawdt.end(),temp1,cmpu);
     vector<Data>::iterator key2=lower_bound(rawdt.begin(),rawdt.end(),temp2,cmpu);
      if(key1!=rawdt.end()){
        for (vector<Data>::iterator vi = key1 ; vi != key2 && jud!=1; ++vi){
          if(vi->ui==i&&vi->ur==1) jud=1;
        }
      }
      if(jud==1)iacc++;
     }
   } 
  cout<<iacc<<"/"<<itot<<endl;
}
void Findtime_item(int i,vector<int> Us)
{vector<int> alltime;
 Data temp;ini(&temp);temp.ui=i; 
 int Ussize=Us.size();
 for (int j = 0; j < Ussize; ++j){
    temp.uu=Us[j];
    vector<Data>::iterator tkey=lower_bound(itemdt.begin(),itemdt.end(),temp,cmpi);
    Data temp2=temp;temp2.ut=INF;
    vector<Data>::iterator tkeylim=lower_bound(itemdt.begin(),itemdt.end(),temp2,cmpi);
    if(tkey==itemdt.end()){cout<<"EMPTY"<<endl; return;}
    for (vector<Data>::iterator svi = tkey; svi != tkeylim; ++svi){
      alltime.push_back(svi->ut);
    }
 }
 sort(alltime.begin(),alltime.end());
 if(alltime.size()==0)cout<<"EMPTY"<<endl;
 else{
  int uni=0;
  int alltimesize=alltime.size();
  for (int h = 0; h < alltimesize; ++h){
     if(alltime[h]!=uni)
      cout<<alltime[h]<<endl;
     uni=alltime[h];
    }
 
   }
}

int main(){
  FILE *input;
  input=fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","r");
  assert(input!=NULL);   
  
  Data temp,temp2;
  Couuser usertemp;
  while(fscanf(input,"%d%d%d%d",&temp.uu,&temp.ui,&temp.ur,&temp.ut)==4){
    if(memcmp(&temp,&temp2,sizeof(Data))==0) continue;
    rawdt.push_back(temp);
    itemdt.push_back(temp);
    temp2=temp;
    
  }  
  fclose(input); 
  sort(rawdt.begin(),rawdt.end(),cmpu);
  sort(itemdt.begin(),itemdt.end(),cmpi);

  Data utemp;ini(&utemp);
  for (vector<Data>::iterator vi = rawdt.begin(); vi != rawdt.end();vi++){
   if(utemp.uu==vi->uu)continue;
   utemp.uu=vi->uu;utemp.ui=INF;
   int dis=0;
   vector<Data>::iterator tempkey=upper_bound(rawdt.begin(),rawdt.end(),utemp,cmpu);
   for (vector<Data>::iterator fvi = vi; fvi != tempkey; ++fvi){
     if(fvi->uu==vi->uu){
      dis++;
       }
     else break;
   }
   usertemp.uid=vi->uu;
   usertemp.cou=dis;
   userap.push_back(usertemp);
  }
 int n;
 while(cin>>n){
  for (int z = 0; z < n; ++z){
   string s;
   cin>>s;
   if(s[0]=='a'){
    int u,i,t;
    cin>>u>>i>>t; 
    Accept(u,i,t);
   }
   if(s[0]=='i'){
   	int u1,u2;
   	cin>>u1>>u2;
   	Items(u1,u2);
   } 
   if(s[0]=='u'){
   	int i1,i2,t1,t2;
   	cin>>i1>>i2>>t1>>t2;
   	Users(i1,i2,t1,t2);
   }	
   if(s[0]=='r'){
    int i,thr;
    cin>>i>>thr;
   	Ratio(i,thr);
   }
   if(s[0]=='f'){
   	int i,utemp;
    char judend;
    vector<int> Us;
   	cin>>i;
    while(cin>>utemp){
      Us.push_back(utemp);
      judend=getchar();
      if(judend=='\n' || judend=='\0')break;
    }
   	Findtime_item(i, Us);
   }
  }//deal each testaction
 }
}//main


