#include "artwork/angle/angle.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <tuple>

struct RefEllipsoid {
public:
  double a;
  double b;
  double c;
  double f;
  double efir;
  double efir2;
  double esed;
  double esed2;

public:
  RefEllipsoid(double longRadius, double oblateness) : a(longRadius), f(oblateness) {
    b = (1.0 - f) * a;
    c = a * a / b;
    efir = std::sqrt(a * a - b * b) / a;
    efir2 = efir * efir;
    esed = std::sqrt(a * a - b * b) / b;
    esed2 = esed * esed;
  }

  double W(double latitude) const {
    return std::sqrt(1.0 - efir2 * std::pow(std::sin(latitude), 2));
  }

  double V(double latitude) const {
    return std::sqrt(1.0 + esed2 * std::pow(std::cos(latitude), 2));
  }

  double N(double latitude) const {
    return a / W(latitude);
  }

  double M(double latitude) const {
    return a * (1 - efir2) / std::pow(W(latitude), 3);
  }
};

const RefEllipsoid WGS1984(6378137.0, 1.0 / 298.257223563);

const RefEllipsoid CGCS2000(6378137.0, 1.0 / 298.257222101);

const RefEllipsoid GRS1980(6378137.0, 1.0 / 298.257222101);

const RefEllipsoid Krasovsky(6378245.0, 1.0 / 298.2997381);

const RefEllipsoid Clarke1866(6378206.4, 1.0 / 294.9786982);

const RefEllipsoid Clarke1880(6378245.0, 1.0 / 293.46);

const RefEllipsoid Bessel1841(6377397.155, 1.0 / 299.1528434);

std::tuple<double, double, double> BLH2XYZ(const RefEllipsoid &ellipsoid, double B, double L, double H) {
  double N = ellipsoid.N(B);
  double X = (N + H) * std::cos(B) * std::cos(L);
  double Y = (N + H) * std::cos(B) * std::sin(L);
  double Z = (N * (1.0 - ellipsoid.efir2) + H) * std::sin(B);
  return {X, Y, Z};
}

std::tuple<double, double, double> XYZ2BLH(const RefEllipsoid &ellipsoid, double X, double Y, double Z) {
  double efir2 = ellipsoid.efir2, esed2 = ellipsoid.esed2;
  double a = ellipsoid.a, b = ellipsoid.b;
  double rxy = std::sqrt(X * X + Y * Y);
  double rxyz = std::sqrt(X * X + Y * Y + Z * Z);
  double u = std::atan2(a * Z * (1.0 + b * esed2 / rxyz), b * rxy);
  double B = std::atan2(Z + esed2 * b * std::pow(std::sin(u), 3), rxy - efir2 * a * std::pow(std::cos(u), 3));
  double L = std::atan2(Y, X);
  double H = rxy * std::cos(B) + Z * std::sin(B) - a * std::sqrt(1.0 - efir2 * std::pow(std::sin(B), 2));
  return {B, L, H};
}

int main(int argc, char const *argv[]) {
  std::cout << std::fixed << std::setprecision(3);
  auto [X, Y, Z] = BLH2XYZ(WGS1984,
                           ns_angle::Angle::make_pangle(30, 14, 56.6),
                           ns_angle::Angle::make_pangle(120, 44, 23.2),
                           22.4);
  std::cout << X << ", " << Y << ", " << Z << std::endl;
  auto [B, L, H] = XYZ2BLH(WGS1984, X, Y, Z);
  std::cout << ns_angle::Angle ::make_rangle(B) << ", "
            << ns_angle::Angle ::make_rangle(L) << ", "
            << H << std::endl;
  return 0;
}
