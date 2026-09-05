/*
https://www.careercup.com/question?id=5680648437104640

You are given an old touch smartphone numbers having dial pad and calculator app.
Aim: The goal is to type a number on dialpad.

But as phone is old, some of the numbers and some operations can't be touched.
For eg. 2,3,5,9 keys are not responding , i.e you cannot use them
But you can always make a number using other numbers and operations in Calculator. There could be multiple ways of making a number

Calculator have 1-9 and +,-,*,/,= as operations. Once you have made the number in Calculator you can copy the number and use it.

You have to find minimum number to touches required to obtain a number.

#Input:#
There will be multiple Test cases .Each test case will consist of 4 lines
1) First line will consist of N,M,O
	N: no of keys working in Dialpad (out of 0,1,2,3,4,5,6,7,8,9)
	M:types of operations supported (+,-,*,/)
	O: Max no of touches allowed
2) second line of input contains the digits that are working e.g 0,2,3,4,6.
3) Third line contains the valued describing operations, 1(+),2(-),3(*),4(/)
4) fourth line contains the number that we want to make .

#Output:#
Output contains 1 line printing the number of touches required to make the number


#Sample Test Case:#
5 
5 3 5
1 2 4 6 0
1 2 3
5
6 4 5 
1 2 4 6 9 8
1 2 3 4
91
6 2 4
0 1 3 5 7 9
1 2 4
28
5 2 10
1 2 6 7 8
2 3
981
6 3 5
1 4 6 7 8 9
1 2 3
18

#Output:#
4
2 
5
9
2



If you have to type 18-> 2 operations. (Each touch is considered an operation),br> If you have to type 5 -> '1+4=' that requires 4 operations. There could be other ways to make '5'.
*/

#include<iostream>
#include<math.h>
using namespace std;
int *working,*operations;
int answer=INT_MAX;
int n,m,o;
int eval(int prev,int curr,int op){
	if(prev==-10000000){
		return curr;
	}
	
	if(op==1){
		return prev+curr;
	}
	if(op==2){
		return prev-curr;
	}
	if(op==3){
		return prev*curr;
	}
	if(op==4){
		if(curr==0){
			return -1;
		}else{
			return prev/curr;
		}
	}
}
bool isDone(int prev,int curr,int Operation,int target){
	if(Operation==4 && curr==0){
		return false;
	}
	
	if(eval(prev,curr,Operation)==target)
		return 1;
	return false;
}
void findMinTouch(int prev,int curr,int ooperation,int tou,int t)
{   if(ooperation!=-1 && curr!=-10000000)
{
	bool k=isDone(prev,curr,ooperation,t);
	if(k && tou<o  )
	{
		if(answer>tou+1)
		answer=tou+1;
	}
}
if(prev==t && tou<o && ooperation !=-1 && curr==-10000000)
{
	answer=min(answer,tou);
	
}
if(ooperation==-1 && curr==t && tou<o )
{
	answer=min(answer,tou);
}
if(tou>o) return ;

	for(int i=0;i<m;i++)
	{
		if(curr==-10000000)
		break;
		if(curr==0 && ooperation==4) continue;
		int val=eval(prev,curr,ooperation);
		findMinTouch(val,-10000000,operations[i],tou+1,t);
	}
	for(int i=0;i<n;i++)
	{
		if(curr==-10000000)
		{
			findMinTouch(prev,working[i],ooperation,tou+1,t);
		}
		else
		{
			int val=abs(curr);
			val=val*10+working[i];
			if(curr<0){
				val*=-1;
			}
			findMinTouch(prev,val,ooperation,tou+1,t);
		}
	}
}
int main(){
	int t;
	cin>>t;
	int count = 0;
	while(t--){
		answer=INT_MAX;
		cin>>n>>m>>o;
		working=new int[n + 2];
		for(int i=0;i<n;i++){
			cin>>working[i];
		}
		operations=new int[m + 2];
		for(int i=0;i<m;i++){
			cin>>operations[i];
		}
		
		int target;
		cin>>target;
		
		findMinTouch(-10000000,-10000000,-1,0,target);
		count++;
		cout<<"#" << count << ": " << answer<<endl;
	}
	return 0;
}



// To pass Samsung's strict constraints without crashing or timing out, a Breadth-First Search (BFS) approach is much better than DFS.

#include <iostream>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

// In Samsung tests, values on the calculator screen usually stay within a reasonable limit.
// We define a boundary to prevent integer overflows and limit our search space.
#define MAX_VAL 100000 

// This structure represents the exact state of our calculator at any given moment.
struct CalcState {
    int prev;       // Accumulated result from previous operations (-1 means empty)
    int curr;       // The number currently being typed on the screen (-1 means empty)
    int op;         // Pending operation: 1(+), 2(-), 3(*), 4(/), -1(none)
    int touches;    // Total number of button presses made so far
};

int workingDigits[12];
int workingOps[6];
int numDigits, numOps, maxTouches, target;

// A 3D visited array to avoid processing the same calculator state multiple times.
// visited[prev_val][curr_val][pending_op] = minimum touches taken to reach this state.
// To handle negative numbers or empty states safely, we add offsets or check bounds.
int visited[1005][1005][5]; 

// Helper function to evaluate the math equation
int calculate(int prev, int curr, int op) {
    if (prev == -1) return curr;
    if (op == 1) return prev + curr;
    if (op == 2) return prev - curr;
    if (op == 3) return prev * curr;
    if (op == 4) {
        if (curr == 0) return -1; // Prevent division by zero
        return prev / curr;
    }
    return curr;
}

int solve() {
    queue<CalcState> q;
    
    // Step 1: Initial States. 
    // We can start by pressing any valid single digit button.
    for (int i = 0; i < numDigits; i++) {
        int digit = workingDigits[i];
        
        // If typing this single digit directly hits the target, we only need 1 touch!
        if (digit == target) return 1; 
        
        // Push this initial state into our BFS queue
        // (prev = -1, curr = digit, op = -1, touches = 1)
        q.push({-1, digit, -1, 1});
    }

    // Step 2: Begin BFS Traversal
    while (!q.empty()) {
        CalcState u = q.front();
        q.pop();

        // If we exceed the maximum allowed touches, we don't explore deeper from here
        if (u.touches >= maxTouches) continue;

        // --- OPTION A: Press a DIGIT key to append to the current number ---
        if (u.curr != -1) { // We can only append if a number is already started
            for (int i = 0; i < numDigits; i++) {
                int nextDigit = workingDigits[i];
                
                // Form the new number by appending the digit (e.g., 1 followed by 8 becomes 18)
                long long nextCurr = (long long)u.curr * 10 + nextDigit;
                
                // Prevent out-of-bound errors or large numbers
                if (nextCurr < MAX_VAL) {
                    int nCurr = (int)nextCurr;
                    int nTouches = u.touches + 1;

                    // If we just typed the target number directly without using operations, we are done!
                    if (u.op == -1 && nCurr == target) {
                        return nTouches;
                    }

                    // Push the updated state into the queue
                    q.push({u.prev, nCurr, u.op, nTouches});
                }
            }
        }

        // --- OPTION B: Press an OPERATOR key (+, -, *, /) ---
        // We can only press an operator if there is a valid current number on the screen
        if (u.curr != -1) {
            for (int i = 0; i < numOps; i++) {
                int nextOp = workingOps[i];
                
                // If there was a pending operation, calculate its intermediate value first
                if (u.op == 4 && u.curr == 0) continue; // Skip division by zero
                int nextPrev = calculate(u.prev, u.curr, u.op);
                
                // Keep the values within a valid positive range for basic calculator constraints
                if (nextPrev >= 0 && nextPrev < MAX_VAL) {
                    // Moving the result to 'prev', clearing 'curr' (-1), setting the new operation
                    q.push({nextPrev, -1, nextOp, u.touches + 1});
                }
            }
        }

        // --- OPTION C: Press the EQUAL (=) key ---
        // We can only hit '=' if we have a previous value, a current value, and an active operation
        if (u.prev != -1 && u.curr != -1 && u.op != -1) {
            if (u.op == 4 && u.curr == 0) continue; // Skip division by zero
            
            int finalResult = calculate(u.prev, u.curr, u.op);
            int nTouches = u.touches + 1; // +1 touch for pressing '='

            // If hitting '=' evaluates to our target, this is our minimum path!
            if (finalResult == target && nTouches <= maxTouches) {
                return nTouches;
            }
        }
    }

    // If the queue runs empty and we never hit the target within maxTouches
    return -1; 
}

int main() {
    int t;
    if (!(cin >> t)) return 0;
    
    int caseNum = 1;
    while (t--) {
        cin >> numDigits >> numOps >> maxTouches;
        
        for (int i = 0; i < numDigits; i++) {
            cin >> workingDigits[i];
        }
        for (int i = 0; i < numOps; i++) {
            cin >> workingOps[i];
        }
        cin >> target;

        int ans = solve();
        cout << "#" << caseNum++ << " " << ans << endl;
    }
    return 0;
}
