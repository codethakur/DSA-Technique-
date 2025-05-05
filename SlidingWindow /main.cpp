#include <iostream>
#include "SlidingWindow.h"
#include <vector>
#include <string>

int countAnagramsBruteForce(const std::string &pat, const std::string &txt)
{
    int k = pat.length();
    int ans = 0;

    for (int i = 0; i <= txt.length() - k; i++)
    {
        std::string window = txt.substr(i, k); // take substring of size k

        // Now, check if window is an anagram of pat
        std::unordered_map<char, int> freq1, freq2;
        for (char ch : pat)
            freq1[ch]++;
        for (char ch : window)
            freq2[ch]++;

        if (freq1 == freq2)
        {
            ans++;
        }
    }
    return ans;
}

int main()
{

#if 0
    std::vector<int>nums = {1,5,4,2,9,9,9};
    int k = 3;
    std::cout<<"maximum Sub array Sum: "
    <<FixedSizeWindow::maximumSubarraySum(nums, k)<<std::endl;
    

    std::vector<int> nums = {12, -1, -7, 8, 15, 30, 16, 28};
    int k = 3;

    std::vector<int> result = FixedSizeWindow::firstNegInt(nums, k);

    std::cout << "First negative integers in each window: ";
    for (int x : result) {
        std::cout << x << " ";
    }
    
    std::string txt = "forxxorfxdofr";
    std::string pat = "for";

    std::cout<<"Count Occurrences Of Anagrams: "<<FixedSizeWindow::countAnagrams(pat, txt)<<std::endl;
    std::cout<<"\nCount Occurrences Of Anagrams (BruteForce) "<<countAnagramsBruteForce(pat, txt);
    

    std::vector<int>nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;

    auto ans = FixedSizeWindow::maxOfSubArrofK(nums, k) ;
    std::cout<<"[ ";
    for(auto i:ans){
        std::cout<<i<<", ";
    }
    std::cout<<"]";
    std::cout << std::endl;


    std::vector<int>nums = {4, 1, 1, 1, 2, 3,5 };
    int k = 5;
    std::cout<<"Largest Subarray of sum K "<<VariableSizeWindow::LargestSubarrayofsumK(nums, k);

    std::string s = "aabacbebebe";
    int k = 3;
    std::cout << "longest K Substr: " << VariableSizeWindow::longestKSubstr(s, k) 
              << std::endl;
    const std::string str = "abcabcbb";
    std::cout << "\nlength Of Longest Substring: "
              << VariableSizeWindow::lengthOfLongestSubstring(str)
              << std::endl;
    #endif          
    
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";

    std::cout << "Minimum window length: " << VariableSizeWindow::minWindow(s, t) << std::endl;

    system("pause>0");
    return 0;
}
