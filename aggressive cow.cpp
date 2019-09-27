/*
https://paste.ubuntu.com/p/ZtGjSfVwTV/
https://ide.codingblocks.com/s/16346
https://www.youtube.com/watch?v=TC6snf6KPdE
*/

/*
You are given an array of integers which represents positions available and an integer c(cows).
Now you have to choose c positions such that minimum difference between cows is maximized.
For example,
1 3 5 8 10
c=3

Output: 4
1 5 10
*/

#include<bits/stdc++.h>
using namespace std;

bool Comperator(int x,int a[],int n,int k){// We want to know if we can get at least x distance with k cows
    int currentCows = 1;
    int leftmost = 0;
    
    for(int i=1;i<n;++i){
        if(a[i] - a[leftmost] >= x){
            leftmost = i;
            ++currentCows;
            if(currentCows == k)
            	return 1;
        }
    }
    return 0;
}

int main()
{
    int t;	cin >> t;
    for(int i=0;i<t;++i){
        int n,k;cin >> n >> k;
        int a[100000];
        for(int j=0;j<n;++j){
            cin >> a[j];
        }

        sort(a,a+n);
        
        int l = 0;
        int r = a[n-1] - a[0] + 1;
        // If we can do with x distance then obviosult we can do it with <=x.
        // So We need to update it
        //True True True True True True True . .. . . False False False ==> We want to find the last true
        
        while(r - l > 0){
            int m = (l + r + 1) /2;
            
            if(Comperator(m,a,n,k)==true){
                l = m; // l is true now
            }  
            else 
            	r = m-1; // R is false now
        }

        cout << l << '\n';
    }
}