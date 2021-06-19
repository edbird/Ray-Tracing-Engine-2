

#ifndef GEOM_HPP
#define GEOM_HPP


#include <cmath>
#include <iostream>


namespace geom
{

    template<class T>
    class vec3
    {

        public:

        T x;
        T y;
        T z;

        vec3()
            : x(static_cast<T>(0))
            , y(static_cast<T>(0))
            , z(static_cast<T>(0))
        {

        }

        vec3(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {

        }

        virtual
        ~vec3()
        {
            
        }

        // will produce weird results for integer types
        // TODO
        T length() const
        {
            T mag2 = x * x + y * y + z * z;
            T mag = std::sqrt(mag2);
            return mag;
        }

        T length_square() const
        {
            T mag2 = x * x + y * y + z * z;
            return mag2;
        }

        // note: does not make much sense for integer types
        void normalize()
        {
            //T mag2 = x * x + y * y + z * z;
            //T f = 1.0 / std::sqrt(mag2);
            T f = 1.0 / length();
            x *= f;
            y *= f;
            z *= f;
        }

        // note: does not make much sense for integer type
        vec3<T> unit() const
        {
            vec3 copy(*this);
            copy.normalize();

            return copy; // again: todo: check
        }

        //template<typename U> ??
        vec3<T> operator-() const
        {
            vec3<T> v;
            v.x = -x;
            v.y = -y;
            v.z = -z;

            return v;
        }



        vec3<T> operator+=(const vec3<T> &v)
        {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;

            return *this;
        }

        // TODO: check
        vec3<T> operator-=(const vec3<T> &v)
        {
            vec3<T> copy(-v);
            *this += copy;

            return *this;
        }

        vec3<T> operator*=(const float x)
        {
            this->x *= x;
            this->y *= x;
            this->z *= x;

            return *this;
        }

        vec3<T> ProjectXY() const
        {
            vec3<T> copy(*this);
            copy.z = 0.0f;
            return copy;
        }

        vec3<T> ProjectXZ() const
        {
            vec3<T> copy(*this);
            copy.y = 0.0f;
            return copy;
        }

        vec3<T> ProjectYZ() const
        {
            vec3<T> copy(*this);
            copy.x = 0.0f;
            return copy;
        }
    /*
        vec3<T> CrushX() const
        {
            vec3<T> copy(*this);
            copy.x = 0.0f;
            return copy;
        }

        vec3<T> CrushY() const
        {
            vec3<T> copy(*this);
            copy.y = 0.0f;
            return copy;
        }

        vec3<T> CrushZ() const
        {
            vec3<T> copy(*this);
            copy.z = 0.0f;
            return copy;
        }
    */
        // swizzel x__
        vec3<T> xxx() const
        {
            vec3<T> v(x, x, x);
            return v;
        }
        vec3<T> xxy() const
        {
            vec3<T> v(x, x, y);
            return v;
        }
        vec3<T> xxz() const
        {
            vec3<T> v(x, x, z);
            return v;
        }
        vec3<T> xyx() const
        {
            vec3<T> v(x, y, x);
            return v;
        }
        vec3<T> xyy() const
        {
            vec3<T> v(x, y, y);
            return v;
        }
        vec3<T> xyz() const
        {
            vec3<T> v(x, y, z);
            return v;
        }
        vec3<T> xzx() const
        {
            vec3<T> v(x, z, x);
            return v;
        }
        vec3<T> xzy() const
        {
            vec3<T> v(x, z, y);
            return v;
        }
        vec3<T> xzz() const
        {
            vec3<T> v(x, z, z);
            return v;
        }

        // swizzel z__
        vec3<T> zxx() const
        {
            vec3<T> v(z, x, x);
            return v;
        }
        vec3<T> zxy() const
        {
            vec3<T> v(z, x, y);
            return v;
        }
        vec3<T> zxz() const
        {
            vec3<T> v(z, x, z);
            return v;
        }
        vec3<T> zyx() const
        {
            vec3<T> v(z, y, x);
            return v;
        }
        vec3<T> zyy() const
        {
            vec3<T> v(z, y, y);
            return v;
        }
        vec3<T> zyz() const
        {
            vec3<T> v(z, y, z);
            return v;
        }
        vec3<T> zzx() const
        {
            vec3<T> v(z, z, x);
            return v;
        }
        vec3<T> zzy() const
        {
            vec3<T> v(z, z, y);
            return v;
        }
        vec3<T> zzz() const
        {
            vec3<T> v(z, z, z);
            return v;
        }

        // swizzel y__
        vec3<T> yxx() const
        {
            vec3<T> v(y, x, x);
            return v;
        }
        vec3<T> yxy() const
        {
            vec3<T> v(y, x, y);
            return v;
        }
        vec3<T> yxz() const
        {
            vec3<T> v(y, x, z);
            return v;
        }
        vec3<T> yyx() const
        {
            vec3<T> v(y, y, x);
            return v;
        }
        vec3<T> yyy() const
        {
            vec3<T> v(y, y, y);
            return v;
        }
        vec3<T> yyz() const
        {
            vec3<T> v(y, y, z);
            return v;
        }
        vec3<T> yzx() const
        {
            vec3<T> v(y, z, x);
            return v;
        }
        vec3<T> yzy() const
        {
            vec3<T> v(y, z, y);
            return v;
        }
        vec3<T> yzz() const
        {
            vec3<T> v(x, z, z);
            return v;
        }
        
    };

    typedef vec3<float> vec3f;
    typedef vec3<double> vec3d;


    template<typename T>
    vec3<T> operator+(const vec3<T> &v1, const vec3<T> &v2)
    {
        vec3<T> v(v2);
        v.x += v1.x;
        v.y += v1.y;
        v.z += v1.z;

        // TODO: check
        return v;
    }

    template<typename T>
    vec3<T> operator-(const vec3<T> &v1, const vec3<T> &v2)
    {
        vec3<T> v(v1);
        v += (-v2);

        return v;
    }


    template<typename T>
    std::ostream &operator<<(std::ostream &os, const vec3<T> v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        
        return os;
    }


    template<typename T>
    float fcosangle(vec3<T> v1, vec3<T> v2)
    {
        v1.normalize();
        v2.normalize();

        return fdot(v1, v2);
    }


    template<typename T>
    float fdot(const vec3<T> v1, const vec3<T> v2)
    {
        float sum = 0.0f;
        sum += v1.x * v2.x;
        sum += v1.y * v2.y;
        sum += v1.z * v2.z;

        return sum;
    }


    template<typename T>
    T dot(const vec3<T> v1, const vec3<T> v2)
    {
        T sum = static_cast<T>(0);
        sum += v1.x * v2.x;
        sum += v1.y * v2.y;
        sum += v1.z * v2.z;

        return sum;
    }


    template<typename T>
    vec3<T> cross(const vec3<T> v1, const vec3<T> v2)
    {
        vec3<T> v(
            v1.y * v2.z - v2.y * v1.z,
            v2.x * v1.z - v1.x * v2.z,
            v1.x * v2.y - v2.x * v1.y
        );

        return v;
    }

    
    template<typename T>
    vec3<T> operator*(const float x, const vec3<T> v)
    {
        vec3<T> copy(v);
        copy *= x;
        return copy;
    }

    template<typename T>
    vec3<T> operator*(const vec3<T> v, const float x)
    {
        return operator*(x, v);
    }

    // note: does not make much sense for integer types
    template<typename T>
    int unit_safe(vec3<T> &v_out, const vec3<T> &v_in)
    {
        if(v_in.length() != 0.f)
        {
            v_out = v_in.unit();
            return 0;
        }
        else
        {
            return 1;
        }
    }


/*
    template<typename T>
    vec3<T> normalize(const vec3<T> v)
    {
        vec3<T> copy(v);
        vec<T>::normalize(*this);
        return v;
    }
*/



}



#endif // GEOM_HPP