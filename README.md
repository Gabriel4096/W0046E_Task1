# Game Systems, W0046E
## Profiling and CPU architecture, Task 1
### Gabriel Kopparmark, gabkop-2@student.ltu.se
### Gabriel4096, https://github.com/Gabriel4096/W0046E_Task1
### 2025-12-2X

# Table of contents
1. [Problem specification](#1-problem-specification)
2. [User guide](#2-user-guide)
3. [Solution description](#3-solution-description)
4. [Limitations](#4-limitations)
5. [Discussion](#5-discussion)
6. [Test runs](#6-test-runs)

# 1. Problem specification
This assignment is about comparing the performance between different sets of operations in C/C++ and inspect their machine instructions. Each set of operations are performed one million times with arguments from pre-generated arrays of pseudo-ramdom numbers. Each iteration's result are added to a final sum. There are four different sets of operations:
1. One sum of $a+b$,
2. Four parallel sums of $a+b$, $a*b$, $a<<b$ and $a-b$,
3. One sum of $(a+b)*(a-b)$,
4. One sum of $(a+b)*(a-b)$ but only the iterations where $a$ is more than half the biggest possible random number.

# 2. User guide
The project is found in the following repository: W0046E_Task1, https://github.com/Gabriel4096/W0046E_Task1. This project was written in C for Linux, using Linux specific functions and must be compiled for Linux to work.

# 3. Solution description
* different versions
* time measurements

# 4 Limitations

# 5. Discussion

# 6. Test runs
