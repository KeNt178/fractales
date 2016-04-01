/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "koch_fonctions.h"

void init_parameters(struct parameters *parameters, int argc, char *argv[])
{
	if (argc > 5) {
		//saisie auto
		parameters->segment_length = atoi(argv[1]);
		parameters->image_size = 2.0 * sqrt(3.0) / 3.0 * parameters->segment_length;
		parameters->nb_iterations = atoi(argv[2]);
		parameters->fg_color = strtol(argv[3], NULL, 0);
		parameters->bg_color = strtol(argv[4], NULL, 0);
		parameters->outfile = argv[5];

		if (argc == 7) {
			//le 7eme arg est-il "all" ?
			parameters->all_images = (strcmp(argv[6], "all") == 0);
		} else {
			//argc = 6, "all" n'est pas renseigne
			parameters->all_images = false;
		}
	} else {
		//saisie manuelle
		char buffer[1];
		parameters->outfile = malloc(50 * sizeof(char));

		printf("Nombre d'arguments erroné, saisie manuelle...\n");

		printf("Longueur segment : ");
		scanf("%d", &(parameters->segment_length));

		parameters->image_size = 2.0 * sqrt(3.0) / 3.0 * parameters->segment_length;

		printf("Nombre itérations : ");
		scanf("%d", &(parameters->nb_iterations));

		printf("Couleur tracé : ");
		scanf("%x", &(parameters->fg_color));

		printf("Couleur fond : ");
		scanf("%x", &(parameters->bg_color));

		printf("Fichier de sortie : ");
		scanf("%s", parameters->outfile);

		printf("Images intermédiaires ? (y/n) : ");
		scanf("%s", buffer);
		parameters->all_images = (strcmp(buffer, "y") == 0) ? true : false;
	}
	printf("Génération des images en cours...\n");
}

void show_koch_list(struct list *koch)
{
    while (koch != NULL) {
    	printf("(%d, %d)", koch->x, koch->y);
		koch = koch->next;
    }
	printf("\n");
}

void show_parameters(const struct parameters *parameters)
{
    printf("Longueur segment : %d\n", parameters->segment_length);
	printf("Taille image : %d\n", parameters->image_size);
	printf("Nombre itérations : %d\n", parameters->nb_iterations);
	printf("Couleur tracé : %#08x\n", parameters->fg_color);
	printf("Couleur fond : %#08x\n", parameters->bg_color);
	printf("Fichier de sortie : %s\n", parameters->outfile);
	printf("Images intermédiaires ? : %s\n", parameters->all_images ? "true" : "false");
}
