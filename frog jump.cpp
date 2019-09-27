/*
https://www.careercup.com/question?id=14989765
http://ideone.com/oXdBaF

Given a 2 D matrix where 1 represent the places where the frog can jump and 0 represent the empty spaces,
the frog can move freely in horizontal direction (on 1’s only) without incurring any cost (jump). 
A vertical jump from a given point of the matrix to other point on the matrix can be taken (on 1’s only) 
with cost as the number of jumps taken.
Given a source and destination, the frog has to reach the destination minimizing the cost (jump).
*/

#include <iostream>
using namespace std;
#define QS 1000005

struct Point{
	int x, y;
};

int n, sX, sY, tX, tY; 
int mat[105][105], dis[105][105], vis[105][105];

Point queue[QS];
int front = 0, rear = 0;

int dirX[] = {1,0,-1,0};
int dirY[] = {0,1,0,-1};

bool isValid(int i, int j){
	return (i>=0 && i<n && j>=0 && j<n);
}

void calculateFrogJump(){
	queue[rear].x = sX;
	queue[rear].y = sY;
	rear = (rear + 1) % QS;

	vis[sX][sY] = 1;
	dis[sX][sY] = 0;

	while(front != rear){
		int p = queue[front].x;
		int q = queue[front].y;
		front = (front + 1) % QS;

		for(int i=0; i<4; i++){
			int newX = p + dirX[i];
			int newY = q + dirY[i];

			if(isValid(newX, newY) && mat[newX][newY] == 1 && vis[newX][newY] == 0){
				/* Horizontal Cost */
				if(i == 0 || i == 2){
					dis[newX][newY] = dis[p][q];
 				}
				else if(i == 1 || i == 3){
					dis[newX][newY] = 1 + dis[p][q];
				}

				vis[newX][newY] = 1;

				queue[rear].x = newX;
				queue[rear].y = newY;
				rear = (rear + 1) % QS;	
			}
		}
	}
	cout << dis[tX][tY];
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> mat[i][j];
			vis[i][j] = 0;
			dis[i][j] = 0;
		}
	}

	cin >> sX >> sY >> tX >> tY;

	calculateFrogJump();
	return 0;
} 