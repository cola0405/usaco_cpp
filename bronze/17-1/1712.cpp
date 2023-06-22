#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ROCK = 0;
int SCISSOR = 2;
int PAPER = 1;

int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    int n;
    cin >> n;

    vector<vector<int>> records;
    for (int i = 0; i < n; i++) {
        vector<int> round(2);
        cin >> round[0] >> round[1];
        records.push_back(round);
    }

    int max_win = 0;
    for (int i=1; i<=3; i++) {
        for (int j=1; j<=3; j++) {
            if (i == j) continue;
            for (int k=1; k<=3; k++) {
                if (i==k || j==k) continue;
                vector<int> rule = {i, j, k};

                // go through record

                int p1_win = 0;
                for (int w = 0; w < n; w++) {
                    int p1 = records[w][0];
                    int p2 = records[w][1];

                    if ((p1 == rule[ROCK] && p2 == rule[SCISSOR])
                            || (p1 == rule[SCISSOR] && p2 == rule[PAPER])
                            || (p1 == rule[PAPER] && p2 == rule[ROCK])){
                        p1_win++;
                    }
                }
                max_win = max(p1_win, max_win);
            }
        }
    }
    cout<<max_win<<endl;

}