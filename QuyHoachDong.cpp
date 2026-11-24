//Viết theo wiki https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm
//Chưa thêm file kiểm thử
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int INF = 1e9;

ll heldKard(int n, vector<vector<int>>& d){
    int FULL = (1 << (n-1))-1;
    vector<vector<int>> dp((1 << (n-1)), vector<int> (n, INF));
    
    vector<int> path;
    
    for(int i=1; i<n; i++){
        int mask = 1 << (i-1);
        dp[mask][i] = d[0][i];
    }
    
    for(int s=2; s<n; s++){
        for(int mask = 0; mask <= FULL; mask++){
            int dem = 0;
            
            for(int i=1; i<n; i++){
                if(mask & 1<<(i-1))
                    dem++;
            }
            
            if(dem!=s) continue;
            
            for(int k=1; k<n; k++){
                if(!(mask & 1 << (k-1)))
                    continue;
                int prevMask = mask ^ 1 << (k-1);
                for(int m=1; m<n; m++){
                    if(!(prevMask & 1 << (m-1)))
                        continue;
                    int cost = dp[prevMask][m] + d[m][k];
                    if(cost < dp[mask][k])
                        dp[mask][k] = cost;
                }
            }
            
        }
    }
    long long ans = INF;

    for (int k = 1; k < n; k++) {
        long long cost = dp[FULL][k] + d[k][0];
        ans = min(ans, cost);
    }
    return ans;
}

int main(){
    int n;
    cin >> n;
    
    vector<vector<int>> d(n, vector<int> (n));
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> d[i][j];
        }
    }
    
    ll kq = heldKard(n, d);
    
    cout << "Duong di ngan nhat: " << kq << endl;
    return 0;
}

// dp[mask][k] là chi phí nhỏ nhất xuất phát từ thành phố 0 đi qua tất cả thành phố mask và kết thúc tp k
// mask là chọn những thành phố cần đi
// k là thành phố cuối cùng
// prevMask là thành phố trước khi đến k
// m thử các thành phố có thể đứng trước k
// cost tính chi phí của đường đi đó
// if (cost < dp[mask][k]) giữ lại đường đi rẻ nhất.

//MÃ GIẢ
//hàm thuật toán TSP (G, n) dành
//    cho k := 2 đến n thực hiện
//        g({k}, k) := d(1, k)
//    kết thúc cho
//
//    for s := 2 to n−1 do
//        for all S ⊆ {2, ..., n}, |S| = s do
//            for all k ∈ S do
//                g(S, k) := min m≠k,m∈S [g(S\{k}, m) + d(m, k)]
//             end for
//        end for
//    end for
//
//    opt := min k≠1 [g({2, 3, ..., n}, k) + d(k, 1)]
//     return (opt)
// end function
