#pragma once

class Vector {
  public:
    Vector(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    Vector add(const Vector& other) const;

  private:
    double x;
    double y;
    double z;
};
