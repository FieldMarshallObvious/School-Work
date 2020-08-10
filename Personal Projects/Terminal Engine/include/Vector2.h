#ifndef INCLUDE_VECTOR2_H
#define INCLUDE_VECTOR2_H

class Vector2{
    private:
        float x, y;

    public:
        Vector2( float x = 0, float y = 0 );
        Vector2( const Vector2& oldVect );
        Vector2& operator=( const Vector2& oldVect );

        virtual ~Vector2( );

        float length( ) const;
        static void add( const Vector2& left, const Vector2& right, Vector2& dest );
        static void subtract( const Vector2& left, const Vector2& right, Vector2& dest );
        static void multiply(  const Vector2& left, const Vector2& right, Vector2& dest );
        static void lerp(  const Vector2& a, const Vector2& b, float t, Vector2& dest );

        static float dotProduct( const Vector2& a, const Vector2& b );
        static float angle( const Vector2& a, const Vector2& b );
        static float distance( const Vector2& a, const Vector2& b );
        static Vector2 getNormalized(const Vector2& v);
		
        Vector2& operator+=(const Vector2& right);
		Vector2& operator-=(const Vector2& right);
		Vector2 operator+(const Vector2& right) const;
		Vector2 operator-(const Vector2& right) const;
		float operator*(const Vector2& b) const;

        void scale(float s);
        void normalize();
        
        inline float getX() const {return this->x;}
        inline float getY() const {return this->y;}

        inline void setX(float x){this->x = x;}
        inline void setY(float y){this->y = y;}
};

#endif