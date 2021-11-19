#include<bits/stdc++.h>
using namespace std;
#define N 10
int max(int a,int b){
	if(a<b){
		return b;
	}
	return a;
}
int min(int a,int b){
	if(a>b){
		return b;
	}
	return a;
}
void link(int n,vector<vector<int> > graph,int (*func)(int,int)){
	vector<pair<vector<int>,vector<int> > > ret;
	vector<vector<int> > ind(n);
	for(int i=0;i<n;i++){
		ind[i].push_back(i);
	}
	while(n>2){
		int mn=INT_MAX;
		int index[2]={-1,-1};
		for(int i=0;i<n;i++){
			for(int j=0;j<i;j++){
				if(graph[i][j]<mn){
					mn=graph[i][j];
					index[0]=i;
					index[1]=j;
				}
			}
		}
		cout<<"minimum element is: ";
		cout<<mn<<'\n';
		cout<<"after merging cluster \'";
		for(int i=0;i<ind[index[1]].size();i++){
			cout<<ind[index[1]][i];
		}
		cout<<"\' and \'";
		for(int i=0;i<ind[index[0]].size();i++){
			cout<<ind[index[0]][i];
		}
		
		for(int i=0;i<index[1];i++){
			graph[index[1]][i]=func(graph[index[1]][i],graph[index[0]][i]);
		}
		for(int i=index[1]+1;i<n;i++){
			graph[i][index[1]]=func(graph[i][index[1]],graph[i][index[0]]);
		}
		graph.erase(graph.begin()+index[0]);
		for(int i=index[0];i<n-1;i++){
			graph[i].erase(graph[i].begin()+index[0]);
		}
		// cout<<n<<"th iteration\n";
		cout<<"\' we get matrix: \n";
		for(int i=0;i<graph.size();i++){
			for(int j=0;j<graph[i].size();j++){
				cout<<graph[i][j]<<' ';
			}
			cout<<0<<endl;
		}
		n--;
		ret.push_back({ind[index[1]],ind[index[0]]});
		for(int i=0;i<ind[index[0]].size();i++){
			ind[index[1]].push_back(ind[index[0]][i]);
		}
		ind.erase(ind.begin()+index[0]);
	}
	ret.push_back({ind[0],ind[1]});
	cout<<"combining clusters at each stage are: \n";
	for(int i=0;i<ret.size();i++){
		// cout<<ret[i].first<<' '<<ret[i].second<<endl;
		for(int j=0;j<ret[i].first.size();j++){
			cout<<ret[i].first[j];
		}
		cout<<' ';
		for(int j=0;j<ret[i].second.size();j++){
			cout<<ret[i].second[j];
		}
		cout<<endl;
	}
}
int main(){
	int n;
	cout<<"Enter the number of nodes: \n";
	cin>>n;
	vector<vector<int> > graph;
	for(int i=0;i<n;i++){
		vector<int> temp;
		for(int j=0;j<i;j++){
			cout<<"enter the distance between "<<i<<" and "<<j<<" nodes:"<<endl;
			int x;
			cin>>x;
			temp.push_back(x);
		}
		graph.push_back(temp);
	}
	cout<<endl<<endl<<endl;
	cout<<"Using Single link:\n";
	link(n,graph,min);
	cout<<endl<<endl<<endl;
	cout<<"Using complete link:\n";
	link(n,graph,max);
}
