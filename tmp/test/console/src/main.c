#include "interface.h"
#include <stdio.h>
#include "gmp.h"

int main(int argc, char** argv)
{
    mpz_t ret1, ret2, ret3, result;
    mpz_inits(ret1, ret2, ret3, result, NULL);
    mpz_t down1, up1, down2, up2, down3, up3;
    mpz_inits(down1, up1, down2, up2, down3, up3, NULL);
    mpz_t op1, op2;
    mpz_inits(op1, op2, NULL);
    mpz_set_ui(down1, 200);
    mpz_set_ui(up1, 30);
    mpz_set_ui(down2, 200);
    mpz_set_ui(up2, 100);
    mpz_set_ui(down3, 200);
    mpz_set_ui(up3, 1);
    cFunc(down1, up1, ret1); 
    cFunc(down2, up2, ret2); 
    cFunc(down3, up3, ret3); 
    mpz_mul(op1, ret1, ret2);
    mpz_div(result, op1, ret3);
    gmp_printf("%Zd\n", result);
    return 0;
}

void fact(const mpz_t op, mpz_t result) {
    mpz_t op1, op2;
    mpz_inits(op1, op2, NULL);
    mpz_set_ui(result, 1); // result = 1;
    mpz_set(op1, op); // op1 = op.
    while (mpz_cmp_ui(op1, 1) >= 0) {
        mpz_mul(result, result, op1); // result = result * op1.
        mpz_sub_ui(op1, op1, 1); // op1 = op1 - 1.
    }
}

void cFunc(const mpz_t down, const mpz_t up, mpz_t retNum) {
    mpz_t result1, result2, result3, op1, op2, op3;
    mpz_inits(result1, result2, result3, op1, op2, op3, NULL);
    fact(down, result1); // result1 = down!.
    fact(up, result2); // result2 = up!.
    mpz_sub(op1, down, up); // op1 = down - up.
    fact(op1, result3); // result3 = (down - up)!.
    mpz_mul(op2, result2, result3); // op2 = up! * (down - up)!
    mpz_div(retNum, result1, op2); // retNum = down! / (up! * (down - up)!).
}
