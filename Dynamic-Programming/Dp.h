#include <string>
#include <limits>
#include <algorithm>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <cstring>
#include <hash_map>
#include<memory>
#include "../Trees.h"

int static t[1001][1001];
// static std::unordered_map<std::string, int>mp;

namespace std
{
    template <>
    struct hash<std::tuple<int, int, bool>>
    {
        std::size_t operator()(const std::tuple<int, int, bool> &key) const noexcept
        {
            auto [a, b, c] = key;
            std::size_t h1 = std::hash<int>{}(a);
            std::size_t h2 = std::hash<int>{}(b);
            std::size_t h3 = std::hash<bool>{}(c);
            return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine hashes
        }
    };
}
static std::unordered_map<std::tuple<int, int, bool>, int> mp;

namespace DynamicProgramming
{

    namespace unbounded
    {
        int coinChangeMin(const int coin[], int n, int sum)
        {
            int t[n + 1][sum + 1];

            for (int i = 0; i <= n; ++i)
            {
                for (int j = 0; j <= sum; ++j)
                {
                    if (i == 0)
                        t[i][j] = INT_MAX - 1;
                    if (j == 0)
                        t[i][j] = 0;
                }
            }

            for (int j = 1; j <= sum; ++j)
            {
                t[1][j] = (j % coin[0] == 0) ? (j / coin[0]) : (INT_MAX - 1);
            }

            for (int i = 2; i <= n; ++i)
            {
                for (int j = 1; j <= sum; ++j)
                {
                    if (coin[i - 1] <= j)
                        t[i][j] = std::min(t[i][j - coin[i - 1]] + 1, t[i - 1][j]);
                    else
                        t[i][j] = t[i - 1][j];
                }
            }

            return (t[n][sum] == INT_MAX - 1) ? -1 : t[n][sum];
        }
    }

    namespace LCS
    {
        int Recursive(std::string_view s1, std::string_view s2, int n, int m)
        {
            if (n == 0 || m == 0)
                return 0;

            if (s1[n - 1] == s2[m - 1])
                return 1 + Recursive(s1, s2, n - 1, m - 1);
            else
                return std::max(Recursive(s1, s2, n, m - 1),
                                Recursive(s1, s2, n - 1, m));
        }

        int memoization(std::string_view s1, std::string_view s2, int n, int m)
        {
            if (n == 0 || m == 0)
                return 0;

            if (t[n][m] != -1)
                return t[n][m];

            if (s1[n - 1] == s2[m - 1])
                return t[n][m] = 1 + memoization(s1, s2, n - 1, m - 1);
            else
                return t[n][m] = std::max(memoization(s1, s2, n, m - 1),
                                          memoization(s1, s2, n - 1, m));
        }

        int Topdown(std::string_view s1, std::string_view s2, int n, int m)
        {
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            return t[n][m];
        }
        int LongestCommSubstringRecursive(std::string_view s1, std::string_view s2, int n, int m, int count)
        {
            if (n == 0 || m == 0)
                return count;

            if (s1[n - 1] == s2[m - 1])
            {
                count = LongestCommSubstringRecursive(s1, s2, n - 1, m - 1, count + 1);
            }

            int c1 = LongestCommSubstringRecursive(s1, s2, n - 1, m, 0);
            int c2 = LongestCommSubstringRecursive(s1, s2, n, m - 1, 0);

            return std::max({count, c1, c2});
        }

        int LongestCommSubstringMemo(std::string_view s1, std::string_view s2, int n, int m, int &maxLen)
        {
            if (n == 0 || m == 0)
                return 0;

            if (t[n][m] != -1)
                return t[n][m];

            LongestCommSubstringMemo(s1, s2, n - 1, m, maxLen);
            LongestCommSubstringMemo(s1, s2, n, m - 1, maxLen);

            if (s1[n - 1] == s2[m - 1])
            {
                t[n][m] = 1 + LongestCommSubstringMemo(s1, s2, n - 1, m - 1, maxLen);
                maxLen = std::max(maxLen, t[n][m]);
                return t[n][m];
            }
            else
            {
                t[n][m] = 0;
                return 0;
            }
        }

        int LongestCommSubstring(std::string s1, std::string s2, int n, int m)
        {
            int result = 0;
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                    {
                        t[i][j] = 1 + t[i - 1][j - 1];
                        result = std::max(result, t[i][j]);
                    }
                    else
                        t[i][j] = 0;
                }
            }

            return result;
        }

        std::string printLongestCommSubsequence(std::string s1, std::string s2, int n, int m)
        {
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            int i = n, j = m;
            std::string result = "";
            while (i > 0 && j > 0)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    result.push_back(s1[i - 1]);
                    i--;
                    j--;
                }
                else
                {
                    if (t[i][j - 1] > t[i - 1][j])
                    {
                        j--;
                    }
                    else
                    {
                        i--;
                    }
                }
            }
            std::reverse(result.begin(), result.end());
            return result;
        }

        int shortestCommSuperSequence(std::string s1, std::string s2, int n, int m)
        {
            return m + n - Topdown(s1, s2, n, m);
        }

        // Minimum Number of Insertion and Deletion to convert String a to String b
        std::tuple<int, int> stringAtoB(const std::string &s1, const std::string &s2, int n, int m)
        {
            int lcs = Topdown(s1, s2, n, m);
            int Deletion = n - lcs;
            int Insertion = m - lcs;

            return {Insertion, Deletion};
        }

        int longestPalindromeSubseq(std::string_view s)
        {
            int n = s.length();
            std::string rev(s.rbegin(), s.rend());
            return Topdown(s, std::string_view(rev), n, n);
        }

        // Minimum no of Deletion to Make a String Palindrome

        int minDeletions(std::string_view s)
        {
            int n = s.length();
            int LPSlenth = longestPalindromeSubseq(s);

            return (n - LPSlenth);
        }

        std::string printShortestCommSubsequence(std::string s1, std::string s2, int n, int m)
        {
            // Build LCS table
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                        t[i][j] = 0;
                }
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            // Backtracking
            int i = n, j = m;
            std::string result = "";

            while (i > 0 && j > 0)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    result.push_back(s1[i - 1]);
                    i--;
                    j--;
                }
                else if (t[i][j - 1] > t[i - 1][j])
                {
                    result.push_back(s2[j - 1]);
                    j--;
                }
                else
                {
                    result.push_back(s1[i - 1]);
                    i--;
                }
            }

            // Add remaining characters
            while (i > 0)
            {
                result.push_back(s1[i - 1]);
                i--;
            }
            while (j > 0)
            {
                result.push_back(s2[j - 1]);
                j--;
            }

            std::reverse(result.begin(), result.end());
            return result;
        }

        int LongestReaptingSubsequence(const std::string str)
        {
            std::string c_str = str;
            int n = str.length();
            int m = c_str.length();
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (str[i - 1] == c_str[j - 1] && i != j)
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            return t[n][m];
        }
        bool SequencePatternMatching(const std::string_view s1, const std::string_view s2)
        {
            int n = s1.length();
            int m = s2.length();

            int LCS_length = Topdown(s1, s2, n, m);
            if (LCS_length == s1.length())
                return true;
            return false;
        }

    }
    namespace MatrixChainMultiplication
    {
        int Recursive(int arr[], int i, int j)
        {
            if (i >= j)
            {
                return 0;
            }
            int mn = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                long long tempAns = Recursive(arr, i, k) +
                                    Recursive(arr, k + 1, j) +
                                    arr[i - 1] * arr[k] * arr[j];

                if (tempAns < mn)
                {
                    mn = tempAns;
                }
            }
            return mn;
        }
        int Memoized(int arr[], int i, int j)
        {
            if (t[i][j] != -1)
            {
                return t[i][j];
            }
            int mn = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                long long tempAns = Memoized(arr, i, k) +
                                    Memoized(arr, k + 1, j) +
                                    arr[i - 1] * arr[k] * arr[j];

                if (tempAns < mn)
                {
                    mn = tempAns; //  mn = std::min(mn, tempAns);
                }
            }
            return t[i][j] = mn;
        }

        int evaluateExprRecur(const std::string &str, int i, int j, bool isTrue)
        {
            if (i > j)
                return 0;

            if (i == j)
            {
                if (isTrue)
                    return str[i] == 'T' ? 1 : 0;
                else
                    return str[i] == 'F' ? 1 : 0;
            }

            int ans = 0;

            for (int k = i + 1; k <= j - 1; k += 2)
            {
                char op = str[k];

                int leftT = evaluateExprRecur(str, i, k - 1, true);
                int leftF = evaluateExprRecur(str, i, k - 1, false);
                int rightT = evaluateExprRecur(str, k + 1, j, true);
                int rightF = evaluateExprRecur(str, k + 1, j, false);

                if (op == '&')
                {
                    if (isTrue)
                        ans += leftT * rightT;
                    else
                        ans += leftF * rightT + leftT * rightF + leftF * rightF;
                }
                else if (op == '|')
                {
                    if (isTrue)
                        ans += leftT * rightT + leftT * rightF + leftF * rightT;
                    else
                        ans += leftF * rightF;
                }
                else if (op == '^')
                {
                    if (isTrue)
                        ans += leftT * rightF + leftF * rightT;
                    else
                        ans += leftT * rightT + leftF * rightF;
                }
            }

            return ans;
        }
        int evaluateExprMemo(const std::string &str, int i, int j, bool isTrue)
        {
            if (i > j)
                return 0;

            if (i == j)
            {
                if (isTrue)
                    return str[i] == 'T' ? 1 : 0;
                else
                    return str[i] == 'F' ? 1 : 0;
            }
            #if 0
                        std::string tempAns = std::to_string(i);
                        tempAns.push_back(' ');
                        tempAns.append(std::to_string(j));
                        tempAns.push_back(' ');
                        tempAns.append(std::to_string(isTrue)); // ch should be int or bool or 'T'/'F'

                        if(mp.find(tempAns)!=mp.end()){
                            return mp[tempAns];
                        }
            #endif
            auto key = std::make_tuple(i, j, isTrue);
            if (mp.find(key) != mp.end())
                return mp[key];

            int ans = 0;

            for (int k = i + 1; k <= j - 1; k += 2)
            {
                char op = str[k];

                int leftT = evaluateExprMemo(str, i, k - 1, true);
                int leftF = evaluateExprMemo(str, i, k - 1, false);
                int rightT = evaluateExprMemo(str, k + 1, j, true);
                int rightF = evaluateExprMemo(str, k + 1, j, false);

                if (op == '&')
                {
                    if (isTrue)
                        ans += leftT * rightT;
                    else
                        ans += leftF * rightT + leftT * rightF + leftF * rightF;
                }
                else if (op == '|')
                {
                    if (isTrue)
                        ans += leftT * rightT + leftT * rightF + leftF * rightT;
                    else
                        ans += leftF * rightF;
                }
                else if (op == '^')
                {
                    if (isTrue)
                        ans += leftT * rightF + leftF * rightT;
                    else
                        ans += leftT * rightT + leftF * rightF;
                }
            }

            return mp[key] = ans;
        }

        bool isScrambleStrRecusion(const std::string &a, const std::string &b)
        {
            if (a == b)
                return true;
            if (a.length() != b.length())
                return false;

            int n = a.length();

            // Optimization: if characters don't match, they can't be scramble
            std::string a_sorted = a;
            std::string b_sorted = b;
            std::sort(a_sorted.begin(), a_sorted.end());
            std::sort(b_sorted.begin(), b_sorted.end());
            if (a_sorted != b_sorted)
                return false;

            for (int i = 1; i < n; ++i)
            {
                // Check if swapping gives a match
                bool condiOne = isScrambleStrRecusion(a.substr(0, i), b.substr(n - i, i)) &&
                                isScrambleStrRecusion(a.substr(i), b.substr(0, n - i));

                // Check if not swapping gives a match
                bool condiTwo = isScrambleStrRecusion(a.substr(0, i), b.substr(0, i)) &&
                                isScrambleStrRecusion(a.substr(i), b.substr(i));

                if (condiOne || condiTwo)
                {
                    return true;
                }
            }

            return false;
        }
        
        bool isScrambleMemo(const std::string& a, const std::string& b) {
            // static map keeps data across recursive calls
            static std::unordered_map<std::string, bool> memo;
        
            if (a == b) return true;
            if (a.length() != b.length()) return false;
        
            std::string key = a + "_" + b;
            if (memo.find(key) != memo.end()) return memo[key];
        
            int n = a.length();
            for (int i = 1; i < n; ++i) {
                // Check with swapping
                bool condition1 = isScrambleMemo(a.substr(0, i), b.substr(n - i)) &&
                                  isScrambleMemo(a.substr(i), b.substr(0, n - i));
        
                // Check without swapping
                bool condition2 = isScrambleMemo(a.substr(0, i), b.substr(0, i)) &&
                                  isScrambleMemo(a.substr(i), b.substr(i));
        
                if (condition1 || condition2) {
                    return memo[key] = true;
                }
            }
        
            return memo[key] = false;
        }
        
        namespace EggDropping{
            int recursion(int egg, int floor)
            {
                

                if(floor==0 || floor==1) return floor;
                if(egg==1) return floor;

                int mn = INT_MAX;
                for(int k=1;k<=floor; k++)
                {
                    int tempAns = 1 + std::max(recursion(egg-1, k-1), recursion(egg, floor-k));

                    mn = std::min(mn, tempAns);
                }
                return mn;
            }
            int memoized(int egg, int floor)
            {
                if(floor==1 || floor==0) return floor;
                if(egg ==1) return floor;

                if(t[egg][floor]!=-1){
                    return t[egg][floor];
                }
                int mn = INT_MAX;
                for (int k = 1; k <= floor; k++)
                {
                    int temAns = 1 + std::max(memoized(egg-1, k-1), memoized(egg, floor-k));
                    mn = std::min(mn, temAns);
                }
                return t[egg][floor] = mn;
            }

            int memoizedOpt(int egg, int floor)
            {
                if(floor==1 || floor==0) return floor;
                if(egg ==1) return floor;

                if(t[egg][floor]!=-1){
                    return t[egg][floor];
                }
                int mn = INT_MAX;
                for (int k = 1; k <= floor; k++)
                {
                    int low = 0;
                    if(t[egg-1][k-1]!=-1){
                        low = t[egg-1][k-1];
                    }else{
                        low = memoizedOpt(egg-1, k-1);
                        t[egg-1][k-1] = low;
                    }
                    int high = 0;
                    if(t[egg][floor-k]!=-1){
                        high = t[egg][floor-k];
                    }else{
                        high =  memoizedOpt(egg, floor-k); 
                        t[egg][floor-k] = high;
                    }
                    
                    int temAns = 1 + std::max(low,high);
                    mn = std::min(mn, temAns);
                }
                return t[egg][floor] = mn;
            }

        } 
        


    }
    namespace PalindromePartitioning
    {
        bool isPlindrom(const std::string &str, int i, int j)
        {
            while (i < j)
            {
                if (str[i] != str[j])
                    return false;
                ++i;
                --j;
            }
            return true;
        }

        int recursive(const std::string &str, int i, int j)
        {
            if (i >= j)
                return 0;

            if (isPlindrom(str, i, j))
                return 0;

            int min = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int tempAns = recursive(str, i, k) + 1 +
                              recursive(str, k + 1, j);
                if (tempAns < min)
                    min = tempAns;
            }
            return min;
        }
        int memoized(const std::string &str, int i, int j)
        {
            if (i >= j)
                return 0;

            if (isPlindrom(str, i, j))
                return 0;

            int min = INT_MAX;
            for (int k = i; k < j; k++)
            {
                // int tempAns = recursive(str, i, k) + 1 + recursive(str, k + 1, j);
                long left = 0, right = 0;

                if (t[i][k] != -1)
                {
                    left = t[i][k];
                }
                else
                {
                    left = memoized(str, i, k);
                    t[i][k] = left;
                }

                if (t[k + 1][j] != -1)
                {
                    right = t[k + 1][j];
                }
                else
                {
                    right = memoized(str, k + 1, j);
                    t[k + 1][j] = right;
                }

                long long tempAns = left + 1 + right;

                if (tempAns < min)
                    min = tempAns;
            }
            return min;
        }

    }
    namespace BinaryTree
    {
        using namespace treesDataStructure;

        int DiameterofBT(std::shared_ptr<BinaryTreeNode<int>> root, int &result) {
            if (!root) return 0;

            int left = DiameterofBT(root->left, result);
            int right = DiameterofBT(root->right, result);

            int tempAns = std::max(left, right) + 1;
            int ans = 1 + left + right;

            result = std::max(result, ans); 
            return tempAns;
        }
        int maxPathAnyNodeToAnyNode(std::shared_ptr<BinaryTreeNode<int>> root, int &result)
        {
            if (!root) return 0;

            int left = DiameterofBT(root->left, result);
            int right = DiameterofBT(root->right, result);

            int tempAns = std::max(std::max(left, right) + root->data, root->data);
            int ans =  std::max(tempAns, left+right+root->data);

            result = std::max(result, ans);
            return tempAns;
        }
        int maxPathLeafNodeToLeafNode(std::shared_ptr<BinaryTreeNode<int>> root, int &result)
        {
            if (!root) return 0;

            int left = DiameterofBT(root->left, result);
            int right = DiameterofBT(root->right, result);
            int ans = 0;
            
            int tempAns = std::max(std::max(left, right) + root->data, root->data);
            if(root->left == nullptr && root->right == nullptr){
                ans =  std::max(tempAns, left+right+root->data);
            }
            result = std::max(result, ans);
            return tempAns;
        }


    }

}
