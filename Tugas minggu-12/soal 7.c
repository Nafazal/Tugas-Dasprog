#include <stdio.h>

/* Model transformator ideal:
   V1/V2 = N1/N2  dan  I1/I2 = N1/N2 */
typedef struct {
    double n1;   /* jumlah lilitan kawat 1 */
    double n2;   /* jumlah lilitan kawat 2 */
    double v1;   /* tegangan input (V)     */
    double i1;   /* arus input (A)         */
} transformer_t;

/* Tegangan output: V2 = V1 * N2 / N1 */
double v_out(const transformer_t *t)
{
    return t->v1 * t->n2 / t->n1;
}

/* Arus output: I2 = I1 * N1 / N2 */
double i_out(const transformer_t *t)
{
    return t->i1 * t->n1 / t->n2;
}

/* Mengubah N1 supaya tegangan output = v2 */
void set_n1_for_v2(double v2, transformer_t *t)
{
    if (v2 <= 0.0) {
        printf("Desired output voltage must be positive.\n");
        return;
    }
    t->n1 = t->n2 * t->v1 / v2;
}

/* Mengubah V1 supaya tegangan output = v2 */
void set_v1_for_v2(double v2, transformer_t *t)
{
    t->v1 = v2 * t->n1 / t->n2;
}

/* Mengubah N2 supaya tegangan output = v2 */
void set_n2_for_v2(double v2, transformer_t *t)
{
    if (t->v1 <= 0.0) {
        printf("Input voltage must be positive.\n");
        return;
    }
    t->n2 = t->n1 * v2 / t->v1;
}

/* Mengubah N2 supaya arus output = i2 */
void set_n2_for_i2(double i2, transformer_t *t)
{
    if (i2 <= 0.0) {
        printf("Desired output current must be positive.\n");
        return;
    }
    t->n2 = t->i1 * t->n1 / i2;
}

/* Membaca N1, N2, V1, I1. Mengembalikan 1 jika sukses. */
int scan_transformer(transformer_t *t)
{
    printf("Enter N1 (turns of wire 1): ");
    if (scanf("%lf", &t->n1) != 1 || t->n1 <= 0.0) return 0;
    printf("Enter N2 (turns of wire 2): ");
    if (scanf("%lf", &t->n2) != 1 || t->n2 <= 0.0) return 0;
    printf("Enter V1 (input voltage, V): ");
    if (scanf("%lf", &t->v1) != 1) return 0;
    printf("Enter I1 (input current, A): ");
    if (scanf("%lf", &t->i1) != 1) return 0;
    return 1;
}

void print_transformer(const transformer_t *t)
{
    printf("  N1 = %.2f turns, N2 = %.2f turns\n", t->n1, t->n2);
    printf("  V1 = %.2f V,  I1 = %.2f A\n", t->v1, t->i1);
    printf("  V2 = %.2f V,  I2 = %.2f A\n", v_out(t), i_out(t));
}

int main(void)
{
    transformer_t t, tmp;
    double want_v2, want_i2;

    if (!scan_transformer(&t)) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("\nOriginal transformer:\n");
    print_transformer(&t);

    printf("\nEnter desired output voltage V2: ");
    scanf("%lf", &want_v2);
    printf("Enter desired output current I2: ");
    scanf("%lf", &want_i2);

    tmp = t;
    set_n1_for_v2(want_v2, &tmp);
    printf("\nChange N1 for V2 = %.2f V:\n", want_v2);
    print_transformer(&tmp);

    tmp = t;
    set_v1_for_v2(want_v2, &tmp);
    printf("\nChange V1 for V2 = %.2f V:\n", want_v2);
    print_transformer(&tmp);

    tmp = t;
    set_n2_for_v2(want_v2, &tmp);
    printf("\nChange N2 for V2 = %.2f V:\n", want_v2);
    print_transformer(&tmp);

    tmp = t;
    set_n2_for_i2(want_i2, &tmp);
    printf("\nChange N2 for I2 = %.2f A:\n", want_i2);
    print_transformer(&tmp);

    return 0;
}