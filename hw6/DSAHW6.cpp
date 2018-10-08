#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;
#define INF 2147483647

vector<double> pitch;
vector<double> note;
int p_num,n_num;
double dis[1010][110];
bool filled[1010][110];

double min(double a,double b){ return (a>b? b:a);}
double dis_cou(int i,int j){
	if(j>i) return INF;
	if(filled[i][j]) return dis[i][j];
	if(i==0){
 	dis[i][j]=fabs(pitch[i]-note[j]);
 	filled[i][j]=1;
 	return dis[i][j];
     }
    if(j==0){
  	dis[i][j]=fabs(pitch[i]-note[j])+dis_cou(i-1,j);
    filled[i][j]=1;
    return dis[i][j];
    }
    dis[i][j]=fabs(pitch[i]-note[j])+min(dis_cou(i-1,j),dis_cou(i-1,j-1));
    filled[i][j]=1;
    return dis[i][j];
}

int main(){
while(scanf("%d",&p_num)!=EOF){
  double p_temp,n_temp;
  double mindis=INF;
  vector<int> path;
  pitch.clear(); note.clear();
  for (int x = 0; x < p_num; ++x){
   scanf("%lf",&p_temp);
   pitch.push_back(p_temp); 
  }

  scanf("%d",&n_num);

  for (int y = 0; y < n_num; ++y){	
   scanf("%lf",&n_temp);
   note.push_back(n_temp);
   for (int i = 0; i < 1010; ++i)for (int j = 0; j < 110; ++j){dis[i][j]=INF;}
   memset(filled, 0, sizeof(filled));
   double tempdis=dis_cou(p_num-1,y);
   if(mindis>tempdis){
    mindis=tempdis;
    path.clear();
    int itemp=p_num-1,jtemp=y;
    while(itemp>0&&jtemp>0){
     if(dis[itemp-1][jtemp]>dis[itemp-1][jtemp-1]){	
      path.push_back(itemp);
      jtemp--;
     }  
      itemp--; 
    }
   }
  }
   printf("%lf\n",mindis);
   printf("0");
   for (int a = path.size()-1; a >=0 ; a--){printf(" %d",path[a]);} 
   printf("\n"); 
 }//input

}
