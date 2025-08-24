#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

vector<vector<int>> gen(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> sums(n + 1);
    
    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0, count = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
                count++;
            }
        }
        sums[count].push_back(sum);
    }
    
    // Sort each group by sum
    for (int i = 0; i <= n; i++) {
        sort(sums[i].begin(), sums[i].end());
    }
    
    return sums;
}

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size();
        int half = n / 2;
        
        // Calculate total sum
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        
        // Split array into two halves
        vector<int> left(nums.begin(), nums.begin() + half);
        vector<int> right(nums.begin() + half, nums.end());
        
        // Generate all possible sums for each half
        vector<vector<int>> leftSums = gen(left);
        vector<vector<int>> rightSums = gen(right);
        
        int minDiff = INT_MAX;
        
        // For each possible number of elements from left half
        for (int i = 0; i <= half; i++) {
            int j = half - i; // number of elements needed from right half
            
            // For each sum with i elements from left
            for (int leftSum : leftSums[i]) {
                // We want: leftSum + rightSum = totalSum/2 (as close as possible)
                // So rightSum should be close to (totalSum/2 - leftSum)
                int target = totalSum / 2 - leftSum;
                
                // Binary search for closest sum in right half with j elements
                auto& candidates = rightSums[j];
                
                // Find the closest sum to target
                auto it = lower_bound(candidates.begin(), candidates.end(), target);
                
                // Check the found position and the previous one
                if (it != candidates.end()) {
                    int rightSum = *it;
                    int sum1 = leftSum + rightSum;
                    int sum2 = totalSum - sum1;
                    minDiff = min(minDiff, abs(sum1 - sum2));
                }
                
                if (it != candidates.begin()) {
                    --it;
                    int rightSum = *it;
                    int sum1 = leftSum + rightSum;
                    int sum2 = totalSum - sum1;
                    minDiff = min(minDiff, abs(sum1 - sum2));
                }
            }
        }
        
        return minDiff;
    }
};

int main() {
    Solution solution;
    
    // Test case 1: Your failing case
    vector<int> nums1 = {91, 14, 16, 82, 32, 2, 38, 94};
    cout << "Test case 1: [91,14,16,82,32,2,38,94]" << endl;
    cout << "Result: " << solution.minimumDifference(nums1) << endl;
    cout << "Expected: 9" << endl << endl;
    
    // Test case 2: Example 1
    vector<int> nums2 = {3, 9, 7, 3};
    cout << "Test case 2: [3,9,7,3]" << endl;
    cout << "Result: " << solution.minimumDifference(nums2) << endl;
    cout << "Expected: 2" << endl << endl;
    
    // Test case 3: Example 2
    vector<int> nums3 = {-36, 36};
    cout << "Test case 3: [-36,36]" << endl;
    cout << "Result: " << solution.minimumDifference(nums3) << endl;
    cout << "Expected: 72" << endl << endl;
    
    // Test case 4: Example 3
    vector<int> nums4 = {2, -1, 0, 4, -2, -9};
    cout << "Test case 4: [2,-1,0,4,-2,-9]" << endl;
    cout << "Result: " << solution.minimumDifference(nums4) << endl;
    cout << "Expected: 0" << endl << endl;
    
    return 0;
}