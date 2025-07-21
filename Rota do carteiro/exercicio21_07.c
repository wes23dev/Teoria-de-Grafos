/* hierholzer_file.c  –  verificar se grafo Euleriano (não direcionado)- leitura de arquivo
 * Uso:   ./hierholzer <arquivo.txt>
 * Formato do arquivo:
 *      V E            # número de vértices e arestas
 *      u v            # E linhas (0-indexado) – arestas não direcionadas
 */
#include <stdio.h>
#include <stdlib.h>

/* ---------- Estruturas ---------- */
typedef struct Edge Edge;
struct Edge { int to, id; Edge *next; };

Edge **adj      = NULL;   /* vetor de ponteiros p/ listas            */
int   *deg      = NULL;   /* grau de cada vértice                    */
int   *vis_edge = NULL;   /* marca aresta já usada (tam = E)         */
int   *vis_v    = NULL;   /* vértices visitados p/ conectividade     */

/* ---------- Adiciona aresta u-v ---------- */
void add_edge(int u, int v, int id)
{
    Edge *a = malloc(sizeof(Edge));
    a->to = v; a->id = id; a->next = adj[u]; adj[u] = a;

    Edge *b = malloc(sizeof(Edge));
    b->to = u; b->id = id; b->next = adj[v]; adj[v] = b;

    deg[u]++; deg[v]++;
}

/* ---------- DFS iterativa p/ conectividade ---------- */
void dfs(int start, int V)
{
    int *stack = malloc(V * sizeof(int));
    int  top   = 0;
    stack[top++] = start;
    vis_v[start] = 1;

    while (top) {
        int u = stack[--top];
        for (Edge *e = adj[u]; e; e = e->next)
            if (!vis_v[e->to]) {
                vis_v[e->to] = 1;
                stack[top++] = e->to;
            }
    }
    free(stack);
}

/* ---------- Hierholzer ---------- */
int *ciclo = NULL, clen = 0;            /* ciclo reverso       */
int *S       = NULL, stop  = 0;           /* pilha do percurso      */


void hierholzer(int start, int E)
{
    S[stop++] = start;
    while (stop) {
        int v = S[stop - 1];
        Edge *e;
        for (e = adj[v]; e && vis_edge[e->id]; e = e->next) ;
        if (e) {                          /* avança por aresta livre */
            vis_edge[e->id] = 1;
            S[stop++] = e->to;
        } else {                          /* sem arestas → registra */
            ciclo[clen++] = v;
            --stop;
        }
    }
}

/* ---------- MAIN ---------- */
int main()
{
    const char *filename = "arquivo.txt";
    

    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("fopen"); return 1; }

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2) {
        fprintf(stderr, "Formato invalido (precisa V E na primeira linha)\n");
        return 1;
    }

    /* Aloca vetores dinamicamente de acordo com V e E */
    adj      = calloc(V, sizeof(Edge*));
    deg      = calloc(V, sizeof(int));
    vis_v    = calloc(V, sizeof(int));
    vis_edge = calloc(E, sizeof(int));
    ciclo  = malloc((E + 1) * sizeof(int));
    S        = malloc((E + 1) * sizeof(int));

    /* Lê arestas */
    for (int i = 0, u, v; i < E; ++i) {
        if (fscanf(fp, "%d %d", &u, &v) != 2) {
            fprintf(stderr, "Linha de aresta faltando\n");
            return 1;
        }
        if (u < 0 || u >= V || v < 0 || v >= V) {
            fprintf(stderr, "Vertice fora do intervalo 0..V-1\n");
            return 1;
        }
        add_edge(u, v, i);
    }
    fclose(fp);

    /* 1. Verifica graus pares e escolhe vértice inicial */
    int start = -1;
    for (int i = 0; i < V; ++i) {
        if (deg[i] & 1) {
   puts("SEM CICLO");
   int contador = 0;
   for (int j = 0; j < V; j++) {
       if (deg[j] % 2 != 0) {
           contador++;
       }
   }
   fprintf(stderr, "Número de vértices ímpares:");
   fprintf(stderr, "%d\n", contador);
   
   if(contador <= 2){
      fprintf(stderr, "É semi-euleriano");
   }else{
       fprintf(stderr, "Não é semi-euleriano, pois possui mais de 2 vertices impares");
   }
   
   return 0;
}

   
   
        if (deg[i]) start = i;
    }
    if (start == -1) { puts("SEM CICLO"); return 0; } /* grafo vazio */

    /* 2. Conectividade sobre vértices de grau > 0 */
    dfs(start, V);
    for (int i = 0; i < V; ++i)
        if (deg[i] && !vis_v[i]) { puts("SEM CICLO"); return 0; }

    /* 3. Hierholzer */
    hierholzer(start, E);
    if (clen != E + 1) { puts("SEM CICLO"); return 0; }

    /* 4. Imprime circuito na ordem correta */
    
    for (int i = clen - 1; i >= 0; --i)
        printf("%d%c", ciclo[i], i ? ' ' : '\n');
int contador1 = 0;
        for (int i = 0; i < V; ++i) {
       
   
   for (int j = 0; j < V; j++) {
       if (deg[j] % 2 != 0) {
           contador1++;
       }
   }
        }
   fprintf(stderr, "Número de vértices ímpares:");
   fprintf(stderr, "%d\n", contador1);
   
   if(contador1 > 0 && contador1 <= 2){
      fprintf(stderr, "É semi-euleriano");
   }else{
       fprintf(stderr, "Não é semi-euleriano, pois possui mais de 2 vertices impares");
   }



   
   return 0;
}