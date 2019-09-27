/*
https://www.cnblogs.com/kingshow123/p/practicec2.html
http://www.voidcn.com/article/p-mpfarobd-bgr.html
*/

/*
There is a mobile piece and a stationary piece on the N×M chessboard. 
The available moves of the mobile piece are the same as set out in the image below. 
You need to capture the stationary piece by moving the mobile piece with the minimum amount of moves.

Write a program to find out the minimum number moves to catch a piece. 

[Input]
Several test cases can be included in the inputs. T, the number of cases is given in the first row of the
inputs. After that, the test cases as many as T (T ≤ 20) are given in a row. 
N, the numbers of the rows and M, the number of columns of the chessboard are given in the first row of
each test case. 
R & C is the location information of the attacking piece and S & K is the location of the defending pieces 
and are given in the row at the second line. However, the location of the uppermost end of the left end 
is (1, 1)

[Output]
For each test case, you should print "Case #T" in the first line where T means the case number.

For each test case, you should output the minimum number of movements to catch a defending piece at the 
first line of each test case. If not moveable, output equals ‘-1’. 

[I/O Example]

Input 
2
9 9
3 5 2 8
20 20
2 3 7 9

Output
Case #1
2
Case #2
5 
*/

#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;
typedef struct
{
    int x;
    int y;
    int level;
}data;
int mv[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};

int main(){
    int T;
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        int n,m,r1,c1,r2,c2;
        cin>>n>>m;
        int a[n+1][m+1];
        memset(a,0,sizeof(int)*(n+1)*(m+1));
        cin>>r1>>c1>>r2>>c2;
        data d,d1,d2;
        queue<data> qt;
        d.x = r1;
        d.y = c1;
        d.level = 0;
        qt.push(d);
        a[d.x][d.y] = 2;
        int tmx,tmy,tml;
        int steps = 0;
        bool f = false;
        while(!qt.empty())
        {
            if(f)
            {
                break;
            }
            d1 = qt.front();
            qt.pop();
            for(int k=0; k<8; k++)
            {
                tmx = d1.x + mv[k][0];
                tmy = d1.y + mv[k][1];
                tml = d1.level + 1;

                if(tmx>=1 && tmx<=n && tmy>=1 && tmy<=m && a[tmx][tmy] == 0)
                {
                    if(tmx == r2 && tmy == c2)
                    {
                        steps = tml;
                        f = true;
                        break;
                    }
                    d2.x = tmx;
                    d2.y = tmy;
                    d2.level = tml;
                    qt.push(d2);
                    a[d2.x][d2.y] = 2;
                }
            }
        }
        if(!f)
        {
            steps = -1;
        }
        cout<<"Case #"<<t<<endl;
        cout<<steps<<endl;
    }
    //cout << "Hello world!" << endl;
    return 0;
}
