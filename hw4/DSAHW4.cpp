#include <stdio.h>
#include <iostream>
using namespace std;

typedef struct bid{
  int bid_id,cli_id,act,pri,shacou;
}Bid;

Bid buy[1000000];//0
int buynum=1;
Bid sell[1000000];//1
int sellnum=1;
bool cancel[1000000]={0};
int transid=0;

int min(int a,int b){return (a<b? a:b);}

void Add_buy(Bid temp){
  int bi=buynum++;
	while(bi>1){
        int bir=bi/2;
        if(temp.pri<buy[bir].pri)break;
        if(temp.pri==buy[bir].pri&&temp.bid_id>buy[bir].bid_id)break;
        buy[bi]=buy[bir];
        bi=bir;
    }
    buy[bi]=temp;
    return;
}
void Add_sell(Bid temp){
  int si=sellnum++;
	while(si>1){
        int sir=si/2;
        if(temp.pri>sell[sir].pri)break;
        if(temp.pri==sell[sir].pri&&temp.bid_id>sell[sir].bid_id)break;
        sell[si]=sell[sir];
        si=sir;
    }
    sell[si]=temp;
    return;
}
void rem_sell(){
   Bid last = sell[--sellnum];
    int si=1;
    while(si*2<sellnum){
       int sl=si*2;
       int sr=si*2+1;
       if(sr<sellnum&&sell[sr].pri<sell[sl].pri) sl=sr;
       if(sr<sellnum&&sell[sr].pri==sell[sl].pri&&sell[sr].bid_id<sell[sl].bid_id)sl=sr;
       if(sell[sl].pri>last.pri) break;
       if(sell[sl].pri==last.pri&&sell[sl].bid_id>last.bid_id) break;
       sell[si]=sell[sl];
       si=sl; 
    }
    sell[si]=last;
    return;
}
void rem_buy(){
   Bid last = buy[--buynum];
    int bi=1;
    while(bi*2<buynum){
       int bl=bi*2;
       int br=bi*2+1;
       if(br<buynum&&buy[br].pri>buy[bl].pri) bl=br;
       if(br<buynum&&buy[br].pri==buy[bl].pri&&buy[br].bid_id<buy[bl].bid_id)bl=br;
       if(buy[bl].pri<last.pri) break;
       if(buy[bl].pri==last.pri&&buy[bl].bid_id>last.bid_id) break;
       buy[bi]=buy[bl];
       bi=bl; 
    }
    buy[bi]=last;
    return;
}

int main(){
	Bid temp;
   while(scanf("%d",&temp.bid_id)!=EOF){
    scanf("%d%d%d%d",&temp.cli_id,&temp.act,&temp.pri,&temp.shacou);
    if(temp.act==2) cancel[temp.pri]=1;
    if(temp.act==0){
      while(temp.pri>=sell[1].pri&&sellnum>1&&temp.shacou>0&&sell[1].shacou>0){
        if(cancel[sell[1].bid_id]){ cancel[sell[1].bid_id]=0; rem_sell(); continue; }
      	 printf("%d\t%d\t%d\t%d\t",transid,temp.cli_id,sell[1].cli_id,sell[1].pri);
      	 transid++;   
         int minsha=min(temp.shacou,sell[1].shacou);
         printf("%d\n",minsha);
      	 temp.shacou-=minsha;
         sell[1].shacou-=minsha;	
         if(sell[1].shacou==0){rem_sell();}
      }
      if(temp.shacou>0){
        Add_buy(temp);
       }
    } //buy
    if(temp.act==1){
      while(temp.pri<=buy[1].pri&&buynum>1&&temp.shacou>0&&buy[1].shacou>0){
        if(cancel[buy[1].bid_id]){ cancel[buy[1].bid_id]=0; rem_buy(); continue; }
         printf("%d\t%d\t%d\t%d\t",transid,buy[1].cli_id,temp.cli_id,temp.pri);
      	 transid++;    
      	 int minsha=min(temp.shacou,buy[1].shacou);
         printf("%d\n",minsha);
         temp.shacou-=minsha;
         buy[1].shacou-=minsha;  
         if(buy[1].shacou==0){rem_buy();}       	  
      }
      if(temp.shacou>0){
        Add_sell(temp);
      }
    }//sell
  }//cin
}//main