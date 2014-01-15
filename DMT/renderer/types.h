#ifndef _SI_TYPES_
#define _SI_TYPES_

enum BUFFER_LAYOUT {
	NONE,
	POS,
	POS_NORM,
	POS_NORM_TC
};


BUFFER_LAYOUT StringToBUFFER_LAYOUT(const SiString&& type);

#endif
