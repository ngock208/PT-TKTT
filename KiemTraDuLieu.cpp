
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<int> sizes = {
        5, 6, 8, 10, 12, 14, 16, 18, 20,
        50, 100, 200, 300, 500, 700, 1000
    };

    int tongFile = 0;
    int soFileHopLe = 0;
    int soFileLoi = 0;

    for (int n : sizes) {
        for (int lan = 1; lan <= 5; lan++) {

            string filename = "testTSP/tsp_"
                + to_string(n) + "_"
                + to_string(lan) + ".txt";

            tongFile++;

            ifstream file(filename);

            if (!file.is_open()) {
                cout << "[LOI] Khong mo duoc: "
                    << filename << endl;
                soFileLoi++;
                continue;
            }

            int m;
            if (!(file >> m) || m != n || m <= 0) {
                cout << "[LOI] Sai so thanh pho: "
                    << filename << endl;
                soFileLoi++;
                continue;
            }

            vector<vector<int>> a(n, vector<int>(n));

            bool hopLe = true;

            // Doc ma tran
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (!(file >> a[i][j])) {
                        hopLe = false;
                        break;
                    }
                }
                if (!hopLe) break;
            }

            if (!hopLe) {
                cout << "[LOI] Thieu du lieu: "
                    << filename << endl;
                soFileLoi++;
                continue;
            }

            // Kiem tra ma tran
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    if (a[i][j] < 0) {
                        hopLe = false;
                    }

                    if (i == j && a[i][j] != 0) {
                        hopLe = false;
                    }

                    if (a[i][j] != a[j][i]) {
                        hopLe = false;
                    }
                }
            }

            if (hopLe) {
                cout << "[OK] " << filename << endl;
                soFileHopLe++;
            }
            else {
                cout << "[LOI] " << filename << endl;
                soFileLoi++;
            }

            file.close();
        }
    }

    cout << "\n===== KET QUA KIEM TRA =====" << endl;
    cout << "Tong so file: " << tongFile << endl;
    cout << "File hop le: " << soFileHopLe << endl;
    cout << "File loi: " << soFileLoi << endl;

    return 0;
}
