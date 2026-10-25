#include <math.h>
#include <stdbool.h>

static double min(double a, double b) {
    return a < b ? a : b;
}

bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2,
                  int y2) {
    double dist = 0.0;

    if (xCenter < x1 || xCenter > x2) {
        dist += min(pow((double)x1 - xCenter, 2), pow((double)x2 - xCenter, 2));
    }
    if (yCenter < y1 || yCenter > y2) {
        dist += min(pow((double)y1 - yCenter, 2), pow((double)y2 - yCenter, 2));
    }

    return dist <= radius * radius;
}
