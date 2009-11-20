#ifndef GRAIN_H_
#define GRAIN_H_

#include <psptypes.h>

#define MAX_GRAIN 500

typedef struct tagGRAIN {
	struct tagGRAIN	*next;
	struct tagGRAIN	*prev;

	ScePspSVector2 s, v;
	short pos;
	unsigned char color;
} GRAIN;

extern GRAIN *grainUseLink;

void initGrain(void);
GRAIN *allocGrain(void);
GRAIN *freeGrain(GRAIN *current);

#endif /* GRAIN_H_ */
