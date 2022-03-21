#include <iomanip>
#include <iostream>
#include <tuple>

double julianDay(std::size_t year, std::size_t month, std::size_t day,
                 std::size_t hour = 0, std::size_t minute = 0, double second = 0) {
  return 1721013.5 +
         367.0 * year -
         int(7.0 / 4.0 * (year + int((month + 9.0) / 12.0))) +
         day +
         (((second / 60.0) + minute) / 60.0 + hour) / 24.0 +
         int(275.0 * month / 9.0);
}

double modJulianDay(std::size_t year, std::size_t month, std::size_t day,
                    std::size_t hour = 0, std::size_t minute = 0, double second = 0) {
  return julianDay(year, month, day, hour, minute, second) - 2400000.5;
}

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, double>
fromJulianDay(double jd) {
  int a = int(jd + 0.5);
  int b = a + 1537;
  int c = int((b - 122.1) / 365.25);
  int d = int(365.25 * c);
  int e = int((b - d) / 30.600);
  double f = jd + 0.5;
  double dms = b - d - int(30.6001 * e) + f - int(f);
  std::size_t day = int(dms);
  dms -= day, dms *= 24.0;
  std::size_t hour = int(dms);
  dms -= hour, dms *= 60.0;
  std::size_t minute = int(dms);
  dms -= minute, dms *= 60.0;
  double second = dms;
  std::size_t month = e - 1 - 12 * int(e / 24.0);
  std::size_t year = c - 4715 - int((7 + month) / 10.0);
  return {year, month, day, hour, minute, second};
}

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, double>
fromModJulianDay(double mjd) {
  return fromJulianDay(mjd + 2400000.5);
}

int main(int argc, char const *argv[]) {
  std::cout << std::fixed << std::setprecision(3);
  {
    std::cout << julianDay(2007, 10, 26, 9, 30) << std::endl;
    auto [year, month, day, hour, minute, second] = fromJulianDay(2454399.896);
    std::cout << year << '-' << month << '-' << day << ' '
              << hour << ':' << minute << ':' << second << std::endl;
  }
  
  {
    std::cout << modJulianDay(2007, 10, 26, 9, 30) << std::endl;
    auto [year, month, day, hour, minute, second] = fromModJulianDay(54399.396);
    std::cout << year << '-' << month << '-' << day << ' '
              << hour << ':' << minute << ':' << second << std::endl;
  }
  return 0;
}
