#include "system.h"

Node* create_node(const char *word) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->frequency = 1;
    new_node->next = NULL;
    for (size_t i = 0; i < NumDocumentos; i++) {
        new_node->document_frequencies[i] = 0;
    }
    new_node->document_count = 0;
    return new_node;
}

void insert(Node **head, const char *word) {
    Node *current = *head;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->frequency++;
            return;
        }
        current = current->next;
    }
    Node *new_node = create_node(word);
    new_node->next = *head;
    *head = new_node;
}

void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

void normalize_words(const char *input, Node **list, const char **stopwords, size_t stopword_count) {
    char buffer[256];
    size_t buffer_index = 0;
    setlocale(LC_ALL, "pt_BR.UTF-8");

    for (size_t i = 0; input[i] != '\0'; i++) {
        unsigned char c = (unsigned char) input[i];
        if (isalnum(c) || (c >= 128)) {
            buffer[buffer_index++] = tolower(c);
        } else {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                if (!is_stopword(buffer, stopwords, stopword_count)) {
                    insert(list, buffer);
                }
                buffer_index = 0;
            }
        }
    }

    if (buffer_index > 0) {
        buffer[buffer_index] = '\0';
        if (!is_stopword(buffer, stopwords, stopword_count)) {
            insert(list, buffer);
        }
    }
}

int is_stopword(const char *word, const char **stopwords, size_t stopword_count) {
    for (size_t i = 0; i < stopword_count; i++) {
        if (strcmp(word, stopwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

size_t load_stopwords(const char *filename, const char ***stopwords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Não foi possível abrir o arquivo de stopwords");
        return 0;
    }

    size_t count = 0;
    char **words = NULL;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) {
        words = realloc(words, sizeof(char*) * (count + 1));
        words[count] = strdup(buffer);
        words[count][strcspn(words[count], "\n")] = '\0';
        count++;
    }

    fclose(file);
    *stopwords = (const char **)words;
    return count;
}

void process_file(const char *filename, Node **list, const char **stopwords, size_t stopword_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        normalize_words(line, list, stopwords, stopword_count);
    }
    fclose(file);
}

void load_documents(const char *files[], Node *lists[]) {
    const char **stopwords = NULL;
    size_t stopword_count = load_stopwords("dataset/stopwords.txt", &stopwords);

    for (int i = 0; i < NumDocumentos; i++) {
        process_file(files[i], &lists[i], stopwords, stopword_count);
    }

    for (size_t i = 0; i < stopword_count; i++) {
        free((void *)stopwords[i]);
    }
    free(stopwords);
}

void load_input_file(const char *filename, Node ***input_lists, size_t *line_count) {
    FILE *input_file = fopen(filename, "r");
    if (!input_file) {
        perror("Não foi possível abrir o arquivo input.txt");
        return;
    }

    *line_count = 0;
    Node **lists = NULL;
    char line[1024];

    while (fgets(line, sizeof(line), input_file)) {
        lists = realloc(lists, sizeof(Node*) * (*line_count + 1));
        lists[*line_count] = NULL;
        normalize_words(line, &lists[*line_count], NULL, 0);
        (*line_count)++;
    }

    fclose(input_file);
    *input_lists = lists;
}

void update_frequency(Node *input_list, Node *document_list, size_t doc_index) {
    while (input_list != NULL) {
        Node *doc_node = document_list;
        while (doc_node != NULL) {
            if (strcmp(input_list->word, doc_node->word) == 0) {
                input_list->document_frequencies[doc_index] = doc_node->frequency;
                break;
            }
            doc_node = doc_node->next;
        }
        input_list = input_list->next;
    }
}

void calculate_tfidf(Node *input_list, double tfidf_sums[]) {
    Node *node = input_list;
    double tf = 0, idf = 0;

    while (node != NULL) {
        for (size_t i = 0; i < NumDocumentos; i++) {
            tf = (double)node->document_frequencies[i] / (double)node->frequency;
            if (node->document_frequencies[i] > 0) {
                node->document_count++;
            }
            idf = log((double)(NumDocumentos) / (1 + (double)node->document_count));
            tfidf_sums[i] += tf * idf;
        }
        node = node->next;
    }
}

void rank_documents(double tfidf_sums[], size_t ranking[]) {
    size_t indices[NumDocumentos];
    for (size_t i = 0; i < NumDocumentos; i++) {
        indices[i] = i;
    }

    for (size_t i = 0; i < NumDocumentos; i++) {
        for (size_t j = i + 1; j < NumDocumentos; j++) {
            if (tfidf_sums[indices[i]] < tfidf_sums[indices[j]]) {
                size_t temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    for (size_t i = 0; i < NumDocumentos; i++) {
        ranking[i] = indices[i];
    }
}

void free_memory(Node *lists[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        free_list(lists[i]);
    }
}
