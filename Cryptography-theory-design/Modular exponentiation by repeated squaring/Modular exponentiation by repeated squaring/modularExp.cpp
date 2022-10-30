#include<stdio.h>
#include<gmp.h>
#include<string.h>

mpz_t pMulq;
//mpz_t cmpNum1, cmpNum2; Unuse for the isParaCorrect func.
char eBinary[10000];
int pointerOfEbinary;

void expmodRecursion(mpz_t m, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul);
bool isParaCorrect(const mpz_t e, const mpz_t p, const mpz_t q);
void expmodIteration(mpz_t m, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul);
void expmodFast(mpz_t n, mpz_t e, mpz_t m, mpz_t retNum);

int main() {
	mpz_t e, m, p, q;
	int dataNum;
	// initialize.
	mpz_init(e);
	mpz_init(m);
	mpz_init(p);
	mpz_init(q);
	mpz_init(pMulq);
	/* for the isParaCorrect func, unuse.
	mpz_set_str(cmpNum1, "65536", 10);
	mpz_set_str(cmpNum2, "2147483648", 10); // cmpNum2 = 2^31.
	*/
	scanf("%d", &dataNum);
	for (int i = 0; i < dataNum; i++) {
		mpz_t rop1, retMul;
		mpz_inits(rop1, retMul, NULL);
		gmp_scanf("%Zd%Zd%Zd%Zd", e, m, p, q);
		mpz_mul(pMulq, p, q); // pMulq = p * q;
		mpz_get_str(eBinary, 2, e); // Convert e to it's binary form.
		pointerOfEbinary = strlen(eBinary) - 1; // pointerOfBinary points to the last bit of e.
		mpz_init_set_ui(rop1, 1u); // rop1 = 1.
		mpz_init_set_ui(retMul, 1u); // retMul = 1.
		expmodRecursion(m, pMulq, pointerOfEbinary, rop1, retMul); // retMul is what we need.
		//expmodFast(pMulq, e, m, retMul);
		gmp_printf("%Zd", retMul);
		printf("\n");
	}
	return 0;
}
/* These threee funcs all work well.*/
void expmodRecursion(mpz_t m, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul) {
	// rop1 = 1, retMul = 1, n = p*q, pointer = lenth of eBinary - 1, m = m.
	// base.
	mpz_mul(rop1, rop1, rop1); // rop1 = rop1^2.
	mpz_mod(rop1, rop1, n); // rop1 = rop1 mod n.
	if (!mpz_cmp_ui(rop1, 1u)) { // rop1 == 1.
		mpz_mul(rop1, rop1, m); // rop1 = m, when first run into this function, gives rop1 a m.
	}
	if (eBinary[pointer] == '1') { // NOTION it's char '1'.
		mpz_mul(retMul, retMul, rop1); // retMul = retMul * rop1 .
		mpz_mod(retMul, retMul, n); // retMul = retMul mod n.
	}
	if (!pointer) { // pointer == 0.
		return;
	}
	expmodRecursion(m, n, pointer - 1, rop1, retMul);
}

void expmodIteration(mpz_t m, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul) {
	// rop1 = 1, retMul = 1, n = p*q, pointer = lenth of eBinary - 1, m = m.
	mpz_set(rop1, m); // rop1 = m.
	if (pointer <= 0) {
		return;
	}
	if (eBinary[pointer] == '1') {
		mpz_mul(retMul, retMul, rop1); // retMul = 1 * m
		mpz_mod(retMul, retMul, n); // retMul = retMul mod n.
	}
	if (pointer <= 0) {
		return;
	}
	for (int j = pointer - 1; j >= 0; j--) {
		mpz_mul(rop1, rop1, rop1); // rop1 = rop1 * rop1.
		mpz_mod(rop1, rop1, n); // rop1 = rop1 mod n.
		if (eBinary[j] == '1') {
			mpz_mul(retMul, retMul, rop1); // retMul = retMul * rop1.
			mpz_mod(retMul, retMul, n); // retMul = retMul mod n.
		}
	}
	// Set array's items to zero.
	for (int k = 0; k <= pointerOfEbinary; k++) {
		eBinary[k] = '\0';
	}
}


void expmodFast(mpz_t n, mpz_t e, mpz_t m, mpz_t retNum) {
	// n = p * q, e = e, m = m, retMul = 1.
	mpz_t rop1, mExp, lsb, rop4;
	mpz_inits(rop1, mExp, lsb, rop4, NULL);
	mpz_init_set_ui(rop1, 1u); // rop1 = 1
	mpz_set(mExp, m); // mExp = m
	while (mpz_cmp_ui(e, 0) != 0) { // e >= 0.
		mpz_and(lsb, e, rop1); // lsb = e & 1.
		if (mpz_cmp_ui(lsb, 1u) == 0) { // the lowest bit of e is 1.
			mpz_mul(retNum, retNum, mExp); // retNum = retNum * mExp.
			mpz_mod(retNum, retNum, n); // retNum = retNum mod n. 
		}
		mpz_mul(mExp, mExp, mExp); // mExp = mExp^2.
		mpz_mod(mExp, mExp, n); // mExp = mExp mod n.
		mpz_fdiv_q_ui(e, e, 2); // e = e >> 1.
	}
}
/** Check the given parameters are correct or not.
  * In this test, the check func isn's need.
  * Cause the test has promised the parameters to be correct.
  */
/*
bool isParaCorrect(const mpz_t e, const mpz_t p, const mpz_t q) {
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
	mpz_sub(rop3, p, q); // rop3 = p - q. // UNUSE.
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
*/

/*	NOTIONS:
		All the three funcs could work well.
		The reason for time limit exceeding is I create a small array
		At first, the sizeof array eBinary is 2050,but it is not big enough, so crach into TLE.
	REFERENT LINKS:
		1. https://github.com/LoveCamille/Cryptography-CourseProject/blob/main/%E6%A8%A1%E9%87%8D%E5%A4%8D%E5%B9%B3%E6%96%B9.c
		2. https://blog.csdn.net/watqw/article/details/123831104
*/
