#include <iostream>
#include <string>
#include "BigNumber.h"
#include "grand.h"
#include <stdlib.h>
#include <sstream>

using namespace std;
using namespace pr0crustes;

class RSA {
private:
	BigNumber p, q, n, phi, e, d, a, b, pb, m, c, dec, cipher;
	string enc;
public:
	void setprivate(BigNumber t) {
		d = t;
	}
	BigNumber getprivate() {
		return d;
	}
	void setpublic(BigNumber t) {
		e = t;
	}
	BigNumber getpublic() {
		return e;
	}
	void setcipher(BigNumber t) {
		cipher = t;
	}
	BigNumber getcipher() {
		return cipher;

	}
	void setn(BigNumber t) {
		n = t;
	}
	BigNumber getn() {
		return n;
	}
	void generatePrime() {
		cout << "Generating prime number......" << endl;
		//p = BigNumber::randomBigNumberInRange(2000, 3000);
		//q = BigNumber::randomBigNumberInRange(2000, 3000);
		p = 101;
		q = 103;
		while (checkPrime(p) == 0 || checkPrime(q) == 0) {
			p = BigNumber::randomBigNumberInRange(2000, 3000);
			q = BigNumber::randomBigNumberInRange(2000, 3000);

			if (checkPrime(p) == 0 && checkPrime(q) == 1) {
				while (checkPrime(p) == 0) {
					p = BigNumber::randomBigNumberInRange(2000, 3000);
				}
			}
			else if (checkPrime(p) == 1 && checkPrime(q) == 0) {
				while (checkPrime(q) == 0) {
					q = BigNumber::randomBigNumberInRange(2000, 3000);
				}
			}
			cout << "Prime number p: " << p << " & q: " << q << endl;
		}
	}
	bool checkPrime(BigNumber p) {
		if (p <= 1) return false;
		if (p <= 3) return true;

		//this is checked so that we can skip
		//middle five numbers in below loop
		if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0) return false;

		for (BigNumber i = 5; i <= p - 3; i = i + 6)
			if (p % i == 0 || p % (i + 2) == 0)
				return false;

		return true;
	}
	BigNumber gcd(BigNumber a, BigNumber b)
	{
		BigNumber result = min(a, b); // Find Minimum of a nd b
		while (result > 0) {
			if (a % result == 0 && b % result == 0) {
				break;
			}
			result--;
		}
		return result; // return gcd of a nd b
	}

	void calculate() {
		cout << "Calculating public key......" << endl;
		BigNumber temp;
		n = p * q;
		phi = (p - 1) * (q - 1);
		temp = BigNumber::randomBigNumberInRange(2000, 3000);
		while (1) {
			if (gcd(temp, phi) == 1) {
				break;
			}
			temp++;
		}
		e = temp;
		cout << "Public key is <" << e << ", " << n << ">" << endl;
		long long int a1 = 1, a2 = 0, a3;
		long long int b1 = 0, b2 = 1, b3;
		long long int d1 = phi.asLongLong(), d2 = e.asLongLong(), d3 = 0, k;
		cout << "d1: " << d1 << ", d2: " << d2 << endl;
		while (d3 != 1) {
			k = d1 / d2;
			cout << "k: " << k << endl;
			a3 = a1 - (a2 * k);
			b3 = b1 - (b2 * k);
			d3 = d1 - (d2 * k);
			a1 = a2;
			b1 = b2;
			d1 = d2;
			a2 = a3;
			b2 = b3;
			d2 = d3;
			cout <<"a1: " << a1 <<  ", b3: " << b3 << ", d3: " << d3 << endl;
		}
		if (b3 > phi.asLongLong()) {
			d = b3 % phi.asLongLong();
		}
		else if (b3 < 0) {
			d = b3 + phi.asLongLong();

		}
		else {
			d = b3;
		}
		cout << "Private key is <" << d << ", " << n << ">" << endl;
	}
	void encrypt(string m) {
		cout << "Encrypting plain text....." << endl;
		for (int i = 0; i < m.length(); i++) {
			char c = m[i];
			string a = to_string(int(c));
			enc += a;
		}
	}
	void encode() {
		BigNumber temp;
		stringstream ss;
		ss << enc;
		ss >> temp;
		BigNumber temp1;
		cout << "A: " << e << ", " << d << endl;
		temp1 = temp.modPow(e, n);
		cipher = temp1;
		cout << "Encrypted Cipher Text: " << temp1 << endl;
	}
	void decode() {
		cout << "Decrypting Cipher Text....." << endl;
		cout << "cipher: " << cipher << ", d: " << d << ", n : " << n << endl;
		BigNumber message = cipher.modPow(d, n);
		dec = message;
	}

	void decrypt() {
		int i = 0;
		int a = 3, b = 2;
		string result, finalresult;
		string decstr = dec.asString();
		while (i != decstr.length()) {
			if (decstr[i] == '1') {
				string temp;
				int num = 0;
				while (a) {
					temp = temp + decstr[i];
					a--;
					i++;
				}
				stringstream ss;
				ss << temp;
				ss >> num;
				result = char(num);
				cout << result << endl;
			}
			else {
				string temp;
				int num = 0;
				while (b) {
					temp = temp + decstr[i];
					//cout << "temp: " << temp << ", decsrt[i]: " << decstr[i] << ", b: " << b << ", i: " << i << endl;
					b--;
					i++;
				}
				stringstream ss;
				ss << temp;
				ss >> num;
				//cout << "num: " << num << ", i: " << i << endl;
				result = char(num);
				cout << result << endl;
			}
			if (a == 0 || b == 0) {
				a = 3;
				b = 2;
			}
			finalresult += result;
		}
		cout << "Decryted plain text: " << finalresult << endl;
	}
};

class Clients {
private:
	string name;
	string message;
public:
	RSA rsa;
	void setmessage(string m) {
		message = m;
	}
	string getmessage() {
		return message;
	}
	void send(string m) {
		cout << "m: " << m << endl;
		rsa.generatePrime();
		rsa.calculate();
		rsa.encrypt(m);
		rsa.encode();
	}
	void receive() {
		rsa.decode();
		rsa.decrypt();
	}
};



int main() {
	Clients Alice, Bob;
	RSA rsa;
	string m;
	cout << "Enter the message you want to encrypt: " << endl;
	getline(cin, m);
	Alice.setmessage(m);
	Alice.send(Alice.getmessage());
	Alice.receive();
	/*Bob.setmessage(m);
	Bob.send(Bob.getmessage());
	cout << "B: " << rsa.getprivate() << endl;
	Alice.receive();*/
	return 0;
}