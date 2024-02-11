//
// Created by larsl on 2/2/2024.
//

#ifndef INVERSEPENDLE__STRUCTS_H_
#define INVERSEPENDLE__STRUCTS_H_

#define G 98.1f
#define MU_ROT 1.f
#define MU_TRANS 0.001f

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
    os << differentials.pos << " " << differentials.vel << " " << differentials.acc << std::endl;
    return os;
  }
};

#endif //INVERSEPENDLE__STRUCTS_H_
