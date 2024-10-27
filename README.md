# Descrição do Algoritmo

Este sistema tem como objetivo ranquear documentos de texto com base na relevância em relação a frases de pesquisa, utilizando o cálculo TF/IDF (Term Frequency-Inverse Document Frequency). A ideia principal é medir a importância de cada termo em um conjunto de documentos, considerando tanto a frequência dos termos dentro dos documentos (TF) quanto a importância geral dos termos no conjunto de documentos (IDF). O sistema lê um conjunto de documentos, normaliza os termos e calcula os scores TF/IDF para cada frase de pesquisa, resultando em um ranqueamento dos documentos.

## Principais Componentes do Sistema
- Leitura de Documentos: O sistema realiza a leitura e o processamento dos documentos, primeiro normalizando os termos (removendo pontuações, removendo stopwords e convertendo cada termo para minúsculo) e, por fim, armazenando os termos em uma lista. Ele faz o mesmo processo com o texto de entrada, mas, em vez de ter uma lista para cada texto, possuirá uma lista para cada frase de pesquisa.

- Cálculo do TF/IDF: Este cálculo envolve a frequência de termos (TF) e a frequência inversa de documentos (IDF), duas métricas fundamentais para determinar a relevância dos termos em relação ao conjunto de documentos analisados.

- Ranqueamento de Documentos: Os documentos são ranqueados com base na soma dos valores de TF/IDF dos termos encontrados nas frases de pesquisa. Para isso, um algoritmo de ordenação é utilizado, permitindo a apresentação dos documentos de acordo com sua relevância.

## Estruturas de Dados

Optei por utilizar listas encadeadas para armazenar os termos e suas respectivas frequências. Essa escolha foi feita por algumas razões:

- **Flexibilidade**: As listas encadeadas permitem que o programa adicione ou remova termos facilmente, adaptando-se a documentos de tamanho variável sem a necessidade de realocar grandes blocos de memória.
- **Complexidade de Memória**: Diferente dos arrays, que têm um tamanho fixo, as listas encadeadas podem crescer e encolher conforme necessário, o que é benéfico para o gerenciamento eficiente da memória em aplicações que lidam com textos de tamanhos dinâmicos.
- **Acesso Sequencial**: A natureza sequencial das listas encadeadas é adequada para o tipo de operação que estamos realizando, que envolve iterar sobre as termos de um documento.

### **Comparação com Alternativas**
Embora as listas encadeadas sejam uma escolha adequada para este projeto, alternativas como arrays dinâmicos ou tabelas de hash poderiam ser consideradas.
- **Arrays Dinâmicos**: Podem oferecer melhor desempenho em acessos aleatórios, mas têm desvantagens em relação à inserção e remoção de elementos, que podem exigir realocação e cópia de dados.
- **Tabelas de Hash**: Poderiam melhorar a eficiência da busca, mas introduziriam complexidade adicional na implementação e no gerenciamento de colisões.

A escolha de listas encadeadas equilibra eficiência, simplicidade e flexibilidade, adequando-se bem às necessidades do projeto.

# Funcionamento

### 1. Inicialização
- O programa começa com a inclusão de um cabeçalho que contém definições e a declaração de uma estrutura de dados (neste caso, uma lista ligada) para armazenar termos e suas frequências.
- Em seguida, são definidas variáveis para armazenar o tempo de execução e uma matriz para armazenar listas de termos de documentos, todas inicializadas como NULL.
- 
### 2. Definição de Documentos
- Uma lista de nomes de arquivos de texto é definida. Esses arquivos contêm os documentos que serão processados. No caso, são seis documentos de literatura.
  
```
   const char *files[] = {
        "dataset/A mão e a luva.txt",
        "dataset/biblia.txt",
        "dataset/DomCasmurro.txt",
        "dataset/quincas borba.txt",
        "dataset/Semana_Machado_Assis.txt",
        "dataset/terremoto.txt"
    };
```

### 3. Carregamento de Documentos
- O programa chama a função load_documents, responsável por carregar e processar os documentos de texto. Essa função:
- Lê os termos de cada arquivo e normaliza-os.
- Insere os termos em uma lista encadeada para cada documento, ignorando os termos que estão na lista de stopwords (termos comuns que não agregam significado, como "e", "o", etc.).
- A estrutura de cada nó na lista contém o termo, sua frequência e a contagem de documentos em que aparece.
- 
### 4. Carregamento de Arquivo de Entrada
- Outra função, load_input_file, é chamada para ler um arquivo de entrada, que contém frases de pesquisa separadas por linha.
- Cada linha é processada da mesma forma que os documentos, resultando em uma lista de termos para cada linha a serem analisadas.
- 
### 5. Cálculo de Frequências e TF-IDF
- Para cada linha do arquivo de entrada, são realizadas as seguintes operações:
- Inicializa um vetor tfidf_scores para armazenar os scores TF-IDF para cada documento.
- Para cada documento, a função update_frequency é chamada para atualizar a frequência dos termos da linha atual na lista de termos do documento.
- A função calculate_tfidf é chamada para calcular os scores TF-IDF:
- O Term Frequency (TF) é calculado como a frequência da palavra na lista de entrada em relação à frequência total no documento.
- O Inverse Document Frequency (IDF) é calculado com base na contagem de documentos em que a palavra aparece.
- O score TF-IDF é armazenado no vetor tfidf_scores.
- 
### 6. Classificação dos Documentos
- Após o cálculo dos scores TF-IDF, a função rank_documents é chamada para classificar os documentos de acordo com seus scores.
-A classificação é armazenada em um vetor ranking, que é impresso para cada linha do arquivo de entrada, mostrando a ordem dos documentos com base na relevância para a linha de pesquisa.

### 7. Liberação de Memória
- Após a execução do processamento, a função free_memory é chamada para liberar a memória alocada para as listas de documentos.
- O programa também libera a memória alocada para as linhas de entrada.
- 
### 8. Cálculo do Tempo de Execução
Finalmente, o programa calcula o tempo total de execução usando as funções clock() e CLOCKS_PER_SEC, exibindo o tempo gasto para processar os documentos e as entradas.

# Exemplo Simples de funcionamento

Entradas que serão utilizadas no exemplo:

Texto 1: 
> A luz do sol passa pelas folhas da árvore.<br/>
As sombras dançavam no chão enquanto o vento sussurrava segredos.<br/>
Um pássaro pousou, trazendo consigo uma mensagem de liberdade.<br/>

Texto 2: 
> No fundo do mar, criaturas misteriosas aguardavam a próxima presa.<br/>
As ondas quebravam suavemente, ocultando um mundo de segredos.<br/>
Uma luz tênue brilhava, revelando um símbolo desconhecido.<br/>

Texto 3: 
> Em uma cidade esquecida, as ruas contavam histórias de tempos antigos.<br/>
As paredes grafitadas vibravam com a energia da juventude rebelde.<br/>
A música pode ecoar, unindo almas em busca de significado.<br/>

Input:
> Mistérios do fundo do mar esperam por quem se atreve a explorar.<br/>
Um pássaro pode ser visto como um símbolo de liberdade e esperança.<br/>
O vento sussurra segredos que só quem tem mais energia consegue ouvir.<br/>

### Etapa 1: Normalização das termos

Primeiramente, cada termo dos textos e do input são normalizados. Isso envolve transformar todas as termos para letras minúsculas, remover caracteres especiais de pontuação e filtrar termos que são consideradas *stopwords* (termos comuns que não agregam valor ao significado, como "o", "a", "e", etc.).

Texto 1:
> luz sol passa pelas folhas árvore<br/>
sombras dançavam chão vento sussurrava segredos<br/>
pássaro pousou trazendo consigo mensagem liberdade<br/>

Texto 2:
> fundo mar criaturas misteriosas aguardavam próxima presa<br/>
ondas quebravam suavemente ocultando mundo segredos<br/>
luz tênue brilhava revelando símbolo desconhecido<br/>

Texto 3:
> cidade esquecida ruas contavam histórias tempos antigos<br/>
paredes grafitadas vibravam energia juventude rebelde<br/>
música pode ecoar unindo almas busca significado<br/>

Input:
> mistérios fundo mar esperam atreve explorar<br/>
pássaro pode ser visto símbolo liberdade esperança<br/>
vento sussurra segredos energia consegue ouvir<br/>

### Etapa 2: Adição das termos em listas 

Lista Texto 1:
- luz 
- sol 
- passa 
- pelas 
- folhas 
- árvore
- sombras
- dançavam 
- chão 
- vento 
- sussurrava 
- segredos
- pássaro
- pousou 
- trazendo 
- consigo 
- mensagem 
- liberdade

Lista Texto 2:
- fundo 
- mar 
- criaturas 
- misteriosas 
- aguardavam
- próxima 
- presa
- ondas 
- quebravam 
- suavemente 
- ocultando 
- mundo 
- segredos
- luz 
- tênue 
- brilhava 
- revelando 
- símbolo 
- desconhecido

Lista Texto 3:
- cidade 
- esquecida 
- ruas 
- contavam 
- histórias 
- tempos 
- antigos
- paredes 
- grafitadas 
- vibravam 
- energia 
- juventude 
- rebelde
- música
- pode
- ecoar 
- unindo 
- almas 
- busca 
- significado

Diferente dos documentos que possuem uma lista para cada texto, no input são criadas listas para cada frase do texto

Lista 1 Input:
- mistérios
- fundo
- mar
- esperam
- atreve
- explorar
  
Lista 2 Input:
- pássaro
- pode
- ser
- visto
- símbolo
- liberdade
- esperança
  
Lista 3 Input:
- vento
- sussurra
- segredos
- energia
- consegue
- ouvir

### Etapa 3: Identificar frequências

Nesta etapa o objetivo é identificar quais termos do input estão presentes nos textos e quantas vezes aparecem.
| Lista Input 1 | frequência texto 1 | frequência texto 2 | frequência texto 3 | 
|---------------|--------------------|--------------------|--------------------| 
| mistérios     | 0                  | 0                  | 0                  |
| fundo         | 0                  | 1                  | 0                  |
| mar           | 0                  | 1                  | 0                  |
| esperam       | 0                  | 0                  | 0                  |
| atreve        | 0                  | 0                  | 0                  |
| explorar      | 0                  | 0                  | 0                  |

| Lista Input 2 | frequência texto 1 | frequência texto 2 | frequência texto 3 | 
|---------------|--------------------|--------------------|--------------------| 
| pássaro       | 1                  | 0                  | 0                  |
| pode          | 0                  | 0                  | 1                  |
| ser           | 0                  | 0                  | 0                  |
| visto         | 0                  | 0                  | 0                  |
| símbolo       | 1                  | 0                  | 0                  |
| liberdade     | 1                  | 0                  | 0                  |
| esperança     | 0                  | 0                  | 0                  |

| Lista Input 3 | frequência texto 1 | frequência texto 2 | frequência texto 3 | 
|---------------|--------------------|--------------------|--------------------| 
| vento         | 1                  | 0                  | 0                  |
| sussurra      | 0                  | 0                  | 0                  |
| segredos      | 1                  | 1                  | 0                  |
| energia       | 0                  | 0                  | 1                  |
| consegue      | 0                  | 0                  | 0                  |
| ouvir         | 0                  | 0                  | 0                  |


### Etapa 4: Cálculo TF-IDF

A frequência do termo (TF) é calculada como:
$\text{TF}(t) = \frac{\text{Frequência}(t)}{\text{Total de termos no documento}}$
onde:
- (Frequência(t))  é o número de vezes que o termo aparece no documento.
- (Total de termos no documento) é o número total de termos presentes no documento, no exemplo: Texto 1:18,Texto 2:19 e Texto 3:19

A frequência inversa do documento (IDF) é calculada como:

$\text{IDF}(t) = \log\left(\frac{N}{n_t}\right)$
onde:
-  (N)  é o total de documentos, no exemplo:3.
- $\( n_t \)$ é o número de documentos que contêm o termo.


| Lista Input 1 | frequência texto 1 | frequência texto 2 | frequência texto 3 | TF Texto 1 | TF Texto 2 | TF Texto 3 | IDF            | 
|---------------|--------------------|--------------------|--------------------|------------|------------|------------|----------------|
| mistérios     | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| fundo         | 0                  | 1                  | 0                  | 0/18=0     | 1/19=0,052 | 0/19=0     | log(3/1)=0,477 |
| mar           | 0                  | 1                  | 0                  | 0/18=0     | 1/19=0,052 | 0/19=0     | log(3/1)=0,477 |
| esperam       | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| atreve        | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| explorar      | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| total         | 0                  | 2                  | 0                  | 0/18=0     | 0,105      | 0          | 0,954          |

| Lista Input 2 | frequência texto 1 | frequência texto 2 | frequência texto 3 | TF Texto 1 | TF Texto 2 | TF Texto 3 | IDF            | 
|---------------|--------------------|--------------------|--------------------|------------|------------|------------|----------------|
| pássaro       | 1                  | 0                  | 0                  | 1/18=0,055 | 0/19=0     | 0/19=0     | log(3/1)=0,477 |
| pode          | 0                  | 0                  | 1                  | 0/18=0     | 0/19=0     | 1/19=0,052 | log(3/1)=0,477 |
| ser           | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| visto         | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| símbolo       | 1                  | 0                  | 0                  | 1/18=0,055 | 0/19=0     | 0/19=0     | log(3/1)=0,477 |
| liberdade     | 1                  | 0                  | 0                  | 1/18=0,055 | 0/19=0     | 0/19=0     | log(3/1)=0,477 |
| esperança     | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| total         | 3                  | 0                  | 1                  | 0,166      | 0          | 0,052      | 1,908          |

| Lista Input 3 | frequência texto 1 | frequência texto 2 | frequência texto 3 | TF Texto 1 | TF Texto 2 | TF Texto 3 | IDF            | 
|---------------|--------------------|--------------------|--------------------|------------|------------|------------|----------------|
| vento         | 1                  | 0                  | 0                  | 1/18=0,055 | 0/19=0     | 0/19=0     | log(3/1)=0,477 |
| sussurra      | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| segredos      | 1                  | 1                  | 0                  | 1/18=0,055 | 1/19=0,052 | 0/19=0     | log(3/2)=0,176 |
| energia       | 0                  | 0                  | 1                  | 0/18=0     | 0/19=0     | 1/19=0,052 | log(3/1)=0,477 |
| consegue      | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| ouvir         | 0                  | 0                  | 0                  | 0/18=0     | 0/19=0     | 0/19=0     | log(3/0)=Null  |
| total         | 2                  | 1                  | 1                  | 0,105      | 0,052      | 0,052      | 1,607          |

### Etapa 5: Raking de Documentos

+ Relevância TF-IDF do input 1 no texto 1:0
+ Relevância TF-IDF do input 1 no texto 2:0,10017
+ Relevância TF-IDF do input 1 no texto 3:0

+ Relevância TF-IDF do input 2 no texto 1:0,316728
+ Relevância TF-IDF do input 2 no texto 2:0
+ Relevância TF-IDF do input 2 no texto 3:0,099216

+ Relevância TF-IDF do input 3 no texto 1:0,168735
+ Relevância TF-IDF do input 3 no texto 2:0,083564
+ Relevância TF-IDF do input 3 no texto 3:0,083564

Agora para finalizar é criado um raking dos inputs de acordo com seus scores

Texto 1
1. input 2
2. input 3
3. input 1

Texto 2
1. input 1
2. input 3
3. input 2

Texto 3
1. input 2
2. input 3
3. input 1



  ![This is an image](https://github.com/RafaelReisyzx/Document-Ranking/blob/main/img/img1.png)




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

- **Descrição**: Normaliza as termos da linha de entrada, removendo stopwords e pontuações.
- **Parâmetros**:
  - `const char *input`: A linha de entrada a ser normalizada.
  - `Node **list`: Ponteiro para a lista onde as termos normalizadas serão armazenadas.
  - `const char **stopwords`: Lista de termos a serem ignoradas.
  - `size_t stopword_count`: Número total de stopwords.

#### Explicação:
1. Inicializa um buffer para armazenar termos.
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
  - `const char **stopwords`: Lista de termos a serem ignoradas.
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

- **Descrição**: Processa um arquivo de texto, normalizando suas termos e armazenando-as em uma lista.
- **Parâmetros**:
  - `const char *filename`: Nome do arquivo a ser processado.
  - `Node **list`: Ponteiro para a lista onde as termos normalizadas serão armazenadas.
  - `const char **stopwords`: Lista de termos a serem ignoradas.
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

- **Descrição**: Carrega múltiplos documentos e armazena suas termos normalizadas em listas.
- **Parâmetros**:
  - `const char *files[]`: Array de nomes de arquivos a serem lidos.
  - `Node *lists[]`: Array de listas onde as termos normalizadas serão armazenadas.

#### Explicação:
1. Carrega as stopwords do arquivo `stopwords.txt`.
2. Itera sobre cada arquivo de documento, chamando `process_file` para normalizar e armazenar as termos.
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
2. Lê cada linha do arquivo e normaliza suas termos.
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

- **Descrição**: Atualiza as frequências de termos da lista de entrada em relação a um documento específico.
- **Parâmetros**:
  - `Node *input_list`: Lista de termos da frase de pesquisa.
  - `Node *document_list`: Lista de termos do documento.
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
  - `Node *input_list`: Lista de termos da frase de pesquisa.
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

## Tempo Execução

Ao realizar o teste com seis documentos ("dataset/A mão e a luva.txt", "dataset/biblia.txt", "dataset/DomCasmurro.txt", "dataset/quincas borba.txt", "dataset/Semana_Machado_Assis.txt" e "dataset/terremoto.txt") utilizando um conjunto de 50 frases de pesquisa aleatórias, o sistema apresentou um tempo de execução total de 67,63 segundos.<br/>

Primeiramente, o número de documentos processados impacta significativamente o desempenho, uma vez que o sistema deve realizar leituras e buscas em cada arquivo individualmente. Além disso, a complexidade dos textos, que pode envolver tanto o tamanho dos documentos quanto a estrutura e a densidade lexical, também exerce influência: textos maiores e mais complexos exigem maior poder computacional para processamento de frases e termos.<br/>

Por fim, o número de frases de pesquisa também é um fator determinante, já que cada frase adiciona uma camada de busca e comparação dentro de cada documento. Quanto maior o número de frases, maior o esforço do sistema para analisar correspondências e calcular relevâncias, o que resulta em maior tempo de execução.<br/>

Assim, observamos que a escalabilidade do sistema pode ser afetada pela combinação desses fatores. Para otimizar o desempenho, estratégias como o uso de algoritmos mais eficientes, processamento paralelo, ou redução do número de termos poderiam ser exploradas, buscando uma melhor adaptação às demandas de desempenho sem comprometer a precisão dos resultados obtidos.<br/>

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
