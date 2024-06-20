/*
There are n balloons and n bullets and each balloon is assigned with a particular number (point).
Whenever a particular balloon is shot the no of points increases by
1.the multiplication of point assigned to balloon on left and that of right side.
2.point assigned to left if no right exists
3.point assigned to right if no left exists.
4.the point assigned to itself if no other balloon exists.
 
You have to output the maximum no of points possible.
 
Input-1
1 2 3 4
 
Output-1
20

Input-2
1 0 2 3 0 4

Output-2
34
*/
 
#include <iostream>
using namespace std;
 
int maxcoins(int A[],int siz)
{
    int nums[siz+2];
    int n=1, points = 0;
 
    for(int i=0;i<siz;i++)
    {
        if(A[i]>0)
        {
            nums[n] = A[i];
            n++;
        }
        else
            points += (n - 1 > 0 ? nums[n - 1] : 1) * (i + 1 < siz ? A[i + 1] : 1);    // balloons with zero points should be removed first using previous and next balloon points
            
    }
    nums[0] = nums[n] = 1;
    n++;

    // dp[i][j]: maximum points that can be collected from balloons from index i to j, (i and j exclusive)
    int dp[n][n] = {};
 
    for(int j=2;j<n;j++)
    {
        for(int left=0;left<n-j;left++)
        {
            int right = left+j;
            for(int i = left+1;i<right;i++)
            {
                if(left==0 && right==n-1)
                    dp[left][right] = max(nums[left]*nums[i]*nums[right] + dp[left][i] + dp[i][right],dp[left][right]);
                else
                    dp[left][right] = max(nums[left]*nums[right] + dp[left][i] + dp[i][right],dp[left][right]);
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return points + dp[0][n-1];
}
 
int main()
{
    int siz;
    cin >> siz;
    int A[siz];
    for(int i=0;i<siz;i++)
        cin >> A[i];
 
    int ans = maxcoins(A,siz);
    cout << ans << endl;
    return 0;
}

/*
5
1 2 3 5 4
*/
