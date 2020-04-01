#ifndef H_CONFIG
#define H_CONFIG

/* INPUT MODE

  Analog  : PWM
*/
#define PWM_INPUT

/* INPUT GPIO PWM */
#define NUM_CHANNEL_GPIO  6
#define CHANNEL_GPIO      {35,34,39,38,37,21}

/* ASSIGN INPUT CHANNEL */
#define NUM_CHANNEL       6


/* ESC MODE

    Analog  : PWM / ONESHOT125 / ONESHOT45 / MULTISHOT
    Digital : DSHOT150 / DSHOT300 / DSHOT600 / DSHOT1200
*/
#define ESC_MODE        DSHOT600

/* GPIO OUTPUT MOTOR */
#define MOTOR_1_GPIO    9
#define MOTOR_2_GPIO    4
#define MOTOR_3_GPIO    27
#define MOTOR_4_GPIO    26



#endif
