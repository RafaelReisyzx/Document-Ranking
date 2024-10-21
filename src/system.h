#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define NumDocumentos 6

typedef struct Node {
    char *word;
    int frequency;
    struct Node *next;
    size_t document_frequencies[NumDocumentos];
    size_t document_count;
} Node;

Node* create_node(const char *word);
void insert(Node **head, const char *word);
void free_list(Node *head);
void normalize_words(const char *input, Node **list, const char **stopwords, size_t stopword_count);
int is_stopword(const char *word, const char **stopwords, size_t stopword_count);
size_t load_stopwords(const char *filename, const char ***stopwords);
void process_file(const char *filename, Node **list, const char **stopwords, size_t stopword_count);
void load_documents(const char *files[], Node *lists[]);
void load_input_file(const char *filename, Node ***input_lists, size_t *line_count);
void free_memory(Node *lists[], size_t count);
void update_frequency(Node *input_list, Node *document_list, size_t doc_index);
void calculate_tfidf(Node *input_list, double tfidf_sums[]);
void rank_documents(double tfidf_sums[], size_t ranking[]);

#endif
