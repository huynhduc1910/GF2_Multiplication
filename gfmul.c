#include <stdio.h>
#include <stdint.h>

/* ---------- GF(2^4), đa thức tối giản x^4 + x + 1 (0x13) ---------- */
/* Rút gọn dùng 0x03 (= x + 1) vì x^4 ≡ x + 1 */
static uint8_t gf16_mul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    a &= 0x0F;
    b &= 0x0F;

    for (int i = 0; i < 4; i++) {
        p ^= (uint8_t)(-(b & 1) & a);        /* nếu bit thấp của b = 1 thì p ^= a */
        uint8_t carry = (a >> 3) & 1;        /* bit x^3 sẽ tràn lên x^4 */
        a = (uint8_t)((a << 1) & 0x0F);      /* a = a * x */
        a ^= (uint8_t)(-carry & 0x03);       /* nếu tràn: XOR với x + 1 */
        b >>= 1;
    }
    return p;
}

/* ---------- GF(2^8), đa thức chuẩn AES x^8 + x^4 + x^3 + x + 1 (0x11B) ---------- */
/* Rút gọn dùng 0x1B vì x^8 ≡ x^4 + x^3 + x + 1 */
static uint8_t gf256_mul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;

    for (int i = 0; i < 8; i++) {
        p ^= (uint8_t)(-(b & 1) & a);        /* nếu bit thấp của b = 1 thì p ^= a */
        uint8_t carry = (a >> 7) & 1;        /* bit x^7 sẽ tràn lên x^8 */
        a = (uint8_t)(a << 1);               /* a = a * x */
        a ^= (uint8_t)(-carry & 0x1B);       /* nếu tràn: XOR với 0x1B */
        b >>= 1;
    }
    return p;
}

int main(void)
{
    /* Test GF(2^4) */
    const uint8_t t16[][2] = { {0x2, 0x3}, {0x7, 0x9}, {0xF, 0xF}, {0x8, 0x8}, {0xA, 0x1} };
    printf("=== GF(2^4), x^4 + x + 1 ===\n");
    for (size_t i = 0; i < sizeof t16 / sizeof t16[0]; i++)
        printf("0x%X * 0x%X = 0x%X\n", t16[i][0], t16[i][1], gf16_mul(t16[i][0], t16[i][1]));

    /* Test GF(2^8) - chuẩn AES */
    const uint8_t t256[][2] = { {0x57, 0x83}, {0x57, 0x13}, {0x02, 0x87}, {0xFF, 0xFF}, {0x53, 0xCA} };
    printf("\n=== GF(2^8), x^8 + x^4 + x^3 + x + 1 (AES) ===\n");
    for (size_t i = 0; i < sizeof t256 / sizeof t256[0]; i++)
        printf("0x%02X * 0x%02X = 0x%02X\n", t256[i][0], t256[i][1], gf256_mul(t256[i][0], t256[i][1]));

    return 0;
}