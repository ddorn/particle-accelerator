
#ifndef PARTICLE_ACCELERATOR_VECTOR3D_H
#define PARTICLE_ACCELERATOR_VECTOR3D_H

using component = double;

class Vector3D {
public:

    Vector3D();
    Vector3D(component, component, component);

    component x() const { return x_; }
    component y() const { return y_; }
    component z() const { return z_; }

    component norm() const;
    component normSquared() const;
    component distanceTo(Vector3D) const;
    component unit() const;

    Vector3D cross(Vector3D) const;
    component dot(Vector3D) const;

private:
    component x_, y_, z_;

};


#endif //PARTICLE_ACCELERATOR_VECTOR3D_H
