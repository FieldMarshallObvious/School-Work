#include "Matrix33.h"
#include "Vector3.h"

Matrix33::Matrix33()
    :m00(1), m01(0), m02(0),
     m10(0), m11(1), m12(0),
     m20(0), m21(0), m22(1)
{}

Matrix33::Matrix33(const Matrix33& oldMatrix)
    :m00(oldMatrix.m00), m01(oldMatrix.m01), m02(oldMatrix.m02),
     m10(oldMatrix.m10), m11(oldMatrix.m11), m12(oldMatrix.m12),
     m20(oldMatrix.m20), m21(oldMatrix.m21), m22(oldMatrix.m22)
{}

Matrix33::~Matrix33(){}

Matrix33& Matrix33::operator=(const Matrix33& m)
{
    this->m00 = m.m00;
    this->m01 = m.m01;
    this->m02 = m.m02;

    this->m10 = m.m10;
    this->m11 = m.m11;
    this->m12 = m.m12;

    this->m20 = m.m20;
    this->m21 = m.m21;
    this->m22 = m.m22;

    return *this; 
}

void Matrix33::add(const Matrix33& left, const Matrix33& right, Matrix33& dest)
{
    dest.m00 = left.m00 + right.m00;
    dest.m01 = left.m01 + right.m01;
    dest.m02 = left.m02 + right.m02;

    dest.m10 = left.m10 + right.m10;
    dest.m11 = left.m11 + right.m11;
    dest.m12 = left.m12 + right.m12;

    dest.m20 = left.m20 + right.m20;
    dest.m21 = left.m21 + right.m21;
    dest.m22 = left.m22 + right.m22;
}

void Matrix33::subtract(const Matrix33& left, const Matrix33& right, Matrix33& dest)
{
    dest.m00 = left.m00 - right.m00;
    dest.m01 = left.m01 - right.m01;
    dest.m02 = left.m02 - right.m02;

    dest.m10 = left.m10 - right.m10;
    dest.m11 = left.m11 - right.m11;
    dest.m12 = left.m12 - right.m12;

    dest.m20 = left.m20 - right.m20;
    dest.m21 = left.m21 - right.m21;
    dest.m22 = left.m22 - right.m22;
} 

void Matrix33::multiply(const Matrix33& left, const Matrix33& right, Matrix33& dest)
{
    float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02;
    float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12;
    float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12;
    float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22;
    float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22;
    float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22;

    dest.m00 = m00;
    dest.m01 = m01;
    dest.m02 = m02;

    dest.m10 = m10;
    dest.m11 = m11;
    dest.m12 = m12;

    dest.m20 = m20;
    dest.m21 = m21;
    dest.m22 = m22;
}

void Matrix33::transform(const Matrix33& left, const Vector3& right, Vector3& dest){
    float x = left.m00 * right.getX() + left.m10 * right.getY() + left.m20 * right.getZ();
    float y = left.m01 * right.getX() + left.m11 * right.getY() + left.m21 * right.getZ();
    float z = left.m02 * right.getX() + left.m12 * right.getY() + left.m22 * right.getZ();

    dest.setX(x);
    dest.setY(y);
    dest.setZ(z);
}

Matrix33& Matrix33::operator+=(const Matrix33& right)
{
    Matrix33::add(*this, right, *this);
    return *this;
}
Matrix33& Matrix33::operator-=(const Matrix33& right)
{
    Matrix33::subtract(*this, right, *this);
    return *this;
}
Matrix33& Matrix33::operator*=(const Matrix33& right)
{
    Matrix33::multiply(*this, right, *this);
    return *this;
}


Matrix33 Matrix33::operator+(const Matrix33& right) const
{
    Matrix33 output;
    Matrix33::add(*this, right, output);

    return output;
}
Matrix33 Matrix33::operator-(const Matrix33& right) const
{
    Matrix33 output;
    Matrix33::subtract( *this, right, output );
    
    return output;
}
Matrix33 Matrix33::operator*(const Matrix33& right) const
{
    Matrix33 output; 
    Matrix33::multiply( *this, right, output );

    return output;
}
Vector3 Matrix33::operator*(const Vector3& vec) const
{
    Vector3 output; 
    Matrix33::transform( *this, vec, output );

    return output;
}

Matrix33& Matrix33::setIdentity(){
	m00 = 1;
	m01 = 0;
	m02 = 0;

	m10 = 0;
	m11 = 1;
	m12 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 1;

    return *this;
}

Matrix33& Matrix33::setZero()
{
	m00 = 0;
	m01 = 0;
	m02 = 0;

	m10 = 0;
	m11 = 0;
	m12 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 0;

    return *this;
}

Matrix33& Matrix33::transpose(){
    float m00 = this->m00;
    float m01 = this->m10;
    float m02 = this->m20;
    float m10 = this->m01;
    float m11 = this->m11;
    float m12 = this->m21;
    float m20 = this->m02;
    float m21 = this->m12;
    float m22 = this->m22;

    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;
    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;
    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;

    return *this;
}

Matrix33& Matrix33::invert()
{
    float determinant = getDeterminant();

    if (determinant != 0) 
    {
        float determinant_inv = (float)1/determinant;

        float t00 = this->m11 * this->m22 - this->m12* this->m21;
        float t01 = - this->m10 * this->m22 + this->m12 * this->m20;
        float t02 = this->m10 * this->m21 - this->m11 * this->m20;
        float t10 = - this->m01 * this->m22 + this->m02 * this->m21;
        float t11 = this->m00 * this->m22 - this->m02 * this->m20;
        float t12 = - this->m00 * this->m21 + this->m01 * this->m20;
        float t20 = this->m01 * this->m12 - this->m02 * this->m11;
        float t21 = -this->m00 * this->m12 + this->m02 * this->m10;
        float t22 = this->m00 * this->m11 - this->m01 * this->m10;

        this->m00 = t00*determinant_inv;
        this->m11 = t11*determinant_inv;
        this->m22 = t22*determinant_inv;
        this->m01 = t10*determinant_inv;
        this->m10 = t01*determinant_inv;
        this->m20 = t02*determinant_inv;
        this->m02 = t20*determinant_inv;
        this->m12 = t21*determinant_inv;
        this->m21 = t12*determinant_inv;
    }

    return *this;
}

Matrix33& Matrix33::negate(){
    this->m00 = -this->m00;
    this->m01 = -this->m01;
    this->m02 = -this->m02;
    this->m10 = -this->m10;
    this->m11 = -this->m12;
    this->m12 = -this->m11;
    this->m20 = -this->m20;
    this->m21 = -this->m22;
    this->m22 = -this->m21;

    return *this;
}

float Matrix33::getDeterminant() const{
    return m00 * (m11 * m22 - m12 * m21)
                + m01 * (m12 * m20 - m10 * m22)
                + m02 * (m10 * m21 - m11 * m20);
}