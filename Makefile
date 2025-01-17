docker:
	docker run --rm -it -v C:\Users\nferr\Developer\RubixCubeSolver\:/src -w /src ev3cc

setup:
	./setup.sh

build:
	arm-linux-gnueabi-gcc -lev3dev-c main.c robot.h robot.c -o main