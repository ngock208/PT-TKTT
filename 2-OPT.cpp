//Dua tren wiki, chua co file kiem thu

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ll tinhChiPhi(int n, vector<int>& path, vector<vector<int>>& d) {
    ll tong = 0;
    for (int i = 0; i < n; i++) {
        int u = path[i];
        //giup thanh pho cuoi co the quay lai thanh pho ban dau
        int v = path[(i + 1) % n];
        tong += d[u][v];
    }
    return tong;
}

ll twoOpt(int n, vector<vector<int>>& d) {

    vector<int> path;

    for (int i = 0; i < n; i++) {
        path.push_back(i);
    }

    ll bestCost = tinhChiPhi(n, path, d);
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 0; i < n - 1; i++) {
            for (int k = i + 2; k < n; k++) {

                // Bo qua hai canh ke nhau de khong bị lap duong di trong ma tran doi xung
                if (i == 0 && k == n - 1)
                    continue;

                // Dao nguoc doan duong
                reverse(path.begin() + i + 1, path.begin() + k + 1);

                ll cost = tinhChiPhi(n, path, d);

                if (cost < bestCost) {
                    bestCost = cost;
                    improved = true;
                }
                else {
                    // Khoi phuc duong di cu
                    reverse(path.begin() + i + 1, path.begin() + k + 1);
                }
            }
        }
    }
    return bestCost;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> d(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    ll kq = twoOpt(n, d);
    cout << "Duong di ngan nhat: " << kq << "\n";

    return 0;
}

// MA GIA
// TINH_CHI_PHI(n, path, d)
//     tong := 0
//     for i := 0 to n−1 do
//         u := path[i]
//         v := path[(i+1) mod n]
//         tong := tong + d[u][v]
//     end for
//     return (tong)
// end function

// TWO_OPT(n, d)
//     path := [0, 1, ..., n−1]
//     bestCost := TINH_CHI_PHI(n, path, d)
//     improved := true
//     while improved do
//         improved := false
//         for i := 0 to n−2 do
//             for k := i+2 to n−1 do
//                 if i = 0 and k = n−1 then continue
//                 reverse(path[i+1 ... k])
//                 cost := TINH_CHI_PHI(n, path, d)
//                 if cost < bestCost then
//                     bestCost := cost
//                     improved := true
//                 else
//                     reverse(path[i+1 ... k])
//         end for
//     end while
//     return (bestCost)
// end function
