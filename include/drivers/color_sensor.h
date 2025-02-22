#ifndef __COLOR_SENSOR_H
#define __COLOR_SENSOR_H

#define BUFFER_SIZE 256

enum Color {
    WHITE,
    YELLOW,
    BLUE,
    RED,
    GREEN,
    ORANGE,
};

typedef struct {
    int red_value;
    int green_value;
    int blue_value;
} RGB;

typedef struct {
    int hue;
    int saturation;
    int value;
} HSV;

typedef struct {
    int number;
    RGB rgb_value;
    HSV hsv_value;
    enum Color color;
    char mode_file_path[256];
    char red_value_file_path[256];
    char green_value_file_path[256];
    char blue_value_file_path[256];
} ColorSensor;

ColorSensor color_sensor;

void color_sensor_init();
enum Color read_color();

#endif
