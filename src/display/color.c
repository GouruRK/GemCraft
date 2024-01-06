#include <MLV/MLV_all.h>
#include <math.h>

MLV_Color transform_color(int angle) {
    static int lightness = 100, saturation = 100;

    int r, g, b;
    if (!angle) angle = 0;

    if (0 <= angle && angle < 60) {
        r = 255; g = angle*4.25; b = 0;
    } else if (60 <= angle && angle < 120) {
        r = 255 - (angle - 60)*4.25; g = 255; b = 0;
    } else if (120 <= angle && angle < 180) {
        r = 0; g = 255; b = (angle - 180)*4.25; 
    } else if (180 <= angle && angle < 240) {
        r = 0; g = 255 - (angle - 180)*4.25; b = 255;
    } else if (240 <= angle && angle < 300) {
        r = (angle - 240)*4.25; g = 0; b = 255;
    } else {
        r = 255; g = 0; b = 255 - (angle - 300)*4.25;
    }

    r = (255 - r)*(100 - saturation)/100 + r;
    g = (255 - g)*(100 - saturation)/100 + g;
    b = (255 - b)*(100 - saturation)/100 + b;

    return MLV_rgba(r*lightness/100, g*lightness/100, b*lightness/100, 255);
}
