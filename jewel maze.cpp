/*
https://blog.csdn.net/lihenair/article/details/17227667
http://www.mamicode.com/info-detail-995985.html
https://www.oipapio.com/cn/article-8650635
https://blog.csdn.net/broadCE/article/details/47959227
--------------------------------------------------------
There is a maze that has one entrance and one exit. Jewels are placed in passages of the maze. 
You want to pick up the jewels after getting into the maze through the entrance and before getting 
out of it through the exit. You want to get as many jewels as possible, but you don’t want to take 
the same passage you used once.

When locations of a maze and jewels are given, find out the greatest number of jewels you can get 
without taking the same passage twice, and the path taken in this case.

Input
There can be more than one test case in the input file. The first line has T, the number of test cases.
Then the totally T test cases are provided in the following lines (T ≤ 10 ).

In each test case, In the first line, the size of the maze N (1 ≤ N ≤ 10) is given. 
The maze is N×N square-shaped. From the second line through N lines, information of the maze is given.
“0” means a passage, “1” means a wall, and “2” means a location of a jewel. The entrance is located 
on the upper-most left passage and the exit is located on the lower-most right passage. 
There is no case where the path from the entrance to the exit doesn’t exist.

Output
From the first line through N lines, mark the path with 3 and output it. In N+1 line, output the 
greatest number of jewels that can be picked up. Each test case must be output separately as a empty.
*/

#include<iostream>
#include<climits>
#define MAX 21
using namespace std;

int n, ans;

bool isValid(int i, int j){
	return (i>=0 && i<n && j>=0 && j<n);
}

void printMatrix(int **arr){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cout << arr[i][j] << " ";	
		cout << endl;
	}
}

int dirX[] = {1,0,-1,0};
int dirY[] = {0,1,0,-1};

void jewelMaze(int **maze, int x, int y, int value, int **visited, int **path){
	if(x == n-1 && y == n-1){
		if(value >= ans){
			ans = value;
			
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++)
				    if(visited[i][j]){
				    	path[i][j] = 3;
					}
					else{
						path[i][j] = maze[i][j];
					}	
			}
		}
		return;
	}

	for(int i=0; i<4; i++){
		int newX = x + dirX[i];
		int newY = y + dirY[i];
		
		if(isValid(newX, newY)){
			
			if(visited[newX][newY] == 0 && maze[newX][newY] == 0){
				visited[newX][newY] = 1;
				jewelMaze(maze, newX, newY, value, visited, path);
				visited[newX][newY] = 0;
			}
			
			if(visited[newX][newY] == 0 && maze[newX][newY] == 2){
				visited[newX][newY] = 1;
				jewelMaze(maze, newX, newY, value+1, visited, path);
				visited[newX][newY] = 0;
			}

		}
	}
	
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		int **maze = new int * [n + 1];
		for(int i=0; i<n; i++){
			maze[i] = new int[n + 1];
		}
		
		int **visited = new int * [n + 1];
		for(int i=0; i<n; i++){
			visited[i] = new int[n + 1];
		}
		
		int **path = new int * [n + 1];
		for(int i=0; i<n; i++){
			path[i] = new int[n + 1];
		}

		// Cleaner and input Maze
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> maze[i][j];
				visited[i][j] = 0;
				path[i][j] = 0;
			}
		}
		
		ans = INT_MIN;
		
		int sX = 0, sY = 0;
		visited[sX][sY] = 1;
		
		// printMatrix(maze);
		
		if(maze[sX][sY] == 2)
			jewelMaze(maze, sX, sY, 1, visited, path);
		else
			jewelMaze(maze, sX, sY, 0, visited, path);
			
			
		cout << "Jewel collected : " << ans << endl;
		
		cout << "Path traversed --> " << endl;
		printMatrix(path); 
		
		cout << endl;
	}
	return 0;
}