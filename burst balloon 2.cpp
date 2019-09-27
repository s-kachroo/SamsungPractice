/*
https://www.youtube.com/watch?v=IFNibRVgFBo - Tushar Roy

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. 
You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.
Input: [3,1,5,8]
Output: 167 
*/

int maxCoins(vector<int>& nums) {
    /* O(n^3) Time and O(n^2) Space */
    int size = nums.size();
    if(size == 0)
        return 0;
        
    int i, j, k;
    vector< vector<int> > dp(size, vector<int>(size, 0));
       
    for(int len = 1; len <= size; len++){
        for(i = 0; i <= size - len; i++){
            j = len + i - 1;
            for(k = i; k <= j; k++){ 
                /* Left/Right Value has default 1 but holds prev and after ballon value if k is in middle */
                int leftValue  = 1;
                int rightValue = 1;
                    
                if(i != 0)
                    leftValue  = nums[i-1];
                if(j != size-1)
                    rightValue = nums[j+1];
                        
                /* Before and After - current k balloon is last to burst select the left side and right side to burst */
                int before = 0;
                int after  = 0;
                    
                if(i != k)
                    before = dp[i][k-1];
                if(j != k)
                    after  = dp[k+1][j];
                    
                dp[i][j] = max(dp[i][j], 
                         leftValue * nums[k] * rightValue + before + after);
            }   
        }
    }    
    return dp[0][size-1];
}
