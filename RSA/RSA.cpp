/*
     By: Abadali Sheikh
     RSA Algorithm implementation
     Source credit for inverse modulo method:
     https://www.rookieslab.com/
*/

#include <iostream>
#include <vector>
using namespace std;

bool isPrime(long int);
int SelectCoPrime(int);
void RSAImplementation (int, int);
vector<long long> extended_euclid_gcd(long long, long long);
long long modulo_multiplicative_inverse(long long, long long);
int gcd(int, int);

/*
 Driver function: Inputs two prime numbers,
 calls to isPrime to test if prime, then calls RSAImplementation
*/
int main(int argc, const char * argv[]) {
    long int num1, num2;
    cout << "Please enter 2 prime numbers: ";
    cin >> num1 >> num2;
    
    while(!isPrime(num1) || !isPrime(num2)) {
        cout << "Numbers are not prime, try again: " ;
        cin >> num1 >> num2;
    }
    RSAImplementation(num1, num2);
    
    return 0;
}

// Checks if number is prime
bool isPrime(long int number)
{
    for(long i = 2; i*i <= number; i++)
    {
        if(number % i == 0)
        {
            return false;
            break;
        }
    }
    return true;
}

// Euclids extended GCD algorithm used for inverse mod
vector<long long> extended_euclid_gcd(long long a, long long b) {
    // Returns a vector `result` of size 3 where:
    // Referring to the equation ax + by = gcd(a, b)
    // result[1] is x
    
    long long s = 0; long long old_s = 1;
    long long t = 1; long long old_t = 0;
    long long r = b; long long old_r = a;
    
    while(r != 0) {
        long long quotient = old_r/r;
        // We are overriding the value of r, before that we store it's current
        // value in temp variable, later we assign it to old_r
        long long temp = r;
        r = old_r - quotient*r;
        old_r = temp;
        
        // We treat s and t in the same manner we treated r
        temp = s;
        s = old_s - quotient*s;
        old_s = temp;
        
        temp = t;
        t = old_t - quotient*t;
        old_t = temp;
    }
    vector<long long> result;
    result.push_back(old_r);
    result.push_back(old_s);
    result.push_back(old_t);
    return result;
}

//calculate inverse modulo using Extended-Euclid algorithm
long long modulo_multiplicative_inverse(long long A, long long M) {
    // A and M are co-prime
    // Returns multiplicative modulo inverse of A under M
    
    // Find gcd using Extended Euclid's Algorithm
    vector<long long> v = extended_euclid_gcd(A, M);
    long long x = v[1];
    
    // In case x is negative, we handle it by adding extra M
    // Because we know that multiplicative inverse of A in range M lies
    // in the range [0, M-1]
    if(x < 0) {
        x += M;
    }
    return x;
}

//Selects a value for e, which is coprime to ø, such that 1 < e < ø
int SelectCoPrime(int bound){
    int num = 0;
    for (int i = 2; i < bound; i++) {
        if (gcd(i,bound) == 1){
            num = i;
            break;
        }
    }
    return num;
}

// Compute GCD of any two numbers
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

//RSA function returns public & private keys
/*
     1) select two prime numbers p,q and set N = p*q
     2) compute ø = (p-1)(q-1)
     3) now select e, which is coprime to ø, such that 1 < e < ø
     coprime iff gcd(e,ø) = 1
     4) secret key d is the inverse of e modulo ø
*/
void RSAImplementation (int prime1, int prime2) {
    // compute public key
    int N = prime1 * prime2;
    int upperBound = (prime1-1)*(prime2-1);
    // need an exponent that is coprime to N and 1 < exponent < upperBound.
    int exponent = SelectCoPrime(upperBound);
    // public key
    cout << "Public Key (N,e): " << N << "," << exponent << endl;
    //calculate inverse of e modulo upperBound, k, for private key
    int k = modulo_multiplicative_inverse(exponent, upperBound);
    cout << "Private Key (N,d): " << N << "," << k << endl;
}
