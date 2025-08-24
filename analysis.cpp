#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Original approach with vector<pair<int,int>>
vector<pair<int,int>> genOriginal(vector<int>& arr) {
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
    return ans;
}

// Improved approach with vector<vector<int>>
vector<vector<int>> genImproved(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> sums(n + 1);
    
    for(int i = 0; i < (1 << n); i++) {
        int sm = 0, num = 0;
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) {
                num++;
                sm += arr[j];
            }
        }
        sums[num].push_back(sm);
    }
    
    // Sort each group by sum
    for(int i = 0; i <= n; i++) {
        sort(sums[i].begin(), sums[i].end());
    }
    
    return sums;
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    
    cout << "=== ORIGINAL APPROACH ISSUES ===\n\n";
    
    auto original = genOriginal(arr);
    auto improved = genImproved(arr);
    
    cout << "1. MIXED SORTING PROBLEM:\n";
    cout << "Original data (sorted by count first, then sum):\n";
    for(auto& p : original) {
        cout << "  count=" << p.first << ", sum=" << p.second << "\n";
    }
    
    cout << "\nProblem: When you sort pairs, it sorts by count FIRST, then by sum.\n";
    cout << "This mixes different counts together and makes binary search confusing.\n\n";
    
    cout << "2. BINARY SEARCH COMPLEXITY:\n";
    cout << "With pairs, you need to search for a specific (count, sum) combination.\n";
    cout << "But lower_bound on pairs compares BOTH fields, which is not what we want.\n";
    cout << "We want to find sums within a specific count group.\n\n";
    
    cout << "3. IMPROVED APPROACH:\n";
    cout << "Sums grouped by count (much cleaner):\n";
    for(int i = 0; i < improved.size(); i++) {
        cout << "  count=" << i << ": [";
        for(int j = 0; j < improved[i].size(); j++) {
            cout << improved[i][j];
            if(j < improved[i].size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    cout << "\n4. SEARCH EXAMPLE:\n";
    cout << "If we want sums with exactly 2 elements:\n";
    cout << "Original: Need to scan through mixed data\n";
    cout << "Improved: Direct access to improved[2] = [";
    for(int j = 0; j < improved[2].size(); j++) {
        cout << improved[2][j];
        if(j < improved[2].size() - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    cout << "5. BINARY SEARCH DEMONSTRATION:\n";
    int target = 5;
    cout << "Looking for sum closest to " << target << " with exactly 2 elements:\n";
    
    // Original approach (complex)
    cout << "Original approach complexity:\n";
    auto it_start = lower_bound(original.begin(), original.end(), make_pair(2, 0));
    auto it_end = lower_bound(original.begin(), original.end(), make_pair(3, 0));
    cout << "  Need to find range [" << (it_start - original.begin()) << ", " << (it_end - original.begin()) << ")\n";
    cout << "  Then search within that range for closest sum\n";
    
    // Improved approach (simple)
    cout << "Improved approach simplicity:\n";
    auto& candidates = improved[2];
    auto it = lower_bound(candidates.begin(), candidates.end(), target);
    cout << "  Direct binary search in improved[2]\n";
    cout << "  Found position: " << (it - candidates.begin()) << "\n";
    if(it != candidates.end()) {
        cout << "  Closest sum >= " << target << ": " << *it << "\n";
    }
    if(it != candidates.begin()) {
        --it;
        cout << "  Closest sum < " << target << ": " << *it << "\n";
    }
    
    return 0;
}