/*
 * Fichier : koch_main.c
 * Description : Trace de fractales geometriques - flocon de koch - programme principal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "koch_fonctions.h"
#include "koch_ihm.h"
#include "create_image.h"

int main(int argc, char **argv)
{
    struct parameters *parametres = malloc(sizeof(struct parameters));
	struct list *koch = malloc(sizeof(struct list));
	uint32_t *picture = NULL;

	//phase d'initialisation
	init_parameters(parametres, argc, argv);
	picture = malloc(parametres->image_size * parametres->image_size * sizeof(uint32_t));
	init_koch(&koch, parametres->image_size, parametres->segment_length);

	if (parametres->all_images) {
		char outfile[strlen(parametres->outfile) + 3];
		for (uint32_t i = 0; i <= parametres->nb_iterations; i++) {

			//generation du nom du fichier du sortie
			get_filename(i, parametres->outfile, outfile);

			//init render create
			init_picture(&picture, parametres->image_size * parametres->image_size, parametres->bg_color);
			render_image_bresenham(picture, koch, parametres->image_size, parametres->fg_color);
			create_image_ppm(picture, parametres->image_size, parametres->image_size, outfile);

			//on evite de generer une iteration suplementaire qui est couteuse
			if (i != parametres->nb_iterations) {
				generer_koch(koch, 1);
			}
		}
	} else {
		//on realise toute les iterations d'un coup
		generer_koch(koch, parametres->nb_iterations);

		//init render create
		init_picture(&picture, parametres->image_size * parametres->image_size, parametres->bg_color);
		render_image_bresenham(picture, koch, parametres->image_size, parametres->fg_color);
		create_image_ppm(picture, parametres->image_size, parametres->image_size, parametres->outfile);
	}

	free_koch(koch);
	if (argc < 6) {
		free(parametres->outfile);
	}
	free(parametres);
	free(picture);
    return EXIT_SUCCESS;
}
