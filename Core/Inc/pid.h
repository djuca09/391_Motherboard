/*
 * pid.h
 *
 *  Created on: Feb 9, 2026
 *      Author: Djuca
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include <stdint.h>
#include <stdio.h>

typedef struct {

    float Kp,Ki,Kd;
    float Ts,Td;
    float u_max,u_min;
    float I,P,D;
    float e_prev;
    float Df_prev;


} PID_t;

void PID_Init(PID_t *pid, float Kp, float Ki, float Kd, float Ts, float Td, float u_max, float u_min);
void PID_Reset(PID_t *pid);
float PID_Update(PID_t *pid, int32_t cmd_pos, int32_t act_pos);
void PID_TuneKi(PID_t *pid, float Ki);
void PID_TuneKp(PID_t *pid, float Kp);
void PID_TuneKd(PID_t *pid, float Kd);

#endif /* INC_PID_H_ */
