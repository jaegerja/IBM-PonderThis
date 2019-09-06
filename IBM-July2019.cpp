/***
This month's challenge is by Hugo Pfoertner. (Thanks!)

A non-intersecting knight's cycle is a closed tour made of legal moves of a chess knight on a rectangular board of size mXn, such that the straight lines connecting consecutively visited fields make a simple polygon of an enclosed area A.
Find two non-intersecting knight's cycles of length 14 on boards of size <=40 such that the difference between their areas is at least 7.

As an example, there are two non-intersecting knight's cycles of length 4 on boards of size <=16 such that the difference between their areas is 1:
The first has an area of 3 on 4x4 board: a1 c2 d4 b3 a1
and the second has an area of 4 on 3x5 board: c1 e2 c3 a2 c1.

Submit your solution as two lines of 15 visited fields (start=end) using algebraic chess notation as we used above.
***/

#include <bits/stdc++.h>
using namespace std;

typedef vector<int>          vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<vector<int>>> vvvi;

int cross(const vi &v1, const vi &v2){ return v1[1]*v2[0] - v1[0]*v2[1]; }
vi diff(const vi &v1, const vi &v2){ return {v1[0] - v2[0], v1[1] - v2[1]}; }
int sign(int x){ return (x>0) - (x<0); }

const int LENGTH = 15;
const int AREA = 40;

//false for segments that only meet at an endpoint
bool segments_intersect(const vvi &s1, const vvi &s2){
    vi d1, d2;
    int b1, b2, s11, s12, s21, s22;
    bool c1, c2;
    d1= diff(s1[1], s1[0]);
    d2= diff(s2[1], s2[0]);

    b1= cross(d1, s1[0]);
    b2= cross(d2, s2[0]);

    s11= sign(cross(d2, s1[0]) - b2);
    s12= sign(cross(d2, s1[1]) - b2);
    s21= sign(cross(d1, s2[0]) - b1);
    s22= sign(cross(d1, s2[1]) - b1);

    c1 = s11!=s12;
    c2 = s21!=s22;
    return c1&&c2&&s11&&s12&&s21&&s22;
}


void print_path(const vvi &p) {
    int minx= 1e9, miny= 1e9;

    for(int j=0; j<p.size(); ++j){
        minx= min(minx, p[j][0]);
        miny= min(miny, p[j][1]);
    }
    for(int j=0; j<p.size(); ++j){
        cout<<  (char)('a' + p[j][0] - minx) << p[j][1] - miny << " ";
    }
    cout<<endl<<endl;
}


void recur(vvi &path, const vvi &bounds, int area){
    int n= path.size();
    auto last = path.back();

    //if path is likely redundant
    if(last[0]<0 || last[1]<-1) return;

    //bounding rectangle is too large
    if((bounds[0][1] - bounds[0][0] + 1)*(bounds[1][1] - bounds[1][0] + 1) > AREA ) return;

    //origin is too far to reach in alloted moves
    if( 3*(LENGTH - path.size()) < abs(last[0]) + abs(last[1]) ) return;

    //path is not simple
    if(n>2){
        bool simple = 1;
        vvi new_seg = {path[n-2], last};
        for(int i=1; i+1<path.size(); ++i){
            vvi seg = {path[i-1], path[i]};
            if(segments_intersect(new_seg, seg) ){
                simple = 0;
                break;
            }
        }
        if(!simple) return;
    }

    //if returned to origin
    if(path.size()>1 && last[0]==0 && last[1]==0){
        if(path.size() < LENGTH) return;
        static int max_area = -1e9;
        static int min_area = +1e9;

        int area2 = abs(area)/2;

        if( area2 > max_area || area2 < min_area ){
            min_area = min( area2, min_area );
            max_area = max( area2, max_area );

            cout<<"Area: "<<area2<<endl;
            print_path(path);
        }
        return;
    }

    //path is too long not to return to origin
    if(path.size()>=LENGTH) return;
    //path self overlaps at a point
    if(count(path.begin(), path.end(), last) > 1) return;

    //for each knight move
    for(int sgnx= -1; sgnx<=+1; sgnx+=2)
    for(int sgny= -1; sgny<=+1; sgny+=2)
    for(int vert=0; vert<=1; ++vert){
        vi next= last;
        next[0]-= sgnx*(2-vert);
        next[1]-= sgny*(1+vert);

        vvi b2 = bounds;
        b2[0][0]= min(next[0], b2[0][0]);
        b2[0][1]= max(next[0], b2[0][1]);
        b2[1][0]= min(next[1], b2[1][0]);
        b2[1][1]= max(next[1], b2[1][1]);

        path.push_back(next);
        recur(path, b2, area + cross(next, last));
        path.pop_back();
    }
}


int main() {
    int area = 0;
    vvi bounds = {{0,0},{0,0}}, path = {{0,0}};
    recur(path, bounds, area);
}
