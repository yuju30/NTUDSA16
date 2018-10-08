#include <stdio.h>
 
int  used[15]={0};
int solution[15];
int N;
int a[15];
 
void backtrack(int n){
 
    if (n == N){
        for (int i=0; i<N; i++){
        	if(i!=N-1) printf("%d ",solution[i]);
            else printf("%d\n",solution[i]);
        }
       return;
    }
    for (int i=1; i<=N; i++)
        if (!used[i]){
            used[i] = 1;
            solution[n] = i;
            backtrack(n+1);
            used[i] = 0;
        }
}
 
 
int main(){
 
  while(scanf("%d",&N)!=EOF){
      backtrack(0);
  }
 
  return 0;
 
}
