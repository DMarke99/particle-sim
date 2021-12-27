#include "vec3d.hpp"

const float& Vec3d::operator()(const int& i) const {
    if (i == 0) return this->x;
    if (i == 1) return this->y;
    if (i == 2) return this->z;
    throw std::invalid_argument("invalid argument");
}

float& Vec3d::operator() (const int& i) {
    if (i == 0) return this->x;
    if (i == 1) return this->y;
    if (i == 2) return this->z;
    throw std::invalid_argument("invalid argument");
}

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

Mat3d::Mat3d(const std::array<std::array<float, 3>, 3>& arr) {
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            this->vals[3*i+j] = arr[i][j];
        }
    }
}

Mat3d::Mat3d(
    const std::array<float, 3>& arr1,
    const std::array<float, 3>& arr2,
    const std::array<float, 3>& arr3
) {
    for (int i = 0; i < 3; ++i){
        this->vals[i] = arr1[i];
        this->vals[3+i] = arr2[i];
        this->vals[6+i] = arr3[i];
    }
}


Mat3d::Mat3d(const std::array<float, 9>& arr) {
    for (int i = 0; i < 9; ++i){
        this->vals[i] = arr[i];
    }
}

Mat3d::Mat3d(const float& val) {
    for (int i = 0; i < 9; ++i){
        this->vals[i] = val;
    }
}

const float& Mat3d::operator()(const int& i, const int& j) const {
    return this->vals[3*i+j];
}

float& Mat3d::operator() (const int& i, const int& j) {
    return this->vals[3*i+j];
}

Mat3d operator+(const Mat3d& mat1, const Mat3d& mat2){
    Mat3d res = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            res(i,j) = mat1(i,j) - mat2(i,j);
        }
    }
    return res;
};

Mat3d operator-(const Mat3d& mat1, const Mat3d& mat2){
    Mat3d res = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            res(i,j) = mat1(i,j) - mat2(i,j);
        }
    }
    return res;
};

Mat3d operator*(const float& k, const Mat3d& mat){
    Mat3d res = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            res(i,j) = k * mat(i,j);
        }
    }
    return res;
};

Mat3d operator*(const Mat3d& mat, const float& k){
    Mat3d res = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            res(i,j) = k * mat(i,j);
        }
    }
    return res;
};

Mat3d operator*(const Mat3d& mat1, const Mat3d& mat2){
    Mat3d res = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            for (int k = 0; k < 3; ++k){
                res(i,k) += mat1(i,j) * mat2(j,k);
            }
        }
    }
    return res;
};

Vec3d operator*(const Mat3d& mat, const Vec3d& vec){
    Vec3d res = {0,0,0};
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            res(i) += mat(i,j) * vec(j);
        }
    }
    return res;
};

Mat3d operator/(const Mat3d& mat, const float& k){
    Mat3d res = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            res(i,j) = mat(i,j)/k;
        }
    }
    return res;
};

void operator+=(Mat3d& mat1, const Mat3d& mat2){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            mat1(i,j) += mat2(i,j);
        }
    }
};

void operator-=(Mat3d& mat1, const Mat3d& mat2){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            mat1(i,j) -= mat2(i,j);
        }
    }
};

void operator*=(Mat3d& mat, const float& k){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            mat(i,j) *= k;
        }
    }
};

void operator/=(Mat3d& mat, const float& k){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            mat(i,j) /= k;
        }
    }
};

float sumsq(const Vec3d& vec){
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
};

Vec3d normed(const Vec3d& vec){
    float sq_dist = sumsq(vec);
    return ((sq_dist <= 1e-16) ? 0.0 : fast_inv_sqrt(sq_dist)) * vec;
};

std::ostream &operator<<(std::ostream &os, const Vec3d& vec) {
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Mat3d& mat) {
    os << "[";

    for (int i = 0; i < 3; ++i){
        os << "[" << mat(i, 0) << ", " << mat(i, 1) << ", " << mat(i, 2) << "]";
        if (i < 2) os << ", ";
    }
    os << "]" ;
    return os;
}