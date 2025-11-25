/*
Given n (1 to 100000)
And a string of size 2n

Where string is made of characters R and B showing the beads of a nacklace which are of two types red and blue respective.
The nacklace has a knot in the middle, between nth and n+1 th bead
You can't move a bead across that knot
You have to find the min number of beads to be removed to make count of blue and red beads same in the necklace
You can remove beads from both the end of the necklace

Ex:
2 RRRR, ans: 4
3 RRBRBR, ans: 2
3 RBBBBB, ans: 6
*/

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int solve(string s, int n)
{
    unordered_map<int, int> mpp;
    mpp[0] = -1;
    int balance = 0;
    int maxLen = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'R')
        {
            balance--;
        }
        else
        {
            balance++;
        }

        if (mpp.find(balance) != mpp.end())
        {
            if (i >= n && mpp[balance] < n)
            {
                int len = i - mpp[balance];
                maxLen = max(maxLen, len);
            }
        }
        else
        {
            mpp[balance] = i;
        }
    }
    return s.length() - maxLen;
}

int main(int argc, char const *argv[])
{
    int testCases;
    cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        int n;
        string s;
        cin >> n;
        cin >> s;

        int res = solve(s, n);
        cout << "#" << i << " " << res << endl;
    }
    return 0;
}
