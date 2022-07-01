#include <iomanip>
#include <iostream>
#include <tuple>

double julianDay(std::size_t year, std::size_t month, std::size_t day,
                 std::size_t hour = 0, std::size_t minute = 0, double second = 0.0) {
  if (month == 1 || month == 2) {
    year -= 1;
    month += 12;
  }
  int A = int(year / 100.0);
  int B = 2 - A + int(A / 4.0);
  return int(365.25 * (year + 4716)) + int(30.6001 * (month + 1)) + day +
         ((second / 60.0 + minute) / 60.0 + hour) / 24.0 + B - 1524.5;
}

double modJulianDay(std::size_t year, std::size_t month, std::size_t day,
                    std::size_t hour = 0, std::size_t minute = 0, double second = 0.0) {
  return julianDay(year, month, day, hour, minute, second) - 2400000.5;
}

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, double>
fromJulianDay(double jd) {
  jd += 0.5;
  int Z = int(jd);
  double F = jd - Z;
  int A;
  if (Z < 2299161) {
    A = Z;
  } else {
    int alpha = int((Z - 1867216.25) / 36524.25);
    A = Z + 1 + alpha - int(alpha / 4.0);
  }
  int B = A + 1524;
  int C = int((B - 122.1) / 365.25);
  int D = int(365.25 * C);
  int E = int((B - D) / 30.6001);
  double dhs = B - D - int(30.6001 * E) + F;
  std::size_t day = int(dhs);
  dhs -= day, dhs *= 24.0;
  std::size_t hour = int(dhs);
  dhs -= hour, dhs *= 60.0;
  std::size_t minute = int(dhs);
  dhs -= minute, dhs *= 60.0;
  double second = dhs;
  std::size_t year, month;
  if (E < 14) {
    month = E - 1;
  } else if (E == 14 || E == 15) {
    month = E - 13;
  }
  if (month > 2) {
    year = C - 4716;
  } else if (month == 1 || month == 2) {
    year = C - 4715;
  }
  return {year, month, day, hour, minute, second};
}

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, double>
fromModJulianDay(double mjd) {
  return fromJulianDay(mjd + 2400000.5);
}

int main(int argc, char const *argv[]) {
  std::cout << std::fixed << std::setprecision(3);
  {
    double jd = julianDay(2007, 10, 26, 9, 30);
    std::cout << jd << std::endl;
    auto [year, month, day, hour, minute, second] = fromJulianDay(jd);
    std::cout << year << '-' << month << '-' << day << ' '
              << hour << ':' << minute << ':' << second << std::endl;
  }

  {
    double mjd = modJulianDay(2007, 10, 26, 9, 30);
    std::cout << mjd << std::endl;
    auto [year, month, day, hour, minute, second] = fromModJulianDay(mjd);
    std::cout << year << '-' << month << '-' << day << ' '
              << hour << ':' << minute << ':' << second << std::endl;
  }
  return 0;
}
