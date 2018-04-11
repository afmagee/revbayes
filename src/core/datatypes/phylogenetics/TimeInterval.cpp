#include "TimeInterval.h"

#include "RbConstants.h"
#include "RbException.h"
#include "RbMathLogic.h"

using namespace RevBayesCore;


TimeInterval::TimeInterval() : min(RbConstants::Double::nan), max(RbConstants::Double::nan)
{
}


TimeInterval::TimeInterval(double mn, double mx) : min(mn), max(mx)
{
    if( max < min )
    {
        throw(RbException("Time interval max < min"));
    }
}


/**
 * Equals operator.

 */
bool TimeInterval::operator==(const RevBayesCore::TimeInterval &t) const
{
    
    return min == t.min && max == t.max;
}


/**
 * Not equals operator. We simply invert the result of the equals operation.
 */
bool TimeInterval::operator!=(const RevBayesCore::TimeInterval &t) const
{
    
    return !operator==(t);
}


/**
 * Get the beginning time of the interval
 */
double TimeInterval::getMin(void) const
{

    if( RbMath::isNan(min) )
    {
        return 0.0;
    }

    return min;
}


/**
 * Set the beginning time of the interval
 */
void TimeInterval::setMin(double s)
{
    if( max < s )
    {
        throw(RbException("Time interval max < min"));
    }

    min = s;
}


/**
 * Get the beginning time of the interval
 */
double TimeInterval::getMax(void) const
{
    if( RbMath::isNan(max) )
    {
        return getMin();
    }

    return max;
}


/**
 * Set the beginning time of the interval
 */
void TimeInterval::setMax(double s)
{
    if( s < min )
    {
        throw(RbException("Time interval max < min"));
    }

    max = s;
}
