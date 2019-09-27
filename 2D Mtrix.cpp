#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        bool isNoPath = false;
        cin>>n;
        char arr[n][n];
        pair<int,int> dp[n][n];
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>arr[i][j];
                dp[i][j].first = 0;
                dp[i][j].second = 0;
            }
        }
        arr[0][0]='0';
        arr[n-1][n-1]='0';
        
        //Move to last coulumn
        for(int i=n-2;i>=0;i--)
        {
            if(arr[i][n-1]=='x')
            {
                for(int j=i;j>=0;j--)
                {
                    dp[j][n-1].first = dp[j][n-1].second = INT_MIN;
                }
                break;
            }
            else
            {
                dp[i][n-1].first = dp[i+1][n-1].first+(arr[i][n-1]-48);
                dp[i][n-1].second = 1;
            }
        }    
        //Move to last row
        for(int i=n-2;i>=0;i--)
        {
            if(arr[n-1][i]=='x')
            {
                for(int j=i;j>=0;j--)
                {
                    dp[n-1][j].first = dp[n-1][j].second = INT_MIN;
                }
                break;
            }
            else
            {
                dp[n-1][i].first = dp[n-1][i+1].first+(arr[n-1][i]-48);
                dp[n-1][i].second = 1;
            }
        }
        
        //Move to Remaining matrix
        for(int i=n-2;i>=0;i--)
        {
            for(int j=n-2;j>=0;j--)
            {
                if(arr[i][j]=='x')
                {
                    dp[i][j].first = dp[i][j].second = INT_MIN;
                }
                else
                {
                    int maxi = max(dp[i][j+1].first,max(dp[i+1][j+1].first,dp[i+1][j].first));
                    int path = 0;
                    if(dp[i][j+1].first==maxi)
                        path += dp[i][j+1].second;
                    if(dp[i+1][j+1].first==maxi)
                        path += dp[i+1][j+1].second;
                    if(dp[i+1][j].first==maxi)
                        path += dp[i+1][j].second;
                    if(maxi==INT_MIN)
                    {
                        isNoPath = true;
                        break;
                    }
                    dp[i][j].first = maxi+(arr[i][j]-48);
                    dp[i][j].second = path;
                }
            }
        }
        if(isNoPath)
            cout<<"0"<<" "<<"0"<<endl;
        else
        cout<<dp[0][0].first<<" "<<dp[0][0].second<<endl;   
    }
	return 0;
}