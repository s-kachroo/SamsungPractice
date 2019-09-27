//https://www.cnblogs.com/kingshow123/p/practicec1.html
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
int mv[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
//int mv[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};

int main()
{
    //freopen("test.txt","r",stdin);
    int T;
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        int n,m;
        int r,c;
        cin>>n>>m;
        int a[m+1][n+1];
        memset(a,0,sizeof(int)*m*n);
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                cin>>a[i][j];
            }
        }

        cin>>r>>c;
        data d,d1,d2;
        queue<data> qt;
        int tmx,tmy,tml;
        d.x = c;
        d.y = r;
        d.level = 1;
        qt.push(d);
        a[d.x][d.y] = 2;
        while(!qt.empty())
        {
            d1 = qt.front();
            qt.pop();
            for(int k=0; k<4; k++)
            {
                tmx = d1.x + mv[k][0];
                tmy = d1.y + mv[k][1];
                tml = d1.level + 1;
                if(a[tmx][tmy] == 1)
                {
                    d2.x = tmx;
                    d2.y = tmy;
                    d2.level = tml;
                    a[d2.x][d2.y] = 2;
                    qt.push(d2);
                }
            }
        }
        cout<<"Case #"<<t<<endl;
        cout<<tml-1<<endl;
    }
    //cout << "Hello world!" << endl;
    return 0;
}
