#ifndef INCLUDE_MATRIX22_H
#define INCLUDE_MATRIX22_H

class Vector2;

class Matrix22{
    public:
        Matrix22();
        Matrix22(const Matrix22& m); 
        Matrix22& operator=(const Matrix22& oldMatrix); 

        virtual ~Matrix22();

        static void add(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static void subtract(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static void multiply(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static void transform(const Matrix22& left, const Vector2& right, Vector2& dest);
    
        Matrix22& operator+=(const Matrix22& right);
        Matrix22& operator-=(const Matrix22& right);
        Matrix22& operator*=(const Matrix22& right);
        Matrix22 operator+(const Matrix22& right) const;
        Matrix22 operator-(const Matrix22& right) const;
        Matrix22 operator*(const Matrix22& right) const;
        Vector2 operator*(const Vector2& vec) const;

        Matrix22& setIdentity();
        Matrix22& setZero();
        Matrix22& transpose();
        Matrix22& invert();
        Matrix22& negate();
        void print() const;

        float getDeterminant() const;

        float m00, m01;
        float m10, m11;
};

#endif