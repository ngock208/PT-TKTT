//chưa add file kiểm thử
//Không tối ưu. Nhược điểm: vẫn cho ra kết quả sai. Ưu điểm: dễ cài đặt
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
using ll = long long;

ll nearestNeighbor(int n, const vector<vector<ll>>& d) {
    vector<bool> visited(n, false);

    int current = 0;
    visited[0] = true;

    ll tong = 0;

    for (int i = 1; i < n; i++) {
        ll minCost = LLONG_MAX;
        int next = -1;

        for (int j = 1; j < n; j++) {
            if (!visited[j] && d[current][j] < minCost) {
                minCost = d[current][j];
                next = j;
            }
        }

        tong += minCost;
        current = next;
        visited[current] = true;
    }

    // Quay ve thanh pho 0
    tong += d[current][0];

    return tong;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<ll>> d(n, vector<ll>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    ll ketQua = nearestNeighbor(n, d);

    cout << "Duong di ngan: " << ketQua << "\n";

    return 0;
}


//MÃ GIẢ
//THUẬT TOÁN NEAREST_NEIGHBOR(n, d)
//    Khởi tạo mảng visited[n] = false
//    current = 0
//    visited[0] = true
//    tong = 0
//    FOR i = 1 TO n - 1 DO
//        minCost = VÔ CÙNG
//        next = -1
//        FOR j = 1 TO n - 1 DO
//            IF visited[j] = false AND d[current][j] < minCost THEN
//                minCost = d[current][j]
//                next = j
//            END IF
//        END FOR
//        tong = tong + minCost
//        current = next
//        visited[current] = true
//    END FOR
//    Quay về thành phố xuất phát
//    tong = tong + d[current][0]
//    RETURN tong


//n    Số lượng thành phố
//d[i][j]    Khoảng cách từ thành phố i đến j
//visited[j]    Kiểm tra thành phố j đã được ghé thăm chưa
//current    Thành phố hiện tại
//next    Thành phố gần nhất tiếp theo
//minCost    Khoảng cách nhỏ nhất tìm được
//tong    Tổng chi phí hành trình


//4
//0 10 15 20
//10 0 35 25
//15 35 0 30
//20 25 30 0
