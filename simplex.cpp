#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    //enter matrix size
    int n = 4, m = 7;
    //enter matrix elements for simplex maximization method
    double arr[n][m] = {
    {3, 1, 8, 1, 0, 0, 4},
    {2, 0, 1, 0, 1, 0, 1},
    {1, 1, 2, 0, 0, 1, 1},
    {-23, -10, -40, 0, 0, 0, 0}
    };

    cout << "initial: " << endl;
    for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
    }

    bool neg = true;

    while(neg) {
        //find pivot_col
        double most_neg = 0;
        int pivot_row = 0, pivot_col = 0;
        for(int j = 0; j < m; j++) {
            if(arr[n-1][j] < most_neg) {
                most_neg = arr[n-1][j];
                pivot_col = j;
            }
        }

        //find pivot_row
        double minimal = 1000000;
        for(int i = 0; i < n; i++) {
            if(arr[i][pivot_col] > 0 && arr[i][m-1]/arr[i][pivot_col] <= minimal) {
                minimal = arr[i][m-1]/arr[i][pivot_col];
                pivot_row = i;
            }
        }

        cout << "pivot_row: " << pivot_row+1 << " pivot col: " << pivot_col+1 << endl << endl;

        double pivot_el = arr[pivot_row][pivot_col];

        // modify non-pivot rows
        for(int i = 0; i < n; i++) {
            if (i != pivot_row) {
                double k = arr[i][pivot_col]/pivot_el;
                for(int j = 0; j < m; j++) {
                    arr[i][j] -= k*arr[pivot_row][j];
                }
            }
        }

        //modify pivot row
        double k = 1.0/pivot_el;
        for(int j = 0; j < m; j++) {
            arr[pivot_row][j] *= k;
        }

        // print
        int maxwidth = 0, sz;
        string str;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                str = to_string(arr[i][j]);
                sz = str.size();
                maxwidth = max(maxwidth, sz);
            }
        }

        maxwidth++;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout.precision(5);
                cout << fixed << arr[i][j];
                str = to_string(arr[i][j]);
                sz = (maxwidth - str.size());
                while (sz--) cout << " ";
            }
            cout << endl;
        }

        //determine whether to stop simplex iteration or not
        int cnt = 0;
        for(int j = 0; j < m; j++) {
            if(arr[n-1][j] >= 0) cnt++;
        }
        if(cnt == m) neg = false;
    }

    return 0;
}
