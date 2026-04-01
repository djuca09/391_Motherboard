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

#endif /* INC_SEQUENCE_H_ */
