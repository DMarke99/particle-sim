#include "vec3d.hpp"

Vec3d operator+(const Vec3d& vec1, const Vec3d& vec2){
    return {
        vec1.x+vec2.x,
        vec1.y+vec2.y,
        vec1.z+vec2.z,
    };
};

Vec3d operator-(const Vec3d& vec1, const Vec3d& vec2){
    return {
        vec1.x-vec2.x,
        vec1.y-vec2.y,
        vec1.z-vec2.z,
    };
};

Vec3d operator*(const float& k, const Vec3d& vec){
    return {
        k*vec.x,
        k*vec.y,
        k*vec.z,
    };
};

Vec3d operator*(const Vec3d& vec, const float& k){
    return {
        k*vec.x,
        k*vec.y,
        k*vec.z,
    };
};

Vec3d operator/(const Vec3d& vec, const float& k){
    return {
        vec.x/k,
        vec.y/k,
        vec.z/k,
    };
};

void operator+=(Vec3d& vec1, const Vec3d& vec2){
    vec1.x+=vec2.x;
    vec1.y+=vec2.y;
    vec1.z+=vec2.z;
};

void operator-=(Vec3d& vec1, const Vec3d& vec2){
    vec1.x-=vec2.x;
    vec1.y-=vec2.y;
    vec1.z-=vec2.z;
};

void operator*=(Vec3d& vec, const float& k){
    vec.x*=k;
    vec.y*=k;
    vec.z*=k;
};

void operator/=(Vec3d& vec, const float& k){
    vec.x/=k;
    vec.y/=k;
    vec.z/=k;
};

float sumsq(const Vec3d& vec){
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
};

Vec3d normed(const Vec3d& vec){
    float sq_dist = sumsq(vec);
    return (sq_dist == 0 ? 0.0 : fast_inv_sqrt(sq_dist)) * vec;
};

std::ostream &operator<<(std::ostream &os, const Vec3d& vec) {
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return os;
}