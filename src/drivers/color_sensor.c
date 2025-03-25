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
            printf("Found sensor-> connected to port: %s\n", port);
            break;
        }
    }

    if (sensor_number == -1) {
        fprintf(stderr, "Failed to find motor connected to port: %s\n", port);
        exit(EXIT_FAILURE);
    }
    
    return sensor_number;
}

color_sensor_t color_sensor_init() {
    const char* sensor_port = "in4";

    color_sensor_t sensor = {
      .number = get_sensor_number(sensor_port),
      .mode_file_path = snprintf(sensor.mode_file_path, sizeof(sensor.mode_file_path), "/sys/class/lego-sensor/sensor%d/mode", sensor.number), 
      .red_value_file_path = snprintf(sensor.red_value_file_path, sizeof(sensor.red_value_file_path), "/sys/class/lego-sensor/sensor%d/value0", sensor.number), 
      .green_value_file_path = snprintf(sensor.green_value_file_path, sizeof(sensor.green_value_file_path), "/sys/class/lego-sensor/sensor%d/value1", sensor.number),
      .blue_value_file_path = snprintf(sensor.blue_value_file_path, sizeof(sensor.blue_value_file_path), "/sys/class/lego-sensor/sensor%d/value2", sensor.number),

    };
    
    printf("Sensor initialized with number: %d\n", sensor.number);

    return sensor;
}

void read_color_values(color_sensor_t *sensor) {
    int fd, fd1, fd2;
    char r[BUFFER_SIZE];
    char g[BUFFER_SIZE];
    char b[BUFFER_SIZE];

    fd = open(sensor->red_value_file_path, O_RDONLY);
    fd1 = open(sensor->green_value_file_path, O_RDONLY);
    fd2 = open(sensor->blue_value_file_path, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "Failed to open red value file: %s\n", sensor->red_value_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    } 

    if (fd1 == -1) {
        fprintf(stderr, "Failed to open green value file: %s\n", sensor->green_value_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    } 

    if  (fd2 == -1) {
        fprintf(stderr, "Failed to open blue value file: %s\n", sensor->blue_value_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    }

    read(fd, r, BUFFER_SIZE);
    read(fd1, g, BUFFER_SIZE);
    read(fd2, b, BUFFER_SIZE);

    close(fd);
    close(fd1);
    close(fd2);

    sensor->rgb_value.red_value = atoi(r);
    sensor->rgb_value.green_value = atoi(g);
    sensor->rgb_value.blue_value = atoi(b);
}

void convert_RGB_to_HSV(color_sensor_t *sensor) {
    float r = sensor->rgb_value.red_value / 255.0;
    float g = sensor->rgb_value.green_value / 255.0;
    float b = sensor->rgb_value.blue_value / 255.0;

    float max = r > g ? (r > b ? r : b) : (g > b ? g : b);
    float min = r < g ? (r < b ? r : b) : (g < b ? g : b);

    float diff = max - min;

    if (max == min) {
        sensor->hsv_value.hue = 0;
    } else if (max == r) {
        sensor->hsv_value.hue = (int)(60 * ((g - b) / diff) + 360) % 360;
    } else if (max == g) {
        sensor->hsv_value.hue = (int)(60 * ((b - r) / diff) + 120) % 360;
    } else {
        sensor->hsv_value.hue = (int)(60 * ((r - g) / diff) + 240) % 360;
    }

    if (max == 0) {
        sensor->hsv_value.saturation = 0;
    } else {
        sensor->hsv_value.saturation = (diff / max) * 100;
    }

    sensor->hsv_value.value = max * 100;
}

void convert_HSV_to_color(color_sensor_t *sensor) {
   if (sensor->hsv_value.hue < 10 && sensor->hsv_value.saturation < 10) {
        sensor->color = WHITE;
    } else if (sensor->hsv_value.hue < 10 && sensor->hsv_value.saturation > 90) {
        sensor->color = RED;
    } else if (sensor->hsv_value.hue > 24 && sensor->hsv_value.hue < 46) {
        sensor->color = ORANGE;
    } else if (sensor->hsv_value.hue > 54 && sensor->hsv_value.hue < 66) {
        sensor->color = YELLOW;
    } else if (sensor->hsv_value.hue > 114 && sensor->hsv_value.hue < 126) {
        sensor->color = GREEN;
    } else if (sensor->hsv_value.hue > 234 && sensor->hsv_value.hue < 246) {
        sensor->color = BLUE;
    } else {
        sensor->color = WHITE;
    }
}

color_t read_color(color_sensor_t *sensor) {
    read_color_values(sensor);
    convert_RGB_to_HSV(sensor);
    convert_HSV_to_color(sensor);

    return sensor->color;
}
