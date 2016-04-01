#ifndef _CREATE_IMAGE_H_
#define _CREATE_IMAGE_H_

#include <inttypes.h>

extern void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename);

/* Calcul les rgb du pixel en binaire */
extern void get_rgb(uint32_t pixel, unsigned char *color);

/* Genere le fichier de sortie en fonction du nombre d'iterations */
extern void get_filename(uint32_t i, char *infile,char *outfile);

#endif
