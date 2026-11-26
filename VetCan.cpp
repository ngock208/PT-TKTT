//Chua them file kiem thu
//Do phuc tap: tất cả trường hợp đều là O(n!)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ll vetCan(int n, vector<vector<int>>&d){
    vector<int> path;
    
    for(int i=1; i<n; i++){
        path.push_back(i);
    }
    
    ll MIN = LLONG_MAX;
    
    do{
        ll tong = 0;
        int current = 0;
        
        for(int i=0; i<(int)path.size(); i++){
            tong += d[current][path[i]];
            current = path[i];
        }
        
        tong += d[current][0];
        
        if(tong < MIN) MIN = tong;
        
    }while(next_permutation(path.begin(), path.end()));
    return MIN;
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
    
    ll kq = vetCan(n, d);
    
    cout << "Duong di ngan nhat: " << kq << endl;
    
    return 0;
}

// MA GIA
// VET_CAN(n, d)
//     path := [1, 2, ..., n−1]
//     MIN := LLONG_MAX
//     do {
//         tong := 0
//         current := 0
//         for i := 0 to n−2 do
//             tong := tong + d[current][path[i]]
//             current := path[i]
//         end for
//         tong := tong + d[current][0]
//         if tong < MIN then
//             MIN := tong
//     while(next_permutation(path.begin(), path.end())
//     return (MIN)
// end function
