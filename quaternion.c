#include <math.h>

#include "quaternion.h"

double quaternion_norm(quaternion a) {
  return a.w*a.w+a.x*a.x+a.y*a.y+a.z*a.z;
}

quaternion quaternion_scale(quaternion a, double s) {
  quaternion r = {
    a.w*s,
    a.x*s,
    a.y*s,
    a.z*s
  };
  return r;
}

quaternion quaternion_add(quaternion a, quaternion b) {
  quaternion r = {
    a.w+b.w,
    a.x+b.x,
    a.y+b.y,
    a.z+b.z
  };
  return r;
}

quaternion quaternion_normalize(quaternion a) {
  return quaternion_scale(a, 1/sqrt(quaternion_norm(a)));
}

// this guys code is wrong http://hamelot.co.uk/mathematics/quaternion-and-vector-math/
// this is correct http://www4.osk.3web.ne.jp/~tnpevips/program/download/complex.h
quaternion quaternion_multiply(quaternion a, quaternion b) {
  quaternion r = {
    a.w*b.w-a.x*b.x-a.y*b.y-a.z*b.z,
    a.w*b.x+a.x*b.w+a.y*b.z-a.z*b.y,
    a.w*b.y-a.x*b.z+a.y*b.w+a.z*b.x,
    a.w*b.z+a.x*b.y-a.y*b.x+a.z*b.w
  };
  return r;
}

// to conjugate [b] by [a] we do [a' b a]
// that means conjugating by [u] then [v]
// is the same as conjugating by [u v]
quaternion quaternion_conjugate(quaternion a, quaternion b) {
  quaternion r = {a.w, -a.x, -a.y, -a.z};
  return quaternion_multiply(r, quaternion_multiply(b, a));
}

quaternion quaternion_axis_angle(float x, float y, float z, float t) {
  quaternion r = {cos(t*0.5),x*sin(t*0.5),y*sin(t*0.5),z*sin(t*0.5)};
  return r;
}

// code stolen from:
// * http://musingsofninjarat.wordpress.com/quaternions-for-better-and-more-flexible-3d-rotation/
// * http://www.flipcode.com/documents/matrfaq.html#Q54
// man glRotate is useful
void quaternion_rotation_matrix(quaternion a, float *m) {
  float xx, yy, zz;
  float xy, xz, yz;
  float wx, wy, wz;
  
  xx=a.x*a.x; yy=a.y*a.y; zz=a.z*a.z;
  xy=a.x*a.y; xz=a.x*a.z; yz=a.y*a.z;
  wx=a.w*a.x; wy=a.w*a.y; wz=a.w*a.z;
  
  m[0+4*0] = 1.0f-2.0f*(yy+zz);
  m[0+4*1] = 2.0f*(xy-wz);
  m[0+4*2] = 2.0f*(xz+wy);
  m[0+4*3] = 0.0f;
  
  m[1+4*0] = 2.0f*(xy+wz);
  m[1+4*1] = 1.0f-2.0f*(xx+zz);
  m[1+4*2] = 2.0f*(yz-wx);
  m[1+4*3] = 0.0f;
  
  m[2+4*0] = 2.0f*(xz-wy);
  m[2+4*1] = 2.0f*(yz+wx);
  m[2+4*2] = 1.0f-2.0f*(xx+yy);
  m[2+4*3] = 0.0f;
  
  m[3+4*0] = 0.0f;
  m[3+4*1] = 0.0f;
  m[3+4*2] = 0.0f;
  m[3+4*3] = 1.0f;
}

void quaternion_rotate_vector(quaternion a, float *x, float *y, float *z) {
  quaternion q = {0,*x,*y,*z};
  quaternion r = quaternion_conjugate(a, q);
  *x = r.x;
  *y = r.y;
  *z = r.z;
}
