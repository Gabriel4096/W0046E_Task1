# Game Systems, W0046E
## Profiling and CPU architecture, Task 1
### Gabriel Kopparmark, gabkop-2@student.ltu.se
### Gabriel4096, https://github.com/Gabriel4096/W0046E_Task1
### 2026-01-07

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
4. One sum of $(a+b)*(a-b)$ but only the iterations where $a$ is more than half the largest possible random number.

# 2. Solution description
The four sets of operations are split into five separate versions of the program, where the 5th version is a branchless version of the 4th set of operations. Every program do a high resolution time measurement of the time taken to add the million expressions.\
This project was written in C using POSIX specific features and must be compiled on a POSIX compliant system to work (raw Windows does not work). The five different versions need to be compiled separately using the compiler flag -DPART set to 1 to 5.

# 3. Limitations
The calculated sums that are shown may be incorrect due to overflow, at least for multiplication and bit shift and rand() is not properly seeded so the numbers and sums are the same each time. These limitations however should not affect the benchmarking goal of this project, as long as the programs are compiled without optimizations.

# 4. Test runs
The five versions of the program was compiled with the following commands:
* gcc main.c -O0 -DPART=1 -o part1
* gcc main.c -O0 -DPART=2 -o part2
* gcc main.c -O0 -DPART=3 -o part3
* gcc main.c -O0 -DPART=4 -o part4
* gcc main.c -O0 -DPART=5 -o part5

These are possible outputs of the five programs on my system:
~~~
Running part 1
Sum = 578608482616
Time: 1.000783 ms
~~~
~~~
Running part 2
Sum = 578608482616
Sum2 = -630507319581
Sum3 = -34203139242197
Sum4 = 302407603124
Time: 2.276837 ms
~~~
~~~
Running part 3
Sum = -963130679604
Time: 1.172300 ms
~~~
~~~
Running part 4
Sum = 302011259718
Time: 3.283799 ms
~~~
~~~
Running part 5
Sum = 302011259718
Time: 1.585567 ms
~~~

These are the machine instructions for the critical loop from the five programs running on my system:\
1. 
~~~
	movl	$0, -8000064(%rbp)
	jmp	.L4
.L5:
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	addl	%edx, %eax
	cltq
	addq	%rax, -8000056(%rbp)
	addl	$1, -8000064(%rbp)
.L4:
	cmpl	$999999, -8000064(%rbp)
	jle	.L5
~~~
2. 
~~~
	movl	$0, -8000088(%rbp)
	jmp	.L4
.L5:
	movl	-8000088(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000088(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	addl	%edx, %eax
	cltq
	addq	%rax, -8000080(%rbp)
	movl	-8000088(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000088(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	imull	%edx, %eax
	cltq
	addq	%rax, -8000072(%rbp)
	movl	-8000088(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000088(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	cltq
	addq	%rax, -8000064(%rbp)
	movl	-8000088(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000088(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	subl	%eax, %edx
	movslq	%edx, %rax
	addq	%rax, -8000056(%rbp)
	addl	$1, -8000088(%rbp)
.L4:
	cmpl	$999999, -8000088(%rbp)
	jle	.L5
~~~
3. 
~~~
	movl	$0, -8000064(%rbp)
	jmp	.L4
.L5:
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	subl	%eax, %edx
	movl	%ecx, %eax
	imull	%edx, %eax
	cltq
	addq	%rax, -8000056(%rbp)
	addl	$1, -8000064(%rbp)
.L4:
	cmpl	$999999, -8000064(%rbp)
	jle	.L5
~~~
4. 
~~~
	movl	$0, -8000064(%rbp)
	jmp	.L4
.L7:
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %eax
	cmpl	%eax, -8000060(%rbp)
	jg	.L10
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %edx
	movl	-8000064(%rbp), %eax
	cltq
	movl	-4000016(%rbp,%rax,4), %eax
	subl	%eax, %edx
	movl	%ecx, %eax
	imull	%edx, %eax
	cltq
	addq	%rax, -8000056(%rbp)
	jmp	.L6
.L10:
	nop
.L6:
	addl	$1, -8000064(%rbp)
.L4:
	cmpl	$999999, -8000064(%rbp)
	jle	.L7
~~~
5. 
~~~
	movl	$0, -8000064(%rbp)
	jmp	.L4
.L5:
	movl	-8000064(%rbp), %eax
	cltq
	movl	-8000016(%rbp,%rax,4), %eax
	cmpl	%eax, -8000060(%rbp)
	setle	%al
	movzbl	%al, %eax
	movl	-8000064(%rbp), %edx
	movslq	%edx, %rdx
	movl	-8000016(%rbp,%rdx,4), %ecx
	movl	-8000064(%rbp), %edx
	movslq	%edx, %rdx
	movl	-4000016(%rbp,%rdx,4), %edx
	addl	%ecx, %edx
	imull	%edx, %eax
	movl	-8000064(%rbp), %edx
	movslq	%edx, %rdx
	movl	-8000016(%rbp,%rdx,4), %ecx
	movl	-8000064(%rbp), %edx
	movslq	%edx, %rdx
	movl	-4000016(%rbp,%rdx,4), %edx
	subl	%edx, %ecx
	imull	%ecx, %eax
	cltq
	addq	%rax, -8000056(%rbp)
	addl	$1, -8000064(%rbp)
.L4:
	cmpl	$999999, -8000064(%rbp)
	jle	.L5
~~~

# 5. Discussion
It is interesting that going from part one to two, with 4x operations only takes 2.3x the time. I think this is due to ILP (instruction-level parallelism) where the CPU can do several instructions at the same time. This works because the four sums are independent. The CPU does not need to wait for the results from the other three sums before calculating the next term.\
Going to part three, doing all operations (except bitshift) together in one sum increases the throughput, almost halving the time. Checking the ASM output in the previous chapter, there are a lot less instructions for the 3rd part than the 2nd part.\
Adding the if statement in part four makes it considerably slower, 2.8x the time compared to part three. The ASM contains more conditional jumps and, since the numbers are random, leads to many branch mispredictions. The most interesting for me was that making the condition branchless more than halved the time of the program and now only 1.35x the time compared part three.
