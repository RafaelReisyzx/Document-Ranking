# Sistema de Ranqueamento de Documentos com TF/IDF

# Descrição do Algoritmo

Este sistema tem como objetivo ranquear documentos de texto com base na relevância em relação a frases de pesquisa, utilizando o algoritmo TF/IDF (Term Frequency-Inverse Document Frequency). A ideia principal é medir a importância de cada termo em um conjunto de documentos, considerando tanto a frequência dos termos dentro dos documentos (TF) quanto a importância geral dos termos no conjunto de documentos (IDF). O sistema lê um conjunto de documentos, normaliza as palavras (removendo stopwords e pontuações) e calcula os scores TF/IDF para cada frase de pesquisa, resultando em um ranqueamento dos documentos.

## Principais Componentes do Sistema
- Leitura de Documentos: O sistema realiza a leitura e o processamento dos documentos, armazenando os termos em uma lista. O processo de normalização envolve a remoção das pontuações do documento, a remoção de stopwords do documento e a conversão dos caracteres para letras minúsculas; garantindo uma uniformidade nos dados.

- Cálculo do TF/IDF: Este cálculo envolve a frequência de termos (TF) e a frequência inversa de documentos (IDF), duas métricas fundamentais para determinar a relevância dos termos em relação ao conjunto de documentos analisados.

- Ranqueamento de Documentos: Os documentos são ranqueados com base na soma dos valores de TF/IDF dos termos encontrados nas frases de pesquisa. Para isso, um algoritmo de ordenação é utilizado, permitindo a apresentação dos documentos de acordo com sua relevância.

## Estruturas de Dados

Optei por utilizar listas encadeadas para armazenar as palavras e suas respectivas frequências. Essa escolha foi feita por algumas razões:

- **Flexibilidade**: As listas encadeadas permitem que o programa adicione ou remova palavras facilmente, adaptando-se a documentos de tamanho variável sem a necessidade de realocar grandes blocos de memória.
- **Complexidade de Memória**: Diferente dos arrays, que têm um tamanho fixo, as listas encadeadas podem crescer e encolher conforme necessário, o que é benéfico para o gerenciamento eficiente da memória em aplicações que lidam com textos de tamanhos dinâmicos.
- **Acesso Sequencial**: A natureza sequencial das listas encadeadas é adequada para o tipo de operação que estamos realizando, que envolve iterar sobre as palavras de um documento.

### **Comparação com Alternativas**
Embora as listas encadeadas sejam uma escolha adequada para este projeto, alternativas como arrays dinâmicos ou tabelas de hash poderiam ser consideradas.
- **Arrays Dinâmicos**: Podem oferecer melhor desempenho em acessos aleatórios, mas têm desvantagens em relação à inserção e remoção de elementos, que podem exigir realocação e cópia de dados.
- **Tabelas de Hash**: Poderiam melhorar a eficiência da busca, mas introduziriam complexidade adicional na implementação e no gerenciamento de colisões.

A escolha de listas encadeadas equilibra eficiência, simplicidade e flexibilidade, adequando-se bem às necessidades do projeto.

# Custo Computacional

O custo computacional do sistema é determinado pelas operações realizadas nas listas encadeadas e na manipulação das frequências de palavras. O custo é analisado em termos de:

### Carga de Documentos
A função `load_documents` itera por todos os documentos, processando cada um deles. O custo computacional desta função é O(n ⋅ m), onde n é o número de documentos e m é o número médio de palavras por documento.

### Atualização de Frequências
A função `update_frequency` percorre cada palavra da lista de entrada para atualizar suas frequências nos documentos. O custo aqui é O(p ⋅ q), onde p é o número de palavras na entrada e q é o número de documentos.

### Cálculo do TF-IDF
A função `calculate_tfidf` calcula a pontuação TF-IDF para cada palavra. O custo é O(p ⋅ n), onde p é o número de palavras na lista de entrada e n é o número de documentos.

### Classificação de Documentos
A função `rank_documents` possui um custo de O(n²) para classificar os documentos com base nas pontuações TF-IDF.

Assim, o custo total do programa pode ser expresso como: O(n ⋅ m) + O(p ⋅ q) + O(p ⋅ n) + O(n²)

## Análise Assintótica
A análise assintótica do sistema pode ser resumida nas seguintes complexidades:

- Carga de Documentos: O(n ⋅ m)
- Atualização de Frequências: O(p ⋅ q)
- Cálculo do TF-IDF: O(p ⋅ n)
- Classificação de Documentos: O(n²)

A complexidade geral do sistema depende da operação mais custosa, que é a classificação de documentos, resultando em uma complexidade assintótica de O(n²).

## Uso de Memória
O uso de memória é uma consideração importante, especialmente em sistemas que manipulam grandes volumes de dados. A memória utilizada pelo sistema é principalmente relacionada ao armazenamento das listas encadeadas e às variáveis auxiliares:

## Listas Encadeadas
Cada lista de palavras utiliza memória para armazenar os nós, onde cada nó armazena uma palavra, sua frequência e as frequências de documentos. O espaço utilizado por cada nó é O(1), e, portanto, a memória total para a lista de entrada pode ser O(p), onde p é o número total de palavras processadas.

## Array de Documentos
O sistema também aloca memória para os arrays que armazenam as listas de documentos e os scores TF-IDF. A memória total para documentos é O(n), onde n é o número de documentos.

Portanto, o uso total de memória do sistema pode ser estimado em O(p + n), onde p representa o total de palavras únicas processadas e n o número de documentos.

# Conclusão
O desempenho do sistema é amplamente dependente do número de documentos, da complexidade dos textos e do número de palavras a serem processadas. A análise do tempo de execução, custo computacional, análise assintótica e uso de memória fornece uma base sólida para entender a eficiência e a escalabilidade do programa. Para otimizações futuras, considerar a implementação de algoritmos de classificação mais eficientes ou estruturas de dados que reduzem a complexidade do tempo e do uso de memória pode ser uma abordagem viável.


# Funções

### `Node* create_node(const char *word)`

```
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
```

- **Descrição**: Cria um novo nó para a lista encadeada.
- **Parâmetros**:
  - `const char *word`: A palavra a ser armazenada no nó.
- **Retorno**: Retorna um ponteiro para o novo nó criado.

#### Explicação:
1. Aloca memória para um novo nó.
2. Copia a palavra para o nó utilizando `strdup`.
3. Inicializa a frequência como 1.
4. Define o ponteiro `next` como `NULL`.
5. Inicializa as frequências de documentos para 0.
6. Retorna o ponteiro do novo nó.

### `void insert(Node **head, const char *word)`

```
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
```

- **Descrição**: Insere uma palavra na lista encadeada, incrementando a frequência se a palavra já existir.
- **Parâmetros**:
  - `Node **head`: Ponteiro para o ponteiro do cabeçalho da lista.
  - `const char *word`: A palavra a ser inserida.

#### Explicação:
1. Itera pela lista encadeada para verificar se a palavra já existe.
2. Se existir, incrementa sua frequência e sai da função.
3. Se não existir, cria um novo nó com `create_node`.
4. Insere o novo nó no início da lista.

### `void free_list(Node *head)`

```
void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}
```

- **Descrição**: Libera a memória alocada para a lista encadeada.
- **Parâmetros**:
  - `Node *head`: Ponteiro para o início da lista.

#### Explicação:
1. Itera pela lista e libera a memória do nó atual.
2. Libera a memória da palavra armazenada no nó.
3. Continua até que todos os nós sejam liberados.

### `void normalize_words(const char *input, Node **list, const char **stopwords, size_t stopword_count)`

```
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
```

- **Descrição**: Normaliza as palavras da linha de entrada, removendo stopwords e pontuações.
- **Parâmetros**:
  - `const char *input`: A linha de entrada a ser normalizada.
  - `Node **list`: Ponteiro para a lista onde as palavras normalizadas serão armazenadas.
  - `const char **stopwords`: Lista de palavras a serem ignoradas.
  - `size_t stopword_count`: Número total de stopwords.

#### Explicação:
1. Inicializa um buffer para armazenar palavras.
2. Itera sobre cada caractere da linha de entrada.
3. Adiciona caracteres alfanuméricos ao buffer, convertendo para minúsculas.
4. Quando um caractere não alfanumérico é encontrado:
   - Se o buffer não estiver vazio, termina a string e verifica se é uma stopword.
   - Se não for uma stopword, insere a palavra na lista.
5. Após a iteração, verifica se ainda há conteúdo no buffer e o insere na lista se não for stopword.

### `int is_stopword(const char *word, const char **stopwords, size_t stopword_count)`

```
int is_stopword(const char *word, const char **stopwords, size_t stopword_count) {
    for (size_t i = 0; i < stopword_count; i++) {
        if (strcmp(word, stopwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
```


- **Descrição**: Verifica se uma palavra é uma stopword.
- **Parâmetros**:
  - `const char *word`: A palavra a ser verificada.
  - `const char **stopwords`: Lista de palavras a serem ignoradas.
  - `size_t stopword_count`: Número total de stopwords.

#### Explicação:
1. Itera sobre a lista de stopwords.
2. Compara a palavra atual com cada stopword.
3. Retorna 1 se for uma stopword, 0 caso contrário.

### `size_t load_stopwords(const char *filename, const char ***stopwords)`

```
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
```

- **Descrição**: Carrega a lista de stopwords de um arquivo.
- **Parâmetros**:
  - `const char *filename`: O nome do arquivo que contém as stopwords.
  - `const char ***stopwords`: Ponteiro para a lista de stopwords a ser preenchida.

#### Explicação:
1. Abre o arquivo e verifica se foi aberto corretamente.
2. Lê cada linha do arquivo e armazena as stopwords em um array dinâmico.
3. Retorna o número total de stopwords lidas.

### `void process_file(const char *filename, Node **list, const char **stopwords, size_t stopword_count)`

```
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
```

- **Descrição**: Processa um arquivo de texto, normalizando suas palavras e armazenando-as em uma lista.
- **Parâmetros**:
  - `const char *filename`: Nome do arquivo a ser processado.
  - `Node **list`: Ponteiro para a lista onde as palavras normalizadas serão armazenadas.
  - `const char **stopwords`: Lista de palavras a serem ignoradas.
  - `size_t stopword_count`: Número total de stopwords.

#### Explicação:
1. Abre o arquivo e verifica se foi aberto corretamente.
2. Lê cada linha do arquivo, chamando `normalize_words` para processá-la.
3. Fecha o arquivo após o processamento.

### `void load_documents(const char *files[], Node *lists[])`

```
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
```

- **Descrição**: Carrega múltiplos documentos e armazena suas palavras normalizadas em listas.
- **Parâmetros**:
  - `const char *files[]`: Array de nomes de arquivos a serem lidos.
  - `Node *lists[]`: Array de listas onde as palavras normalizadas serão armazenadas.

#### Explicação:
1. Carrega as stopwords do arquivo `stopwords.txt`.
2. Itera sobre cada arquivo de documento, chamando `process_file` para normalizar e armazenar as palavras.
3. Libera a memória das stopwords após o uso.

### `void load_input_file(const char *filename, Node ***input_lists, size_t *line_count)`

```
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
```

- **Descrição**: Carrega um arquivo de entrada, normalizando suas linhas e armazenando-as em listas.
- **Parâmetros**:
  - `const char *filename`: Nome do arquivo a ser carregado.
  - `Node ***input_lists`: Ponteiro para as listas de entradas.
  - `size_t *line_count`: Contador de linhas processadas.

#### Explicação:
1. Abre o arquivo de entrada e verifica se foi aberto corretamente.
2. Lê cada linha do arquivo e normaliza suas palavras.
3. Aumenta o contador de linhas a cada linha processada.
4. Fecha o arquivo após o processamento.

### `void update_frequency(Node *input_list, Node *document_list, size_t doc_index)`

```
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
```

- **Descrição**: Atualiza as frequências de palavras da lista de entrada em relação a um documento específico.
- **Parâmetros**:
  - `Node *input_list`: Lista de palavras da frase de pesquisa.
  - `Node *document_list`: Lista de palavras do documento.
  - `size_t doc_index`: Índice do documento.

#### Explicação:
1. Itera pela lista de entrada (input_list).
2. Para cada palavra na lista de entrada, itera pela lista do documento.
3. Se a palavra existir no documento, atualiza sua frequência correspondente no array `document_frequencies`.

### `void calculate_tfidf(Node *input_list, double tfidf_sums[])`

```
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
```

- **Descrição**: Calcula os valores TF/IDF para a lista de entrada.
- **Parâmetros**:
  - `Node *input_list`: Lista de palavras da frase de pesquisa.
  - `double tfidf_sums[]`: Array onde os scores TF/IDF serão armazenados.

#### Explicação:
1. Inicializa as variáveis TF e IDF.
2. Itera pela lista de entrada.
3. Para cada palavra, calcula a frequência (TF) em relação ao documento.
4. Calcula o valor IDF considerando o total de documentos e a frequência da palavra nos documentos.
5. Atualiza os valores TF/IDF no array `tfidf_sums`.

### `void rank_documents(double tfidf_sums[], size_t ranking[])`
```
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
```

- **Descrição**: Ordena os documentos com base nos scores TF/IDF.
- **Parâmetros**:
  - `double tfidf_sums[]`: Array de scores TF/IDF dos documentos.
  - `size_t ranking[]`: Array para armazenar a classificação dos documentos.

#### Explicação:
1. Inicializa um array `indices` para armazenar os índices dos documentos.
2. Realiza a ordenação utilizando um algoritmo de ordenação (ex: Bubble Sort).
3. Armazena a classificação resultante no array `ranking`.

### `void free_memory(Node *lists[], size_t count)`

```
void free_memory(Node *lists[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        free_list(lists[i]);
    }
}
```

- **Descrição**: Libera a memória alocada para as listas de documentos.
- **Parâmetros**:
  - `Node *lists[]`: Array de listas a serem liberadas.
  - `size_t count`: Contador de listas.

#### Explicação:
1. Itera sobre o array de listas e chama `free_list` para cada uma delas.


# Compilação e Execução

A pasta do repositorio possui um arquivo Makefile que contém as instruções para compilar e executar. Para usar essas instruções, você pode usar o terminal do seu sistema
operacional e navegar até o diretório raiz do projeto.

Existem três comandos principais que você pode usar no Makefile:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

Em resumo, para executar o programa, você precisa navegar até o diretório raiz do projeto e executar o comando make para compilar o programa e, em seguida, 
executar o comando make run para executá-lo.Se você precisar limpar a compilação anterior, pode usar o comando make clean antes de executar a compilação.