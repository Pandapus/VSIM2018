#include "bspline.h"

BSpline::BSpline()
{

}

uint BSpline::getIntervalFromTime(float x, vector<float> &knots)
{
    for(uint i = 0; i < knots.size()-1; i++)
    {
        if(x >= knots[i] && x < knots[i+1])
            return i;
    }
}

// https://chi3x10.wordpress.com/2009/10/18/de-boor-algorithm-in-c/
Vec3 BSpline::evaluate(uint k, uint degree, uint i, float x, vector<float> &knots, vector<Vec3> &ctrlPoints)
{
    // Please see wikipedia page for detail
    // note that the algorithm here kind of traverses in reverse order
    // comapred to that in the wikipedia page
    if( k == 0)
        return ctrlPoints[i];
    else
    {
        float alpha = (x-knots[i])/(knots[i+degree+1-k]-knots[i]);
        return (evaluate(k-1,degree, i-1, x, knots, ctrlPoints)*(1-alpha )+evaluate(k-1,degree, i, x, knots, ctrlPoints)*alpha );
    }
}
