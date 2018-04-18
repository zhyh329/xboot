#ifndef __GRAPHIC_DOBJECT_H__
#define __GRAPHIC_DOBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xboot.h>
#include <graphic/matrix.h>
#include <graphic/display.h>

enum dobject_type_t {
	DOBJECT_TYPE_CONTAINER,
	DOBJECT_TYPE_NODE,
};

enum alignment_t {
	ALIGN_NONE				= 0,
	ALIGN_LEFT				= 1,
	ALIGN_TOP				= 2,
	ALIGN_RIGHT				= 3,
	ALIGN_BOTTOM			= 4,
	ALIGN_LEFT_TOP			= 5,
	ALIGN_RIGHT_TOP			= 6,
	ALIGN_LEFT_BOTTOM		= 7,
	ALIGN_RIGHT_BOTTOM		= 8,
	ALIGN_LEFT_CENTER		= 9,
	ALIGN_TOP_CENTER		= 10,
	ALIGN_RIGHT_CENTER		= 11,
	ALIGN_BOTTOM_CENTER		= 12,
	ALIGN_HORIZONTAL_CENTER	= 13,
	ALIGN_VERTICAL_CENTER	= 14,
	ALIGN_CENTER			= 15,
	ALIGN_LEFT_FILL			= 16,
	ALIGN_TOP_FILL			= 17,
	ALIGN_RIGHT_FILL		= 18,
	ALIGN_BOTTOM_FILL		= 19,
	ALIGN_HORIZONTAL_FILL	= 20,
	ALIGN_VERTICAL_FILL		= 21,
	ALIGN_CENTER_FILL		= 22,
};

struct dobject_t
{
	enum dobject_type_t type;
	struct dobject_t * parent;
	struct list_head entry;
	struct list_head children;

	double width, height;
	double x, y;
	double rotation;
	double scalex, scaley;
	double anchorx, anchory;
	double alpha;
	enum alignment_t alignment;
	int visible;
	int touchable;
	int mflag;
	struct matrix_t local_matrix;
	struct matrix_t global_matrix;

	void (*draw)(struct dobject_t * o, struct display_t * d);
	void * priv;
};

typedef void (*dobject_draw_t)(struct dobject_t * o, struct display_t * d);

struct dobject_t * dobject_alloc_container(void);
struct dobject_t * dobject_alloc_node(dobject_draw_t draw, void * priv);
bool_t dobject_free(struct dobject_t * o);
bool_t dobject_add(struct dobject_t * parent, struct dobject_t * o);
bool_t dobject_remove(struct dobject_t * parent, struct dobject_t * o);
bool_t dobject_remove_self(struct dobject_t * o);

void dobject_set_width(struct dobject_t * o, double w);
void dobject_set_height(struct dobject_t * o, double h);
void dobject_set_size(struct dobject_t * o, double w, double h);
void dobject_set_x(struct dobject_t * o, double x);
void dobject_set_y(struct dobject_t * o, double y);
void dobject_set_position(struct dobject_t * o, double x, double y);
void dobject_set_rotation(struct dobject_t * o, double r);
void dobject_set_scale_x(struct dobject_t * o, double x);
void dobject_set_scale_y(struct dobject_t * o, double y);
void dobject_set_scale(struct dobject_t * o, double x, double y);
void dobject_set_archor_x(struct dobject_t * o, double x);
void dobject_set_archor_y(struct dobject_t * o, double y);
void dobject_set_archor(struct dobject_t * o, double x, double y);
void dobject_set_alpha(struct dobject_t * o, double alpha);
void dobject_set_alignment(struct dobject_t * o, enum alignment_t align);
void dobject_set_visible(struct dobject_t * o, int visible);
void dobject_set_touchable(struct dobject_t * o, int touchable);
struct matrix_t * dobject_local_matrix(struct dobject_t * o);
struct matrix_t * dobject_global_matrix(struct dobject_t * o);
void dobject_bounds(struct dobject_t * o, double * x1, double * y1, double * x2, double * y2);
void dobject_global_to_local(struct dobject_t * o, double * x, double * y);
void dobject_local_to_global(struct dobject_t * o, double * x, double * y);
int dobject_hit_test_point(struct dobject_t * o, double x, double y);

#ifdef __cplusplus
}
#endif

#endif /* __GRAPHIC_DOBJECT_H__ */
