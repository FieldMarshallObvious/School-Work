#ifndef INCLUDE_MATRIX33_H
#define INCLUDE_MATRIX33_H

class Vector3;

class Matrix33{
    public: 
        Matrix33(); 
        Matrix33(const Matrix33& m);
        Matrix33& operator=(const Matrix33& oldMatrix);

        virtual ~Matrix33(); 
        
        static void add(const Matrix33& left, const Matrix33& right, Matrix33& dest);
        static void subtract(const Matrix33& left, const Matrix33& right, Matrix33& dest);
        static void multiply(const Matrix33& left, const Matrix33& right, Matrix33& dest);
        static void transform(const Matrix33& left, const Vector3& right, Vector3& dest);

        Matrix33& operator+=(const Matrix33& right);
        Matrix33& operator-=(const Matrix33& right);
        Matrix33& operator*=(const Matrix33& right);
        Matrix33 operator+(const Matrix33& right);
        Matrix33 operator-(const Matrix33& right);
        Matrix33 operator*(const Matrix33& right);
        Vector3 operator*(const Vector3& vec);
        

        Matrix33& setIdentity();
        Matrix33& setZero();
        Matrix33& transpose();
        Matrix33& invert();
        Matrix33& negate();
        
		void print() const;
    
        float getDeterminant() const;
        
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
};
    
#endif