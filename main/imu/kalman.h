#ifndef KALMAN_H
#define KALMAN_H

class Kalman {
public:
  Kalman();
  void update(float *rate_est, float *angle_est, float rate_gyro, float accel_acc);

private:
  float R_gyro = 0.01f;
  float R_acc = 0.5f;

  float Q_rate = 0.1f;
  float Q_angle = 0.001f;
  float Q_biais = 0.003f;

  float X[3] = {0};

  float P[3][3] = {0};

  float dt = 0.001f;

};

void kalman_update(float _rate_est[], float _angle_est[], float _rate_gyro[], float _angle_acc[]);

#endif
