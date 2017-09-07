#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#define MAX 30000
using namespace std;

struct node{
	char alpha;
	int count;
	bool valid;
	bool used;
};

bool compare(string a,string b){
	if(a.size()==b.size()){
		return a<b;
	}
	return a.size()<b.size();
}


char max(node freq[]){
	int max=0;
	for(int i=1;i<26;i++){
		if(freq[i].count>freq[max].count){
			max=i;
		}
	}
	return freq[max].alpha;
}


int main(){
	string dictionary[MAX];
	int pass=0;
	for(int i=0;i<MAX;i++){
		cin>>dictionary[i];
	}		
	sort(dictionary,dictionary+MAX,compare);	//sort the dictionary length wise	
	int max_length=dictionary[MAX-1].size();	//size of largest word
	map<int,int>range;	
	range[0]=-1;	//for tracking the range of words having same length
	for(int i=0;dictionary[i].size()<max_length;i++){
		while(dictionary[i].size()==dictionary[i+1].size() && dictionary[i].size()<max_length)
			i++;
		range[dictionary[i].size()]=i;
	}
	range[max_length]=MAX-1;
	
	for(int k=0;k<MAX;k++){
		string word;
		word=dictionary[k];
		int length=word.size();
		int start=range[length-1]+1;
		int end=range[length];
		vector<char>test_set(end-start+1);
		for(int i=0;i<=(end-start);i++){
			test_set[i]='t';
		}	
		int miss=0,flag=0,correct=0;
		node freq[26];
		for(int i=0;i<26;i++){
			freq[i].used=false;
			freq[i].alpha='a'+i;
		}
		while(miss<6){	
			//cout<<"a";			
			for(int i=0;i<26;i++){
				freq[i].valid=true;
			//	freq[i].alpha='a'+i;
				freq[i].count=0;
			}			
			for(int i=start;i<=end;i++){
				if(test_set[i-start]=='t'){
					for(int j=0;j<dictionary[i].size();j++){
						if(freq[dictionary[i][j]-'a'].valid==true && freq[dictionary[i][j]-'a'].used==false){
							freq[dictionary[i][j]-'a'].valid=false;
							freq[dictionary[i][j]-'a'].count++;
						}
					}
				}
			}	
			char guess=max(freq);
			freq[guess-'a'].used=true;
			vector<int>place;
			for(int i=0;i<word.size();i++){
				if(word[i]==guess){
					flag=1;
					correct++;
					place.push_back(i);
				}
			}
			if(flag==0){
				miss++;
				for(int i=start;i<=end;i++){
					if(dictionary[i].find(guess)>=0&&dictionary[i].find(guess)<dictionary[i].size()){
						test_set[i-start]='f';
					}
				}
			}
			else if(correct<word.size()){	
				for(int i=start;i<=end;i++){
					for(int j=0;j<place.size();j++){
						if(dictionary[i][place[j]]!=guess){
							test_set[i-start]='f';
							break;
						}
					}
				}			
			}
			else
				break;
			flag=0;
		}
		if(flag){
			pass++;
		}
	}
	cout<<pass<<endl;
	cout<<(float)(pass*100)/MAX;
	return 0;
}
