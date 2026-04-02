/*
 * sequence.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Djuca
 */

#ifndef INC_SEQUENCE_H_
#define INC_SEQUENCE_H_

#include <stdint.h>

typedef struct {
    float position_mm;
    uint32_t fire_time_ms;
} SequenceStep_t;

typedef struct {
    SequenceStep_t *steps;
    uint16_t length;
    uint16_t current_step;
} Sequence_t;

void sequence_Init(Sequence_t *sequence, uint16_t length);

void step_Init(SequenceStep_t *step, float mm, uint32_t ms);

void addStep(Sequence_t *sequence, float mm, uint32_t ms, uint16_t ind);

void addSteps(Sequence_t *sequence, float *mm, uint32_t *ms, uint16_t len);

uint8_t indexSeq(Sequence_t *sequence);

#endif /* INC_SEQUENCE_H_ */
