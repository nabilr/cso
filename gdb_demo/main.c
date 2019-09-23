int main(int argc, char **argv)
{
    int res;
    int num1 = 10;
    int num2 = 20;

    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;

    res = sum(num1,num2);
    print_result(num1, num2, res);
    return 0;
}

