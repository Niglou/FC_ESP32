#ifndef KALMAN_H
#define KALMAN_H

class Kalman {
public:
  Kalman();
  void init();
  void set_dt(float dt);
  float get_dt();
  void update(float *rate_est, float *angle_est, float rate_gyro, float accel_acc);

private:
  float R_gyro;
  float R_acc;

  float Q_rate;
  float Q_angle;
  float Q_biais;

  float X[3];

  float P[3][3];

  float dt;

};

#endif
