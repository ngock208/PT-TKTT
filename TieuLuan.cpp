
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Ham doc du lieu TSP tu file
bool docDuLieu(const string& tenFile,
    vector<vector<int>>& khoangCach) {

    ifstream file(tenFile);

    if (!file.is_open()) {
        cout << "Khong mo duoc file: " << tenFile << endl;
        return false;
    }

    int n;

    if (!(file >> n) || n <= 0) {
        cout << "So thanh pho khong hop le!" << endl;
        return false;
    }

    khoangCach.assign(n, vector<int>(n));

    // Doc ma tran khoang cach
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(file >> khoangCach[i][j])) {
                cout << "Du lieu ma tran khong day du!" << endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}

int main() {
    
    cout << "CHUONG TRINH BAT DAU!" << endl;

    vector<int> sizes = {
        5, 6, 8, 10, 12, 14, 16, 18, 20,
        50, 100, 200, 300, 500, 700, 1000
    };

    vector<vector<int>> khoangCach;

    int tongFile = 0;
    int docThanhCong = 0;
    int docThatBai = 0;

    for (int n : sizes) {

        for (int lan = 1; lan <= 5; lan++) {
            
            cout << "Dang doc file: " << n << "_" << lan << endl;

            string tenFile = "testTSP/tsp_"
                + to_string(n) + "_"
                + to_string(lan) + ".txt";

            tongFile++;

            if (docDuLieu(tenFile, khoangCach)) {
                docThanhCong++;
            }
            else {
                docThatBai++;
                cout << "Loi tai file: " << tenFile << endl;
            }
        }
    }

    cout << "\n========== KET QUA KIEM TRA ==========" << endl;
    cout << "Tong so file: " << tongFile << endl;
    cout << "Doc thanh cong: " << docThanhCong << endl;
    cout << "Doc that bai: " << docThatBai << endl;

    return 0;
}
