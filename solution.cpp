#include <vector>
#include <algorithm>
#include <climits>
#include <map>
using namespace std;

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
        
        // Generate all possible sums for first half
        // sums1[i] contains all possible sums using exactly i elements from first half
        vector<vector<int>> sums1(half + 1);
        
        for (int mask = 0; mask < (1 << half); mask++) {
            int sum = 0;
            int count = 0;
            for (int i = 0; i < half; i++) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                    count++;
                }
            }
            sums1[count].push_back(sum);
        }
        
        // Sort all sum arrays for binary search
        for (int i = 0; i <= half; i++) {
            sort(sums1[i].begin(), sums1[i].end());
        }
        
        // Generate all possible sums for second half
        vector<vector<int>> sums2(half + 1);
        
        for (int mask = 0; mask < (1 << half); mask++) {
            int sum = 0;
            int count = 0;
            for (int i = 0; i < half; i++) {
                if (mask & (1 << i)) {
                    sum += nums[half + i];
                    count++;
                }
            }
            sums2[count].push_back(sum);
        }
        
        // Sort all sum arrays for binary search
        for (int i = 0; i <= half; i++) {
            sort(sums2[i].begin(), sums2[i].end());
        }
        
        int minDiff = INT_MAX;
        
        // Try all possible combinations
        for (int i = 0; i <= half; i++) {
            int j = half - i; // number of elements needed from second half
            
            for (int sum1 : sums1[i]) {
                // We want sum1 + sum2 to be as close as possible to totalSum/2
                int target = totalSum / 2 - sum1;
                
                // Find the closest sum2 to target in sums2[j]
                auto& vec = sums2[j];
                auto it = lower_bound(vec.begin(), vec.end(), target);
                
                // Check the element at iterator position
                if (it != vec.end()) {
                    int sum2 = *it;
                    int subset1Sum = sum1 + sum2;
                    int subset2Sum = totalSum - subset1Sum;
                    minDiff = min(minDiff, abs(subset1Sum - subset2Sum));
                }
                
                // Check the element before iterator position
                if (it != vec.begin()) {
                    --it;
                    int sum2 = *it;
                    int subset1Sum = sum1 + sum2;
                    int subset2Sum = totalSum - subset1Sum;
                    minDiff = min(minDiff, abs(subset1Sum - subset2Sum));
                }
            }
        }
        
        return minDiff;
    }
};

// Test function
#include <iostream>
int main() {
    Solution sol;
    vector<int> nums = {91, 14, 16, 82, 32, 2, 38, 94};
    cout << "Result: " << sol.minimumDifference(nums) << endl;
    
    // Test with provided examples
    vector<int> test1 = {3, 9, 7, 3};
    cout << "Test 1: " << sol.minimumDifference(test1) << endl;
    
    vector<int> test2 = {-36, 36};
    cout << "Test 2: " << sol.minimumDifference(test2) << endl;
    
    vector<int> test3 = {2, -1, 0, 4, -2, -9};
    cout << "Test 3: " << sol.minimumDifference(test3) << endl;
    
    return 0;
}