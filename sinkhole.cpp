/*
https://www.geeksforgeeks.org/samsung-competency-test-25-aug-19/
*/
/*
	----IIT(ISM) Dhanbad----
	Author: Siddhant Choudhary
	
	--samsumg coding test--
	
	Q.There is a large plot with various sinkholes present. 
	Since one sinkhole can combine with another sinkhole, it is required to get
	at most one sinkhole while occupying the plot. You have to find the maximum 
	square-area formed with at most one sinkhole present.
	If there are two plots with the same area then print the one with 
	lesser sinkhole present otherwise if the sinkholes are also same then print
	anyone. For each case, you have to print the bottom leftmost coordinate and 
	top rightmost point. Please keep in mind that the plot starts with (1, 1).

	Time limit= 1sec and Memory limit– 256Mb

	Input: First line will give the number of test cases. For each test case, we
	will be given the size of the plot matrix N x M (where 1<=N, M<=1000). Next
	line will give the number of sinkholes present in the matrix K (1<=K<=N+M). 
	Next, K-lines will give the coordinates of the sinkholes.

	Output: For each test case, you have to print the number of the test case
	and the coordinates of the resultant square.
	i.e. #i xb yb xt yt (ith test case, xb=bottomost left x-coordinate, 
	yb=bottomost  left y-coordinate, xt= topmost right x-coordinate,
	yt= topmost right y-coordinate)
	
  *	time complexity of my approach = O(n*m*log(min(m,n))) *
*/

#include <iostream>
using namespace std;

#define INT_MAX 100000;

int xb,yb,xt,yt;

int fun(int dp[][1001], int N, int M, int k){
	int msum = INT_MAX;
	for(int i=0; i<=N-k; i++){
		for(int j=0; j<=M-k; j++){
			int sum = dp[i+k][j+k]-dp[i+k][j]-dp[i][j+k]+dp[i][j];
			if(sum < msum){
				msum = sum;
				if(msum <=1){
					xb = i+k;
					yb = j+1;
					xt = i+1;
					yt = j+k;
				}
			}
		}
	}
	return msum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	/* input */
	int N,M;
	cin>>N>>M;
	int A[N][M];
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			A[i][j]=0;
		}
	}
	int K;
	cin>>K;
	for(int i=0; i<K; i++){
		int x,y;
		cin>>x>>y;
		A[x-1][y-1]=1;
	}
	
	int dp[1001][1001]; /* dp[i][j] = sum of submatrix top-left(0,0) to bottom-right(i,j) */
	for(int i=0; i<1001; i++){
		for(int j=0; j<1001; j++){
			dp[i][j]=0;
		}
	}
	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			dp[i][j] = dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+A[i-1][j-1];
		}
	}
	/* applying binary search */
	int l=1, r=min(M,N);
	int ones;
	while(l<r){
		int mid = (l+r)/2;
		ones = fun(dp,N,M,mid);
		//if no. of ones > 1 means we need to decrease the submatix size 
		if(ones >1){
			r = mid;
		}
		//else increase the submatrix size
		else{
			l = mid+1;
		}
	}
	/* output */
	cout<<xb<<" "<<yb<<" "<<xt<<" "<<yt<<endl;
	return 0;
}