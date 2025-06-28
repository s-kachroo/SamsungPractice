/*
https://www.hackerearth.com/problem/algorithm/question-7-4
*/

#include<iostream>
using namespace std;

struct Node{
    bool left, right, up, down;
};

struct Point{
    int x, y;  
};

int n, m, sX, sY, len;
int arr[1005][1005];
int vis[1005][1005], dis[1005][1005];

int result;
Node pipes[1005][1005];
Point queue[1000005];

bool isValid(int i, int j){
    return (i>=0 && i<n && j>=0 && j<m);
}

void bfs(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            vis[i][j] = 0;
            dis[i][j] = 0;
        }
    }
    
    int front = 0, rear = 0; 
    
    dis[sX][sY] = 1;
    vis[sX][sY] = 1;
    
    if( arr[sX][sY] == 0 ){
        result = 0;
        return;
    }
    
    queue[rear].x = sX;
    queue[rear].y = sY;
    rear = (rear + 1) % 1000005;
    
    while(front != rear){
        int p = queue[front].x;
        int q = queue[front].y;
        front = (front + 1) % 1000005;
        
        if( 1 + dis[p][q] <= len ){
            
            /* Row Up */
            if( isValid(p-1, q) && vis[p-1][q] == 0 && pipes[p-1][q].down && pipes[p][q].up ){
                vis[p-1][q] = 1;
                dis[p-1][q] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p-1;
                queue[rear].y = q;
                rear = (rear + 1) % 1000005;
            } 
            
            /* Row Down */
            if( isValid(p+1, q) && vis[p+1][q] == 0 && pipes[p+1][q].up && pipes[p][q].down ){
                vis[p+1][q] = 1;
                dis[p+1][q] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p+1;
                queue[rear].y = q;
                rear = (rear + 1) % 1000005;
            } 
            
            /* Column Left */
            if( isValid(p, q-1) && vis[p][q-1] == 0 && pipes[p][q-1].right && pipes[p][q].left ){
                vis[p][q-1] = 1;
                dis[p][q-1] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p;
                queue[rear].y = q-1;
                rear = (rear + 1) % 1000005;
            }          

            /* Column Right */
            if( isValid(p, q+1) && vis[p][q+1] == 0 && pipes[p][q+1].left && pipes[p][q].right ){
                vis[p][q+1] = 1;
                dis[p][q+1] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p;
                queue[rear].y = q+1;
                rear = (rear + 1) % 1000005;
            }          
                        
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	//code
	int t;
	cin >> t;
	while(t--){
	    result = 1;
	    cin >> n >> m >> sX >> sY >> len;
	    
	    for(int i=0; i<n; i++){
	        for(int j=0; j<m; j++){
	            cin >> arr[i][j];
	            
	            if( arr[i][j] == 1 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = true;
	                pipes[i][j].up = true;
	                pipes[i][j].down = true;
	            } 
	            else if( arr[i][j] == 2 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = false;
	                pipes[i][j].up = true;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 3 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = true;
	                pipes[i][j].up = false;
	                pipes[i][j].down = false;	                
	            }
	            else if( arr[i][j] == 4 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = true;
	                pipes[i][j].up = true;
	                pipes[i][j].down = false;
	            }
	            else if( arr[i][j] == 5 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = true;
	                pipes[i][j].up = false;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 6 ){
	                pipes[i][j].left = true;
                    pipes[i][j].right = false;
	                pipes[i][j].up = false;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 7 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = false;
	                pipes[i][j].up = true;
	                pipes[i][j].down = false;	                
	            }
	            else{
	                pipes[i][j].left = false;
	                pipes[i][j].right = false;
	                pipes[i][j].up = false;
	                pipes[i][j].down = false;	                
	            }
	 
	        }
	    }
	    
	    bfs();
	    cout << result << "\n";
	}
	return 0;
}

// Simple Bfs, just check the type of pipe then select it's neighbors.. and check if neighbors allow reverse movement (pipe compatibility.. eg. Up-Down pipe has adjacent neighbor as left-right pipe then 
// it pipes ain't compatible.. endoscopy can't be performed)
// #include <bits/stdc++.h>
// using namespace std;
// #define ll long long int
// #define vi vector<int>
// #define pii pair<int, int>
// #define F first
// #define S second
// #define input(a)                       \
//     for (int i = 0; i < a.size(); i++) \
//     cin >> a[i]
// #define print(a)     \
//     for (auto i : a) \
//     cout << i << ' '
// #define all(a) a.begin(), a.end()

// bool isValid(int r, int c, vector<vector<int>> &a)
// {
//     return (r >= 0 && c >= 0 && r < a.size() && c < a[0].size());
// }

// void solve()
// {
//     int h, w;
//     cin >> h >> w;
//     pii st;
//     cin >> st.first >> st.second;
//     int l;
//     cin >> l;

//     vector<vector<int>> gmap(h, vector<int>(w));
//     for (int i = 0; i < h; i++)
//         for (int j = 0; j < w; j++)
//             cin >> gmap[i][j];

//     if (gmap[st.first][st.second] == 0)
//     {
//         cout << 0 << endl;
//         return;
//     }

//     vector<vector<bool>> vis(h, vector<bool>(w, 0));
//     int res = 1;
//     vis[st.first][st.second] = 1;
//     l--;

//     queue<pair<int, int>> q;
//     q.push({st.first, st.second});

//     int dr[] = {-1, 1, 0, 0};
//     int dc[] = {0, 0, -1, 1};
//     int opposite[] = {1, 0, 3, 2};

//     vector<vector<int>> pipe = {
//         {},
//         {0, 1, 2, 3},
//         {0, 1},
//         {2, 3},
//         {0, 3},
//         {1, 3},
//         {1, 2},
//         {0, 2}};

//     while (l > 0 && !q.empty())
//     {
//         int size = q.size();
//         while (size--)
//         {
//             auto top = q.front();
//             int r = top.first;
//             int c = top.second;
//             q.pop();
//             int pipetype = gmap[r][c];

//             for (int dir : pipe[pipetype])
//             {
//                 int nr = r + dr[dir];
//                 int nc = c + dc[dir];

//                 if (isValid(nr, nc, gmap) && !vis[nr][nc] && gmap[nr][nc] != 0)
//                 {
//                     int neighborType = gmap[nr][nc];
//                     if (find(pipe[neighborType].begin(), pipe[neighborType].end(), opposite[dir]) != pipe[neighborType].end())
//                     {
//                         vis[nr][nc] = 1;
//                         res++;
//                         q.push({nr, nc});
//                     }
//                 }
//             }
//         }
//         l--;
//     }

//     cout << res << endl;
// }

// int main()
// {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
//     cout.tie(0);
//     int t = 1;
//     cin >> t;
//     while (t--)
//         solve();
//     return 0;
// }
