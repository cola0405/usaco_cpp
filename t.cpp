#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    int A, B, N;
    cin >> A >> B >> N;

    /* Read the costs and routes. */
    vector<int> costs(N);
    vector<vector<int> > routes(N);
    for (int i = 0; i < N; i++) {
        int ln;
        cin >> costs[i] >> ln;
        routes[i].resize(ln);
        for (int j = 0; j < ln; j++) {
            cin >> routes[i][j];
        }
    }

    /* ca2u[u] gives the cheapest route cost from A to u. */
    vector<int> ca2u(10001, 100000);
    ca2u[A] = 0;

    /* D2[u] gives the cheapest route cost form u to B. */
    vector<int> cu2b(10001, 100000);
    cu2b[B] = 0;



    /* Update D1 and D2 based on each route. */
    for (int i = 0; i < N; i++) {
        int cost = costs[i];
        vector<int>& route = routes[i];

        /* Determine the position of A and B in the route, if present. */
        int pos_a = route.size();
        int pos_b = -1;
        for (int j = 0; j < route.size(); j++) {
            if (route[j] == A) {
                pos_a = j;
            } else if (route[j] == B) {
                pos_b = j;
            }
        }

        /* For each city u after A update D1[u].  Similarly update D2[u] for each
         * city u before B. */
        for (int j = 0; j < route.size(); j++) {
            if (pos_a <= j) {
                ca2u[route[j]] = min(ca2u[route[j]], cost);
            }
            if (j <= pos_b) {
                cu2b[route[j]] = min(cu2b[route[j]], cost);
            }
        }
    }

    /* Calculate the minimum cost for each possible intermediate node. */
    int result = 100000;
    for (int i = 1; i <= 10000; i++) {
        result = min(result, ca2u[i] + cu2b[i]);
    }

    /* Output the minimum cost pair (or single) ticket, if possible. */
    if (result == 100000) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}