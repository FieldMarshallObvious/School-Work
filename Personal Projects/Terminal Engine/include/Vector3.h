#ifndef INCLUDE_VECTOR3_H
#define INCLUDE_VECTOR3_H

class Vector3{
    private:
        float x, y, z;

    public:
        Vector3( float x = 0, float y = 0, float z = 0 );
        Vector3( const Vector3& oldVect );
        Vector3& operator=( const Vector3& oldVect );

        virtual ~Vector3( );

        float length( ) const;
        static void add( const Vector3& left, const Vector3& right, Vector3& dest );
        static void subtract( const Vector3& left, const Vector3& right, Vector3& dest );
        static void crossProduct( const Vector3& a, const Vector3& b, Vector3& dest );
        static void lerp(  const Vector3& a, const Vector3& b, float t, Vector3& dest );
		
        Vector3& operator%=(const Vector3& right);
        Vector3& operator+=(const Vector3& right);
		Vector3& operator-=(const Vector3& right);
		Vector3 operator+(const Vector3& right);
		Vector3 operator-(const Vector3& right);
		Vector3 operator%(const Vector3& right);
		float operator*(const Vector3& b);

        static float dotProduct( const Vector3& a, const Vector3& b );
        static float angle( const Vector3& a, const Vector3& b );
        static float distance( const Vector3& a, const Vector3& b );
        static Vector3 getNormalized(const Vector3& v);

        Vector3& scale(float s);
        Vector3&  normalize();
        
        inline float getX() const {return this->x;}
        inline float getY() const {return this->y;}
        inline float getZ() const {return this->z;}

        inline void setX(float x){this->x = x;}
        inline void setY(float y){this->y = y;}
        inline void setZ(float z){this->z = z;}
};

#endif