#pragma once
#include "math.hpp"
#include <iostream>
#include <array>
#include <stdexcept>

class Vec3d {
    public:
        float x, y, z;
        const float& operator()(const int& i) const;
        float& operator()(const int& i);
};

Vec3d operator+(const Vec3d& vec1, const Vec3d& vec2);
Vec3d operator-(const Vec3d& vec1, const Vec3d& vec2);
Vec3d operator*(const float& k, const Vec3d& vec);
Vec3d operator*(const Vec3d& vec, const float& k);
Vec3d operator/(const Vec3d& vec, const float& k);

void operator+=(Vec3d& vec1, const Vec3d& vec2);
void operator-=(Vec3d& vec1, const Vec3d& vec2);
void operator*=(Vec3d& vec, const float& k);
void operator/=(Vec3d& vec, const float& k);

class Mat3d {
    private:
        std::array<float, 9> vals = { 0 };
    public:
        Mat3d(const std::array<std::array<float, 3>, 3>& arr);
        Mat3d(
            const std::array<float, 3>& arr1,
            const std::array<float, 3>& arr2,
            const std::array<float, 3>& arr3
        );
        Mat3d(const std::array<float, 9>& arr);
        Mat3d(const float& val);
        const float& operator()(const int& i, const int& j) const;
        float& operator()(const int& i, const int& j);
};

Mat3d operator+(const Mat3d& mat1, const Mat3d& mat2);
Mat3d operator-(const Mat3d& mat1, const Mat3d& mat2);
Mat3d operator*(const float& k, const Mat3d& mat);
Mat3d operator*(const Mat3d& mat, const float& k);
Mat3d operator*(const Mat3d& mat1, const Mat3d& mat2);
Vec3d operator*(const Mat3d& mat, const Vec3d& vec);
Vec3d operator*(const Vec3d& vec, const Mat3d& mat);
Mat3d operator/(const Mat3d& mat, const float& k);

void operator+=(Mat3d& mat1, const Mat3d& mat2);
void operator-=(Mat3d& mat1, const Mat3d& mat2);
void operator*=(Mat3d& mat, const float& k);
void operator/=(Mat3d& mat, const float& k);

float sumsq(const Vec3d& vec);
Vec3d normed(const Vec3d& vec);
std::ostream &operator<<(std::ostream &os, const Vec3d& vec);
std::ostream &operator<<(std::ostream &os, const Mat3d& mat);