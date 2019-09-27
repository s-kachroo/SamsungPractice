/*
https://www.geeksforgeeks.org/samsung-interview-experience-on-campus-for-r-d-noida/

A binary matrix of nxm was given, you have to toggle any column k number of times so that you can get the maximum 
number of rows having all 1’s.

for eg, n=3, m=3,

            1 0 0

            1 0 1

            1 0 0

if k=2, then we will toggle column 2 and 3 once and we will get rows 1 and 3 with 1 1 1 and 1 1 1 i.e. all 1’s so 
answer is 2 as there are 2 rows with all 1’s.

if k=3, then we will toggle column 2 thrice and we will get row 2 with 1 1 1 i.e. all 1’s so answer is 1 as there 
is 1 row with all 1’s.
*/

#include<iostream>

using namespace std;
int grid[100][100];
int temp[100][100];
int maxi=-1;

/* restores original given matrix*/
void restore(int grid[][100],int r,int c){
	
	for(int i=0;i<r;i++){
	    for(int j=0;j<c;j++){
	        grid[i][j]=temp[i][j];		
	    }
    }
}

/* calculates  energy*/
int caleng(int grid[][100], int r, int c){
	int allone=0,eng=0;
    for(int i=0;i<r;i++){
	    for(int j=0;j<c;j++){
		    if(grid[i][j]==1){
			    allone++;
		    }
		    if(allone==c){
		    	eng++;
		    }
	    }
	    allone=0;
    }
    return eng;
}

/* flips the column*/
void flip(int grid[][100],int r,int c,int k){
	for(int i=0;i<r;i++){
        if(grid[i][k]==1){
	        grid[i][k]=0;
	    }	
	    else if(grid[i][k]==0){
	        grid[i][k]=1;
	    }		
	}
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int r,int row,int col){   
    if (index == r){  
        for (int j = 0; j < r; j++){ 
			flip(grid,row,col,data[j]);
		}

		if(maxi < caleng(grid,row,col)){
			maxi = caleng(grid,row,col);
		}  

		restore(grid,row,col);       
        return;  
    }  
  
    for (int i = start; i <= end && end - i + 1 >= r - index; i++){  
        data[index] = arr[i];  
        combinationUtil(arr, data, i+1, end, index+1, r,row,col);  
    }  
}  


void printCombination(int arr[], int n, int r,int row,int col)  {  
    int data[r];  
    combinationUtil(arr, data, 0, n-1, 0, r,row,col);  
}  

int main(){
	int t=0;
	cin>>t;
	int testcase=0;
	while(t--){
		testcase++;
			
			int c,r=0;
			cin>>r>>c;
			int s=0;
			cin>>s;
			int arr[c];
			for(int j=0;j<c;j++){
				arr[j]=j;
			}	
		       
			for(int i=0;i<r;i++){
				for(int j=0;j<c;j++){
					cin>>grid[i][j];
					temp[i][j]=grid[i][j];
				}
			}
			
			maxi=caleng(temp,r,c);	// if initial energy is max so this is corner case ......
			 
			if(s%2==0&&s>=c){
			    for(int i=2;i<=c;i=i+2){
			        printCombination(arr, c, i,r,c);
			        restore(grid,r,c);	
			    }	
			}

			// if flips are even and flips are greater than colums then check for all columns....
			if(s%2!=0&&s>=c){
			    for(int i=1;i<=c;i=i+2){
			        printCombination(arr, c, i,r,c);
			        restore(grid,r,c);	
			    }	
			}

			// if flips are odd and flips are greater than colums then check for all columns....
			if(s%2==0&&s<c){
			    for(int i=2;i<=s;i=i+2){
			        printCombination(arr, c, i,r,c);
			        restore(grid,r,c);	
			    }	
			}

			// if flips are lessthan columns and even then we dont need to check for all combinations with even length eg if flips are 3 and colums are 5 than we won't be checking for {1,2,3,4,5}....or if we have 2 flips we won't be checking for {1,2,3,4} types of combinations 
			if(s%2!=0&&s<c){
			    for(int i=1;i<=s;i=i+2){
			        printCombination(arr, c, i,r,c);
			        restore(grid,r,c);	
			    }	
			}

		cout<<"#"<<testcase<<" "<<maxi<<endl;
		maxi=-1;
	}
}


/* the idea/approch behind the problem is that if we have given flips as even then only even length combination of flips will give max ans
 for eg I have 50 filps and 5 columns then even size combinations are {1,2},{2,3},{3,4},{4,5},{1,3} and so on here length of combination is 2 similarly check for combination length 4 and no need to check for 6 length combination becoz we have only 5 columns
 {1,2,3,4} is one of the combination that we need to check if we will check for all combinations like {1},{2} and so on all possible combinations including odd length combinations we will encounter TLE
 similarly if flips are odd we have to check for odd size combination length({1,2,3},{1},{2},{3}..... and so on ) this isn't exactly bruteforce but kindoff this method won't lead to TLE thats for sure.here combinations lisited above are the places where we have to flip column 

                <----------------------------------------HOPE THIS WILL HELP YOU FOR ALL THE SOLUTIONS TO SAMSUNG PROBLEMS LIKE ENDOSCOPE WORMHOLES types AND MANY MORE DO LET ME KNOW--------------------------------------->

*/