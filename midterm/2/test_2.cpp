#include <iostream>
using namespace std;



void pre(int a[], int num,int i){
    if(i>=num) return;
    if(a[i]!=-1){
      cout<<a[i]<<" ";
      if(a[2*i]==-1&&a[2*i+1]==-1)
       return;
    }     
    if(a[2*i]!=-1)
      pre(a,num,2*i);
    if(a[2*i+1]!=-1)
      pre(a,num,2*i+1);
  return;
}
void in(int b[], int num,int i){
    if(i>=num) return;
    if(b[i]!=-1){
      if(b[2*i]==-1){
         cout<<b[i]<<" ";
         b[i]=-1;
       if(b[2*i+1]!=-1)
         in(b,num,2*i+1);
       else
         in(b,num,i/2);
        }
      if(b[2*i]!=-1)
      	in(b,num,2*i);
  
    }     
    
  return;
}

void post(int c[], int num,int i){
    if(i>=num) return;
    if(c[i]!=-1){
      if(c[2*i]==-1&&c[2*i+1]==-1){
         cout<<c[i]<<" ";
         c[i]=-1;
       post(c,num,i/2);//
        }
     else{
       if(c[2*i]!=-1)
        post(c,num,2*i);
       if(c[2*i+1]!=-1)
        post(c,num,2*i+1);
     }
    }     
    
  return;
}
int main(){
    int atemp,num=0;
    char judend;
    int A[110],B[110],C[110];
    for (int j = 0; j < 110; ++j){
    	A[j]=-1;B[j]=-1;C[j]=-1;
    }
    while(cin>>atemp){
          A[num]=atemp;B[num]=atemp;C[num]=atemp;
          num++;
          judend=getchar();
          if(judend=='\n' || judend=='\0')break;
        }//each line
    pre(A,num,1);
    cout<<endl;
    in(B,num,1);
    cout<<endl;
    post(C,num,1);
}
