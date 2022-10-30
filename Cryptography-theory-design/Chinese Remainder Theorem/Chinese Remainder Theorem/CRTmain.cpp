#include<stdio.h>
#include<gmp.h>
#include<string.h>
#include<iostream>

mpz_t* mpzArray = new mpz_t[10000];
mpz_t pMulq, faiN;
char dBinary[10000];
int pointerOfDbinary;

void expmodRecursion(mpz_t c, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul);
void expmodIteration(mpz_t c, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul);
void expmodFast(mpz_t n, mpz_t d, mpz_t c, mpz_t retNum);
void getd(mpz_t e, mpz_t p, mpz_t q, mpz_t d, mpz_t faiN);
void precomputedDExp(mpz_t n, mpz_t d, mpz_t c);
void CRTsolveRSA(mpz_t p, mpz_t q, mpz_t retNum, mpz_t n, mpz_t c, mpz_t d);
int main() {
	mpz_t e, c, p, q, d;
	int dataNum;
	// initialize.
	mpz_init(e);
	mpz_init(c);
	mpz_init(p);
	mpz_init(q);
	mpz_init(d);
	mpz_init(pMulq);
	mpz_init(faiN);

	scanf("%d", &dataNum);
	gmp_scanf("%Zd%Zd%Zd", p, q, e);
	mpz_mul(pMulq, p, q); // pMulq = p * q;
	getd(e, p, q, d, faiN); // Get d.
	if (mpz_cmp(d, faiN) > 0) { // Extension of the Euler's Theorem.
		mpz_mod(d, d, faiN);
		mpz_add(d, d, faiN);
	}
	mpz_get_str(dBinary, 2, d); // Convert d to it's binary form.
	pointerOfDbinary = strlen(dBinary) - 1; // pointerOfDbinary points to the last bit of d.

	for (int i = 0; i < dataNum; i++) {
		int pointer1 = pointerOfDbinary;
		mpz_t rop1, dV2, retMul;
		mpz_inits(rop1, dV2, retMul, NULL);
		mpz_set(dV2, d);
		gmp_scanf("%Zd", c);
		mpz_init_set_ui(rop1, 1u); // rop1 = 1.
		mpz_init_set_ui(retMul, 1u); // retMul = 1.
		//expmodRecursion(c, pMulq, pointer1, rop1, retMul); // retMul is what we need.
		//expmodIteration(c, pMulq, pointer1, rop1, retMul); // Iteration version.
		//expmodFast(pMulq, dV2, c, retMul);
		CRTsolveRSA(p, q, retMul, pMulq, c, dV2);
		gmp_printf("%Zd", retMul);
		printf("\n");
	}
	return 0;
}
/* These threee funcs all work well.*/
void expmodRecursion(mpz_t c, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul) {
	// rop1 = 1, retMul = 1, n = p*q, pointer = lenth of dBinary - 1, c = c.
	// general.
	mpz_mul(rop1, rop1, rop1); // rop1 = rop1^2.
	mpz_mod(rop1, rop1, n); // rop1 = rop1 mod n.
	if (!mpz_cmp_ui(rop1, 1u)) { // rop1 == 1.
		mpz_mul(rop1, rop1, c); // rop1 = c, when first run into this function, gives rop1 a c.
	}
	if (dBinary[pointer] == '1') { // NOTION it's char '1'.
		mpz_mul(retMul, retMul, rop1); // retMul = retMul * rop1.
		mpz_mod(retMul, retMul, n); // retMul = retMul mod n.
	}
	// base.
	if (!pointer) { // pointer == 0.
		return;
	}
	expmodRecursion(c, n, pointer - 1, rop1, retMul);
}

void expmodIteration(mpz_t c, mpz_t n, int pointer, mpz_t rop1, mpz_t retMul) {
	// rop1 = 1, retMul = 1, n = p*q, pointer = lenth of dBinary - 1, c = c.
	mpz_set(rop1, c); // rop1 = c.
	if (pointer <= 0) {
		return;
	}
	if (dBinary[pointer] == '1') {
		mpz_mul(retMul, retMul, rop1); // retMul = 1 * c
		mpz_mod(retMul, retMul, n); // retMul = retMul mod n.
	}
	if (pointer <= 0) {
		return;
	}
	for (int j = pointer - 1; j >= 0; j--) {
		mpz_mul(rop1, rop1, rop1); // rop1 = rop1 * rop1.
		mpz_mod(rop1, rop1, n); // rop1 = rop1 mod n.
		if (dBinary[j] == '1') {
			mpz_mul(retMul, retMul, rop1); // retMul = retMul * rop1.
			mpz_mod(retMul, retMul, n); // retMul = retMul mod n.
		}
	}
}


void expmodFast(mpz_t n, mpz_t d, mpz_t c, mpz_t retNum) {
	// n = p * q, d = d, c = c, retMul = 1.
	mpz_t rop1, cExp, lsb;
	mpz_inits(rop1, cExp, lsb, NULL);
	mpz_init_set_ui(rop1, 1u); // rop1 = 1
	mpz_set(cExp, c); // cExp = c
	while (mpz_cmp_ui(d, 0) != 0) { // d >= 0.
		mpz_and(lsb, d, rop1); // lsb = d & 1.
		if (mpz_cmp_ui(lsb, 1u) == 0) { // the lowest bit of d is 1.
			mpz_mul(retNum, retNum, cExp); // retNum = retNum * cExp.
			mpz_mod(retNum, retNum, n); // retNum = retNum mod n. 
		}
		mpz_mul(cExp, cExp, cExp); // cExp = cExp^2.
		mpz_mod(cExp, cExp, n); // cExp = cExp mod n.
		mpz_fdiv_q_ui(d, d, 2); // d = d >> 1.
	}
}

void getd(mpz_t e, mpz_t p, mpz_t q, mpz_t d, mpz_t faiN) {
	// n = p * q, d = retNum.
	mpz_t rop1, rop2;
	mpz_inits(rop1, rop2, NULL);
	mpz_sub_ui(rop1, p, 1u); // rop1 = p - 1.
	mpz_sub_ui(rop2, q, 1u); // rop2 = q - 1.
	mpz_mul(faiN, rop1, rop2); // faiN = (p-1)*(q-1).
	mpz_invert(d, e, faiN); // get e's invertion by mod faiN.
}

// Precomputed c's exp. eg. c c^2 c^4 c^16... !!! Ignoring C's different between each other, so useless.
void precomputedDExp(mpz_t n, mpz_t d, mpz_t c) {
	// n = p * q, d = d, c = c, retMul = 1.
	int i = 0;
	mpz_t cExp;
	mpz_init(cExp);
	mpz_set(cExp, c); // cExp = c
	while (mpz_cmp_ui(d, 0) != 0) { // d >= 0.
		mpz_init(mpzArray[i]);
		mpz_set(mpzArray[i], cExp);
		mpz_mul(cExp, cExp, cExp); // cExp = cExp^2.
		mpz_mod(cExp, cExp, n); // cExp = cExp mod n.
		mpz_fdiv_q_ui(d, d, 2); // d = d >> 1.
		i++;
	}
}

/* By using extension of the Euler's theorem to simplify the caculation.*/
void simplify(mpz_t faiN, mpz_t d, mpz_t retD) {
	mpz_set(retD, d); // retD = d.
	if (mpz_cmp(d, faiN) > 0) {
		;
	}

}

void CRTsolveRSA(mpz_t p, mpz_t q, mpz_t retNum, mpz_t n, mpz_t c, mpz_t d) {
	// p = p, q = q, retNum = 1, n = pMulq.
	mpz_t dp, dq, qInv;
	mpz_t rop1, rop2, rop3, rop4, h, rop5, rop6;
	mpz_t m1, m2;
	mpz_inits(dp, dq, qInv, rop1, rop2, rop3, rop4, h, rop5, rop6, NULL);
	mpz_init_set_ui(m1, 1);
	mpz_init_set_ui(m2, 1);
	mpz_sub_ui(rop1, p, 1); // rop1 = p - 1.
	mpz_sub_ui(rop2, q, 1); // rop2 = q - 1.
	mpz_mod(dp, d, rop1); // dp = d mod p-1.
	mpz_mod(dq, d, rop2); // dq = d mod q-1.
	mpz_invert(qInv, q, p); // qInv = q^(-1) mod p.
	expmodFast(n, dp, c, m1);
	expmodFast(n, dq, c, m2);
	mpz_sub(rop3, m1, m2); // rop3 = m1 - m2.
	mpz_mul(rop4, qInv, rop3); // rop4 = qInv * (m1 - m2).
	mpz_mod(h, rop4, p); // h = rop4 mod p.
	mpz_mul(rop5, h, q); // rop5 = hq.
	mpz_add(rop6, m2, rop5); // rop6 = m2 + h*q.
	mpz_mod(retNum, rop6, n); // retNum = (m2 + h*q) mod n.
}