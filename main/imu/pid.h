#ifndef PID_H
#define PID_H

#define LIMIT_PID 	600.0f
#define LIMIT_I 	300.0f

typedef struct Kpid Kpid;
struct Kpid {
  float P;
  float I;
  float D;
};

class PID {
public:
  PID();
  PID(float Kp, float Ki, float Kd);
  void Kp(float Kp);
  void Ki(float Ki);
  void Kd(float Kd);
  void K(float Kp, float Ki, float Kd);
  float Kp();
  float Ki();
  float Kd();
  float calcul(float as_cmd, float as_mesure);
  void reset_i_sum();

private:
  float _Kp;
  float _Ki;
  float _Kd;
  float _last_error;
  float _sum_i;

};
/*
float PID_calcul(Kpid constante, float va_cmd, float va_mesure, float *last_error, float *sum_i);
*/
#endif
