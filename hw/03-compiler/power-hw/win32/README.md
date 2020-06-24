# 方法

```
創建一個power.c的檔案，然後把程式碼寫在裡面並儲存
在jitCall.c檔的最下面增加一段程式碼

int (*power)(int a, int b);


int main() 
{
  power = (int (*)(int, int))powcode;
  printf("pow(7, 2)=%d\n", power(7,2));

}

pow( , )的數字就可以算出平方值

```

## 執行結果

```
PS C:\Users\user\Desktop\110710519\co108a\sp108b\hw\03-compiler\power-hw\win32> gcc jitCall.c -o jitCall
PS C:\Users\user\Desktop\110710519\co108a\sp108b\hw\03-compiler\power-hw\win32> ./jitCall

pow(7, 2)=49

```
