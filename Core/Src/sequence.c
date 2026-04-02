/*
 * sequence.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Djuca
 */
#include <stdlib.h>
#include "sequence.h"

void sequence_Init(Sequence_t *sequence, uint16_t length){

	sequence->length = length;
	sequence->current_step = 0;
	sequence->steps = malloc(sizeof(SequenceStep_t) * length);

}

void step_Init(SequenceStep_t *step, float mm, uint32_t ms){
	step->fire_time_ms = ms;
	step->position_mm = mm;
}

void addStep(Sequence_t *sequence, float mm, uint32_t ms, uint16_t ind){

	step_Init(&(sequence->steps[ind]),mm,ms);

}

void addSteps(Sequence_t *sequence, float *mm, uint32_t *ms, uint16_t len){

	for(int i = 0; i<len; i++)
		addStep(sequence,mm[i],ms[i],i);

}

uint8_t indexSeq(Sequence_t *sequence){

	sequence->current_step += 1;
	if(sequence->current_step == sequence->length){
		sequence->current_step = 0;
		return 1;
	}else
		return 0;

}
