#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/drivers/color_sensor.h"

short get_sensor_number(const char *port) {
    char color_sensor_address_path[BUFFER_SIZE];
    char address[BUFFER_SIZE];
    int sensor_number = -1;

    for (int i = 0; i < 2; i++) {
        sprintf(color_sensor_address_path, "/sys/class/lego-sensor/sensor%d/address", i);
        int fd = open(color_sensor_address_path, O_RDONLY);
    
        if (fd == -1) {
            fprintf(stderr, "Failed to open motor address: %s\n", color_sensor_address_path);
            perror("Error");
            exit(EXIT_FAILURE);
        }

        read(fd, address, 256);
        close(fd);

        char *curr_port = strstr(address, ":");
        curr_port++;
        curr_port[strcspn(curr_port, "\n")] = 0;

        if (strcmp(curr_port, port) == 0) {
            sensor_number = i;
            printf("Found color_sensor connected to port: %s\n", port);
            break;
        }
    }

    if (sensor_number == -1) {
        fprintf(stderr, "Failed to find motor connected to port: %s\n", port);
        exit(EXIT_FAILURE);
    }
    
    return sensor_number;
}

void color_sensor_init() {
    const char* sensor_port = "in4";
    color_sensor.number = get_sensor_number(sensor_port);
    snprintf(color_sensor.mode_file_path, sizeof(color_sensor.mode_file_path), "/sys/class/lego-sensor/sensor%d/mode", color_sensor.number);
    snprintf(color_sensor.red_value_file_path, sizeof(color_sensor.red_value_file_path), "/sys/class/lego-sensor/sensor%d/value0", color_sensor.number);
    snprintf(color_sensor.green_value_file_path, sizeof(color_sensor.green_value_file_path), "/sys/class/lego-sensor/sensor%d/value1", color_sensor.number);
    snprintf(color_sensor.blue_value_file_path, sizeof(color_sensor.blue_value_file_path), "/sys/class/lego-sensor/sensor%d/value2", color_sensor.number);

    printf("Sensor initialized with number: %d\n", color_sensor.number);
}

void read_color_values() {
    int fd, fd1, fd2;
    char r[BUFFER_SIZE];
    char g[BUFFER_SIZE];
    char b[BUFFER_SIZE];

    fd = open(color_sensor.red_value_file_path, O_RDONLY);
    fd1 = open(color_sensor.green_value_file_path, O_RDONLY);
    fd2 = open(color_sensor.blue_value_file_path, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "Failed to open red value file: %s\n", color_sensor.red_value_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    } 

    if (fd1 == -1) {
        fprintf(stderr, "Failed to open green value file: %s\n", color_sensor.green_value_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    } 

    if  (fd2 == -1) {
        fprintf(stderr, "Failed to open blue value file: %s\n", color_sensor.blue_value_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    }

    read(fd, r, BUFFER_SIZE);
    read(fd1, g, BUFFER_SIZE);
    read(fd2, b, BUFFER_SIZE);

    close(fd);
    close(fd1);
    close(fd2);

    color_sensor.rgb_value.red_value = atoi(r);
    color_sensor.rgb_value.green_value = atoi(g);
    color_sensor.rgb_value.blue_value = atoi(b);
}

void convert_RGB_to_HSV() {
    float r = color_sensor.rgb_value.red_value / 255;
    float g = color_sensor.rgb_value.green_value / 255;
    float b = color_sensor.rgb_value.blue_value / 255;

    float max = r > g ? (r > b ? r : b) : (g > b ? g : b);
    float min = r < g ? (r < b ? r : b) : (g < b ? g : b);

    float diff = max - min;

    if (max == min) {
        color_sensor.hsv_value.hue = 0;
    } else if (max == r) {
        color_sensor.hsv_value.hue = (int)(60 * ((g - b) / diff) + 360) % 360;
    } else if (max == g) {
        color_sensor.hsv_value.hue = (int)(60 * ((b - r) / diff) + 120) % 360;
    } else {
        color_sensor.hsv_value.hue = (int)(60 * ((r - g) / diff) + 240) % 360;
    }

    if (max == 0) {
        color_sensor.hsv_value.saturation = 0;
    } else {
        color_sensor.hsv_value.saturation = (diff / max) * 100;
    }

    color_sensor.hsv_value.value = max * 100;
}

void convert_HSV_to_color() {
   if (color_sensor.hsv_value.hue < 10 && color_sensor.hsv_value.saturation < 10) {
        color_sensor.color = WHITE;
    } else if (color_sensor.hsv_value.hue < 10 && color_sensor.hsv_value.saturation > 90) {
        color_sensor.color = RED;
    } else if (color_sensor.hsv_value.hue > 24 && color_sensor.hsv_value.hue < 46) {
        color_sensor.color = ORANGE;
    } else if (color_sensor.hsv_value.hue > 54 && color_sensor.hsv_value.hue < 66) {
        color_sensor.color = YELLOW;
    } else if (color_sensor.hsv_value.hue > 114 && color_sensor.hsv_value.hue < 126) {
        color_sensor.color = GREEN;
    } else if (color_sensor.hsv_value.hue > 234 && color_sensor.hsv_value.hue < 246) {
        color_sensor.color = BLUE;
    } else {
        color_sensor.color = WHITE;
    }
}

enum Color read_color() {
    read_color_values();
    convert_RGB_to_HSV();
    convert_HSV_to_color();

    return color_sensor.color;
}
