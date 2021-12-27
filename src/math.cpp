#include "math.hpp"

float fast_inv_sqrt( const float& x ) {
   
   const float threehalfs = 1.5F;
   float y = x;
   
   long i = * ( long * ) &y;
   i = 0x5f3759df - ( i >> 1 ); 
   y = * ( float * ) &i;
   
   y = y * ( threehalfs - ( (x * 0.5F) * y * y ) );
   y = y * ( threehalfs - ( (x * 0.5F) * y * y ) );
   y = y * ( threehalfs - ( (x * 0.5F) * y * y ) );
   return y;
}

int sgn(const float& val) {
    return (0.0 < val) - (val < 0.0);
}
int sgn(const double& val) {
    return (0.0 < val) - (val < 0.0);
}
