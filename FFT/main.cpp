#include <iostream>
#include <array>
#include <cmath>
#include <complex>
#include <random>

#define N 1024
#define Ts 0.001

typedef std::array<double, N> darray;
typedef std::array<std::complex<double>, N> carray;

double NumberGenerator() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(0.0, 0.1);
  return dis(gen);
}

darray CreateData(double amplitude, double frequency, double phase) {
  darray data = {};
  double time = 0.0f;
  for (double &x : data) {
    double random_number = NumberGenerator();
    double input = 2.0f * M_PI * frequency * time;
    x = amplitude * std::sin(input + phase) + random_number;
    time += Ts;
  }
  return data;
}

std::complex<double> GetFactor(double expo) {
  double real_part = std::cos(2 * M_PI * expo);
  double imag_part = std::sin(-2 * M_PI * expo);
  return {real_part, imag_part};
}

int Log2(int number) {
  return static_cast<int>(std::log2(number));
}

uint64_t BitReverser(uint64_t number) {
  uint64_t reversed_number = 0;
  for (int i = 0; i < Log2(N); ++i) {
    reversed_number <<= 1;
    reversed_number |= (number & 1);
    number >>= 1;
  }
  return reversed_number;
}

void BitReverseCopy(carray &values, darray &data) {
  for (int i = 0; i < N; ++i) {
    values[BitReverser(i)] = std::complex<double>(data[i], 0);
  }
}

void IterativeFFT(carray &values, darray &data) {
  BitReverseCopy(values, data);
  for (int s = 2; s <= N; s <<= 1) {
    int m = s;
    auto w_m = GetFactor(1.0f / m);
    for (int k = 0; k < N; k += m) {
      auto w = std::complex<double>(1.0, 0.0);
      for (int j = 0; j < m / 2; ++j) {
        auto t = w * values[k + j + m / 2];
        auto u = values[k + j];
        values[k + j] = u + t;
        values[k + j + m / 2] = u - t;
        w = w * w_m;
      }
    }
  }
}

std::complex<double> SliceDFT(darray &data, double frequency) {
  auto number = std::complex(0.0, 0.0);
  auto w_m = GetFactor(1.0f * frequency / N), w = std::complex<double>(1.0, 0.0);
  for (auto point : data) {
    number += point * w;
    w *= w_m;
  }
  return number;
}

void PrintResult(carray &results) {
  for (int l = 0; l < N; ++l) {
    double absolute = std::abs(results[l]);
    if (absolute < 100.0f)
      continue;
    double phase = 180.0f / M_PI * std::arg(results[l]);
    printf("Frequency: %4.2f | Abs: %4.2f Phase: %4.2f\n", double(l) / (Ts * N), absolute, phase);
  }
}

int main() {
  // create signal vector
  double _frequency = 299.8; // max N/2 Hertz frequency
  double _phase = 0.0f / 180.0f * M_PI; // in [degrees]
  auto data = CreateData(1.0, _frequency, _phase);
  auto data2 = CreateData(2.0, _frequency, _phase + M_PI_4);

  /*for (int i = 0; i < N; ++i) {
    printf("Time: %4.4f | Value: %4.2f\n", double(i)/1000, data[i]);
  }*/

  carray freq_values = {};
  IterativeFFT(freq_values, data);
  PrintResult(freq_values);
  IterativeFFT(freq_values, data2);
  PrintResult(freq_values);

  auto dft_slice = SliceDFT(data, _frequency * (Ts * N));
  printf("Frequency: %4.2f | Abs: %4.2f Phase: %4.2f\n",
         _frequency,
         std::abs(dft_slice),
         180.0f / M_PI * std::arg(dft_slice));
}

/*
  darray frequencies = {};
  for (int i = 0; i < N; ++i) {
    frequencies[i] = i; // 0 - 1000 Hz?
  }
  std::array<std::complex<double>, N> freq_values = {};
  for (int k = 0; k < N / 2; ++k) {
    std::complex<double> &freq_value = freq_values[k];
    for (int j = 0; j < N; ++j) {
      double expo = double(k * j) / N;
      std::complex<double> increment = GetFactor(expo);
      increment *= data[j];
      freq_value += increment;
    }
    freq_values[k + N / 2] = freq_value;
  }
  */
