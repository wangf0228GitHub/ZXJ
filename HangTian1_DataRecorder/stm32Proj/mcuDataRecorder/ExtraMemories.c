#include "ExtraMemories.h"

void __attribute__((constructor)) IDT71V321_Init()
{
	extern void *_siidt71v321_data, *_sidt71v321_data, *_eidt71v321_data;
	extern void *_sidt71v321_bss, *_eidt71v321_bss;

	void **pSource, **pDest;
	for (pSource = &_siidt71v321_data, pDest = &_sidt71v321_data; pDest != &_eidt71v321_data; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sidt71v321_bss; pDest != &_eidt71v321_bss; pDest++)
		*pDest = 0;

}

