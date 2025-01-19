docker:
	docker run --rm -it -v C:\Users\nferr\Developer\RubixCubeSolver\:/src -w /src ev3cc

build:
	arm-linux-gnueabi-gcc main.c robot.h robot.c cube.h cube.c -o main