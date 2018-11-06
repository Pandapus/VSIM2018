#ifndef BSPLINE_H
#define BSPLINE_H

#include <vector>
#include "vec3.h"

using namespace gsl;
using namespace std;

class BSpline
{
public:
    BSpline();

    uint getIntervalFromTime(float x, vector<float> &knots);
    float evaluateBasisFunction(uint i, uint p, float x);
    Vec3 evaluate(uint k, uint degree, uint i, float x, vector<float> &knots, vector<Vec3> &ctrlPoints);
};

#endif // BSPLINE_H
