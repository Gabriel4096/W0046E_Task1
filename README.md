# Game Systems, W0046E
## Profiling and CPU architecture, Task 1
### Gabriel Kopparmark, gabkop-2@student.ltu.se
### Gabriel4096, https://github.com/Gabriel4096/W0046E_Task1
### 2026-01-0X

# Table of contents
1. [Problem specification](#1-problem-specification)
2. [Solution description](#2-solution-description)
3. [Limitations](#3-limitations)
4. [Test runs](#4-test-runs)
5. [Discussion](#5-discussion)

# 1. Problem specification
This assignment is about comparing the performance between different sets of operations in C/C++ and inspect their machine instructions. Each set of operations are performed one million times with arguments from pre-generated arrays of pseudo-ramdom numbers. Each iteration's result are added to a final sum. There are four different sets of operations:
1. One sum of $a+b$,
2. Four parallel sums of $a+b$, $a*b$, $a<<b$ and $a-b$,
3. One sum of $(a+b)*(a-b)$,
4. One sum of $(a+b)*(a-b)$ but only the iterations where $a$ is more than half the biggest possible random number.

# 2. Solution description
The four sets of operations are split into five separate versions of the program, where the 5th version is a branchless version of the 4th set of operations. Every program do a high resolution time measurement of the time taken to add the million expressions.\
This project was written in C using POSIX specific features and must be compiled on a POSIX compliant system to work (raw Windows does not work). The five different versions need to be compiled separately using the compiler flag -DPART set to 1 to 5.

# 3. Limitations

# 4. Test runs

# 5. Discussion
