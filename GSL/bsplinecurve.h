#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include "gltypes.h"
#include <vector>
#include "vec3.h"

using namespace gsl;

class BSplineCurve
{
public:
    BSplineCurve();

    unsigned int getIntervalFromTime(float x, std::vector<float> &knots);
    Vec3 evaluate(unsigned int k, unsigned int degree, unsigned int i, float x, std::vector<float> &knots, std::vector<gsl::Vec3>& ctrlPoints);
};

#endif // BSPLINECURVE_H
