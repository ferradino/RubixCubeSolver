#ifndef __COLOR_SENSOR_H
#define __COLOR_SENSOR_H

#define BUFFER_SIZE 256

typedef enum {
    WHITE,
    YELLOW,
    BLUE,
    RED,
    GREEN,
    ORANGE,
} color_t;

typedef struct RGB {
    int red_value;
    int green_value;
    int blue_value;
} rgb_t;

typedef struct HSV {
    int hue;
    int saturation;
    int value;
} hsv_t;

typedef struct ColorSenor {
    int number;
    rgb_t rgb_value;
    hsv_t hsv_value;
    color_t color;
    char mode_file_path[256];
    char red_value_file_path[256];
    char green_value_file_path[256];
    char blue_value_file_path[256];
} color_sensor_t;

color_sensor_t color_sensor_init(const char* port);
color_t read_color(color_sensor_t *sensor);

#endif
