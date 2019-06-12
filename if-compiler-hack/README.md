# Compiler

```
D:\Users\User\Desktop\sp\if-compiler-hack>make
gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler

D:\Users\User\Desktop\sp\if-compiler-hack>compiler.exe test\while.c
i = 1;
while (i<10) i = i + 1;

========== lex ==============
token=i
token==
token=1
token=;
token=while
token=(
token=i
token=<
token=10
token=)
token=i
token==
token=i
token=+
token=1
token=;
========== dump ==============
0:i
1:=
2:1
3:;
4:while
5:(
6:i
7:<
8:10
9:)
10:i
11:=
12:i
13:+
14:1
15:;
============ parse =============
@1
D = A
@t0
M = D
@t0
D = M
@i
M = D
(L0)
@i
D = A
@t1
M = D
@10
D = A
@t2
M = D
@t2
D = M
@t3
M = D
@t1
D = M
@t3
M = D < M
@t3
D = M
@L1
D; JEQ
@i
D = A
@t4
M = D
@1
D = A
@t5
M = D
@t5
D = M
@t6
M = D
@t4
D = M
@t6
M = D + M
@t6
D = M
@i
M = D
@L0
0; JMP
(L1)
```
