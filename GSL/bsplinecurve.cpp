#include "bsplinecurve.h"


BSplineCurve::BSplineCurve()
{

}

unsigned int BSplineCurve::getIntervalFromTime(float x, std::vector<float> &knots)
{
    for(unsigned int i = 0; i < knots.size(); i++)
        if(x >= knots[i] && x < knots[i+1])
            return i;
}

Vec3 BSplineCurve::evaluate(unsigned int k, unsigned int degree, unsigned int i, float x, std::vector<float> &knots, std::vector<Vec3> &ctrlPoints)
{
    if(k == 0)
        return ctrlPoints[i];
    else
    {
        float alpha = (x-knots[i])/(knots[i + degree + 1 - k]-knots[i]);
        return(evaluate(k-1, degree, i-1, x, knots, ctrlPoints)*(1-alpha)+evaluate(k-1, degree, i, x, knots, ctrlPoints)*alpha);
    }
}




