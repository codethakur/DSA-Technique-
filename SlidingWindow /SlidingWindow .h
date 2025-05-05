#include <climits>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <list>
#include <string>
#include <unordered_map>

static std::unordered_map<char, int> charMap;

namespace FixedSizeWindow
{
    long long maximumSubarraySum(std::vector<int> &nums, int k)
    {
        if (k > nums.size())
        {
            throw std::runtime_error("not valid array!");
        }

        int i = 0, j = 0;
        long long sum = 0;
        long long mx = LLONG_MIN;
        while (j < nums.size())
        {
            sum += nums[j];

            if (j - i + 1 < k)
            {
                j++;
            }
            else if (j - i + 1 == k)
            {
                mx = std::max(mx, sum);
                sum -= nums[i];
                i++;
                j++;
            }
        }
        return mx;
    }
    std::vector<int> firstNegInt(std::vector<int> nums, int k)
    {
        if (nums.size() < k)
        {
            throw std::runtime_error("Invalid array");
        }

        std::vector<int> res;
        std::list<int> NegIntList;
        int i = 0, j = 0;

        while (j < nums.size())
        {
            if (nums[j] < 0)
            {
                NegIntList.push_back(nums[j]);
            }

            if (j - i + 1 < k)
            {
                j++;
            }
            else if (j - i + 1 == k)
            {
                if (NegIntList.empty())
                {
                    res.push_back(0);
                }
                else
                {
                    res.push_back(NegIntList.front());
                    if (nums[i] == NegIntList.front())
                    {
                        NegIntList.pop_front();
                    }
                }
                i++;
                j++;
            }
        }

        return res;
    }
    
    int countAnagrams(const std::string &pat, const std::string &txt)
    {
        if (txt.length() < pat.length())
        {
            throw std::runtime_error("txt length is less than pat length!");
        }

        int k = pat.length();
        unsigned int ans = 0;

        // Build initial map with pattern
        for (char ch : pat)
        {
            charMap[ch]++;
            
        }
        int count_letter = charMap.size();

        int i = 0, j = 0;

        while (j < txt.length())
        {
            // Work for current character
            if (charMap.find(txt[j]) != charMap.end())
            {
                charMap[txt[j]]--;
                if (charMap[txt[j]] == 0)
                {
                    count_letter--;
                }
            }

            if (j - i + 1 < k)
            {
                j++;
            }
            else if (j - i + 1 == k)
            {
                if (count_letter == 0)
                {
                    ans++;
                }

                // Before sliding window, undo effect of i-th character
                if (charMap.find(txt[i]) != charMap.end())
                {
                    charMap[txt[i]]++;
                    if (charMap[txt[i]] == 1)
                    {
                        count_letter++;
                    }
                }
                i++;
                j++;
            }
        }
        return ans;
    }

    std::vector<int> maxOfSubArrofK(std::vector<int>& nums, int k) {
        int i = 0, j = 0;
        std::list<int> currMaxList;
        std::vector<int> ans;
        
        while (j < nums.size()) {
            while (!currMaxList.empty() && currMaxList.back() < nums[j]) {
                currMaxList.pop_back();
            }
            currMaxList.push_back(nums[j]);
            
            if (j - i + 1 < k) {
                j++;
            } else if (j - i + 1 == k) {
                ans.push_back(currMaxList.front());  
                if (currMaxList.front() == nums[i]) {
                    currMaxList.pop_front();
                }
                i++;
                j++;
            }
        }
        return ans;
    }  

}
namespace VariableSizeWindow
{
    int LargestSubarrayofsumK(std::vector<int>&nums, int k)
    {
        int i=0, j=0;
        int mx = INT_MIN;
        long int sum = 0;
        while (j<nums.size())
        {
            sum = sum+nums[j];
           
            if(sum>k){
                while (sum>k)
                {
                   sum = sum-nums[i];
                   i++;
                }
                
            }
            if(sum == k)
            {
                mx = std::max(mx, j-i+1);

            }
            j++;
        }
        return mx;
        
    }
    int largestSubarraySumKwithNeg(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> hashMap; // {prefix_sum, count}
        hashMap[0] = 1; // Important: handle case when prefix sum itself is exactly k
        int n = nums.size();
        int s = 0;
        int subarrayCount = 0;

        for (int i = 0; i < n; i++) {
            s += nums[i];
            if (hashMap.find(s - k) != hashMap.end()) {
                subarrayCount += hashMap[s - k];
            }
            hashMap[s]++;
        }

        return subarrayCount;
    }
    int longestKSubstr(const std::string &s, int k) {
        int i = 0, j = 0;
        int mx = -1;
    
        while (j < s.length()) {
            charMap[s[j]]++;
    
            if (charMap.size() > k) {
                while (charMap.size() > k) {
                    charMap[s[i]]--;
                    if (charMap[s[i]] == 0) {
                        charMap.erase(s[i]);
                    }
                    i++;
                }
            }
    
            if (charMap.size() == k) {
                mx = std::max(mx, j - i + 1);
            }
    
            j++;
        }
    
        return mx;
    }

    int lengthOfLongestSubstring(const std::string &s) {
        int i = 0, j = 0;
        int mx = 0;
    
        while (j < s.length()) {
            charMap[s[j]]++;
    
            // If the window has duplicates
            while (charMap.size() < j - i + 1) {
                charMap[s[i]]--;
                if (charMap[s[i]] == 0) {
                    charMap.erase(s[i]);
                }
                i++;
            }
    
            // If the window has all unique characters
            if (charMap.size() == j - i + 1) {
                mx = std::max(mx, j - i + 1);
            }
    
            j++;
        }
    
        return mx;
    }
    std::string minWindow(const std::string s, std::string t) {
        for (char ch : t) charMap[ch]++;

        int i = 0, j = 0;
        int count = charMap.size();
        int minLen = INT_MAX;
        int startIndex = 0;
    
        while (j < s.size()) {
            if (charMap.find(s[j]) != charMap.end()) {
                charMap[s[j]]--;
                if (charMap[s[j]] == 0) count--;
            }
    
            while (count == 0) {
                if (j - i + 1 < minLen) {
                    minLen = j - i + 1;
                    startIndex = i;
                }
    
                if (charMap.find(s[i]) != charMap.end()) {
                    charMap[s[i]]++;
                    if (charMap[s[i]] > 0) count++;
                }
                i++;
            }
    
            j++;
        }
        return minLen == INT_MAX ? "" : s.substr(startIndex, minLen);
        //return minLen == INT_MAX ? 0 : minLen;
    }
    
} 
