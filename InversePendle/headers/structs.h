//
// Created by larsl on 2/2/2024.
//

#ifndef INVERSEPENDLE__STRUCTS_H_
#define INVERSEPENDLE__STRUCTS_H_

#include <iostream>

#define G 9.81f
#define MU_ROT 0.01f
#define MU_TRANS 0.01f
#define LAMBDA 0.2f
#define ETA 0.1f
#define THETA_X_FACTOR 50.f
#define CM_TO_M 100

struct Orientation {
  float x = 0.f;
  float y = 0.f;
  float angle = 0.f;
};

struct Differentials {
  float acc = 0;
  float vel = 0;
  float pos = 0;

  friend std::ostream& operator <<(std::ostream& os, const Differentials& differentials){
    os << differentials.pos << " " << differentials.vel << " " << differentials.acc << "\n";
    return os;
  }

  // Overloading the + operator for the struct
  Differentials operator+(const Differentials& other) const {
    Differentials result;
    result.pos = this->pos + other.pos;
    result.vel = this->vel + other.vel;
    result.acc = this->acc + other.acc;
    return result;
  }

};

template <typename T>
float sgn(T val) {
  return (T(0) < val) - (val < T(0));
}


#endif //INVERSEPENDLE__STRUCTS_H_
