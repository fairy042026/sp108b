# 習題：編譯器加上 IF 的語法

## 測試範例

```
a = 3;
b = 5;
if (a > b)
   t = a;

else 
  t = b;

```

## 測試中遇到的問題

ˋˋˋ
一開始寫好了程式碼然後執行，卻發現無論怎麼更改程式碼，執行的結果都不會變
剛開始我以為是我的程式碼有錯，請學姊幫忙看，但整個程式的邏輯是沒問題的
於是我去請教老師，找到了問題。

無論怎麼執行，執行結果都不變是因為，在執行之前，需要先做一個動作：make
--> ming32-make

執行此指令之後，程式碼就可以正常執行了，跑出來的結果也沒問題。

ˋˋˋ

## 執行方法
1.在compiler.c點右鍵-open in terminal
2.先執行mingw32-make，不然可能會出現上述問題
3.執行./compiler.c test/sum.c(sum.c是放置測試範例的檔案，存在test資料夾裡)


## 執行結果
ˋˋˋ
========== lex ==============
token=a
token==
token=3
token=;
token=b
token==
token=5
token=;
token=if
token=(
token=a
token=>
token=b
token=)
token=t
token==
token=a
token=;
token=else
token=t
token==
token=b
token=;
========== dump ==============
0:a
1:=
2:3
3:;
4:b
5:=
6:5
7:;
8:if
9:(
10:a
11:>
12:b
13:)
14:t
15:=
16:a
17:;
18:else
19:t
20:=
21:b
22:;
============ parse =============
t0 = 3
a = t0
t1 = 5
b = t1
t2 = a
t3 = b
t4 = t2 > t3
if not T4 goto L0
t5 = a
t = t5
goto L1
(L0)
t6 = b
t = t6
(L1)
ˋˋˋ
