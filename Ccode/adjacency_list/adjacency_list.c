#include<stdio.h>
#include<stdlib.h>

typedef struct a {
    int value;
    struct a* up;
    struct a* down;
    struct a* left;
    struct a* right;
} adjList;

int main() {
    adjList node;
    adjList* node2 = (adjList*) malloc(sizeof(adjList));
    node2->value = 2;
    node2->down = &node;
    node.value = 1;
    printf("%d\n%d\n", node.value, node2->value);
    printf("%d\n", node2->down->value);
    return 0;
}