//=====[Libraries]=============================================================

#include "mbed.h"

#include "load_cell.h"

#include "espresso_scale.h"
#include "Hx711.h"
#include <cstdint>

//=====[Declaration and initialization of public global objects]===============
Hx711 loadcell(D11,D10,128);
uint32_t  LOADCELL_OFFSET =0;
const float LOADCELL_SCALE = 2172;

void loadCellInit(){
    loadcell.power_up();

    LOADCELL_OFFSET = read_average(5);
    
    loadcell.set_offset(LOADCELL_OFFSET);
    //loadcell.set_scale(LOADCELL_SCALE);
    //auto_scale(LOADCELL_SCALE);
}

uint32_t loadCellReadRaw(){
    return loadcell.readRaw();
}

float loadCellRead(){
    
    float x =  loadcell.read()/LOADCELL_SCALE;
    if (x<0 && x>-0.2)
        x=0;
    return x;
}

uint32_t read_average(int times) {
	long sum = 0;
	for (int i = 0; i < times; i++) {
		sum += loadcell.readRaw();
	}
	return sum / times;
}

void auto_scale(float scale){
    float diff;
    while(diff>0.002){
        loadcell.set_scale(scale);
        scale=scale/10;
    }
}

uint32_t getOffset(){
    return LOADCELL_OFFSET;
}

void tare(){

    LOADCELL_OFFSET = read_average(5);
    loadcell.set_offset(LOADCELL_OFFSET);

}