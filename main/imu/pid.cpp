#include "pid.h"

PID::PID() {}

PID::PID(float Kp, float Ki, float Kd) {
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}

void PID::Kp(float Kp) { _Kp = Kp; }
void PID::Ki(float Ki) { _Ki = Ki; }
void PID::Kd(float Kd) { _Kd = Kd; }
void PID::K(float Kp, float Ki, float Kd) {
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}
float PID::Kp() { return _Kp; }
float PID::Ki() { return _Ki; }
float PID::Kd() { return _Kd; }

void PID::reset_i_sum() { _sum_i = 0; }

float PID::calcul(float as_cmd, float as_mesure) {
  float error, Pc, Ic, Dc, PIDc;

  error = as_cmd - as_mesure;

  Pc = _Kp * error;

  _sum_i += error;
  Ic = _Ki * _sum_i;

  Dc = _Kd * (error - _last_error);
  _last_error = error;

  PIDc = Pc + Ic + Dc;

  if(PIDc > LIMIT_PID) PIDc = LIMIT_PID;
  else if(PIDc < -LIMIT_PID) PIDc = -LIMIT_PID;

  return PIDc;
}

/*
float PID_calcul(Kpid constant, float va_cmd, float va_mesure, float *last_error, float *sum_i) {

  float error = 0,
        P = 0,
        I = 0,
        D = 0;

  error = va_cmd - va_mesure;

  P = constant.P * error;

  if(error < LIMIT_I) {
    *sum_i += error;
    I = constant.I * *sum_i; }

  D = constant.D * (error - *last_error);

  *last_error = error;

  if(P > LIMIT_PID) P = LIMIT_PID;
  else if(P < -LIMIT_PID) P = -LIMIT_PID;

  if(I > LIMIT_PID) I = LIMIT_PID;
  else if(I < -LIMIT_PID) I = -LIMIT_PID;

  if(D > LIMIT_PID) D = LIMIT_PID;
  else if(D < -LIMIT_PID) D = -LIMIT_PID;

  return P + I + D;

}
*/
