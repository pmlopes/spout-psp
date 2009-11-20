#include "grain.h"

GRAIN grain[MAX_GRAIN];

GRAIN *grainUseLink, *grainFreeLink;

void initGrain(void)
{
	int i;

	for(i = 0; i < MAX_GRAIN - 1; i ++) {
		grain[i].next = &grain[i + 1];
	}
	grain[i].next = NULL;

	grainFreeLink = grain;
	grainUseLink = NULL;

	return;
}

GRAIN *allocGrain(void)
{
	GRAIN *current = grainFreeLink;

	if(current) {
		grainFreeLink = current->next;

		current->next = grainUseLink;
		current->prev = NULL;
		if(current->next) {
			current->next->prev = current;
		}
		grainUseLink = current;
	}

	return current;
}

GRAIN *freeGrain(GRAIN *current)
{
	GRAIN *next = current->next;

	if(next) {
		next->prev = current->prev;
	}
	if(current->prev) {
		current->prev->next = next;
	} else {
		grainUseLink = next;
	}

	current->next = grainFreeLink;
	grainFreeLink = current;

	return next;
}
