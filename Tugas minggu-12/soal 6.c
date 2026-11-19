#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 50
#define WORD_LEN 20
#define LANG_LEN 30

typedef struct {
    char language[LANG_LEN];
    int count;
    char words[MAX_WORDS][WORD_LEN];
} wordlist_t;

/* Mengembalikan true jika word ada di dalam list */
bool contains(const char *word, const wordlist_t *list)
{
    int i;
    for (i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], word) == 0)
            return true;
    }
    return false;
}

/* Menambah kata ke list (tanpa urutan). */
void add_word(const char *word, wordlist_t *list)
{
    if (strlen(word) >= WORD_LEN) {
        printf("Word too long, not added.\n");
        return;
    }
    if (list->count >= MAX_WORDS) {
        printf("List full, word not added.\n");
        return;
    }
    if (contains(word, list))
        return;                      /* sudah ada: list tidak berubah */

    strcpy(list->words[list->count], word);
    list->count++;
}

/* Format file: baris/kata pertama = bahasa, sisanya = kata-kata.
   Mengembalikan true jika file berhasil dibuka. */
bool load_word_list(const char *filename, wordlist_t *list)
{
    FILE *fp = fopen(filename, "r");
    char buf[100];

    if (fp == NULL)
        return false;

    list->count = 0;
    if (fscanf(fp, "%29s", list->language) != 1) {
        fclose(fp);
        return false;
    }
    while (fscanf(fp, "%99s", buf) == 1)
        add_word(buf, list);

    fclose(fp);
    return true;
}

/* True jika bahasa sama, jumlah sama, dan semua kata list a ada di list b */
bool equal_lists(const wordlist_t *a, const wordlist_t *b)
{
    int i;

    if (strcmp(a->language, b->language) != 0)
        return false;
    if (a->count != b->count)
        return false;
    for (i = 0; i < a->count; i++) {
        if (!contains(a->words[i], b))
            return false;
    }
    return true;
}

/* Menampilkan semua kata dalam empat kolom */
void display_word_list(const wordlist_t *list)
{
    int i;

    printf("Language: %s (%d words)\n", list->language, list->count);
    for (i = 0; i < list->count; i++) {
        printf("%-20s", list->words[i]);
        if ((i + 1) % 4 == 0 || i == list->count - 1)
            printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    const char *filename = (argc > 1) ? argv[1] : "words.txt";
    wordlist_t list1, list2;
    char word[100];
    int i;

    if (!load_word_list(filename, &list1)) {
        printf("Cannot open data file: %s\n", filename);
        return 1;
    }

    /* Isi list kedua dari keyboard */
    list2.count = 0;
    printf("Enter a language: ");
    scanf("%29s", list2.language);
    printf("Enter 12 words:\n");
    for (i = 0; i < 12; i++) {
        scanf("%99s", word);
        add_word(word, &list2);
    }

    /* Mencari kata di list pertama */
    printf("\nEnter words to search for in the first list (type quit to stop):\n");
    while (scanf("%99s", word) == 1 && strcmp(word, "quit") != 0) {
        if (contains(word, &list1))
            printf("\"%s\" is found in the first list.\n", word);
        else
            printf("\"%s\" is NOT found in the first list.\n", word);
    }

    /* Membandingkan kedua list */
    printf("\n");
    if (equal_lists(&list1, &list2))
        printf("The two lists are equal.\n");
    else
        printf("The two lists are NOT equal.\n");

    printf("\nFirst list:\n");
    display_word_list(&list1);
    printf("Second list:\n");
    display_word_list(&list2);

    return 0;
}