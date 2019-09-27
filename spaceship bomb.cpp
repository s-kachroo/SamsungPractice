/*
https://www.careercup.com/question?id=5652067409461248
https://www.geeksforgeeks.org/samsung-interview-experience-set-28-campus/

http://ideone.com/JXMl4L
https://ide.geeksforgeeks.org/tiyLThcuSN -> Zero
https://ide.geeksforgeeks.org/3Ks1tpOkwn

*https://code.hackerearth.com/ea07cfD?key=1cb190b158c79639d66d35f7dfa8ef7a -> One

Similr Problem - https://ide.codingblocks.com/s/95965


You’ll be given a grid as below:

    0 1 0 2 0
    0 2 2 2 1
    0 2 1 1 1
    1 0 1 0 0
    0 0 1 2 2
    1 1 0 0 1
    x x S x x

In the grid above,
  1: This cell has a coin.
  2: This cell has an enemy.
  0: It contains nothing.

  The highlighted(yellow) zone is the control zone. S is a spaceship that we need to control so that we can get 
  maximum coins.
  Now, S’s initial position will be at the center and we can only move it right or left by one cell or do not move.
  At each time, the non-highlighted part of the grid will move down by one unit.
  We can also use a bomb but only once. If we use that, all the enemies in the 5×5 region above the control zone 
  will be killed.
  If we use a bomb at the very beginning, the grid will look like this:

    0 1 0 2 0
    0 0 0 0 1
    0 0 1 1 1
    1 0 1 0 0
    0 0 1 0 0
    1 1 0 0 1
    x x S x x

  As soon as, the spaceship encounters an enemy or the entire grid has come down, the game ends.
  For example,
  At the very first instance, if we want to collect a coin we should move left( coins=1). This is because when the 
  grid comes down by 1 unit we have a coin on the second position and by moving left we can collect that coin. 
  Next, we should move right to collect another coin (coins=2).
  After this, remain at the same position (coins=4).
  This is the current situation after collecting 4 coins.

    0 1 0 2 0 0 1 0 0 0
    0 2 2 2 1 -->after using 0 0 0 0 1
    x x S x x -->bomb x x S x x

   Now, we can use the bomb to get out of this situation. After this, we can collect at most 1 coin. So maximum coins=5.
*/
#include<bits/stdc++.h>
using namespace std;
void updateMatrix(int row,char ** matrix){
    if(row<0){
        return;
    }
    int upLimit=max(0,row-4);
    for(int i=row;i>=upLimit;i--){
        for(int j=0;j<=4;j++){
            if(matrix[i][j]=='2'){
                matrix[i][j]='0';
            }
        }
    }
}
int findMaxPoints(int row,int col,int bombs,char ** matrix){
    if(row<=0 || col<0 || col>=5){
        return 0;
    }
    int answer=0;
    if(row>0 && matrix[row-1][col]!='2'){
        answer=max(answer,(matrix[row-1][col]=='1'?1:0)+findMaxPoints(row-1,col,bombs,matrix));
    }
    if(col>0 && row>0 && matrix[row-1][col-1]!='2'){
        answer=max(answer,(matrix[row-1][col-1]=='1'?1:0)+findMaxPoints(row-1,col-1,bombs,matrix));
    }
    if(col<4 && row>0 && matrix[row-1][col+1]!='2'){
        answer=max(answer,(matrix[row-1][col+1]=='1'?1:0)+findMaxPoints(row-1,col+1,bombs,matrix));
    }

    if(answer==0 && bombs>0){
        updateMatrix(row-1,matrix);
        answer=findMaxPoints(row,col,bombs-1,matrix);
    }

    return answer;
}
int main(){
    int t, row;
    cin >> t;
    int tNo = 0;
    while(t--){
        cin >> row;
        char ** matrix=new char*[row + 2];
        for(int i=0; i<row; i++){
            matrix[i]=new char[5];
            for(int j=0;j<5;j++){
                cin>>matrix[i][j];
            }
        }
        tNo++;
        cout<< "#" << tNo << " : " << findMaxPoints(row,2,1,matrix) << endl;        
    }
    return 0;
}

/* 
No rech top 

#include <iostream>
using namespace std;
int det[5][5];
int mat[13][5];

void detonate(int r)
{
    for(int i=r;i>r-5 && i>=0;i--)
    {
        for(int j=0;j<5;j++)
        {
            det[r-i][j]=0;
            if(mat[i][j]==2)
            {
                det[r-i][j]=2;
                mat[i][j]=0;
            }
        }
    }
}

void undet(int r)
{
    for(int i=r;i>r-5 && i>=0;i--)
        for(int j=0;j<5;j++)
        {
            if( det[r-i][j]==2)
                mat[i][j]=2;
        }
}
void func(int n,int pos,int c,int &max)
{
    if(pos>4||pos<0||c<0)
        return;

    if(mat[n][pos]==2)
        c-=1;
    else if(mat[n][pos]==1)
        c+=1;

    if(n==0)
    {
        if(c>max)
            max=c;
        return;
    }
    else
    {
        func(n-1,pos+1,c,max);
        func(n-1,pos-1,c,max);
        func(n-1,pos,c,max);
    }
}
int main()
{
    int t;
    cin>>t;
    int count=1;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=0;i<n;i++)
            for(int j=0;j<5;j++)
                cin>>mat[i][j];
        int max=-1,c;
        for(int j=0;j<5;j++)
            mat[n][j]=0;
        mat[n][2]=3;
        for(int j=n;j>=5;j--)
        {
            c=-1;
            detonate(j-1);
            func(n,2,0,c);
            if(c>max)
                max=c;
            undet(j-1);
        }
        if(max<0)
            max=-1;
        cout<<"#"<<count<<" "<<max<<endl;
        count++;
    }
}
*/

/*
#include <iostream>
using namespace std;
int det[5][5];
int mat[13][5];

void detonate(int r){
    for(int i=r;i>r-5 && i>=0;i--){
        for(int j=0;j<5;j++){
            det[r-i][j]=0;
            if(mat[i][j]==2){
                det[r-i][j]=2;
                mat[i][j]=0;
            }
        }
    }
}

void undet(int r){
    for(int i=r;i>r-5 && i>=0;i--)
        for(int j=0;j<5;j++){
            if( det[r-i][j]==2)
                mat[i][j]=2;
        }
}

void func(int n,int pos,int c,int &max){
    if(pos>4||pos<0||c<0)
        return;

    if(mat[n][pos]==2)
        c-=1;
    else if(mat[n][pos]==1)
        c+=1;

    if(n==0){
        if(c>max)
            max=c;
        return;
    }
    else{
        func(n-1,pos+1,c,max);
        func(n-1,pos-1,c,max);
        func(n-1,pos,c,max);
    }
}

int main(){
    int t;
    cin>>t;
    int count=1;
    while(t--){
        int n;
        cin>>n;

        for(int i=0;i<n;i++)
            for(int j=0;j<5;j++)
                cin>>mat[i][j];
        for(int j=0;j<5;j++)
            mat[n][j]=0;
        mat[n][2]=3;

        int max=-1,c;
        for(int j=n;j>=5;j--){
            c=-1;
            detonate(j-1);
            func(n,2,0,c);

            if(c>max)
                max=c;
            
            undet(j-1);
        }

        if(max<0)
            max=-1;
        
        cout<<"#"<<count<<" "<<max<<endl;
        count++;
    }
}
*/