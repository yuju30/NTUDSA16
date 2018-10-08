#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <map>
#include <unordered_set>
//<bits/stdc++.h>
using namespace std;

unordered_set<string> DIC;
vector<string> ED1;
vector<string> ED2;
vector<string> ANS;

void Substitute(string s,int ed){
	int slen=s.length();
  for (int i = 0; i < slen; ++i){
  	for (char j = 'a'; j <= 'z'; ++j){
      string jtemp=s;
      jtemp[i]=j;
      if(ed==1) ED1.push_back(jtemp);
      if(ed==2) ED2.push_back(jtemp);
  	}
  }
}
void Insert(string s,int ed){
    int slen=s.length();
  for (int i = 0; i <= slen; ++i){
  	for (char j = 'a'; j <= 'z'; ++j){
     string jtemp;
     jtemp.assign(1,j);
     string itemp=s;
     itemp=itemp.insert(i,jtemp);
     if(ed==1) ED1.push_back(itemp);
     if(ed==2) ED2.push_back(itemp); 
    }
  }  
}
void Delete(string s,int ed){
	int slen=s.length();
  for (int i = 0; i < slen; ++i){
  	string dtemp=s;
    dtemp=dtemp.erase(i,1);
    if(ed==1) ED1.push_back(dtemp);
    if(ed==2) ED2.push_back(dtemp);
  }  
}
void Transpose(string s,int ed){
	int slen=s.length();
  for (int i = 0; i < slen-1; ++i){
  	string ttemp=s;
  	char itemp=ttemp[i];
  	ttemp[i]=ttemp[i+1];
    ttemp[i+1]=itemp;
    if(ed==1) ED1.push_back(ttemp);
    if(ed==2) ED2.push_back(ttemp);
  }  
}
int main(){
  ifstream input("/tmp2/dsa2016_hw5/cmudict-0.7b");
  string temp,no_use;
  while(input>>temp){
  	getline(input,no_use);
  	int templen=temp.length();
  	for (int i = 0; i < templen; ++i){
  		if(temp[i]>='A'&&temp[i]<='Z'){temp[i]=temp[i]-'A'+'a';}
  	}
    DIC.insert(temp);
   } 
  input.close();
  string intemp,inno_use;
  while(cin>>intemp){
   getline(cin,inno_use);
      ED1.clear();ED2.clear();ANS.clear();
      if(DIC.count(intemp)>0) cout<<intemp<<" ==> OK"<<endl;
      else{
      	Substitute(intemp,1);
	    Insert(intemp,1);
	    Delete(intemp,1);
        Transpose(intemp,1);
        sort(ED1.begin(), ED1.end());
        vector<string>::iterator it1=unique(ED1.begin(), ED1.end());   
        ED1.erase(it1,ED1.end());
        int ed1len=ED1.size();
        for (int i = 0; i < ed1len; ++i){
	   	  Substitute(ED1[i],2);
		  Insert(ED1[i],2);
		  Delete(ED1[i],2);
	      Transpose(ED1[i],2);
	    }
	    sort(ED2.begin(), ED2.end());
	    vector<string>::iterator it2=unique(ED2.begin(), ED2.end());   
	    ED2.erase(it2,ED2.end()); 
	    for (int e1 = 0; e1 < ed1len; ++e1){if(DIC.count(ED1[e1])>0) ANS.push_back(ED1[e1]);}
	    for (int e2 = 0; e2 < ED2.size(); ++e2){if(DIC.count(ED2[e2])>0) ANS.push_back(ED2[e2]);}
	    if(ANS.size()>0){
		    sort(ANS.begin(), ANS.end());
		    vector<string>::iterator ita=unique(ANS.begin(), ANS.end());   
		    ANS.erase(ita,ANS.end());
		    cout<<intemp<<" ==>";
		    for (int pa = 0; pa < ANS.size(); ++pa){cout<<" "<<ANS[pa];}
		    cout<<endl;	
	    }
	    else{cout<<intemp<<" ==> NONE"<<endl;}
	    
      }//not in DIC
  }//input
}//main