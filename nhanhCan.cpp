
#include <iostream>
#include <vector> 
using namespace std;

const long long INF = 1e15;

int n;
vector<vector<int>> a;
vector<bool> visited;
vector<int> path, bestPath;

long long bestCost = INF;

// Ham tinh can duoi
long long tinhCan(int current, long long cost) {
    long long bound = cost;

    // Tim canh nho nhat tu thanh pho hien tai
    // den mot thanh pho chua tham
    long long minCurrent = INF;

    for (int j = 0; j < n; j++) {
        if (!visited[j]) {
            minCurrent = min(minCurrent, (long long)a[current][j]);
        }
    }

    if (minCurrent == INF)
        return INF;

    bound += minCurrent;

    // Tim canh nho nhat di ra tu moi thanh pho chua tham
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            long long minOut = INF;

            for (int j = 0; j < n; j++) {
                if (i != j) {
                    minOut = min(minOut, (long long)a[i][j]);
                }
            }

            if (minOut == INF)
                return INF;

            bound += minOut;
        }
    }

    return bound;
}

// Ham nhanh can
void nhanhCan(int current, int count, long long cost) {

    // Dieu kien dung
    if (count == n) {
        long long total = cost + a[current][0];

        if (total < bestCost) {
            bestCost = total;
            bestPath = path;
            bestPath.push_back(0);
        }

        return;
    }

    // Tinh can duoi
    long long bound = tinhCan(current, cost);

    // Dieu kien cat nhanh
    if (bound >= bestCost)
        return;

    // Thu cac thanh pho chua tham
    for (int i = 0; i < n; i++) {

        if (!visited[i]) {

            // Danh dau thanh pho da tham
            visited[i] = true;

            // Them thanh pho vao duong di
            path.push_back(i);

            // Goi de quy
            nhanhCan(i, count + 1, cost + a[current][i]);

            // Quay lui
            path.pop_back();
            visited[i] = false;
        }
    }
}

// Ham nhap du lieu
void nhap() {
    cout << "Nhap so thanh pho: ";
    cin >> n;

    a.resize(n, vector<int>(n));

    cout << "Nhap ma tran chi phi:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

// Ham khoi tao
void khoiTao() {
    visited.assign(n, false);

    path.clear();
    bestPath.clear();

    bestCost = INF;

    visited[0] = true;
    path.push_back(0);
}

// Ham xuat ket qua
void xuat() {
    if (bestCost == INF) {
        cout << "\nKhong tim thay hanh trinh hop le!";
        return;
    }

    cout << "\nChi phi nho nhat: " << bestCost;

    cout << "\nDuong di toi uu: ";

    for (int i = 0; i < bestPath.size(); i++) {
        cout << bestPath[i];

        if (i < bestPath.size() - 1)
            cout << " -> ";
    }

    cout << endl;
}

// Ham main
int main() {
    nhap();

    if (n <= 0) {
        cout << "So thanh pho khong hop le!";
        return 0;
    }

    if (n == 1) {
        cout << "Chi phi nho nhat: 0";
        cout << "\nDuong di toi uu: 0 -> 0";
        return 0;
    }

    khoiTao();

    nhanhCan(0, 1, 0);

    xuat();

    return 0;
}
