/*
 * mvm.h
 *
 *  Created on: 01.04.2019
 *      Author: Nils
 */

#ifndef MVM_H_
#define MVM_H_

#include "lvgl.h"


void createMoveGraph(lv_obj_t * parent);

void mvm_refresher_task(void * p);

void fkt_btn_motor2(uint8_t command);

void sendpoints();

void fkt_mvm_startposition();

void mvm_position_update();


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* MVM_H_ */
