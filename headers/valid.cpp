#define lli long long int

bool isValidNum(lli num)
{
    for (int i = 0; i < 10; i++)
    {
        if (num == 0)
            return false;

        if ((num % 10) < 0 || (num % 10) > 9)
            return false;

        num /= 10;
    }

    return true;
}

bool isValidOp(int op, int n)
{
    if (op < 1 || op > n)
        return false;
    return true;
}