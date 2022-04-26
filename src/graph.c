#include "../include/graph.h"

// void parcours(hash_t **E, article_t **N, int s, size_t E_size,
//               size_t N_size) {
//     size_t dist[E_size];
//     size_t pred[E_size];
//     size_t
//         F[E_size]; // Tableau qui contient tout les somment a
//         explorer

//     for (int i = 0; i < E_size; i++) {

//         dist[i] = 999999;
//         pred[i] = -1;
//         F[i] = 1; // On met tout a 1, au debut on a tout a explorer
//     }

//     dist[s] = 0;
//     F[s] = 0;

//     for (int i = 0; i < E_size; i++) {

//         if (!F[i]) { // si c'est un sommet déjà exploré, on va voir
//         ou
//                      // il nous mene

//             // On parcours les liaisons qu'il a avec les autre
//             sommets

//             int *voisins = malloc(sizeof(int));
//             neighbours(F[i], N, E, voisins);
//             size_t j = voisins[0];

//             for (int k = 1; k <= j; k++) {
//                 if (dist[voisins[k]] > dist[i] + 1) {
//                     dist[voisins[k]] = dist[i] + 1;
//                     pred[voisins[k]] = i;
//                 }
//             }
//         }
//     }

//     int size2 = sizeof(pred);

//     for (int i = 0; i < size2; i++) {
//         printf("Distance du plus court chemin: %ld\n", pred[i]);
//     }
// }

int *calc_neighbors(int s, article_t **graph_article,
                    hash_t **hash_tab, int *neighbors) {

    if (hash_tab[s] == NULL)
        return NULL;

    int size_article = (hash_tab[s]->article)[0];

    for (int i = 1; i <= size_article; i++) {

        int article = (hash_tab[s]->article)[i];

        int size_author = (graph_article[article - 1]->author)[0];

        for (int j = 1; j < size_author; j++) {

            int here = is_in(neighbors[0], neighbors,
                             (graph_article[article]->author)[j]);

            if (here != 1 &&
                (graph_article[article]->author)[j] != s) {

                (neighbors[0])++;
                neighbors = realloc(neighbors,
                                    (neighbors[0] + 1) * sizeof(int));
                neighbors[neighbors[0]] =
                    (graph_article[article]->author)[j];
            }
        }
    }

    return neighbors;
}

int is_in(size_t size, int *tab, int elem) {

    for (int j = 0; j < size; j++) {

        if (tab[j] == elem) {
            return 1;
        }
    }

    return 0;
}

int *dist_n(int n, char *author, article_t **graph_article,
            hash_t **hash_tab, pair_t *pair) {

    if (n == 0)
        return NULL;

    size_t index =
        getBucketIndex2(author, hash_tab, pair->size) % pair->size;

    int *neighbors = malloc(2 * sizeof(int));
    neighbors[0] = 1;
    neighbors[1] = index;

    neighbors =
        calc_neighbors(index, graph_article, hash_tab, neighbors);

    if (neighbors == NULL)
        return NULL;

    if (n == 1)
        return neighbors;

    // i : iterator in author's neigbors list
    // k : counter of the number of the distance
    int i = 0, k = 0;

    while (k < n) {

        int *copy_neighbors = calc_neighbors(
            neighbors[i], graph_article, hash_tab, neighbors);

        if (copy_neighbors == NULL)
            return neighbors;

        if ((i % neighbors[0]) == 0)
            k++;

        i++;
    }

    return neighbors;
}