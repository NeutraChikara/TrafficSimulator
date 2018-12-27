//
// Created by stud on 12/27/18.
//

#include "Roads.h"
#include <cmath>


int Roads::GetEntrypoint(int pointX, int pointY, int newPointX, int newpointY) {
    int dx = pointX - newPointX;
    int dy = pointY - newpointY;

    if (abs(dx) > abs(dy)) {
        return (dx > 0 ? 0 : 2);

    } else {
        return (dy > 0 ? 3 : 1);
    }


}


int Roads::GetExitPoint(int pointX, int pointY, int newPointX, int newpointY) {
    int dx = pointX - newPointX;
    int dy = pointY - newpointY;

    if (abs(dx) > abs(dy)) {
        return (dx > 0 ? 2 : 0);

    } else {
        return (dy > 0 ? 1 : 3);
    }
}
