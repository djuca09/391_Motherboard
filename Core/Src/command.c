/*
 * command.c
 *
 *  Created on: Feb 9, 2026
 *      Author: Djuca
 */
#include "command.h"
#include <math.h>

void command_Init(Command_t *command, float Ktj, float v_max, float Ts){

	command->Ktj = Ktj;
	command->v_max = v_max; // mm/s
	command->Ts = Ts;

	command->target_pos = 0;
	command->pos_inc = 0;
	command->cmd_pos = 0;
}


int32_t position_Move(Command_t *command, float pos_mm, int32_t actual_pos){

	return position_Speed_Move(command, pos_mm, actual_pos, command->v_max);

}

int32_t position_Speed_Move(Command_t *command, float pos_mm, int32_t actual_pos, float spd){

	//Limit to max velocity
	if(spd > command->v_max) spd = command->v_max;

	//Task to joint space
	command->target_pos = (int32_t)lroundf(pos_mm * command->Ktj);

	//Using speed and sample time to calculate increment
	command->pos_inc = (int32_t)lroundf(spd*command->Ktj*command->Ts);

	//Scalar to vector
	if(command->target_pos < actual_pos) command->pos_inc *= -1;

	command->cmd_pos = actual_pos;

	return command->target_pos;

}

int32_t update_Command_Position(Command_t *command){

	int32_t new_cmd = command->cmd_pos + command->pos_inc;

	if(command->pos_inc > 0 && new_cmd >= command->target_pos)
		command->cmd_pos = command->target_pos;

	else if(command->pos_inc < 0 && new_cmd <= command->target_pos)
		command->cmd_pos = command->target_pos;

	else command->cmd_pos = new_cmd;

	return command->cmd_pos;

}

void command_Reset(Command_t *command){
	command->target_pos = 0;
	command->pos_inc = 0;
	command->cmd_pos = 0;
}

