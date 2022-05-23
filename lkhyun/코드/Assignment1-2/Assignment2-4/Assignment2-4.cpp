#include <iostream>
using namespace std;
int recursion_func(int i, int n)
{
    if (n > i)
    {
        return 0;
    }
    else
    {
        return (n)+recursion_func(i, n + 1) + recursion_func(i, n + 1);
    }

}
int main()
{
    int a;
    int num = 0;
    cout << "Enter Any Positive Number: ";
    cin >> a;
    cout << recursion_func(a, num);
    return 0;

}