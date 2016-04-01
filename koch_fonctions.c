/*
 * Fichier : koch_fonctions.c
 * Description : Trace de fractales geometriques - flocon de koch - generation des points et rendu des lignes
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "koch_fonctions.h"
#include "create_image.h"

#define PI 3.14159265

/* Initialisation de la liste chainee koch correspondant au triangle
   de Koch initial */
void init_koch(struct list **koch, uint32_t size, uint32_t segment_length)
{
	struct list *a = *koch;
	struct list *e = malloc(sizeof(struct list));
	struct list *i = malloc(sizeof(struct list));
	struct list *last = malloc(sizeof(struct list));

	a->next = e;
	e->next = i;
	i->next = last;
	last->next = NULL;

	a->x = size / 2 - segment_length / 2;
	a->y = sqrt(3.0) / 6.0 * segment_length;

	e->x = size / 2;
	e->y = size;

	i->x = size / 2 + segment_length / 2;;
	i->y = a->y;

	//last = 4eme point pour fermer le triangle (memes coordonnees que a)
	last->x = a->x;
	last->y = a->y;
}

/* Initialisation de l'image avec la couleur de fond definie dans les
   parametres */
void init_picture(uint32_t **picture, uint32_t size, uint32_t bg_color)
{
	for (uint32_t i = 0; i < size; i++) {
		(*picture)[i] = bg_color;
    }
}

/* Calcul de la fractale de Koch apres un nombre d'iterations donne ;
   generation de la liste chainee koch correspondante */
void generer_koch(struct list *koch, uint32_t nb_iterations)
{
	if (nb_iterations > 0) {
		struct list *a = koch;
		struct list *e = a->next;

		while (e != NULL) {
			insertion_bcd(a, e);

			//mise a jour du couple a-e
			a = e;
			e = e->next;
		}

		//appel récursif sur la liste
		generer_koch(koch, nb_iterations - 1);
	}
}

/* Insertion de b, c et d entre a et e */
void insertion_bcd(struct list *a, struct list *e) {
	struct list *b = NULL;
	struct list *c = NULL;
	struct list *d = NULL;

	b = malloc(sizeof(struct list));
	c = malloc(sizeof(struct list));
	d = malloc(sizeof(struct list));


	//calcul des coordonnées
	b->x = (int32_t)a->x + (int32_t)(e->x - a->x) / 3;
	b->y = (int32_t)a->y + (int32_t)(e->y - a->y) / 3;
	d->x = (int32_t)a->x + (int32_t)(2 * (e->x - a->x)) / 3;
	d->y = (int32_t)a->y + (int32_t)(2 * (e->y - a->y)) / 3;
	c->y = (int32_t)(b->y + d->y) * cos(PI / 3.0) + (int32_t)(d->x - b->x) * sin(PI / 3.0);
	c->x = (int32_t)(b->x + d->x) * cos(PI / 3.0) - (int32_t)(d->y - b->y) * sin(PI / 3.0);

	//réorganisation des liaisons
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
}

/* Rendu image via algorithme bresehem - version generalisee
   simplifiee */
void render_image_bresenham(uint32_t *picture, struct list *koch, uint32_t size, uint32_t fg_color)
{
	struct list *p0 = koch;
	struct list *p1 = koch->next;

	while (p1 != NULL) {
		putLine(picture, size, fg_color, p0->x, p0->y, p1->x, p1->y);
		p0 = p1;
		p1 = p1->next;
	}
}

/* Dessine une ligne de couleur fg_color sur picture entre p0 et p1 */
void putLine(uint32_t *picture, uint32_t size, uint32_t fg_color, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
	int32_t e2, index;
	int32_t dx = (x0 < x1) ? x1 - x0 : x0 - x1;
	int32_t dy = (y0 < y1) ? y1 - y0 : y0 - y1;
	int32_t sx = (x0 < x1) ? 1 : -1;
	int32_t sy = (y0 < y1) ? 1 : -1;
	int32_t err = dx - dy;

	while (x0 != x1 || y0 != y1) {
		index = x0 * size + y0;
		picture[index] = fg_color;

		e2 = 2 * err;
		if (e2 > -dy) {
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 < dx) {
			err = err + dx;
			y0 = y0 + sy;
		}
	}
}

/* Liberation de la memoire allouee a la liste chainee */
void free_koch(struct list *koch)
{
	struct list *p = NULL;

	while (koch != NULL) {
		p = koch;
		koch = koch->next;
		free(p);
    }
}
