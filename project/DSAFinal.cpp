#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;

unordered_map<string, unsigned int> table;
vector<string> cdd;
int num;
vector<string> que_ele;
typedef struct data{
   string s;
   unsigned int fre;
   bool operator<(const struct data &A) const {
   		if(fre != A.fre) return fre < A.fre;
   		return s < A.s;
   }	
   bool operator==(const struct data &A) const {
   		return s == A.s && fre == A.fre;
   }
}Data;
vector<Data> Ans;

string pps[20] = {"about","after","at","before","between","by","down","for","from","in",
"near","of","on","since","than","to","under","up","with","without"};

int min(int a,int b){return a>b? b:a ;}

bool cmpa(Data a,Data b){
  if(a.fre!=b.fre) return a.fre > b.fre; 
  for (int i = 0; i < min(a.s.length(),b.s.length()); ++i){
    if(a.s[i]!=b.s[i]) return a.s[i]<b.s[i];
   } 
 return 0;
}
int judge(string s){
   for (int i = 0; i < 20; ++i){
   	if(s==pps[i]) return 1;
   }
 return 0;
}
vector<string> Edit(vector<string> vecs,int edi_num){
  vector<string> ret;
  //insert
  string s=vecs[0];
  for (int add = 1; add < edi_num; ++add){s+=" "+vecs[add];}
  int slen=s.length();	
  for (int i = 0; i < slen; ++i){
    if(s[i]==' '){
      for (int iprep = 0; iprep < 20; ++iprep){
		string intemp=s;
		intemp=intemp.insert(i," "+pps[iprep]);
		ret.push_back(intemp);
	  }
    }
    if(i==0){
      for (int iprep = 0; iprep < 20; ++iprep){
		string intemp=s;
		intemp=pps[iprep]+" "+intemp;
		ret.push_back(intemp);
	  }
    }
    if(i==slen-1){
      for (int iprep = 0; iprep < 20; ++iprep){
		string intemp=s;
		intemp=intemp+" "+pps[iprep];
		ret.push_back(intemp);
	  }
    } 
  }
  //delete
  for (int d = 0; d < edi_num; ++d){
  	string detemp;
  	for (int a = 0; a < edi_num; ++a){
         if(a!=d){
           if(detemp.length()>0) detemp+=" "+vecs[a];
           else detemp=vecs[a];
         } 
  	}
    ret.push_back(detemp);
  }
  //sub
  for (int s = 0; s < edi_num; ++s){
  	vector<string> sub=vecs;
    for (int a = 0; a < 20; ++a){
      sub[s]=pps[a];
      string subtemp=sub[0];
      for (int i = 1; i < edi_num; ++i){subtemp+=" "+sub[i];} 
      ret.push_back(subtemp);
    }
  }
  return ret; 	
}//Edit end

void Find(vector<string> gen,int ind){
  if(ind==num){
   int sta;
   int gen_size=gen.size();
   for (sta = 0; sta < gen_size; ++sta){if(gen[sta]!="")break; }	
   string cddtemp=gen[sta];
   for (int i = sta+1; i < gen_size; ++i){if(gen[i]!="")cddtemp+=" "+gen[i];}
   cdd.push_back(cddtemp);	
   return;
  }
  if(judge(que_ele[ind])){
  	vector<string> edit;
  	int edi_end;
    for (edi_end = ind; edi_end< num; ++edi_end){
    	if(judge(que_ele[edi_end]))edit.push_back(que_ele[edi_end]);
    	else {break;}
    }//calculate continuous prep
    vector<string> prep_edit=Edit(edit,edi_end-ind);
   /* for (int i = 0; i < prep_edit.size(); ++i){
    	cout<<prep_edit[i]<<endl;
    }
    cout<<"============"<<endl;*/
    for (int ge_ed = 0; ge_ed < prep_edit.size(); ++ge_ed){
       gen.push_back(prep_edit[ge_ed]);
       Find(gen,edi_end);
       gen.pop_back();
     }
  }//prep
  if(!judge(que_ele[ind])){
    gen.push_back(que_ele[ind]); 
    Find(gen,ind+1);
  }//not prep
}
vector<string> Edit_a(string s){
  vector<string> ret;	
  int slen=s.length();	
  for (int i = 0; i < slen; ++i){
    if(s[i]==' '){
      for (int iprep = 0; iprep < 20; ++iprep){
		string intemp=s;
		intemp=intemp.insert(i," "+pps[iprep]);
		ret.push_back(intemp);
		cdd.push_back(intemp);
	  }
    }
    if(i==0){
      for (int iprep = 0; iprep < 20; ++iprep){
		string intemp=s;
		intemp=pps[iprep]+" "+intemp;
		ret.push_back(intemp);
		cdd.push_back(intemp);
	  }
    }
    if(i==slen-1){
      for (int iprep = 0; iprep < 20; ++iprep){
		string intemp=s;
		intemp=intemp+" "+pps[iprep];
		ret.push_back(intemp);
		cdd.push_back(intemp);
	  }
    } 
  }
 return ret;
}
int main(){
   ifstream twogr("/tmp2/dsa2016_project/2gm.small.txt");
   ifstream thrgr("/tmp2/dsa2016_project/3gm.small.txt");
   ifstream fourgr("/tmp2/dsa2016_project/4gm.small.txt");
   ifstream fivegr("/tmp2/dsa2016_project/5gm.small.txt");
   string two;
   while(getline(twogr,two)){
  	int end=two.find("\t",0);
  	int twolen=two.length();
  	string two_word=two.substr(0,end);
  	string two_num=two.substr(end+1,twolen-end-1);
    int two_numlen=twolen-end-1;
    unsigned int two_renum=0;
    for (int i = 0; i < two_numlen; ++i){two_renum+=(two_num[i]-'0')*pow(10,two_numlen-i); }
   table.insert(unordered_map<string, unsigned int>::value_type(two_word, two_renum));
   }
   twogr.close();
  
   string thr;	
   while(getline(thrgr,thr)){
  	int end=thr.find("\t",0);
  	int thrlen=thr.length();
  	string thr_word=thr.substr(0,end);
  	string thr_num=thr.substr(end+1,thrlen-end-1);
    int thr_numlen=thrlen-end-1;
    unsigned int thr_renum=0;
    for (int i = 0; i < thr_numlen; ++i){thr_renum+=(thr_num[i]-'0')*pow(10,thr_numlen-i); }
   table.insert(unordered_map<string, unsigned int>::value_type(thr_word, thr_renum));
   } 
   thrgr.close();

   string four;	
   while(getline(fourgr,four)){
  	int end=four.find("\t",0);
  	int fourlen=four.length();
  	string four_word=four.substr(0,end);
  	string four_num=four.substr(end+1,fourlen-end-1);
    int four_numlen=fourlen-end-1;
    unsigned int four_renum=0;
    for (int i = 0; i < four_numlen; ++i){four_renum+=(four_num[i]-'0')*pow(10,four_numlen-i); }
   table.insert(unordered_map<string, unsigned int>::value_type(four_word, four_renum));
   }
   fourgr.close();

   string five;	
   while(getline(fivegr,five)){
  	int end=five.find("\t",0);
  	int fivelen=five.length();
  	string five_word=five.substr(0,end);
  	string five_num=five.substr(end+1,fivelen-end-1);
    int five_numlen=fivelen-end-1;
    unsigned int five_renum=0;
    for (int i = 0; i < five_numlen; ++i){five_renum+=(five_num[i]-'0')*pow(10,five_numlen-i); }
   table.insert(unordered_map<string, unsigned int>::value_type(five_word, five_renum));
   }
   fivegr.close();
//--------------read file
  string que;
  while(getline(cin,que)){
  	  num=0;
  	  que_ele.clear();
      cdd.clear();
      Ans.clear();
  	  int que_len=que.length();
  	  int s_sta=0,have_prep=0;
  	  cdd.push_back(que);
      for (int cq = 0; cq < que_len; ++cq){
             if(que[cq]==' '||que[cq]=='\n'){
              que_ele.push_back(que.substr(s_sta,cq-s_sta));
              if(judge(que_ele[num]))have_prep=1;
              s_sta=cq+1;
              num++;
             }    	
        }
      if(s_sta<que_len){
      	que_ele.push_back(que.substr(s_sta,que_len-s_sta));
      	if(judge(que_ele[num]))have_prep=1;
        num++;
      }//haven't cut 
    if(have_prep){
      vector<string> gen;  
      Find(gen,0); 
    }//have prep
    else{
      vector<string> edit1=Edit_a(que);
      for (int i = 0; i < edit1.size(); ++i){
        vector<string> temp;
      	temp=Edit_a(edit1[i]);
      }
    }//no prep 
   // for (int f = 0; f < cdd.size(); ++f){cout<<cdd[f]<<endl;}
    sort(cdd.begin(), cdd.end());
    vector<string>::iterator it1=unique(cdd.begin(), cdd.end());   
    cdd.erase(it1,cdd.end());

    for (int f = 0; f < cdd.size(); ++f){
    	auto findstr = table.find(cdd[f]);
    	if(findstr!=table.end()){
          Data dtemp;
          dtemp.s=(*findstr).first;
          dtemp.fre=(*findstr).second;
          Ans.push_back(dtemp);
    	}
    }
    sort(Ans.begin(),Ans.end(),cmpa);
    int ans_size=Ans.size();
    if(ans_size>10) ans_size=10;
   cout<<"query: "<<que<<endl;
    printf("output: %d\n",ans_size);
    for (int a = 0; a < ans_size; ++a){
     cout<<Ans[a].s<<'\t'<<Ans[a].fre/10<<endl;	
    }
  }//getline

}//main