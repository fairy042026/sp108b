int power(int a, int b){
    int pow=1;
    for (int i = b; i > 0; i--)pow*= a;
    return pow;
}