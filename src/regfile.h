#ifndef _H_REGFILE_
#define _H_REGFILE_

enum {
	REG_CONFIG		= 1,
	REG_READ_ONLY		= 2,
	REG_LINKED		= 4
};

enum {
#include "regdefs.h"
};

typedef union {

	float		f;
	int		i;
}
reg_val_t;

typedef struct {

	const char		*sym;
	const char		fmt[4];

	int			mode;
	reg_val_t		*link;

	void			(* proc) (const void *reg, void *lval, const void *rval);
	void			(* format) (const void *reg);
}
reg_t;

extern const reg_t	regfile[];

void reg_getval(const reg_t *reg, void *lval);
void reg_setval(const reg_t *reg, const void *rval);
void reg_format_rval(const reg_t *reg, const void *rval);
void reg_format(const reg_t *reg);

const reg_t *reg_search(const char *sym);
const reg_t *reg_search_fuzzy(const char *sym);

void reg_GET(int reg_ID, void *lval);
void reg_SET(int reg_ID, const void *rval);

int reg_GET_I(int reg_ID);
float reg_GET_F(int reg_ID);

void reg_SET_I(int reg_ID, int rval);
void reg_SET_F(int reg_ID, float rval);

#endif /* _H_REGFILE_ */

