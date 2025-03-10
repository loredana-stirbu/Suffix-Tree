/* ȘTIRBU Loredana - 313CD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINE_SIZE 256

typedef char T;

typedef struct node
{
    T litera;
    struct node *children[27];
} Node, *Tree;

typedef struct NodeCoada
{
    Tree data; 
    struct NodeCoada *next;
} NodeCoada;

typedef struct queue
{
    NodeCoada *head, *tail;
    int size;
} *Queue;

Tree createNode(T litera)
{
    Tree nod = (Tree)malloc(sizeof(Node));
    if (nod == NULL)
    {
        return NULL;
    }
    nod->litera = litera;
    for (int i = 0; i < 27; ++i)
    {
        nod->children[i] = NULL;
    }
    return nod;
}

// CERINTA 1
int cmp(const void *a, const void *b)
{
    // compar lungimile la doua siruri
    size_t len_a = strlen(*(const char **)a);
    size_t len_b = strlen(*(const char **)b);
    return (len_a > len_b) - (len_a < len_b);
}

char **desp_sufixe(char *sir) // despart sufixele si le anexez direct "$"
{
    int lungime_sir = strlen(sir);
    int nr_sufixe = lungime_sir + 1; // nr de sufixe pentru un sir de dimensiune n este n+1

    // aloc memorie pentru sufixele cu $
    char *sir_dolar = (char *)malloc((lungime_sir + 2) * sizeof(char));
    strcpy(sir_dolar, sir);
    // adaug $ la sfarsitul sirului si marchez sfarsitul lui
    sir_dolar[lungime_sir] = '$';
    sir_dolar[lungime_sir + 1] = '\0';

    // aloc memorie pentru arrayul de pointeri
    char **sufixe = (char **)malloc(nr_sufixe * sizeof(char *));
    sufixe[0] = &sir_dolar[lungime_sir]; // ca primul sufix sa fie $

    for (int i = 0; i < lungime_sir; i++)
    {
        sufixe[i + 1] = &sir_dolar[i];
    }
    // sortez dupa lungime
    qsort(sufixe, nr_sufixe, sizeof(char *), cmp);
    return sufixe;
}

void insert_sir(Tree root, char *sir)
{
    if (root == NULL || sir == NULL)
    {
        return;
    }
    Tree temp = root;
    int lungime_sir = strlen(sir);
    for (int i = 0; i < lungime_sir; i++)
    {
        int idx;
        if (sir[i] == '$')
        {
            idx = 0; // setez indexul pentru $
        }
        else
        {
            idx = sir[i] - 'a' + 1; // calc indexul pentru caractere
        }
        // daca nu exista un copil la acest index creez un nou nod
        if (temp->children[idx] == NULL)
        {
            temp->children[idx] = createNode(sir[i]);
        }

        temp = temp->children[idx];
    }

    // adauga $ la sf de sir doar daca acesta nu exista deja
    if (sir[lungime_sir - 1] != '$' && temp->children[0] == NULL)
    {
        temp->children[0] = createNode('$');
    }
}

// creez arborele de sufixe pentru un sir dat
void createTree(Tree root, char *sir)
{
    if (root == NULL || sir == NULL)
    {
        return;
    }
    // obtin sufixele
    char **sufixe = desp_sufixe(sir);
    int nr_sufixe = strlen(sir) + 1;

    // iterez pentru fiecare sufix
    for (int i = 0; i < nr_sufixe; ++i)
    {
        insert_sir(root, sufixe[i]);
    }
}

void freeTree(Tree root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < 27; ++i)
    {
        freeTree(root->children[i]);
    }

    free(root);
}

NodeCoada *initNode(Tree data)
{
    NodeCoada *node = malloc(sizeof(struct NodeCoada));
    node->data = data;
    node->next = NULL;
    return node;
}

Queue initQueue(Tree data)
{
    Queue queue = malloc(sizeof(Queue));
    queue->head = queue->tail = initNode(data);
    queue->size = 1;
    return queue;
}

int isEmptyQueue(Queue queue)
{
    if (queue == NULL || queue->head == NULL || queue->size == 0)
        return 1;
    return 0;
}

void enqueue(Queue queue, Tree data)
{

    if (!queue)
        return;
    NodeCoada *newNode = malloc(sizeof(NodeCoada));
    if (!newNode)
        return;
    newNode->data = data;
    newNode->next = NULL;

    if (queue->tail == NULL)
    {
        queue->head = queue->tail = newNode;
    }
    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->size++;
}

Tree dequeue(Queue queue)
{
    if (isEmptyQueue(queue))
    {
        return NULL;
    }

    NodeCoada *tmp = queue->head;
    Tree data = tmp->data;
    queue->head = queue->head->next;
    queue->size--;

    if (queue->size == 0)
    {
        queue->tail = NULL;
    }
    free(tmp);
    return data;
}

void print_tree_by_levels(Tree root, FILE *outputFile)
{
    if (root == NULL)
        return;

    Queue queue = initQueue(root);
    bool flag = true; // folosesc asta pentru a scapa de primul nod gol

    while (!isEmptyQueue(queue))
    {
        int level_size = queue->size;
        bool flag_char = true; // folosesc pentru fiecare nivel sa scap de spatiu inainte la prima litera

        for (int i = 0; i < level_size; i++)
        {
            Tree node = dequeue(queue);
            // afisez nodului daca nu e nodul root
            if (node->litera != '\0')
            {
                if (!flag && !flag_char)
                {
                    fprintf(outputFile, " ");
                }
                fprintf(outputFile, "%c", node->litera);
                flag = false;
                flag_char = false;
            }

            // adaug toti copiii nodului in coada
            for (int j = 0; j < 27; j++)
            {
                if (node->children[j])
                {
                    enqueue(queue, node->children[j]);
                }
            }
        }

        if (!flag)
        {
            fprintf(outputFile, " \n");
        }
        flag_char = true;
    }
}

// CERINTA 2

int noduri_frunza(Tree root)
{
    if (root == NULL)
    {
        return 0;
    }
    int count = 0;

    // verific dacă nodul este o frunza ce contine $
    if (root->litera == '$')
    {
        count = 1;
    }
    // apelez funcția pentru toti copiii nodului curent
    for (int i = 0; i < 27; i++)
    {
        count += noduri_frunza(root->children[i]);
    }
    return count;
}

int calc_sufix_lungime_K(Tree root, int K)
{
    if (root == NULL)
    {
        return 0;
    }
    Queue coada = initQueue(root);
    for (int i = 0; i < 27; i++)
    {
        if (root->children[i] != NULL)
        {
            enqueue(coada, root->children[i]);
        }
    }
    dequeue(coada);
    int level_length = 0;
    int depth = 0;
    int count = 0;
    // parcg arborele in latime folosind BFS
    while (!isEmptyQueue(coada))
    {
        level_length = coada->size;
        while (level_length != 0)
        {
            Tree temp = dequeue(coada);
            level_length--;
            if (temp != NULL)
            {
                for (int i = 0; i < 27; i++)
                {
                    if (temp->children[i] != NULL)
                    {
                        enqueue(coada, temp->children[i]);
                    }
                }
                // verific daca adancimea curenta este egală cu K si daca nodul are copil $
                if (depth + 1 == K && temp->children[0] != NULL && temp->children[0]->litera == '$')
                {
                    count++;
                }
            }
        }
        depth++;
    }
    return count;
}

int maxDirectDesc(Tree root)
{
    if (root == NULL)
    {
        return 0;
    }

    int maxDescendants = 0;

    Queue queue = initQueue(root);

    // parcg arborele in latime folosind BFS
    while (!isEmptyQueue(queue))
    {
        Tree current_node = dequeue(queue);

        int count_curr = 0;

        // numar direct descendentii pentru nodul curent
        for (int i = 0; i < 27; i++)
        {
            if (current_node->children[i] != NULL)
            {
                count_curr++;
                enqueue(queue, current_node->children[i]);
            }
        }

        // actualizez dacă nr de descendenti este mai mare
        if (count_curr > maxDescendants)
        {
            maxDescendants = count_curr;
        }
    }

    return maxDescendants;
}

// CERINTA 3

int verif_sufix(Tree root, char *sir)
{
    if (root == NULL || sir == NULL)
    {
        return 0;
    }
    int lungime_sir = strlen(sir);
    Tree temp = root;
    // parcurg arborele pentru fiecare caracter din sir
    for (int i = 0; i < lungime_sir; i++)
    {
        // calc indexul copilului pentru caracterul curent din șir.
        int idx = sir[i] - 'a' + 1;
        if (temp->children[idx] == NULL)
        {
            return 0;
        }
        temp = temp->children[idx];
    }
    // verific daca exista un nod cu $ ca fiu al nodului curent
    if (temp->children[0] != NULL && temp->children[0]->litera == '$')
    {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    (void)argc;
    if (argc < 4) // verific daca nr de argumente este mai mic ca 4
    {
        return 1;
    }
    char *command = argv[1];

    if (strcmp(command, "-c1") == 0)
    {
        char *IN = argv[2];
        char *OUT = argv[3];
        FILE *inputFile = fopen(IN, "r");
        FILE *outputFile = fopen(OUT, "w");

        int numStrings; // variabila pentru nr de siruri de pe prima linie
        fscanf(inputFile, "%d", &numStrings);
        Tree root = createNode('\0');

        for (int i = 0; i < numStrings; ++i)
        {
            char line[MAX_LINE_SIZE];
            fscanf(inputFile, "%255s", line);
            createTree(root, line);
        }
        print_tree_by_levels(root, outputFile);

        freeTree(root);
        fclose(inputFile);
        fclose(outputFile);
    }
    else if (strcmp(command, "-c2") == 0)
    {
        char *IN = argv[3];
        char *OUT = argv[4];
        FILE *inputFile = fopen(IN, "r");
        FILE *outputFile = fopen(OUT, "w");

        int numStrings;
        fscanf(inputFile, "%d", &numStrings);
        Tree root = createNode('\0');
        for (int i = 0; i < numStrings; ++i)
        {
            char line[MAX_LINE_SIZE];
            fscanf(inputFile, "%s", line);
            createTree(root, line);
        }
        int K = atoi(argv[2]);
        int numLeafNodes = noduri_frunza(root);
        int numSuffixesOfLengthK = calc_sufix_lungime_K(root, K);
        int maxDescendants = maxDirectDesc(root);

        fprintf(outputFile, "%d\n", numLeafNodes);
        fprintf(outputFile, "%d\n", numSuffixesOfLengthK);
        fprintf(outputFile, "%d\n", maxDescendants);

        freeTree(root);
        fclose(inputFile);
        fclose(outputFile);
    }
    else if (strcmp(command, "-c3") == 0)
    {
        char *IN = argv[2];
        char *OUT = argv[3];
        FILE *inputFile = fopen(IN, "r");
        FILE *outputFile = fopen(OUT, "w");
        int N, M;
        fscanf(inputFile, "%d %d", &N, &M);
        Tree root = createNode('\0');
        char line[MAX_LINE_SIZE];
        for (int i = 0; i < N; ++i)
        {
            fscanf(inputFile, "%s", line);
            createTree(root, line);
        }

        for (int i = 0; i < M; i++)
        {
            fscanf(inputFile, "%s", line);
            fprintf(outputFile, "%d\n", verif_sufix(root, line));
        }

        freeTree(root);
        fclose(inputFile);
        fclose(outputFile);
    }

    return 0;
}