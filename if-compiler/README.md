# Compiler

```
D:\Users\User\Desktop\sp\if-compiler>make
gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler

D:\Users\User\Desktop\sp\if-compiler>compiler.exe test\if.c
a=1;
b=2;
if (a < 0){
    b = b + 1;
}
========== lex ==============
token=a
token==
token=1
token=;
token=b
token==
token=2
token=;
token=if
token=(
token=a
token=<
token=0
token=)
token={
token=b
token==
token=b
token=+
token=1
token=;
token=}
========== dump ==============
0:a
1:=
2:1
3:;
4:b
5:=
6:2
7:;
8:if
9:(
10:a
11:<
12:0
13:)
14:{
15:b
16:=
17:b
18:+
19:1
20:;
21:}
============ parse =============
t0 = 1
a = t0
t1 = 2
b = t1
t2 = a
t3 = 0
t4 = t2 < t3
if not T4 goto L0
t5 = b
t6 = 1
t7 = t5 + t6
b = t7
(L0)
```
