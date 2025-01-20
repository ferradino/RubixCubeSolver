#include "robot.h"

void startRobot() { }

void stopRobot() { }

void rotateCube() { 
  int fd = open("/sys/class/tacho-motor/motor1/command", O_WRONLY);
  write(fd, "reset\n", 6);

  int fd2 = open("/sys/class/tacho-motor/motor1/position_sp", O_WRONLY);
  write(fd2, "180\n", 4);
  close(fd2);

  int fd3 = open("/sys/class/tacho-motor/motor1/speed_sp", O_WRONLY);
  write(fd3, "350\n", 4);
  close(fd3);

  write(fd, "run-to-rel-pos\n", 20);
  sleep(5);
  close(fd);
}

void flipCube(){
  int fd = open("/sys/class/tacho-motor/motor0/command", O_WRONLY);
  write(fd, "reset\n", 6);

  int fd2 = open("/sys/class/tacho-motor/motor0/speed_sp", O_WRONLY);
  write(fd2, "350\n", 4);

  write(fd, "run-forever\n", 12);

  sleep(5);

  write(fd, "stop\n", 5);

  write(fd2, "-350\n", 4);

  write(fd, "run-forever\n", 12);

  sleep(5);

  write(fd, "stop\n", 5);

  close(fd2);
  
  close(fd);
}

void readColor() {
}