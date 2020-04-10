
#include <math.h>

#include "rx.h"

float apply_rc_expo(float command)
{
  float commandf = command / 500;
  float absCommandf = abs(commandf);

  command = commandf * (absCommandf*absCommandf*absCommandf) * 0.5 + commandf * 0.5;

  return command * 500;

}
