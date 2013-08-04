typedef struct {
  double w,x,y,z;
} quaternion;

double quaternion_norm(quaternion a);
quaternion quaternion_scale(quaternion a, double s);
quaternion quaternion_normalize(quaternion a);
quaternion quaternion_add(quaternion a, quaternion b);
quaternion quaternion_multiply(quaternion a, quaternion b);
quaternion quaternion_conjugate(quaternion a, quaternion b);
quaternion quaternion_axis_angle(float x, float y, float z, float t);
void quaternion_rotation_matrix(quaternion a, float *m);
void quaternion_rotate_vector(quaternion a, float *x, float *y, float *z);
