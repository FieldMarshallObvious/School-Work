#include "Matrix44.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>

#define DET33(t00, t01, t02, t10, t11, t12, t20, t21, t22) (((t00) * ((t11) * (t22) - (t12) * (t21))) + ((t01) * ((t12) * (t20) - (t10) * (t22))) + ((t02) * ((t10) * (t21) - (t11) * (t20))))

Matrix44::Matrix44()
    :m00(1), m01(0), m02(0), m03(0),
     m10(0), m11(1), m12(0), m13(0),
     m20(0), m21(0), m22(1), m23(0),
     m30(0), m31(0), m32(0), m33(0)
{}

Matrix44::Matrix44 (const Matrix44& oldMatrix)
    :m00(oldMatrix.m00), m01(oldMatrix.m01), m02(oldMatrix.m02), m03(oldMatrix.m03),
     m10(oldMatrix.m10), m11(oldMatrix.m11), m12(oldMatrix.m12), m13(oldMatrix.m13),
     m20(oldMatrix.m20), m21(oldMatrix.m21), m22(oldMatrix.m22), m23(oldMatrix.m23),
     m30(oldMatrix.m30), m31(oldMatrix.m31), m32(oldMatrix.m32), m33(oldMatrix.m33)
{}

Matrix44::~Matrix44() {}

Matrix44& Matrix44::operator=(const Matrix44& m)
{
    this->m00 = m.m00;
    this->m01 = m.m01;
    this->m02 = m.m02;
    this->m03 = m.m03;

    this->m10 = m.m10;
    this->m11 = m.m11;
    this->m12 = m.m12;
    this->m13 = m.m13;

    this->m20 = m.m20;
    this->m21 = m.m21;
    this->m22 = m.m22;
    this->m23 = m.m23;

    this->m30 = m.m30;
    this->m31 = m.m31;
    this->m32 = m.m32;
    this->m33 = m.m33;

    return *this; 
}

void Matrix44::add( const Matrix44& left, const Matrix44& right, Matrix44& dest )
{
    dest.m00 = left.m00 + right.m00;
    dest.m01 = left.m01 + right.m01;
    dest.m02 = left.m02 + right.m02;
    dest.m03 = left.m03 + right.m03;

    dest.m10 = left.m10 + right.m10;
    dest.m11 = left.m11 + right.m11;
    dest.m12 = left.m12 + right.m12;
    dest.m13 = left.m13 + right.m13;

    dest.m20 = left.m20 + right.m20;
    dest.m21 = left.m21 + right.m21;
    dest.m22 = left.m22 + right.m22;
    dest.m23 = left.m23 + right.m23;

    dest.m30 = left.m30 + right.m30;
    dest.m31 = left.m31 + right.m31;
    dest.m32 = left.m32 + right.m32;
    dest.m33 = left.m33 + right.m33;
}

void Matrix44::subtract( const Matrix44& left, const Matrix44& right, Matrix44& dest ) 
{
    dest.m00 = left.m00 - right.m00;
    dest.m01 = left.m01 - right.m01;
    dest.m02 = left.m02 - right.m02;
    dest.m03 = left.m03 - right.m03;

    dest.m10 = left.m10 - right.m10;
    dest.m11 = left.m11 - right.m11;
    dest.m12 = left.m12 - right.m12;
    dest.m13 = left.m13 - right.m13;

    dest.m20 = left.m20 - right.m20;
    dest.m21 = left.m21 - right.m21;
    dest.m22 = left.m22 - right.m22;
    dest.m23 = left.m23 - right.m23;

    dest.m30 = left.m30 - right.m30;
    dest.m31 = left.m31 - right.m31;
    dest.m32 = left.m32 - right.m32;
    dest.m33 = left.m33 - right.m33;
} 

void Matrix44::multiply( const Matrix44& left, const Matrix44& right, Matrix44& dest )
{
    float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
    float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
    float m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
    float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
    float m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
    float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
    float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
    float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
    float m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
    float m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
    float m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
    float m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
    float m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;

    dest.m00 = m00;
    dest.m01 = m01;
    dest.m02 = m02;
    dest.m03 = m03;
    dest.m10 = m10;
    dest.m11 = m11;
    dest.m12 = m12;
    dest.m13 = m13;
    dest.m20 = m20;
    dest.m21 = m21;
    dest.m22 = m22;
    dest.m23 = m23;
    dest.m30 = m30;
    dest.m31 = m31;
    dest.m32 = m32;
    dest.m33 = m33;
}

void Matrix44::transform( const Matrix44& left, const Vector4& right, Vector4& dest )
{
    float x = left.m00 * right.getX() + left.m10 * right.getY() + left.m20 * right.getZ();
    float y = left.m01 * right.getX() + left.m11 * right.getY() + left.m21 * right.getZ();
    float z = left.m02 * right.getX() + left.m12 * right.getY() + left.m22 * right.getZ();
    float w = left.m03 * right.getX() + left.m13 * right.getY() + left.m23 * right.getW();

    dest.setX(x);
    dest.setY(y);
    dest.setZ(z);
    dest.setW(w);
}

void Matrix44::setIdentity()
{
	m00 = 1;
	m01 = 0;
	m02 = 0;
    m03 = 0;

	m10 = 0;
	m11 = 1;
	m12 = 0;
    m13 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 1;
    m23 = 0;

    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 1;
}

void Matrix44::setZero()
{
	m00 = 0;
	m01 = 0;
	m02 = 0;
    m03 = 0;

	m10 = 0;
	m11 = 0;
	m12 = 0;
    m13 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 0;
    m23 = 0;

    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 0;
}

void Matrix44::transpose()
{
    float m00 = this->m00;
    float m01 = this->m10;
    float m02 = this->m20;
    float m03 = this->m30;
    float m10 = this->m01;
    float m11 = this->m11;
    float m12 = this->m21;
    float m13 = this->m31;
    float m20 = this->m02;
    float m21 = this->m12;
    float m22 = this->m22;
    float m23 = this->m32;
    float m30 = this->m03;
    float m31 = this->m13;
    float m32 = this->m23;
    float m33 = this->m33;

    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;
    this->m03 = m03;
    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;
    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;
    this->m30 = m30;
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;   
}

void Matrix44::invert()
{
    float determinant = getDeterminant();

    if (determinant != 0) {
        float determinant_inv = (float)1/determinant;

        float t00 =  DET33(m11, m12, m13, m21, m22, m23, m31, m32, m33);
        float t01 = -DET33(m10, m12, m13, m20, m22, m23, m30, m32, m33);
        float t02 =  DET33(m10, m11, m13, m20, m21, m23, m30, m31, m33);
        float t03 = -DET33(m10, m11, m12, m20, m21, m22, m30, m31, m32);

        float t10 = -DET33(m01, m02, m03, m21, m22, m23, m31, m32, m33);
        float t11 =  DET33(m00, m02, m03, m20, m22, m23, m30, m32, m33);
        float t12 = -DET33(m00, m01, m03, m20, m21, m23, m30, m31, m33);
        float t13 =  DET33(m00, m01, m02, m20, m21, m22, m30, m31, m32);

        float t20 =  DET33(m01, m02, m03, m11, m12, m13, m31, m32, m33);
        float t21 = -DET33(m00, m02, m03, m10, m12, m13, m30, m32, m33);
        float t22 =  DET33(m00, m01, m03, m10, m11, m13, m30, m31, m33);
        float t23 = -DET33(m00, m01, m02, m10, m11, m12, m30, m31, m32);

        float t30 = -DET33(m01, m02, m03, m11, m12, m13, m21, m22, m23);
        float t31 =  DET33(m00, m02, m03, m10, m12, m13, m20, m22, m23);
        float t32 = -DET33(m00, m01, m03, m10, m11, m13, m20, m21, m23);
        float t33 =  DET33(m00, m01, m02, m10, m11, m12, m20, m21, m22);

        m00 = t00*determinant_inv;
        m11 = t11*determinant_inv;
        m22 = t22*determinant_inv;
        m33 = t33*determinant_inv;
        m01 = t10*determinant_inv;
        m10 = t01*determinant_inv;
        m20 = t02*determinant_inv;
        m02 = t20*determinant_inv;
        m12 = t21*determinant_inv;
        m21 = t12*determinant_inv;
        m03 = t30*determinant_inv;
        m30 = t03*determinant_inv;
        m13 = t31*determinant_inv;
        m31 = t13*determinant_inv;
        m32 = t23*determinant_inv;
        m23 = t32*determinant_inv;
    }
}

void Matrix44::negate()
{
    this->m00 = -this->m00;
    this->m01 = -this->m01;
    this->m02 = -this->m02;
    this->m03 = -this->m03;

    this->m10 = -this->m10;
    this->m11 = -this->m11;
    this->m12 = -this->m12;
    this->m13 = -this->m13;

    this->m20 = -this->m20;
    this->m21 = -this->m22;
    this->m22 = -this->m21;
    this->m23 = -this->m23;

    this->m30 = -this->m30;
    this->m31 = -this->m31;
    this->m32 = -this->m32;
    this->m33 = -this->m33;
}

void Matrix44::scale( const Vector3& scale )
{
    this->m00 = this->m00 * scale.getX();
    this->m01 = this->m01 * scale.getX();
    this->m02 = this->m02 * scale.getX();
    this->m03 = this->m03 * scale.getX();

    this->m10 = this->m10 * scale.getY();
    this->m11 = this->m11 * scale.getY();
    this->m12 = this->m12 * scale.getY();
    this->m13 = this->m13 * scale.getY();

    this->m20 = this->m20 * scale.getZ();
    this->m21 = this->m21 * scale.getZ();
    this->m22 = this->m22 * scale.getZ();
    this->m23 = this->m23 * scale.getZ();
}

void Matrix44::rotate(const Vector3& eulerAxis, float angle){
    float c = (float) cos(angle);
    float s = (float) sin(angle);
    float oneminusc = 1.0f - c;
    float xy = eulerAxis.getX()*eulerAxis.getY();
    float yz = eulerAxis.getY()*eulerAxis.getZ();
    float xz = eulerAxis.getX()*eulerAxis.getZ();
    float xs = eulerAxis.getX()*s;
    float ys = eulerAxis.getY()*s;
    float zs = eulerAxis.getZ()*s;

    float f00 = eulerAxis.getX()*eulerAxis.getX()*oneminusc+c;
    float f01 = xy*oneminusc+zs;
    float f02 = xz*oneminusc-ys;
    float f10 = xy*oneminusc-zs;
    float f11 = eulerAxis.getY()*eulerAxis.getY()*oneminusc+c;
    float f12 = yz*oneminusc+xs;
    float f20 = xz*oneminusc+ys;
    float f21 = yz*oneminusc-xs;
    float f22 = eulerAxis.getZ()*eulerAxis.getZ()*oneminusc+c;

    float t00 = this->m00 * f00 + this->m10 * f01 + this->m20 * f02;
    float t01 = this->m01 * f00 + this->m11 * f01 + this->m21 * f02;
    float t02 = this->m02 * f00 + this->m12 * f01 + this->m22 * f02;
    float t03 = this->m03 * f00 + this->m13 * f01 + this->m23 * f02;
    float t10 = this->m00 * f10 + this->m10 * f11 + this->m20 * f12;
    float t11 = this->m01 * f10 + this->m11 * f11 + this->m21 * f12;
    float t12 = this->m02 * f10 + this->m12 * f11 + this->m22 * f12;
    float t13 = this->m03 * f10 + this->m13 * f11 + this->m23 * f12;

    this->m20 = this->m00 * f20 + this->m10 * f21 + this->m20 * f22;
    this->m21 = this->m01 * f20 + this->m11 * f21 + this->m21 * f22;
    this->m22 = this->m02 * f20 + this->m12 * f21 + this->m22 * f22;
    this->m23 = this->m03 * f20 + this->m13 * f21 + this->m23 * f22;
    this->m00 = t00;
    this->m01 = t01;
    this->m02 = t02;
    this->m03 = t03;
    this->m10 = t10;
    this->m11 = t11;
    this->m12 = t12;
    this->m13 = t13;
}

void Matrix44::translate( const Vector3& translation )
{
    this->m30 += this->m00 * translation.getX() + this->m10 * translation.getY() + this->m20 * translation.getZ();
    this->m31 += this->m01 * translation.getX() + this->m11 * translation.getY() + this->m20 * translation.getZ();
    this->m32 +=  this->m02 * translation.getX() + this->m12 * translation.getY() + this->m20 * translation.getZ();
    this->m33 +=  this->m03 * translation.getX() + this->m13 * translation.getY() + this->m20 * translation.getZ();
}

float Matrix44::getDeterminant() const 
{
    float f = m00 * ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32)
            - m13 * m22 * m31
            - m11 * m23 * m32
            - m12 * m21 * m33);
    f -= m01 * ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32)
            - m13 * m22 * m30
            - m10 * m23 * m32
            - m12 * m20 * m33);
    f += m02 * ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31)
            - m13 * m21 * m30
            - m10 * m23 * m31
            - m11 * m20 * m33);
    f -= m03 * ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31)
            - m12 * m21 * m30
            - m10 * m22 * m31
            - m11 * m20 * m32);
    return f;
}