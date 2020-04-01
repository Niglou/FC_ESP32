#include <math.h>
#include "kalman.h"

#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f

Kalman::Kalman() {}

void Kalman::init() {
  R_gyro = 0.001f;
  R_acc = 10.0f;
  Q_rate = 0.001f;
  Q_angle = 0.0001f;
  Q_biais = 0.000001f;
  dt = 0.001f;

  for(int i=0; i<3; i++) X[i] = 0;

  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      P[i][j] = 0;

}

void Kalman::set_dt(float dt) {
  this->dt = dt;
}

float Kalman::get_dt() { return dt; }

void Kalman::update(float *rate_est, float *angle_est, float rate_gyro, float accel_acc) {
  unsigned int i, j;

  // **************** Prédiction
  // Xp = A*X
  float Xp[3] = {0};
  Xp[0] = X[0];
  Xp[1] = dt*X[0] + X[1];
  Xp[2] = X[2];

  float _gcosalpha = -cos(Xp[1]*DEG_TO_RAD);

  // Pp = A*P*At + Q
  float Pp[3][3] = {0};
  Pp[0][0] = P[0][0] + Q_rate;
  Pp[0][1] = dt*P[0][0] + P[0][1];
  Pp[0][2] = P[0][2];
  Pp[1][0] = dt*P[0][0] + P[0][1];
  Pp[1][1] = dt*(dt*P[0][0] + P[1][0]) + dt*P[0][1] + P[1][1] + Q_angle;
  Pp[1][2] = dt*P[0][2] + P[1][2];
  Pp[2][0] = P[2][0];
  Pp[2][1] = dt*P[2][0] + P[2][1];
  Pp[2][2] = P[2][2] + Q_biais;

  // ***************** Mise à jour
  // HPpHtR = H*Pp*Ht + R
  float HPpHtR[2][2] = {0};
  /*
  // LINEAIRE
  HPpHtR[0][0] = Pp[0][0] + Pp[2][0] + Pp[0][2] + Pp[2][2] + R_gyro;
  HPpHtR[0][1] = Pp[0][1] + Pp[2][1];
  HPpHtR[1][0] = Pp[1][0] + Pp[1][2];
  HPpHtR[1][1] = Pp[1][1] + R_acc;
  */
  // ETENDUE
  HPpHtR[0][0] = Pp[0][0] + Pp[2][0] + Pp[0][2] + Pp[2][2] + R_gyro;
  HPpHtR[0][1] = (Pp[0][1] + Pp[2][1]) * _gcosalpha;
  HPpHtR[1][0] = (Pp[1][0] + Pp[1][2]) * _gcosalpha;
  HPpHtR[1][1] = Pp[1][1] * _gcosalpha * _gcosalpha + R_acc;

  // PpHt = Pp*Ht
  float PpHt[3][2] = {0};
  /*
  // LINEAIRE
  PpHt[0][0] = Pp[0][0] + Pp[0][2];
  PpHt[0][1] = Pp[0][1];
  PpHt[1][0] = Pp[1][0] + Pp[1][2];
  PpHt[1][1] = Pp[1][1];
  PpHt[2][0] = Pp[2][0] + Pp[2][2];
  PpHt[2][1] = Pp[2][1];
  */
  // ETENDUE
  PpHt[0][0] = Pp[0][0] + Pp[0][2];
  PpHt[0][1] = Pp[0][1] * _gcosalpha;
  PpHt[1][0] = Pp[1][0] + Pp[1][2];
  PpHt[1][1] = Pp[1][1] * _gcosalpha;
  PpHt[2][0] = Pp[2][0] + Pp[2][2];
  PpHt[2][1] = Pp[2][1] * _gcosalpha;

  float inv_sca = 1.0 / (HPpHtR[0][0]*HPpHtR[1][1] - HPpHtR[0][1]*HPpHtR[1][0]);
  float inv_HPpHtR[2][2] = {0};
  inv_HPpHtR[0][0] = HPpHtR[1][1] * inv_sca;
  inv_HPpHtR[0][1] = -HPpHtR[0][1] * inv_sca;
  inv_HPpHtR[1][0] = -HPpHtR[1][0] * inv_sca;
  inv_HPpHtR[1][1] = HPpHtR[0][0] * inv_sca;

  float K[3][2] = {0};
  for(i = 0; i < 3; i++)
    for(j = 0; j < 2; j++)
      K[i][j] = PpHt[i][0]*inv_HPpHtR[0][j] + PpHt[i][1]*inv_HPpHtR[1][j];

  // P = (I - K*H)*Pp
  float IKH[3][3] = {0};
  /*
  // LINEAIRE
  IKH[0][0] = 1 - K[0][0];
  IKH[0][1] = -K[0][1];
  IKH[0][2] = -K[0][0];
  IKH[1][0] = -K[1][0];
  IKH[1][1] = 1 - K[1][1];
  IKH[1][2] = -K[1][0];
  IKH[2][0] = -K[2][0];
  IKH[2][1] = -K[2][1];
  IKH[2][2] = 1 - K[2][0];
  */
  // ETENDUE
  IKH[0][0] = 1 - K[0][0];
  IKH[0][1] = -K[0][1] * _gcosalpha;
  IKH[0][2] = -K[0][0];
  IKH[1][0] = -K[1][0];
  IKH[1][1] = 1 - K[1][1] * _gcosalpha;
  IKH[1][2] = -K[1][0];
  IKH[2][0] = -K[2][0];
  IKH[2][1] = -K[2][1] * _gcosalpha;
  IKH[2][2] = 1 - K[2][0];

  for(i = 0; i < 3; i++)
    for(j = 0; j < 3; j++)
      P[i][j] = IKH[i][0]*Pp[0][j] + IKH[i][1]*Pp[1][j] + IKH[i][2]*Pp[2][j];

  // X = Xp + K*(mesure - H*Xp)
  float MHXp[2];
  /*
  // LINEAIRE
  MHXp[0] = _rate_gyro[e] - (Xp[0] + Xp[2]);
  MHXp[1] = accel_acc[e] - Xp[1];
  */
  MHXp[0] = rate_gyro - (Xp[0] + Xp[2]);
  MHXp[1] = accel_acc + sin(Xp[1]*DEG_TO_RAD);

  for(i = 0; i < 3; i++)
    X[i] = Xp[i] + (K[i][0]*MHXp[0] + K[i][1]*MHXp[1]);

  if(X[1] > 180) X[1] -= 360;
  else if(X[1] < -180) X[1] += 360;

  *rate_est = X[0];

  *angle_est = X[1];

}
