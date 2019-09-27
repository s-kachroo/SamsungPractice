/*
https://www.geeksforgeeks.org/samsung-r-d-noida-question-september-2018/
https://code.hackerearth.com/8ca41dM?key=54591adea7ca921ac55169b10f163508

You have to place an electronic banner of a company as high as it can be, so that whole the city can view the banner 
standing on top of TWO PILLERS.
The height of two pillers are to be chosen from given array.. say [1, 2, 3, 4, 6]. We have to maximise the height
of the two pillars standing side by side, so that the pillars are of EQUAL HEIGHT and banner can be placed on top of it.
In the above array, (1, 2, 3, 4, 6) we can choose pillars like this, say two pillars as p1 and p2.
In case, there is no combination possible, print 0.

INPUT :
1
5
1 2 3 4 6
Output :
8
*/

#include <iostream>
using namespace std;

void solve(int a[], int vis[], int p1, int p2, int n, int &ans){
    if(p1 == p2){
        if(p1 > ans){
            ans = p1;
        }
    }


    for(int i=0 ; i<n ; ++i){
        if(vis[i] == 0){
            vis[i] = 1;
            solve(a, vis, p1 + a[i], p2, n, ans);
            solve(a, vis, p1, p2 + a[i], n, ans);
            vis[i] = 0;
        }
    }
}

int main(){
    int n;
    cin>>n;
    int a[n];

    for(int i=0 ; i<n ; ++i){
        cin>>a[i];
    }

    int vis[n] = {0};
    int ans = -1;
    solve(a,vis,0,0,n,ans);

    cout<<ans;
}