/* 
https://www.careercup.com/question?id=5745468609921024 
https://gist.github.com/gunpreet34/d0e45eedd61dadbf42fe6540da98facf
https://ideone.com/SlO2P5 - BitMasking Solution
http://ideone.com/tdNRtQ - TARGET_SAMSUNG
*/

/*
Mr. Kim has to deliver refrigerators to N customers. From the office, he is going to visit all the customers and then return to his home. 
Each location of the office, his home, and the customers is given in the form of integer coordinates (x,y) (0≤x≤100, 0≤y≤100) . 
The distance between two arbitrary locations (x1, y1) and (x2, y2) is computed by |x1-x2| + |y1-y2|, where |x| denotes the absolute value 
of x; for instance, |3|=|-3|=3. The locations of the office, his home, and the customers are all distinct. You should plan an optimal way 
to visit all the N customers and return to his among all the possibilities.
You are given the locations of the office, Mr. Kim’s home, and the customers; the number of the customers is in the range of 5 to 10. 
Write a program that, starting at the office, finds a (the) shortest path visiting all the customers and returning to his home. 
Your program only have to report the distance of a (the) shortest path.

Constraints

5≤N≤10. Each location (x,y) is in a bounded grid, 0≤x≤100, 0≤y≤100, and x, y are integers.

Input

You are given 10 test cases. Each test case consists of two lines; the first line has N, the number of the customers, and the 
following line enumerates the locations of the office, Mr. Kim’s home, and the customers in sequence. Each location consists of 
the coordinates (x,y), which is reprensented by ‘x y’.

Output

Output the 10 answers in 10 lines. Each line outputs the distance of a (the) shortest path. Each line looks like ‘#x answer’ 
where x is the index of a test case. ‘#x’ and ‘answer’ are separated by a space.

I/O Example

Input (20 lines in total. In the first test case, the locations of the office and the home are (0, 0) and (100, 100) respectively, 
and the locations of the customers are (70, 40), (30, 10), (10, 5), (90, 70), (50, 20).)

5 ← Starting test case #1

0 0 100 100 70 40 30 10 10 5 90 70 50 20

6 ← Starting test case #2

88 81 85 80 19 22 31 15 27 29 30 10 20 26 5 14

10 ← Starting test case #3

39 9 97 61 35 93 62 64 96 39 36 36 9 59 59 96 61 7 64 43 43 58 1 36

Output (10 lines in total)

#1 200

#2 304

#3 366
*/
#include<iostream>
#include<climits>
using namespace std;
int x[20],y[20],n,ans;

int abs(int i){//Absolute function
	if(i>0){
		return i;
	}
	return -i;
}

int dist(int i, int j){//Calc dist between 2 points
    int x1 = x[i], x2 = x[j];
    int y1 = y[i], y2 = y[j];
    
    return (abs(x1-x2) + abs(y1-y2));
}

void optimalPath(int x,bool visited[],int nodes,int value){
	if(n == nodes){//If number of nodes equal n then set value of answer
		ans = min(ans,value + dist(x,n+1));
	}
	for(int i=1;i<=n;i++){
		if(!visited[i]){
			visited[i] = true;
			optimalPath(i,visited,nodes+1,value + dist(x,i));//Dfs call
			visited[i] = false;
		}
	}
}

int main(){
	int tCases;
	cin >> tCases;//For testcases
	for(int i=0;i<tCases;i++){
		ans=INT_MAX;//Set ans to max value
		cin >> n;
		cin >> x[n+1] >> y[n+1] >> x[0] >> y[0];//Input destination and source x,y coordinates
		for(int i=1;i<=n;i++){//Input drop off location coordinates
			cin >> x[i] >> y[i];
		}
		bool visited[n+2]={false};
		optimalPath(0,visited,0,0);
		cout << "#" << i+1 << " " << ans << endl;
	}
	return 0;
}

/*
#include <iostream>
#include <cstring>
using namespace std;

bool marked[105][105];

struct point {
    int x;
    int y;
};

int absDiff(point i, point j)
{
    int xd = (i.x > j.x) ? i.x - j.x : j.x - i.x ;
    int yd = (i.y > j.y) ? i.y - j.y : j.y - i.y ;
    return xd + yd ;
}

int solve(point a, point b, point arr[], point &end, int nodes)
{
    int curDist = absDiff(a, b);
    marked[b.x][b.y] = 1;
    int dist = 0, minDist = 1000007 ;
    for(int i = 0; i < nodes; i++){
        if(marked[arr[i].x][arr[i].y] == 0){
            dist = solve(b, arr[i], arr, end, nodes);
            if(dist < minDist)
                minDist = dist ;
        }
    }
    marked[b.x][b.y] = 0;
    if(minDist == 1000007){
        minDist = absDiff(b, end);
    }
    
    return curDist + minDist ;
}

int main()
{
    int test;
    cin >> test ;
    for(int l = 1; l <= test; l++){
        
        int nodes;
        cin >> nodes ;
        point start, end;
        point arr[nodes + 3];
        
        cin >> start.x >> start.y ;
        cin >> end.x >> end.y ;
        
        for(int u = 0; u < nodes; u++){
            cin >> arr[u].x >> arr[u].y ;
        }
        
        int dist = 0, minDist = 100007 ;
        for(int i = 0; i < nodes; i++){
            memset(marked, 0, sizeof(bool) * (nodes + 2) * (nodes + 2));
            dist = solve(start, arr[i], arr, end, nodes);
            if(dist < minDist)
                minDist = dist ;
        }
        
        cout << "#" << l << " " << minDist << endl ;
    }
    return 0;
}
*/