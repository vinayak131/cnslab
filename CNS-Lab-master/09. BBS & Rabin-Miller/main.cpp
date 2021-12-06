/* Author : AKSHAT AGARWAL */
/*

9. Write a program to generate large random number using BBS random number generator algorithm and check whether the generated number is prime or not using RABIN-MILLER primality testing algorithm.

*/

#include <bits/stdc++.h>
using namespace std;

int randInRange(int low, int high) // excluding high and low
{
    return rand()%(high-(low+1)) + (low+1) ;
}

int genPrime3mod4()
{
    while(true)
    {
        int num = randInRange(10000,100000); // to generate large random number
        if(num%4 != 3) continue;

        bool prime = true;
        for(int i=2; i<=sqrt(num); i++)
        {
            if(num % i == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime) return num;
    }
}

int bbs(int p, int q)
{
    long long n = (long long)p*q ;

    long long s; // non-zero and relatively prime to n
    do{ s = rand(); } while(s%p==0 || s%q==0 || s==0);

    int B = 0;
    long long x = (s*s) % n;
    for(int i=0; i<10; i++) // to generate 10 bit output
    {
        x = (x*x) % n;
        B = B<<1 | (x & 1); // x%2 = x&1
    }

    if(B==0) return bbs(p,q); // check that the number generated should not be zero
    cout<<"Blum Blum Shub"<<endl<<"--------------"<<endl;
    cout<<"p = "<< p <<"\nq = "<< q <<"\nn = "<< n <<"\ns = "<< s <<endl;
    return B;
}

// (a pow b) % n
int powModN(int a, int b, int n)
{
	int res=1;
	for(int i=0; i<b; i++)
	{
        res = (res * a) % n;
	}
	return res;
}

string rabinMiller(int n)
{
    int k = 0;        // power of 2
    int q = n-1;      // q -> odd
    while(q % 2 == 0) // n-1 = 2^k * q
    {
        q = q/2 ;
        k++ ;
    }

    int a = randInRange(1, n-1);

    cout << "\nRabin Miller(" << n << ")\n-----------------" << endl;
    cout << n-1 << " = 2^" << k << " * " << q << endl;
    cout << "k = " << k << "\nq = " << q << "\na = " << a << endl;

    // if (a pow q)%n == 1
    if(powModN(a,q,n) == 1) return "inconclusive";

    for(int j=0; j<k ; j++)
    {
        if(powModN(a, pow(2,j)*q, n) == n-1) return "inconclusive";
    }
    return "composite";
}

int main()
{
    srand(time(NULL));
    int p = genPrime3mod4(); // large prime number (p%4=3)
    int q = genPrime3mod4(); // large prime number (q%4=3)
    int randNum = bbs(p, q);
    cout << "Random number generated by BBS = " << randNum << endl;

    cout << rabinMiller(randNum) << endl ;
}

/*************** output-1 **************
Blum Blum Shub
--------------
p = 10223
q = 34543
n = 353133089
s = 22252
Random number generated by BBS = 443

Rabin Miller(443)
-----------------
442 = 2^1 * 221
k = 1
q = 221
a = 81
Inconclusive
****************************************/

/**************** output-2 **************
Blum Blum Shub
--------------
p = 25447
q = 41983
n = 1068341401
s = 27864
Random number generated by BBS = 982

Rabin Miller(982)
-----------------
981 = 2^0 * 981
k = 0
q = 981
a = 234
Composite
****************************************/
