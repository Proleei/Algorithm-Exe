#include<stdio.h>
#include<gmp.h>
#include<iostream>

bool isSecurity(const mpz_t e, const mpz_t p, const mpz_t q);

mpz_t cmpNum1, cmpNum2; //used for compare.
int main() {
	int dataNum;
	mpz_t e, p, q;
	mpz_t n, faiN, d;
	mpz_t rop1, rop2;
	//initialize these mpz_t vars = 0.
	mpz_init(e);
	mpz_init(p);
	mpz_init(q);
	mpz_init(n);
	mpz_init(faiN);
	mpz_init(d);
	mpz_init(rop1);
	mpz_init(rop2);
	mpz_set_str(cmpNum1, "65536", 10);
	mpz_set_str(cmpNum2, "2147483648", 10); // cmpNum2 = 2^31.
	scanf("%d", &dataNum);
	for (int i = 0; i < dataNum; i++) {
		gmp_scanf("%Zd%Zd%Zd", e, p, q);
		if (isSecurity(e, p, q)) {
			mpz_mul(n, p, q); // n = p * q.
			mpz_sub_ui(rop1, p, 1u); // rop1 = p - 1.
			mpz_sub_ui(rop2, q, 1u); // rop2 = q - 1.
			mpz_mul(faiN, rop1, rop2); // faiN = (p-1)*(q-1).
			mpz_invert(d, e, faiN); // get e's invertion by mod faiN.
			gmp_printf("%Zd", d);
			printf("\n");
		}
		else {
			printf("ERROR\n");
		}
	}
	return 0;
}

bool isSecurity(const mpz_t e, const mpz_t p, const mpz_t q) {
	mpz_t rop1, rop2, rop3, rop4, rop5, rop6;
	mpz_t rop7, rop8, rop9, rop10;
	mpz_init(rop1);
	mpz_init(rop2);
	mpz_init(rop3);
	mpz_init(rop4);
	mpz_init(rop5);
	mpz_init(rop6);
	mpz_init(rop7);
	mpz_init(rop8);
	mpz_init(rop9);
	mpz_init(rop10);
	mpz_mul(rop1, p, q); // rop1 = p * q.
	mpz_sqrt(rop2, rop1); // rop2 = (p * q)^(1 / 2).
	mpz_sub(rop3, p, q); // rop3 = p - q. // Unuse.
	mpz_sub(rop4, rop2, p); // rop4 = sqrt(p*q) - p
	mpz_abs(rop5, rop4); // rop5 = |sqrt(p*q) - p|

	mpz_sub_ui(rop6, p, 1u); // rop6 = p - 1.
	mpz_sub_ui(rop7, q, 1u); // rop7 = q - 1.
	mpz_mul(rop9, rop6, rop7); // rop9 = (p - 1) * (q - 1).
	mpz_gcd(rop10, rop9, e); // rop10 = gcd((p - 1) * (q - 1), e).
	mpz_gcd(rop8, rop6, rop7); // rop8 = gcd(p-1 , q-1).
	if (mpz_cmp(e, cmpNum1) <= 0) { // e < 65536.
		return false;
	}
	else if (mpz_cmp(rop5, cmpNum2) <= 0 || mpz_cmp(p, q) == 0) { // p's too close with q.
		return false;
	}
	else if (mpz_probab_prime_p(p, 40) < 1 || mpz_probab_prime_p(q, 40) < 1) { // p or q isn's a prime.
		return false;
	}
	else if (mpz_cmp_ui(rop10, 1u) > 0) { // (p-1)*(q-1) and e aren't coprime.
		return false;
	}
	else if (mpz_cmp_ui(rop8, 20u) > 0) { //if gcd(p-1, q-1) > 20, too smooth.
		return false;
	}
	else {
		return true;
	}
}

/** Some referent links.
  * 1.https://gmplib.org/manual/Integer-Functions
  * 2.https://blog.csdn.net/p_s_p/article/details/118554163
  * 3.https://blog.csdn.net/qq_43434682/article/details/108663070
  */
