#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ataque{
	char name [150];
	float attack_prob;
	struct ataque *next;
}node;


node *read_file(char *filename, node *list, int category);
node *insert_list (node *list, char name[], float attack_prob);
node *sort_list_name(node *list);
node *sort_list_prob(node *list);
node *sort_3(node *list);
void swap (node *atacante1, node *atacante2);
void write_file (char arg[], int n , node *list[]);
