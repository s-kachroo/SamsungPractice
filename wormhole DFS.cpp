/*
https://www.careercup.com/question?id=5677905146281984
https://github.com/arjunsk/samsung_interview/blob/master/wormhole.cpp
https://gist.github.com/gunpreet34/b58c38b3556271059182244676ba06a1
https://hack.codingblocks.com/contests/c/782/870
https://discuss.codingblocks.com/t/test-case-of-minimum-time-traversal-problem/12944

http://ideone.com/Sbx7MA
*/

/*
There is one spaceship. X and Y co-odinate of source of spaceship and destination spaceship is given.
There are N number of warmholes; each warmhole has 5 values. First 2 values are starting co-ordinate
of warmhole and after that value no. 3 and 4 represents ending co-ordinate of warmhole and last 5th 
value is represents cost to pass through this warmhole. Now these warmholes are bi-directional. Now 
the to go from (x1,y1) to (x2,y2) is abs(x1-x2)+abs(y1-y2). The main problem here is to find minimum 
distance to reach spaceship from source to destination co-ordinate using any number of warm-hole. 
It is ok if you wont use any warmhole.
*/
#include <iostream>
#include <climits>
using namespace std;

int ANS = INT_MAX, n, temp = 0;
int w[35][5];
int mask[35];

int abs(int i){
    return (i>=0) ? i : -1*i;
}

int min(int x, int y){
    return (x>=y) ? y : x;
}

int dist(int sX, int sY, int tX, int tY){
    return abs(sX-tX) + abs(sY-tY);
}

void wormhole(int sX, int sY, int tX, int tY, int value){
    ANS = min(ANS, dist(sX, sY, tX, tY) + value);

    for(int i=0; i<n; i++){
        if(mask[i] == 0){
            mask[i] = 1;

            /* Choose lower end of wormhole */
            temp = dist(sX, sY, w[i][0], w[i][1]) + w[i][4] + value;
            wormhole(w[i][2], w[i][3], tX, tY, temp);

            /* Choose upper end of wormhole */
            temp = dist(sX, sY, w[i][2], w[i][3]) + w[i][4] + value;
            wormhole(w[i][0], w[i][1], tX, tY, temp);

            mask[i] = 0;
        }
    }
}

int main() {
    int t, sX, sY, tX, tY;
    cin >> t;
    while(t--){
    	ANS = INT_MAX;
        cin >> n;
        cin >> sX >> sY >> tX >> tY;
        for(int i=0; i<n; i++){
            mask[i] = 0;
            for(int j=0; j<5; j++){
                cin >> w[i][j];
            }
        }

        wormhole(sX, sY, tX, tY, 0);
        cout << ANS << endl;
    }
    return 0;
}

// #include<iostream>
// using namespace std;

// int n, a[2001][6];
 
// int min(int x , int y){
//     return(x>=y) ? y : x ;
// }

// int abs(int x){
// 	return (x > 0) ? x : -x ;
// }

// int dist(int x1 , int y1 , int x2 , int y2){
// 	return abs(x2-x1) + abs(y2 - y1);
// }

// void wormhole ( int x1 , int y1 , bool *visited , int &ans , int val ) {
// 	if ( x1 == a[n+1][0] && y1 == a[n+1][1] ){
// 		ans = min ( ans , val);
// 	    return ;
// 	}
	    
// 	for ( int i = 1 ; i <= n + 1 ;i++) {
// 		if (!visited[i]) {
// 	    	visited[i] = true ;
	    	 	 
// 	    	//entry
// 	    	wormhole ( a[i][2] , a[i][3] , visited , ans , val + dist ( x1 , y1 , a[i][0] , a[i][1] ) + a[i][4]);
	    	
// 	    	//exit
// 	    	wormhole ( a[i][0] , a[i][1] , visited , ans , val + dist ( x1 , y1 , a[i][2] , a[i][3] ) + a[i][4]);
	    	 	 
// 	    	visited[i] = false;
// 		}
// 	}	
// }

// int main(){
//     int t;	cin >> t ;
//     for (int i = 1; i <= t ; i++){
// 		cin >> n;
// 	    int sx, sy, dx,dy;
// 		cin>>sx>>sy>>dx>>dy; 
		 
// 		a[0][0] = sx ; a[0][1] = sy ; a[0][2] = sx ; a[0][3] = sy ; a[0][4] = 0 ;
		 
//         for ( int i = 1 ; i <= n ;i++ ){
// 			cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
// 		}	
		 
//         a[n+1][0] = dx ; a[n+1][1] = dy ; a[n+1][2] = dx ; a[n+1][3] = dy ; a[n+1][4] = 0 ;
         
//         int ans ;  
//         bool visited[n+2] = { false };

//         ans = dist (a[0][0] , a[0][1] , a[n+1][0] , a[n+1][1]);        
//         visited[0] = true ;
           
//         wormhole(sx ,sy , visited , ans , 0);
          
//         cout << "#" << i << " : " << ans << endl;
//   	}
//   return 0;
// }