# 📚 Technique

A repository of algorithmic problem-solving techniques categorized by approach.

## 🛠️ Tech Stack

- **Language**: C++
- **Compiler Version**: GCC 14.2.0 (compatible with C++17)

---

## 🗂️ Folder Structure

Technique/
├── Sliding Window/
│   ├── SlidingWindow.h
│   ├── main.cpp
├── Dynamic Programming/
│   ├── Dp.h
│   ├── main.cpp





---

## 🚀 Contents

### 1️⃣ Sliding Window

This folder contains solutions for problems utilizing the **sliding window** technique, including:

- **Count Occurrences of Anagrams in a String** → Sliding window + hashmap
- **Maximum of All Subarrays of Size K** → Sliding window + deque (list)
- **Largest Subarray with Sum K (Positive Integers)** → Sliding window
- **Largest Subarray with Sum K (Including Negative Integers)** → Prefix sum + hashmap
- **Count Number of Subarrays with Sum Equal to K** → Prefix sum + hashmap
- **Longest Substring with Exactly K Unique Characters** → Sliding window + hashmap
- **Length of Longest Substring Without Repeating Characters** → Sliding window + hashmap (fixed + variable size window)
- **Minimum Window Substring Containing All Characters of Another String** → Sliding window + hashmap (returning length & returning substring)

---

### 2️⃣ Dynamic Programming

This folder includes solutions covering various types of **Dynamic Programming** strategies:

✅ **Memoization** (Top-down DP)  
✅ **Tabulation** (Bottom-up DP)  
✅ **1D DP**  
✅ **2D DP**  
✅ **State Compression DP**  
✅ **Subset/Knapsack DP**  
✅ **DP on Strings**  
✅ **DP on Subsequences**  
✅ **DP with Bitmasking**

Each solution includes a `.cpp` file (and optional `.h` header files) for clarity and modularity.

---

## 💻 How to Compile

Use g++ (or any compatible C++17 compiler):

```bash
g++ filename.cpp -o output
./output
