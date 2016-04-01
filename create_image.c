/*
 * Fichier : create_image.c
 * Description : Creation d'un fichier ppm a partir d'une image sous la forme
 *               d'un tableau uint32_t *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "create_image.h"

void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename)
{
	//ouverture du fichier et ecriture de l'entete
    FILE *file = fopen(filename, "wb");
	fprintf(file, "P6\n%d %d\n255\n", size_x, size_y);

	unsigned char color[3];

	//ecriture de chaque pixel de picture
	for (int32_t i = 0; i < size_x * size_y; i++) {
			get_rgb(pic[i], color);
			fwrite(color, 1, 3, file);
	}

	//fermeture du fichier
	fclose(file);
}

/* Calcul les rgb du pixel en binaire */
void get_rgb(uint32_t pixel, unsigned char *color) {
	color[0] = (pixel >> 16) & 0xFF;
	color[1] = (pixel >> 8) & 0xFF;
	color[2] = pixel & 0xFF;
}

/* Genere le fichier de sortie en fonction du nombre d'iterations */
void get_filename(uint32_t i, char *infile, char *outfile) {
	if (i < 10) {
		sprintf(outfile, "0%u_%s", i, infile);
	} else {
		sprintf(outfile, "%u_%s", i, infile);
	}
}
