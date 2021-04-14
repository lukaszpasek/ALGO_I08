#include<iostream>
#include<vector>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

struct point
{
  double x,y;
};
struct circle
{
    double x,y,r;
};

double count_x(point a,point b,double p)
{
   return ((b.x*b.x) - (a.x*a.x) + (b.y*b.y) - (a.y*a.y) - 2*p*(b.y-a.y))/(2*(b.x-a.x));
}
double count_y(point a, point b,point c)
{
    double numerator = -a.x*c.x*c.x - a.x*c.y*c.y + a.x*b.x*b.x+a.x*b.y*b.y+b.x*c.x*c.x+b.x*c.y*c.y-b.x*b.x*c.x - b.y*b.y*c.x+a.x*a.x*c.x - a.x*a.x*b.x+a.y*a.y*c.x-a.y*a.y*b.x;
    double denominator = a.y*c.x -a.y*b.x - b.y*c.x - c.y*a.x + c.y*b.x+b.y*a.x;
    return (numerator/(2*denominator));
}

template < typename P1 , typename P2 >
double dist(P1 a, P2 b) {return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); }
bool belong(point a,vector<point> &R)
{
    for(int i=0 ; i<R.size() ; i++)
    {
        if(R[i].x==a.x && R[i].y==a.y) return true;
    }
    return false;
}
circle solve(int n,vector<point> &T,vector<point> R)
{
     circle result;
     if(R.empty())
     {
     result.x=(T[0].x+T[1].x)/2;
     result.y=(T[0].y+T[1].y)/2;
     result.r=dist(result,T[0]);
     }
     else if(R.size()==1)
     {
     result.x=(T[0].x+R[0].x)/2;
     result.y=(T[0].y+R[0].y)/2;
     result.r=dist(result,R[0]);
     }
       else if(R.size()==2)
     {
     result.x=(R[1].x+R[0].x)/2;
     result.y=(R[1].y+R[0].y)/2;
     result.r=dist(result,R[0]);
     }
        else if(R.size()==3)
     {
     result.y=count_y(R[0],R[1],R[2]);
     result.x=count_x(R[0],R[1],result.y);
     result.r=dist(result,R[0]);
     return result;
     }

    for(int i=0 ; i<n ; i++)
    {
       if(dist(T[i],result)>result.r && !belong(T[i],R))
       {
           R.push_back(T[i]);
           result=solve(i+1,T,R);
           R.pop_back();
       }
    }
    return result;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cout << fixed << setprecision(9);
    int z;
    cin>>z;
    while(z--)
    {
        int n;
        cin>>n;
        vector<point> T(n),R;
        for(int i=0 ; i<n ; i++) cin>>T[i].x>>T[i].y;
        shuffle(T.begin(),T.end(),default_random_engine{});
        circle result=solve(n,T,R);
        cout<<result.r<<endl;
    }


    return 0;
}