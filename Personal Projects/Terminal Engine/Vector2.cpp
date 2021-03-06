#include "Vector2.h"
#include <math.h>

//Constructor
Vector2::Vector2(float x, float y)
  //Initilization List
  :x(x), y(y)
    {}

//Copy Constructor
Vector2::Vector2( const Vector2& oldVector )
    :x(oldVector.x), y(oldVector.y)
{}

Vector2& Vector2::operator=( const Vector2& oldVector )
{
    x = oldVector.x;
    y = oldVector.y;

    return *this;
}

Vector2::~Vector2(){}

float Vector2::length() const
{
    return sqrt( x * x + y * y );
}

void Vector2::add( const Vector2& left, const Vector2& right, Vector2& dest )
{
    dest.x = left.x + right.x;
    dest.y = left.y + right.y;
}

void Vector2::subtract( const Vector2& left, const Vector2& right, Vector2& dest )
{
    dest.x = left.x - right.x;
    dest.y = left.y - right.y;
}

void Vector2::multiply( const Vector2& left, const Vector2& right, Vector2& dest )
{
    dest.x = left.x * right.x;
    dest.y = left.y * right.y;   
}

void Vector2::lerp(  const Vector2& a, const Vector2& b, float t, Vector2& dest )
{
    dest.x = a.x + ( ( b.x - a.x ) * t );
    dest.y = a.y + ( ( b.y - a.y ) * t );
}

Vector2& Vector2::operator+=(const Vector2& right)
{
    Vector2::add(*this, right, *this);
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& right)
{
    Vector2::subtract( *this, right, *this );
    return *this;
}

Vector2 Vector2::operator+(const Vector2& right) const
{
    Vector2 output;
    Vector2::add( *this, right, output );

    return output;
}
Vector2 Vector2::operator-(const Vector2& right) const
{
    Vector2 output;
    Vector2::subtract( *this, right, output );

    return output;
}
float Vector2::operator*(const Vector2& b) const
{
    float output = Vector2::dotProduct( *this, b );

    return output;
}

float Vector2::dotProduct( const Vector2& left, const Vector2& right )
{
    return left.x * right.x + left.y * right.y;
}

float Vector2::angle( const Vector2& left, const Vector2& right )
{
    float dot = Vector2::dotProduct( left, right );

    return acos( dot/(left.length() *  right.length()));
}

float Vector2::distance( const Vector2& a, const Vector2& b )
{
    float xDiff = a.x - b.x;
    float yDiff = a.y - b.y;

    return sqrt( xDiff * xDiff + yDiff * yDiff );
}

Vector2 Vector2::getNormalized( const Vector2& input )
{
    Vector2 ret(input);

    ret.normalize();

    return ret;
}

void Vector2::scale( float s )
{
    x += s;
    y += s;
}

void Vector2::normalize( )
{
    float mag = length( ); 

    x /= mag;
    y /= mag;
}