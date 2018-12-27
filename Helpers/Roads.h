//
// Created by stud on 12/27/18.
//

#ifndef TRAFFICSIMULATOR_LIENS_H
#define TRAFFICSIMULATOR_LIENS_H


class Roads {
public:
    static int GetEntrypoint(int pointX, int pointY, int newPointX, int newpointY);
    static int GetExitPoint(int pointX, int pointY, int newPointX, int newpointY);

};


#endif //TRAFFICSIMULATOR_LIENS_H
