#include <unistd.h>
#include <fcntl.h>

int main(void) {
  int fd = open("/sys/class/tacho-motor/motor1/command", O_WRONLY);
  write(fd, "reset\n", 6);

  int fd2 = open("/sys/class/tacho-motor/motor1/speed_sp", O_WRONLY);
  write(fd2, "500\n", 4);
  close(fd2);

  write(fd, "run-forever\n", 12);

  sleep(4);
  
  write(fd, "stop\n", 5);
  close(fd);

  return 0;
}