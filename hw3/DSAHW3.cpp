#include <iostream>
#include <stdio.h>
using namespace std;

typedef struct line{
 int ele[30];
 int num;
}Line;

int m,n;
int map[40][40];
Line row[40];
Line col[40];
    void ini_ele(Line *a)
    {
      for (int i = 0; i < 40; ++i)    
       for (int j = 0; j < 30; ++j){
        a[i].ele[j]=0;a[i].num=0;
       }
    }
    void itsectrow(int r){
       int morow=0,lastlen=row[r].num-1;
      for (int ir = 0; ir < row[r].num; ++ir){
        int k=row[r].ele[ir];
        lastlen+=k;
        while(k--){
          morow=(morow+1)<<1;
        }
        if(ir!=row[r].num-1) morow<<=1;
      }
      morow>>=1;
      int result=morow;
      for(int mr=1;mr<=n-lastlen;mr++){
        int temp=morow<<mr;
        result=result&temp;
      }
      int rn=1;
      for (int ind = 1;ind <= n; rn<<=1,ind++){
       if(result&rn) map[r][n-ind]=2;
      }
    }
    void itsectcol(int c){
        int mocol=0,lastlen=col[c].num-1;
      for (int ic = 0; ic < col[c].num; ++ic){
        int k=col[c].ele[ic];
        lastlen+=k;
        while(k--){
          mocol=(mocol+1)<<1;
        }
        if(ic!=col[c].num-1) mocol<<=1;
      }
      mocol>>=1;
      int result=mocol;
      for(int mc=1;mc<=m-lastlen;mc++){
        int temp=mocol<<mc;
        result=result&temp;
      }
      int cn=1;
      for (int ind = 1;ind <= m; cn<<=1,ind++){
       if(result&cn) map[m-ind][c]=2; 
       }
    }
    int judrow(int r,int c){
        int jud=0,judn=0;
        for (int jc = 0; jc <= c ; ++jc){
            if(judn>row[r].num) return -1;
            if(map[r][jc]>=1)jud++;
            if(map[r][jc]==0&&jud>0){
             if(jud!=row[r].ele[judn]) return -1;
             judn++;jud=0;
            }
         }
        if(jud>0){
             if(judn>=row[r].num) return -1;
             if(jud>row[r].ele[judn]) return -1;
             if(c!=n-1&&jud<=row[r].ele[judn]) return 0;
             judn++;
         }//last one
        if(c==n-1&&judn!=row[r].num) return -1;
        if(c==n-1&&judn==row[r].num) return 1;
        else return 0; 
    }
    int judcol(int r,int c){
        int jud=0,judn=0;
        for (int jr = 0; jr <= r ; ++jr){
            if(judn>col[c].num) return -1;
            if(map[jr][c]>=1)jud++;
            if(map[jr][c]==0&&jud>0){
             if(jud!=col[c].ele[judn]) return -1;
             judn++;jud=0;
            }
         }
        if(jud>0){
             if(judn>=col[c].num) return -1;
             if(jud>col[c].ele[judn]) return -1;
             if(r!=m-1&&jud<=col[c].ele[judn]) return 0;
             judn++;
         }//last one
        if(r==m-1&&judn!=col[c].num) return -1;
        if(r==m-1&&judn==col[c].num) return 1;
        else return 0; 
    }
    int find(int r,int c){
       if(c==n){c=0;r+=1;}
          if(r==m){
             for (int y = 0; y < m; ++y){
               for (int x = 0; x < n; ++x){
                if(map[y][x]>=1)cout<<"#";
                else cout<<".";  
                }
                cout<<endl;
               }      
            return 1;      
             }          
            if(judrow(r,c)==1){if(find(r+1,0))return 1;}
            if(map[r][c]==2){
              if(c==n-1){if(judrow(r,c+1)!=1) return 0;}
              if(find(r,c+1))return 1; 
             }
            else{
            map[r][c]=1;
            if(judrow(r,c)!=-1&&judcol(r,c)!=-1){if(find(r,c+1))return 1;}
            map[r][c]=0;
            if(judrow(r,c)!=-1&&judcol(r,c)!=-1){if(find(r,c+1))return 1;}
            }
      return 0;  
    }
int main(){
 while(cin>>m>>n){
  ini_ele(row);ini_ele(col);memset(map,0,sizeof(map));
   for (int i = 0; i < m; ++i){
        int rtemp,rei=0;
        char judend; 
        while(cin>>rtemp){
          row[i].ele[rei]=rtemp;rei++;
          judend=getchar();
          if(judend=='\n' || judend=='\0')break;
        }//each line
        row[i].num=rei;
     }  
   for (int j = 0; j < n; ++j){
        int ctemp,cei=0;
        char judend; 
        while(cin>>ctemp){
          col[j].ele[cei]=ctemp;cei++;
          judend=getchar();
          if(judend=='\n' || judend=='\0')break;
        }//each line
        col[j].num=cei;
     }
   for (int iy = 0; iy < m; ++iy){itsectrow(iy);}
   for (int ix = 0; ix < n; ++ix){itsectcol(ix);}
    find(0,0);  
 }  
}
