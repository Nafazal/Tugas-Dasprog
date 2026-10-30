#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

/* Membalik string di tempat (in-place) */
void reverse(char *s)
{
    int i = 0;
    int j = (int)strlen(s) - 1;
    char temp;

    while (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

int main(void)
{
    char input[MAX_LEN];
    char output[MAX_LEN];
    int len;

    printf("Input  : ");
    if (fgets(input, MAX_LEN, stdin) == NULL)
        return 1;

    /* buang karakter newline di akhir hasil fgets */
    len = (int)strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';

    strcpy(output, input);
    reverse(output);

    printf("Output : %s\n", output);
    return 0;
}