#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
     
int N;
map<int,int> slopechg;   // slopechg[t] is how much the slope of f(y) changes when y=t
     
int main(void)
{
   ifstream fin ("teleport.in");
   ofstream fout ("teleport.out");

   long long current_f = 0, slope_f = 0, current_y = -2000000000;

   fin >> N;
   for (int i=0; i<N; i++) {
      int a, b;
      fin >> a >> b;
      current_f += abs(a-b);
      
      // Now add any slope change breakpoints...      
      if (abs(a) > abs(a-b)) continue;
      slopechg[b]+=2;   // sorted by key
      if (a<b && a<0)   { slopechg[0]--; slopechg[2*b]--; }
      if (a<b && a>=0)  { slopechg[2*b-2*a]--; slopechg[2*a]--; }
      if (a>=b && a<0)  { slopechg[2*b-2*a]--; slopechg[2*a]--; }
      if (a>=b && a>=0) { slopechg[0]--; slopechg[2*b]--; }
   }      

   // Now scan y forward and apply slope changes to trace out f(y), keeping track of min
   long long min_f = current_f;
   for (auto p : slopechg) {
      int new_y = p.first, delta_slope = p.second;
      current_f += slope_f * (new_y - current_y);
      current_y = new_y;
      slope_f += delta_slope;
      min_f = min(min_f, current_f);
   }

   fout << min_f << "\n";
   return 0;
}