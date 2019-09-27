/*
Given random points in a 2-D plane, construct a convex polygon with minimum area of covering and 
which encompasses all the given points.
*/
#include<bits/stdc++.h>
int cou = 0;

struct Point{
    int x, y;
};
 
int orientation(Point p, Point q, Point r){
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0; 
    return (val > 0)? 1: 2; 
}

bool cmp(Point &a, Point &b){
    if(a.x==b.x&&a.y==b.y)
        cou++;
    
    if(a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

bool myFunc(Point &a, Point &b){
    return (a.x==b.x && a.y==b.y);
}    
 
void convexHull(Point *points, int n){
    cou = 0;
    if (n < 3){
        cout << "-1";
        return;    
    } 
    
    vector<Point> hull;
    
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
 
    int p = l, q;
    do{
        hull.push_back(points[p]);
        
        q = (p+1)%n;
        
        for (int i = 0; i < n; i++)
        {
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
        p = q;
 
    } while (p != l); 
    
    sort(hull.begin(), hull.end(), cmp);
    
    auto ip = unique(hull.begin(), hull.end(), myFunc); 
    
    hull.resize(std::distance(hull.begin(), ip)); 
    
    if(n < 4 && cou > 0 || hull.size() < 3){
        cout << "-1";
        return;
    }
    else{
        for (int i = 0; i < hull.size(); i++){
            if(i != hull.size() - 1)
                cout << hull[i].x << " " << hull[i].y << ", ";
            else
                cout << hull[i].x << " " << hull[i].y; 
        }        
    }
}
 
int main(){
    int t, n;
    cin >> t;
    while(t--){
        cin >> n;
        Point *points = new Point[n];

        for(int i=0; i<n; i++){
            cin >> points[i].x >> points[i].y;                
        }
        
        convexHull(points, n);
        cout << "\n";
    }
    return 0;
}