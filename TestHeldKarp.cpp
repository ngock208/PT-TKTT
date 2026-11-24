
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Hang so vo cung
const long long INF = 1e18;

// HAM DOC DU LIEU TSP TU FILE
bool docDuLieu(const string& tenFile,
    vector<vector<int>>& d) {

    ifstream file(tenFile);

    if (!file.is_open()) {
        cout << "Khong mo duoc file: " << tenFile << endl;
        return false;
    }

    int n;

    if (!(file >> n) || n < 2 || n > 20) {
        cout << "So thanh pho khong hop le!" << endl;
        return false;
    }

    d.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(file >> d[i][j])) {
                cout << "Ma tran khong day du!" << endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}

// THUAT TOAN QUY HOACH DONG HELD-KARP
long long HeldKarp(int n, const vector<vector<int>>& d) {

    int FULL = (1 << n) - 1;

    vector<vector<long long>> dp(
        1 << n, vector<long long>(n, INF)
    );

    dp[1][0] = 0;

    for (int mask = 1; mask <= FULL; mask++) {

        for (int u = 0; u < n; u++) {

            if (!(mask & (1 << u))) continue;
            if (dp[mask][u] == INF) continue;

            for (int v = 0; v < n; v++) {

                if (mask & (1 << v)) continue;

                int newMask = mask | (1 << v);

                long long cost = dp[mask][u] + d[u][v];

                if (cost < dp[newMask][v]) {
                    dp[newMask][v] = cost;
                }
            }
        }
    }

    long long ans = INF;

    for (int i = 1; i < n; i++) {
        ans = min(ans, dp[FULL][i] + d[i][0]);
    }

    return ans;
}

// HAM MAIN

int main() {

    vector<int> sizes = {
        5, 6, 8, 10, 12, 14, 16, 18, 20
    };

    vector<vector<int>> khoangCach;
    
    ofstream csv("testTSP/KetQua_HeldKarp.csv");

    if (!csv.is_open()) {
        cout << "Khong tao duoc file CSV!" << endl;
        return 1;
    }

    csv << "LoaiDuLieu,n,lan,chiPhi,thoiGian_ms,trungBinh_ms,doLechChuan_ms\n";

    cout << "========== THUC NGHIEM HELD-KARP ==========" << endl;

    for (int n : sizes) {

        double tongThoiGian = 0;
        int soLanThanhCong = 0;
        vector<double> thoiGianCacLan;

        cout << "\nSo thanh pho: " << n << endl;

        for (int lan = 1; lan <= 5; lan++) {

            string tenFile = "testTSP/tsp_"
                + to_string(n) + "_"
                + to_string(lan) + ".txt";

            if (!docDuLieu(tenFile, khoangCach)) {
                cout << "Khong doc duoc: " << tenFile << endl;
                continue;
            }

            auto batDau = chrono::high_resolution_clock::now();

            long long ketQua = HeldKarp(n, khoangCach);

            auto ketThuc = chrono::high_resolution_clock::now();

            chrono::duration<double, milli> thoiGian =
                ketThuc - batDau;

            tongThoiGian += thoiGian.count();
            thoiGianCacLan.push_back(thoiGian.count());

            soLanThanhCong++;
            //
            csv << "LanChay,"
                << n << ","
                << lan << ","
                << ketQua << ","
                << fixed << setprecision(6)
                << thoiGian.count()
                << ",,\n";
            //
            cout << "Lan " << lan
                << " | Chi phi: " << ketQua
                << " | Thoi gian: " << thoiGian.count()
                << " ms" << endl;
        }

        if (soLanThanhCong > 0) {

            double trungBinh = tongThoiGian / soLanThanhCong;

            double tongBinhPhuong = 0;

            for (double t : thoiGianCacLan) {
                tongBinhPhuong += (t - trungBinh) * (t - trungBinh);
            }

            double doLechChuan = 0;

            if (soLanThanhCong > 1) {
                doLechChuan = sqrt(tongBinhPhuong / (soLanThanhCong - 1));
            }

            cout << "Thoi gian trung binh: "
                << trungBinh << " ms" << endl;

            cout << "Do lech chuan: "
                << doLechChuan << " ms" << endl;

            csv << "ThongKe,"
                << n << ",,,,"
                << fixed << setprecision(6)
                << trungBinh << ","
                << doLechChuan << "\n";
        }
    }
    csv.close();
    return 0;
}
