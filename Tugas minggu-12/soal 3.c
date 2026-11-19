#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-12

/* Bilangan dalam notasi ilmiah: mantissa (0.1 <= m < 1.0) dan eksponen */
typedef struct {
    double mantissa;
    int exponent;
} sci_not_t;

/* Menormalkan hasil supaya 0.1 <= |mantissa| < 1.0 */
sci_not_t normalize(sci_not_t x)
{
    if (x.mantissa == 0.0) {
        x.exponent = 0;
        return x;
    }
    while (fabs(x.mantissa) >= 1.0 - EPS) {
        x.mantissa /= 10.0;
        x.exponent++;
    }
    while (fabs(x.mantissa) < 0.1 - EPS) {
        x.mantissa *= 10.0;
        x.exponent--;
    }
    return x;
}

/* Memecah string seperti "0.25000e3" menjadi mantissa dan eksponen.
   Mengembalikan 1 jika berhasil, 0 jika format salah. */
int scan_sci(const char *str, sci_not_t *result)
{
    char buf[64];
    char *e_pos, *end;
    double m;
    long ex = 0;

    if (strlen(str) >= sizeof(buf))
        return 0;
    strcpy(buf, str);

    e_pos = strpbrk(buf, "eE");
    if (e_pos != NULL) {
        *e_pos = '\0';
        ex = strtol(e_pos + 1, &end, 10);
        if (end == e_pos + 1 || *end != '\0')
            return 0;
    }

    m = strtod(buf, &end);
    if (end == buf || *end != '\0' || m <= 0.0)
        return 0;

    result->mantissa = m;
    result->exponent = (int)ex;
    *result = normalize(*result);
    return 1;
}

sci_not_t sci_add(sci_not_t a, sci_not_t b)
{
    sci_not_t r;
    if (a.exponent >= b.exponent) {
        r.exponent = a.exponent;
        r.mantissa = a.mantissa + b.mantissa * pow(10.0, b.exponent - a.exponent);
    } else {
        r.exponent = b.exponent;
        r.mantissa = b.mantissa + a.mantissa * pow(10.0, a.exponent - b.exponent);
    }
    return normalize(r);
}

sci_not_t sci_sub(sci_not_t a, sci_not_t b)
{
    sci_not_t r;
    if (a.exponent >= b.exponent) {
        r.exponent = a.exponent;
        r.mantissa = a.mantissa - b.mantissa * pow(10.0, b.exponent - a.exponent);
    } else {
        r.exponent = b.exponent;
        r.mantissa = a.mantissa * pow(10.0, a.exponent - b.exponent) - b.mantissa;
    }
    return normalize(r);
}

sci_not_t sci_mul(sci_not_t a, sci_not_t b)
{
    sci_not_t r;
    r.mantissa = a.mantissa * b.mantissa;
    r.exponent = a.exponent + b.exponent;
    return normalize(r);
}

sci_not_t sci_div(sci_not_t a, sci_not_t b)
{
    sci_not_t r;
    r.mantissa = a.mantissa / b.mantissa;   /* b.mantissa tidak pernah 0 untuk input positif */
    r.exponent = a.exponent - b.exponent;
    return normalize(r);
}

void print_sci(sci_not_t x)
{
    printf("%.5fe%d", x.mantissa, x.exponent);
}

int main(void)
{
    char s1[64], s2[64];
    sci_not_t a, b;

    printf("Enter two positive numbers in scientific notation\n");
    printf("(example: 0.25000e3 0.20000e1): ");
    if (scanf("%63s %63s", s1, s2) != 2) {
        printf("Input error.\n");
        return 1;
    }

    if (!scan_sci(s1, &a) || !scan_sci(s2, &b)) {
        printf("Invalid format. Use <positive number>e<integer>.\n");
        return 1;
    }

    printf("Values input: ");
    print_sci(a);
    printf(" ");
    print_sci(b);
    printf("\n");

    printf("Sum: ");
    print_sci(sci_add(a, b));
    printf("\n");

    printf("Difference: ");
    print_sci(sci_sub(a, b));
    printf("\n");

    printf("Product: ");
    print_sci(sci_mul(a, b));
    printf("\n");

    printf("Quotient: ");
    print_sci(sci_div(a, b));
    printf("\n");

    return 0;
}