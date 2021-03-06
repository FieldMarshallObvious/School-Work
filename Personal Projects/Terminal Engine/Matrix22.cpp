#include "Matrix22.h"
#include "Vector2.h"

Matrix22::Matrix22()
    :m00(1), m01(0),
    m10(0), m11(1)
{}

Matrix22::Matrix22(const Matrix22& oldMatrix)
    :m00(oldMatrix.m00), m01(oldMatrix.m01),
     m10(oldMatrix.m10), m11(oldMatrix.m11)
{}

Matrix22::~Matrix22(){}

void Matrix22::add(const Matrix22& left, const Matrix22& right, Matrix22& dest){
    dest.m00 = left.m00 + right.m00;
    dest.m01 = left.m01 + right.m01;
    dest.m10 = left.m10 + right.m10;
    dest.m11 = left.m11 + right.m11;
}

void Matrix22::subtract(const Matrix22& left, const Matrix22& right, Matrix22& dest)
{
    dest.m00 = left.m00 - right.m00;
    dest.m01 = left.m01 - right.m01;
    dest.m10 = left.m10 - right.m10;
    dest.m11 = left.m11 - right.m11;
}

void Matrix22::multiply(const Matrix22& left, const Matrix22& right, Matrix22& dest){
    float m00 = left.m00 * right.m00 + left.m10 * right.m01;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11;

    dest.m00 = m00;
    dest.m01 = m01;
    dest.m10 = m10;
    dest.m11 = m11;
}

void Matrix22::transform(const Matrix22& left, const Vector2& right, Vector2& dest){
    float x = left.m00 * right.getX() + left.m10 * right.getY();
    float y = left.m01 * right.getX() + left.m11 * right.getY();

    dest.setX(x);
    dest.setY(y);
}

Matrix22& Matrix22::operator+=(const Matrix22& right)
{
    Matrix22::add(*this, right, *this);
    return *this;
}
Matrix22& Matrix22::operator-=(const Matrix22& right)
{
    Matrix22::subtract(*this, right, *this);
    return *this;
}
Matrix22& Matrix22::operator*=(const Matrix22& right)
{
    Matrix22::multiply(*this, right, *this);
    return *this;
}


Matrix22 Matrix22::operator+(const Matrix22& right) const
{
    Matrix22 output;
    Matrix22::add(*this, right, output);

    return output;
}
Matrix22 Matrix22::operator-(const Matrix22& right) const
{
    Matrix22 output;
    Matrix22::subtract( *this, right, output );
    
    return output;
}
Matrix22 Matrix22::operator*(const Matrix22& right) const
{
    Matrix22 output; 
    Matrix22::multiply( *this, right, output );

    return output;
}

Vector2 Matrix22::operator*(const Vector2& vec) const
{
    Vector2 output; 
    Matrix22::transform( *this, vec, output );

    return output;
}


Matrix22& Matrix22::setIdentity()
{
    m00 = 1;
    m11 = 1;
    m01 = 0;
    m10 = 0;

    return *this;
}

Matrix22& Matrix22::setZero()
{
    m00 = 0;
    m11 = 0;
    m01 = 0;
    m10 = 0;

    return *this;
}

Matrix22& Matrix22::transpose() 
{
    float temp = m01;
    m01 = m10;
    m10 = temp;

    return *this;
}

Matrix22& Matrix22::invert()
{
    float determinant = getDeterminant();

    if ( determinant != 0 )
    {
        float determinant_inv = 1/(float)determinant;

        float t00 = this->m11*determinant_inv;
        float t01 = -this->m01*determinant_inv;
        float t11 = this->m00*determinant_inv;
        float t10 = -this->m10*determinant_inv;

        this->m00 = t00;
        this->m01 = t01;
        this->m10 = t10;
        this->m01 = t01;
    }

    return *this;
}

Matrix22& Matrix22::negate() 
{
    m00 = -m00;
    m01 = -m01;
    m10 = -m10;
    m11 = -m11;

    return *this;
}

float Matrix22::getDeterminant() const
{
    return m00 * m11 - m01 * m10;
}