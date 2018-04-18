/*
 * kernel/graphic/dobject.c
 *
 * Copyright(c) 2007-2018 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <xboot.h>
#include <graphic/dobject.h>

enum {
	MFLAG_TRANSLATE		= (0x1 << 0),
	MFLAG_ROTATE		= (0x1 << 1),
	MFLAG_SCALE			= (0x1 << 2),
	MFLAG_ANCHOR		= (0x1 << 3),
	MFLAG_LOCAL_MATRIX	= (0x1 << 4),
};

static struct dobject_t * __dobject_alloc(enum dobject_type_t type, dobject_draw_t draw, void * priv)
{
	struct dobject_t * o;

	o = malloc(sizeof(struct dobject_t));
	if(!o)
		return NULL;

	o->type = type;
	o->parent = o;
	init_list_head(&o->entry);
	init_list_head(&o->children);

	o->width = 0;
	o->height = 0;
	o->x = 0;
	o->y = 0;
	o->rotation = 0;
	o->scalex = 1;
	o->scaley = 1;
	o->anchorx = 0;
	o->anchory = 0;
	o->alpha = 1;
	o->alignment = ALIGN_NONE;
	o->visible = 1;
	o->touchable = 1;
	o->mflag = 0;
	matrix_init_identity(&o->local_matrix);
	matrix_init_identity(&o->global_matrix);

	o->draw = draw;
	o->priv = priv;

	return o;
}

struct dobject_t * dobject_alloc_container(void)
{
	return __dobject_alloc(DOBJECT_TYPE_CONTAINER, NULL, NULL);
}

struct dobject_t * dobject_alloc_node(dobject_draw_t draw, void * priv)
{
	return __dobject_alloc(DOBJECT_TYPE_NODE, draw, priv);
}

bool_t dobject_free(struct dobject_t * o)
{
	if(!o)
		return FALSE;
	free(o);
	return TRUE;
}

bool_t dobject_add(struct dobject_t * parent, struct dobject_t * o)
{
	if(!parent || !o)
		return FALSE;

	if(parent->type != DOBJECT_TYPE_CONTAINER)
		return FALSE;

	o->parent = parent;
	list_add_tail(&o->entry, &parent->children);
	return TRUE;
}

bool_t dobject_remove(struct dobject_t * parent, struct dobject_t * o)
{
	struct dobject_t * pos, * n;

	if(!parent || !o)
		return FALSE;

	if(parent->type != DOBJECT_TYPE_CONTAINER)
		return FALSE;

	list_for_each_entry_safe(pos, n, &(parent->children), entry)
	{
		if(pos == o)
		{
			pos->parent = pos;
			list_del(&(pos->entry));
			return TRUE;
		}
	}
	return FALSE;
}

bool_t dobject_remove_self(struct dobject_t * o)
{
	struct dobject_t * parent;
	struct dobject_t * pos, * n;
	bool_t ret;

	if(!o)
		return FALSE;

	if(o->type == DOBJECT_TYPE_CONTAINER)
	{
		list_for_each_entry_safe(pos, n, &(o->children), entry)
		{
			dobject_remove_self(pos);
		}
	}

	parent = o->parent;
	if(parent && (parent != o))
	{
		ret = dobject_remove(parent, o);
		if(ret)
			dobject_free(o);
		return ret;
	}

	dobject_free(o);
	return TRUE;
}

void dobject_set_width(struct dobject_t * o, double w)
{
	o->width = w;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_height(struct dobject_t * o, double h)
{
	o->height = h;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_size(struct dobject_t * o, double w, double h)
{
	o->width = w;
	o->height = h;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_x(struct dobject_t * o, double x)
{
	o->x = x;
	if((o->x != 0.0) || (o->y != 0.0))
		o->mflag |= MFLAG_TRANSLATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_y(struct dobject_t * o, double y)
{
	o->y = y;
	if((o->x != 0.0) || (o->y != 0.0))
		o->mflag |= MFLAG_TRANSLATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_position(struct dobject_t * o, double x, double y)
{
	o->x = x;
	o->y = y;
	if((o->x != 0.0) || (o->y != 0.0))
		o->mflag |= MFLAG_TRANSLATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_rotation(struct dobject_t * o, double r)
{
	o->rotation = r;
	if(o->rotation != 0.0)
		o->mflag |= MFLAG_ROTATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_scale_x(struct dobject_t * o, double x)
{
	o->scalex = x;
	if((o->scalex != 1.0) || (o->scaley != 1.0))
		o->mflag |= MFLAG_SCALE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_scale_y(struct dobject_t * o, double y)
{
	o->scaley = y;
	if((o->scalex != 1.0) || (o->scaley != 1.0))
		o->mflag |= MFLAG_SCALE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_scale(struct dobject_t * o, double x, double y)
{
	o->scalex = x;
	o->scaley = y;
	if((o->scalex != 1.0) || (o->scaley != 1.0))
		o->mflag |= MFLAG_SCALE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_archor_x(struct dobject_t * o, double x)
{
	o->anchorx = x;
	if((o->anchorx != 0.0) || (o->anchory != 0.0))
		o->mflag |= MFLAG_ANCHOR;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_archor_y(struct dobject_t * o, double y)
{
	o->anchory = y;
	if((o->anchorx != 0.0) || (o->anchory != 0.0))
		o->mflag |= MFLAG_ANCHOR;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_archor(struct dobject_t * o, double x, double y)
{
	o->anchorx = x;
	o->anchory = y;
	if((o->anchorx != 0.0) || (o->anchory != 0.0))
		o->mflag |= MFLAG_ANCHOR;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

void dobject_set_alpha(struct dobject_t * o, double alpha)
{
	o->alpha = alpha;
}

void dobject_set_alignment(struct dobject_t * o, enum alignment_t align)
{
	o->alignment = align;
}

void dobject_set_visible(struct dobject_t * o, int visible)
{
	o->visible = visible ? 1 : 0;
}

void dobject_set_touchable(struct dobject_t * o, int touchable)
{
	o->touchable = touchable ? 1 : 0;
}

struct matrix_t * dobject_local_matrix(struct dobject_t * o)
{
	struct matrix_t * m = &o->local_matrix;
	if(o->mflag & MFLAG_LOCAL_MATRIX)
	{
		matrix_init_identity(m);
		if(o->mflag & MFLAG_TRANSLATE)
			matrix_translate(m, o->x, o->y);
		if(o->mflag & MFLAG_ROTATE)
			matrix_rotate(m, o->rotation);
		if(o->mflag & MFLAG_ANCHOR)
			matrix_translate(m, -o->anchorx * o->width * o->scalex, -o->anchory * o->height * o->scaley);
		if(o->mflag & MFLAG_SCALE)
			matrix_scale(m, o->scalex, o->scaley);
		o->mflag &= ~(MFLAG_LOCAL_MATRIX);
	}
	return m;
}

struct matrix_t * dobject_global_matrix(struct dobject_t * o)
{
	struct dobject_t * t = o;
	struct matrix_t m;

	matrix_init_identity(&m);
	while((o->parent != o))
	{
		matrix_multiply(&m, &m, dobject_local_matrix(o));
		o = o->parent;
	}
	memcpy(&t->global_matrix, &m, sizeof(struct matrix_t));
	return &t->global_matrix;
}

void dobject_bounds(struct dobject_t * o, double * x1, double * y1, double * x2, double * y2)
{
	struct matrix_t * m = dobject_global_matrix(o);
	*x1 = 0;
	*y1 = 0;
	*x2 = o->width;
	*y2 = o->height;
	matrix_transform_bounds(m, x1, y1, x2, y2);
}

void dobject_global_to_local(struct dobject_t * o, double * x, double * y)
{
	struct matrix_t m;

	memcpy(&m, dobject_global_matrix(o), sizeof(struct matrix_t));
	matrix_invert(&m);
	matrix_transform_point(&m, x, y);
}

void dobject_local_to_global(struct dobject_t * o, double * x, double * y)
{
	struct matrix_t * m = dobject_global_matrix(o);
	matrix_transform_point(m, x, y);
}

int dobject_hit_test_point(struct dobject_t * o, double x, double y)
{
	dobject_global_to_local(o, &x, &y);
	return ((x >= 0) && (y >= 0) && (x <= o->width) && (y <= o->height)) ? 1 : 0;
}
