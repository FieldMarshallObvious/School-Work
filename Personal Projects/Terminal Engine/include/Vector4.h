#ifndef INCLUDE_VECTOR4_H
#define INCLUDE_VECTOR4_H

class Vector4{
    private:
        float x, y, z, w;

    public:
        Vector4( float x = 0, float y = 0, float z = 0, float w = 0 );
        Vector4( const Vector4& oldVect );
        Vector4& operator=( const Vector4& oldVect );

        virtual ~Vector4( );

        float length( ) const;
        static void add( const Vector4& left, const Vector4& right, Vector4& dest );
        static void subtract( const Vector4& left, const Vector4& right, Vector4& dest );
        static void multiply(  const Vector4& left, const Vector4& right, Vector4& dest );
        static void lerp(  const Vector4& a, const Vector4& b, float t, Vector4& dest );


        static float dotProduct( const Vector4& a, const Vector4& b );
        static float distance( const Vector4& a, const Vector4& b );
        static Vector4 getNormalized(const Vector4& v);

        void scale(float s);
        void normalize();
        
        inline float getX() const {return this->x;}
        inline float getY() const {return this->y;}
        inline float getZ() const {return this->z;}
        inline float getW() const {return this->w;}

        inline void setX(float x){this->x = x;}
        inline void setY(float y){this->y = y;}
        inline void setZ(float z){this->z = z;}
        inline void setW(float w){this->w = w;}
};

#endif