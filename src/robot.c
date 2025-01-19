#include "robot.h"

bool startRobot() { 
  return brick_init(); 
}

void stopRobot() { 
  brick_uninit();
}

void rotateCube() { 
  tacho_reset(OUTA);
  tacho_set_speed_sp(OUTA, tacho_get_max_speed(OUTA, 0) * 0.75);
  tacho_run_forever(OUTA);
  sleep_ms(4000);
  tacho_stop(OUTA);
}

void flipCube(){
}

void readColor() {
}