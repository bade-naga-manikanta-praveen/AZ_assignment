#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 3};
    
    cout << "=== DEMONSTRATING THE ISSUES ===\n\n";
    
    // Your original approach
    vector<pair<int,int>> ans;
    int n = arr.size();
    for(int i = 0; i < (1LL << n); i++) {
        int sm = 0, num = 0;
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) {
                num++;
                sm += arr[j];
            }
        }
        ans.push_back({num, sm});
    }
    sort(ans.begin(), ans.end());
    
    cout << "1. YOUR DATA STRUCTURE OUTPUT:\n";
    for(auto& p : ans) {
        cout << "   (count=" << p.first << ", sum=" << p.second << ")\n";
    }
    
    cout << "\n2. PROBLEM 1 - BINARY SEARCH CONFUSION:\n";
    cout << "When you search for make_pair(2, 4), what does lower_bound find?\n";
    
    auto it = lower_bound(ans.begin(), ans.end(), make_pair(2, 4));
    if(it != ans.end()) {
        cout << "   Found: (count=" << it->first << ", sum=" << it->second << ")\n";
    }
    cout << "   But this searches for EXACT (count=2, sum=4) combination!\n";
    cout << "   What if you want count=2 but sum closest to 4?\n\n";
    
    cout << "3. PROBLEM 2 - WHAT YOU ACTUALLY NEED:\n";
    cout << "In meet-in-the-middle, you need:\n";
    cout << "   - All sums with EXACTLY k elements\n";
    cout << "   - Then find the sum closest to target among those\n\n";
    
    cout << "4. WITH PAIRS, YOU NEED COMPLEX LOGIC:\n";
    cout << "To find sums with exactly 2 elements:\n";
    
    // Complex way to find range
    auto start = lower_bound(ans.begin(), ans.end(), make_pair(2, INT_MIN));
    auto end = lower_bound(ans.begin(), ans.end(), make_pair(3, INT_MIN));
    
    cout << "   Range for count=2: positions " << (start - ans.begin()) 
         << " to " << (end - ans.begin()) - 1 << "\n";
    cout << "   Elements in this range:\n";
    for(auto it2 = start; it2 != end; ++it2) {
        cout << "     sum=" << it2->second << "\n";
    }
    
    cout << "\n   Now you need another binary search within this range!\n";
    cout << "   This is error-prone and complex.\n\n";
    
    cout << "5. BETTER APPROACH - GROUPED BY COUNT:\n";
    vector<vector<int>> grouped(n + 1);
    
    for(int i = 0; i < (1LL << n); i++) {
        int sm = 0, num = 0;
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) {
                num++;
                sm += arr[j];
            }
        }
        grouped[num].push_back(sm);
    }
    
    for(int i = 0; i <= n; i++) {
        sort(grouped[i].begin(), grouped[i].end());
    }
    
    cout << "   Grouped structure:\n";
    for(int i = 0; i <= n; i++) {
        cout << "     count=" << i << ": [";
        for(int j = 0; j < grouped[i].size(); j++) {
            cout << grouped[i][j];
            if(j < grouped[i].size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    cout << "\n   To find sum closest to 4 with exactly 2 elements:\n";
    cout << "   Just: lower_bound(grouped[2].begin(), grouped[2].end(), 4)\n";
    cout << "   Much simpler and less error-prone!\n\n";
    
    cout << "6. SPECIFIC ERROR IN YOUR ORIGINAL CODE:\n";
    cout << "In your line:\n";
    cout << "   auto it=lower_bound(st2.begin(),st2.end(),make_pair(hf - num, (sm/2) - sm1));\n";
    cout << "\n";
    cout << "This searches for an EXACT pair (count, sum), but:\n";
    cout << "   - The exact sum (sm/2) - sm1 might not exist\n";
    cout << "   - You want the CLOSEST sum, not exact match\n";
    cout << "   - lower_bound on pairs compares BOTH fields\n";
    cout << "   - This makes the search logic much more complex\n";
    
    return 0;
}