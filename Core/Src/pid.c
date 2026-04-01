/*
 * pid.c
 *
 *  Created on: Feb 9, 2026
 *      Author: Djuca
 */

#include "pid.h"

void PID_Init(PID_t *pid, float Kp, float Ki, float Kd, float Ts, float Td, float u_max, float u_min)
{
    if (pid == 0) return;

    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->Ts = Ts;
    pid->Td = Td;
    pid->u_max = u_max;
    pid->u_min = u_min;

    // Internal state
    pid->D = 0.0f;
    pid->P = 0.0f;
    pid->I = 0.0f;
    pid->e_prev = 0.0f;
    pid->Df_prev = 0.0f;

}

void PID_Reset(PID_t *pid){
	pid->I = 0.0f;
	pid->e_prev = 0.0f;
	pid->Df_prev = 0.0f;
}

void PID_ResetI(PID_t *pid){
	pid->I = 0.0f;
}

float PID_Update(PID_t *pid, int32_t cmd_pos, int32_t act_pos)
{
    if (pid == 0) return 0.0f;

    float e = cmd_pos - act_pos;

    // Derivative
    float de = (e - pid->e_prev) / pid->Ts;
    float D  = pid->Kd * de;
    pid->D = D;

    //Before checking for saturation
    float I_unsat = pid->I + pid->Ki * e * pid->Ts;
    float u = (pid->Kp * e) + I_unsat + D;
    pid->P = pid->Kp * e;

    //Check for saturation
    if (u > pid->u_max){
    	u = pid->u_max; //Clip
    	if(e < 0.0f) pid->I = I_unsat; //Allow unwinding
    }
    else if (u < pid->u_min){
    	u = pid->u_min;
    	if(e > 0.0f) pid->I = I_unsat;
    }
    else pid->I = I_unsat;

    // Save for next step
    pid->e_prev = e;

    return u;
}

void PID_TuneKi(PID_t *pid, float ki){
	pid->Ki = ki;
}

void PID_TuneKp(PID_t *pid, float kp){
	pid->Kp = kp;
}

void PID_TuneKd(PID_t *pid, float kd){
	pid->Kd = kd;
}

