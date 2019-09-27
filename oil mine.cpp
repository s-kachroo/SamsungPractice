/*
https://www.careercup.com/question?id=5740719907012608
https://stackoverflow.com/questions/39673898/divide-array-into-k-contiguos-partitions-such-that-sum-of-maximum-partition-is-m/39675396
http://ideone.com/r60yH4 - Sameer Code
https://www.careercup.com/question?id=5730470801702912
*/

/*
There is an island surrounded by oil mines. You will be given n companies and m oil mines having values.
You have to distribute the mines to "n" companies in fair manner. Remember the companies can have oil 
mines adjacent to each other and not in between of each others.After distributing them compute the 
difference of oil mines from the company getting highest and company getting lowest. This number 
should be minimum.(then only the distribution can be termed as fair).

Input 
2 
2 4 
6 13 10 2 
2 4 
6 10 13 2 

output 
5 
1
*/

#include <iostream>
#include <climits>
using namespace std;

int companies, mines, ANS;

int MIN(int x, int y){
    return (x>=y) ? y : x;
}

int MAX(int x, int y){
    return (x>=y) ? x : y;
}

void calculateOilMines(int i, int *oilMines, bool *visited, int minV, int maxV, int sum,
                        int nodes, int &ANS){
    // Base Case
    if(visited[i]){
        int newMin = MIN(sum, minV);
        int newMax = MAX(sum, maxV);

        if(nodes == companies - 1){
            ANS = min(ANS, newMax - newMin);
        }
        return;
    }

    // Main Case
    visited[i] = 1;
    int j = (i + 1) % mines;

    calculateOilMines(j, oilMines, visited, minV, maxV, sum + oilMines[i], nodes, ANS);

    int newMin = MIN(sum, minV);
    int newMax = MAX(sum, maxV);

    calculateOilMines(j, oilMines, visited, newMin, newMax, oilMines[i], nodes + 1, ANS);

    visited[i] = 0;
    return;
}

int main() {
	// your code goes here
	int t;
	cin >> t;
	while(t--){
		cin >> companies >> mines;
		int  *oilMines = new int[mines + 1];
		bool *visited  = new bool[mines + 1];

		for(int i=0; i<mines; i++){
            cin >> oilMines[i];
            visited[i] = 0;
        }
			
        ANS = INT_MAX;    
        for(int i=0; i<mines; i++)
            calculateOilMines(i, oilMines, visited, INT_MAX, INT_MIN, 0, 0, ANS);  

		cout << ANS <<endl;		
	}
	return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;
int ans=9999;
void findMinDiff(int company[],int n)
{
    int mini = 9999;
    int maxi=0;
    for(int i=0;i<n;i++)
    {
        mini = min(mini,company[i]);
        maxi = max(maxi,company[i]);
    }
    if(ans>(maxi-mini))
        ans = maxi-mini;
}
void findAns(int end,int curr,int oil[],int company[],int m,int n,int num)
{
    if((curr+1)%m==end)
    {
        for(int j = num;j<n;j++)
        {
            company[j]+=oil[curr];
            findMinDiff(company,n);
            company[j]-=oil[curr];
        }
        return;
    }
    if(num==n)
        return;
    company[num]+=oil[curr];
    findAns(end,(curr+1)%m,oil,company,m,n,num);
    company[num]-=oil[curr];
    findAns(end,curr,oil,company,m,n,num+1);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ans=9999;
        int n,m;
        cin>>n>>m;
        int oil[m];
        for(int i=0;i<m;i++)
            cin>>oil[i];
        int company[n];
        for(int i=0;i<n;i++)
        {
            company[i]=0;
        }
        for(int i=0;i<m;i++)
        {
            findAns(i,i,oil,company,m,n,0);
        }
        cout<<ans<<endl;
    }
}
*/