#include <bits/stdc++.h>

using namespace std;

void get_indices(int * arr, int n) {
        vector < pair < int, int > > new_arr;
        int i;
        for (i = 0; i < n; i++) {
                new_arr.push_back(make_pair(arr[i], i + 1));
        }
        sort(new_arr.begin(), new_arr.end());

        /*cout << "The vector after sort operation is:\n" ; 
        for ( i=0; i<n; i++) 
        { 
            cout << new_arr[i].first << " "
                 << new_arr[i].second << endl; 
        } 
        cout << endl;  */

        int l, r, p, q;
        int sum = 0;
        int sum1;
        l = 0;
        r = n - 1;
        int flag = 1;
        while (l < r && flag == 1) {
                sum1 = new_arr[l].first + new_arr[r].first;
                if (sum1 < sum)
                        l++;
                else if (sum1 > sum)
                        r--;
                else {
                        flag = 0;
                        p = new_arr[l].second;
                        q = new_arr[r].second;
                        cout << "Indices are \n";
                        if (p < q)
                                cout << "p is " << p << " " << q << endl << endl;
                        else
                                cout << "q is " << q << " " << p << endl << endl;
                }
        }
        if (l >= r) {
                cout << "Sum not found!\n";
                cout << -1 << endl << endl;
        }
}

int main() {
        int k, n, i, j;
        cin >> k;
        cin >> n;
        int * arr = (int * ) malloc(n * sizeof(int));
        for (i = 0; i < k; i++) {

                for (j = 0; j < n; j++) {
                        scanf("%d", & arr[j]);
                }
                get_indices(arr, n);
        }
        return 0;
}
