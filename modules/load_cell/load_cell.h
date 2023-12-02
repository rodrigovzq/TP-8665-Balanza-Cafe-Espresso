//=====[#include guards - begin]===============================================

#ifndef _LOAD_CELL_H_
#define _LOAD_CELL_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================


void loadCellInit();

uint32_t loadCellReadRaw();

float loadCellReadGr();
float loadCellReadOz();
uint32_t read_average(int times);
void auto_scale(float scale);

uint32_t getOffset();
void tare();

//=====[#include guards - end]=================================================

#endif // _LOAD_CELL_H_