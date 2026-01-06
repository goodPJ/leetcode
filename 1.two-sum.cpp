/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

#include <vector>
#include <unordered_map>
using namespace std;

// @lc code=start
class Solution {
public:
// Hash map solution
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map; // value -> index
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            if (num_map.find(complement) != num_map.end()) {
                return {num_map[complement], i};
            }
            num_map[nums[i]] = i;
        }
        return {}; // should never reach here as per problem statement
    };
};
// @lc code=end

// basic solution:brute force
// vector<int> twoSum(vector<int>& nums, int target) {
//         int i = 0;
//         bool flag = false;
//         vector<int> result;
//         for (i = 0; i < nums.size(); i++) {
//             for (int j = i + 1; j < nums.size(); j++) {
//                 if (nums[i] + nums[j] == target) {
//                     result.push_back(i);
//                     result.push_back(j);
//                     flag = true;
//                     break;
//                 }
//             }
//             if (flag)
//                 break;
//         }
//         return result;
//     }