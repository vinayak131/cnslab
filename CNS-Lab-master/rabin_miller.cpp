#include <bits/stdc++.h>
using namespace std;

int randInRange(int low, int high) // excluding high and low
{
    return rand() % (high - (low + 1)) + (low + 1);
}

int genPrime3mod4()
{
    while (true)
    {
        int num = randInRange(10000, 100000); // to generate large random number
        if (num % 4 != 3)
            continue;

        bool prime = true;
        for (int i = 2; i <= sqrt(num); i++)
        {
            if (num % i == 0)
            {
                prime = false;
                break;
            }
        }
        if (prime)
            return num;
    }
}

// (a pow b) % n
int powModN(int a, int b, int n)
{
    int res = 1;
    for (int i = 0; i < b; i++)
    {
        res = (res * a) % n;
    }
    return res;
}

string rabinMiller(int n)
{
    int k = 0;         // power of 2
    int q = n - 1;     // q -> odd
    while (q % 2 == 0) // n-1 = 2^k * q
    {
        q = q / 2;
        k++;
    }

    int a = randInRange(1, n - 1);

    cout << "\nRabin Miller(" << n << ")\n-----------------" << endl;
    cout << n - 1 << " = 2^" << k << " * " << q << endl;
    cout << "k = " << k << "\nq = " << q << "\na = " << a << endl;

    // if (a pow q)%n == 1
    if (powModN(a, q, n) == 1)
        return "inconclusive";

    for (int j = 0; j < k; j++)
    {
        if (powModN(a, pow(2, j) * q, n) == n - 1)
            return "inconclusive";
    }
    return "composite";
}

int main()
{
    srand(time(NULL));
    int p = genPrime3mod4(); // large prime number (p%4=3)
    int q = genPrime3mod4(); // large prime number (q%4=3)

    cout << rabinMiller(27) << endl;
}