#include <iostream>
#include <string>
#include "LCS/LCS.h"
#include <cstring>

int main()
{
#if 0
    std::string s1 = "AXY";
    std::string s2 = "ADXCPY";

    int n = s1.length();
    int m = s2.length();

    std::cout << "LCS-Recursive of S1 and S2: "
              << DynamicProgramming::LCS::Recursive(s1, s2, n, m)
              << std::endl;

    std::memset(t, -1, sizeof(t));
    std::cout << "LCS-memoization of S1 and S2: "
              << DynamicProgramming::LCS::memoization(s1, s2, n, m)
              << std::endl;

    std::cout << "LCS-Top Down of S1 and S2: "
              << DynamicProgramming::LCS::Topdown(s1, s2, n, m)
              << std::endl;

    std::cout << "LongestCommSubstring: "
              << DynamicProgramming::LCS::LongestCommSubstring(s1, s2, n, m)
              << std::endl;

    std::cout << "Printing Longest common subsequence: "
              << DynamicProgramming::LCS::printLongestCommSubsequence(s1, s2, n, m)
              << std::endl;

    std::cout << "Shortes Super Sequence: "
              << DynamicProgramming::LCS::shortestCommSuperSequence(s1, s2, n, m)
              << std::endl;


    auto [insertion, deletion] = DynamicProgramming::LCS::stringAtoB(s1, s2, s1.length(), s2.length());
    std::cout << "Minimum Number of Insertion = " << insertion<<"\n"
              << " and Deletion = " << deletion
              << " to convert String a to String b." 
              << std::endl;

    std::cout<<"longest palindromic subsequence's length:"
             <<DynamicProgramming::LCS::longestPalindromeSubseq(s1)
             <<std::endl;
        
    
    std::cout<<"Minimum no of Deletion to make plaindrom: "
            <<DynamicProgramming::LCS::minDeletions(s1)
            <<std::endl;

    std::cout << "SCS: " << DynamicProgramming::LCS::printShortestCommSubsequence(s1, s2, n, m)
              << std::endl;
    std::cout << "LongestReaptingSubsequence: " << DynamicProgramming::LCS::LongestReaptingSubsequence(s1)
              << std::endl;
    std::cout << "Sequence Pattern Matching: "
              << DynamicProgramming::LCS::SequencePatternMatching(s1, s2)
              << std::endl;

    int arr[] = {40, 20, 30, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 1;
    int j = n - 1;
    std::cout << "Resursion: Matrix Chain Multiplication: "
              << DynamicProgramming::MatrixChainMultiplication::Recursive(arr, i, j)
              << std::endl;
    std::cout << "Memoized: Matrix Chain Multiplication: "
              << DynamicProgramming::MatrixChainMultiplication::Recursive(arr, i, j)
              << std::endl;

    std::string str = "Nitin";
    std::transform(str.begin(), str.end(), str.begin(), ::tolower); // case-insensitive
    int i = 0;
    int j = str.length() - 1;

    std::cout << "Recursion: Palindrome Partitioning : "
              <<DynamicProgramming::PalindromePartitioning::memoized(str, i, j)
              << std::endl;

    std::string str = "T|F&T^F";
    int j = str.length() - 1;
    bool ch;
    std::cout << "Recursion__Evaluate Expression To True Boolean Parenthesization: "
              << DynamicProgramming::MatrixChainMultiplication::evaluateExprRecur(str, 0, j, ch)
              << std::endl;
    std::cout << "memo__Evaluate Expression To True Boolean Parenthesization: "
              << DynamicProgramming::MatrixChainMultiplication::evaluateExprMemo(str, 0, j, ch)
              << std::endl;

    std::string s1 = "great", s2 = "rgeat";
    std::cout << "isScramble string Recusion: "
              << DynamicProgramming::MatrixChainMultiplication::isScrambleStrRecusion(s1, s2)
              << std::endl;
    std::cout << "isScramble string Memoized: "
              << DynamicProgramming::MatrixChainMultiplication::isScrambleMemo(s1, s2)
                        << std::endl;

    memset(t, -1, sizeof(t));

    int egg = 3, floor = 5;
    std::cout << "887.[recursion]: Super Egg Drop: "
              << DynamicProgramming::MatrixChainMultiplication::EggDropping::recursion(egg, floor)
              << std::endl;
    std::cout << "887. [memoized]: Super Egg Drop: "
              << DynamicProgramming::MatrixChainMultiplication::EggDropping::memoized(egg, floor)
              << std::endl;
    std::cout << "887. [memoizedOpt]: Super Egg Drop: "
              << DynamicProgramming::MatrixChainMultiplication::EggDropping::memoizedOpt(egg, floor)
              << std::endl;
   
    #endif
    auto root = std::make_shared<treesDataStructure::BinaryTreeNode<int>>();
    root->data = 1;
    root->left = std::make_shared<treesDataStructure::BinaryTreeNode<int>>();
    root->left->data = 2;
    root->right = std::make_shared<treesDataStructure::BinaryTreeNode<int>>();
    root->right->data = 3;

    int result = 0;
    DynamicProgramming::BinaryTree::DiameterofBT(root, result);  
    
    std::cout << "Diameter: " << result << std::endl;
    system("pause>0");
    return 0;
}
