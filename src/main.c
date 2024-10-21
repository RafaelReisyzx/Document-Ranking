#include "system.h"

int main() {
    clock_t start_time, end_time;
    double total_time;
    Node *document_lists[NumDocumentos] = {NULL};
    Node **input_lines = NULL;
    size_t input_line_count = 0;
    start_time = clock();

    const char *files[] = {
        "dataset/A mão e a luva.txt",
        "dataset/biblia.txt",
        "dataset/DomCasmurro.txt",
        "dataset/quincas borba.txt",
        "dataset/Semana_Machado_Assis.txt",
        "dataset/terremoto.txt"
    };
  
    load_documents(files, document_lists);
    load_input_file("dataset/input.txt", &input_lines, &input_line_count);

    for (size_t x = 0; x < input_line_count; x++) {
        double tfidf_scores[NumDocumentos] = {0};
        for (size_t y = 0; y < NumDocumentos; y++) {
            update_frequency(input_lines[x], document_lists[y], y);
        }
        calculate_tfidf(input_lines[x], tfidf_scores); 
        size_t ranking[NumDocumentos];
        rank_documents(tfidf_scores, ranking);

        printf("Ranking linha %zu do input.txt:\n", x + 1);
        for (size_t i = 0; i < NumDocumentos; i++) {
            printf("%zu. Documento %zu)\n", i + 1, ranking[i] + 1);
        }
        printf("\n");
    }

    free_memory(document_lists, NumDocumentos);
    free(input_lines);

    end_time = clock();
    total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo total de execução: %f segundos\n", total_time);

    return 0;
}
