/*
 * command.h
 *
 *  Created on: Feb 9, 2026
 *      Author: Djuca
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include <stdint.h>

typedef struct {
    int32_t target_pos;
    int32_t pos_inc;
    int32_t cmd_pos;
    float Ktj;
    float v_max; // mm/s
    float Ts;
} Command_t;

void command_Init(Command_t *command, float Ktj, float v_max, float Ts);
void position_Move(Command_t *command, float pos_mm, int32_t actual_pos);
void position_Speed_Move(Command_t *command, float pos_mm, int32_t actual_pos, float spd);
int32_t update_Command_Position(Command_t *command);
void command_Reset(Command_t *command);

#endif /* INC_COMMAND_H_ */
