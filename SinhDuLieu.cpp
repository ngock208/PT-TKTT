
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <filesystem>
#include <cmath>
#include <string>

using namespace std;
namespace fs = filesystem;

int main() {
    // 1. Khoi tao bo sinh so ngau nhien
    int seed = 42;
    mt19937 boSinhSo(seed);

    uniform_int_distribution<int>phanPhoi(0, 10000);

    // 2. Danh sach kich thuoc du lieu
    vector<int> sizes = {
        5, 6, 8, 10, 12, 14, 16, 18, 20,
        50, 100, 200, 300, 500, 700, 1000
    };

    // 3. Tao thu muc chua cac file test
    fs::create_directories("testTSP");

    int tongFile = 0;

    // 4. Lap qua tung kich thuoc
    for (int n : sizes) {

        // Moi kich thuoc tao 5 bo du lieu
        for (int lan = 1; lan <= 5; lan++) {

            // Tao ten file
            string filename = "testTSP/tsp_"
                + to_string(n) + "_"
                + to_string(lan) + ".txt";

            ofstream file(filename);

            if (!file.is_open()) {
                cout << "Loi tao file: " << filename << endl;
                return 1;
            }

            // 5. Sinh toa do ngau nhien cho cac thanh pho
            vector<pair<int, int>> city(n);

            for (int i = 0; i < n; i++) {
                city[i].first = phanPhoi(boSinhSo);
                city[i].second = phanPhoi(boSinhSo);
            }

            // 6. Ghi so luong thanh pho
            file << n << "\n";

            // 7. Tinh ma tran khoang cach Manhattan

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    int d = abs(city[i].first - city[j].first)
                        + abs(city[i].second - city[j].second);

                    file << d;

                    if (j < n - 1) {
                        file << "\t";
                    }
                }

                file << "\n";
            }

            file.close();

            tongFile++;

            cout << "Da tao: " << filename << endl;
        }
    }

    cout << "\nHoan thanh sinh du lieu TSP!" << endl;
    cout << "Tong so file: " << tongFile << endl;
    cout << "Thu muc: " << fs::absolute("testTSP") << endl;

    return 0;
}
