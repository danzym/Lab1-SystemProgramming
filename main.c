#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_LENGTH 30

bool has_unique_chars(const char *word) {
    bool alpha[26] = {false};
    while (*word) {
        char c = tolower(*word);
        if (c >= 'a' && c <= 'z') {
            if (alpha[c - 'a']) {
                return false;
            }
            alpha[c - 'a'] = true;
        }
        word++;
    }
    return true;
}

bool is_unique_word(const char word[MAX_WORD_LENGTH + 1], char unique_words[][MAX_WORD_LENGTH + 1], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, unique_words[i]) == 0) {
            return false;
        }
    }
    return true;
}

void sanitize_word(char *word) {
    char *dst = word;
    while (*word) {
        if (*word != ',' && *word != '.') {
            *dst++ = *word;
        }
        word++;
    }
    *dst = '\0';
}

int main() {
    FILE *file = fopen("wordsExampleLab1SysProg.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char word[MAX_WORD_LENGTH + 1];
    char unique_words[1000][MAX_WORD_LENGTH + 1] = {0};
    int unique_words_count = 0;

    while (fscanf(file, "%30s", word) != EOF) {
        sanitize_word(word);

        if (has_unique_chars(word) && is_unique_word(word, unique_words, unique_words_count)) {
            strcpy(unique_words[unique_words_count], word);
            unique_words_count++;
        }
    }

    fclose(file);

    for (int i = 0; i < unique_words_count; i++) {
        printf("%s\n", unique_words[i]);
    }

    return 0;
}