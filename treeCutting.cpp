/*
SRI Delhi, IIT B, 2026 FTE

We have a road that is a line of integer positions (0,1,...,n). There may be up to one tree on the left and up to one tree on the right at each integer position (i in {1,...,n-1}). Each tree has an integer height (h in [1,1000]). The total number of trees is (T).

A robot starts at position (0). Its job is to cut every tree and deliver them all at position (n). Rules:

* Cutting a tree costs (1) (so cutting all trees costs (T) in total; this part is fixed).
* Moving the robot a distance (d) along the line costs (d).
* The robot can carry any number of trees, but the stack of carried trees must always be in non-increasing order from bottom to top. Equivalently: every time the robot picks up a new tree, its height must be less equal to the height of the tree currently on top of the stack (if any). This permits equal heights.
* The robot must finish at position (n) after having cut and delivered all trees.

Goal: find the minimum total cost = (movement cost) + (cutting cost (=T)).

Input Format:
n -> length of road (5 <= n <= 1000)
left[i] -> n length array of left side tree heights
right[i] -> n length array of right side tree heights

E.g.
Input:
1
5
0 3 2 1 0
0 3 2 1 0

Output:
#1 11

*/

#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int n;
int dp[1001][1001];

int solve(vector<vector<int>> &trees, int treeVal, int pos) {
    if (treeVal == 0) {
        return n - pos;
    }

    if (dp[treeVal][pos] != -1) {
        return dp[treeVal][pos];
    }

    if (trees[treeVal].empty()) {
        return dp[treeVal][pos] = solve(trees, treeVal - 1, pos);
    }

    vector<int> &line = trees[treeVal];
    int t = line.size();
    int cost = INT_MAX;

    int L = line.front();
    int R = line.back();

    if (pos < L) {
        int dist = R - pos;
        int nPos = R;

        int curr = t + dist + solve(trees, treeVal - 1, nPos);
        cost = min(cost, curr);
    } else if (pos > R) {
        int dist = pos - L;
        int nPos = L;

        int curr = t + dist + solve(trees, treeVal - 1, nPos);
        cost = min(cost, curr);
    } else {
        int dist1 = (pos - L) + (R - L);
        int nPos1 = R;
        int curr1 = t + dist1 + solve(trees, treeVal - 1, nPos1);

        int dist2 = (R - pos) + (R - L);
        int nPos2 = L;
        int curr2 = t + dist2 + solve(trees, treeVal - 1, nPos2);

        cost = min({cost, curr1, curr2});
    }

    return dp[treeVal][pos] = cost;
}

int main(int argc, char const *argv[]) {
    int testCases;
    cin >> testCases;

    for (int t = 1; t <= testCases; t++) {
        cin >> n;

        vector<vector<int>> trees(1001);
        memset(dp, -1, sizeof(dp));

        int a;
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a > 0)
                trees[a].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a > 0)
                trees[a].push_back(i);
        }

        for (int i = 0; i < 1001; i++) {
            if (trees[i].empty()) {
                continue;
            }
            sort(trees[i].begin(), trees[i].end());
        }

        int minCost = solve(trees, 1000, 0);
        cout << "#" << t << " " << minCost << endl;
    }

    return 0;
}