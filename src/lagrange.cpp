#include <iostream>
#include <vector>

/**
 * @brief using lagrange interpolation formula to interpolate
 *
 * @param data the source data
 * @param tarX the target node
 * @return double the result
 */
double lagrange(const std::vector<std::pair<double, double>> &data, const double &tarX) {
  double tarVal = 0.0;
  for (int k = 0; k != data.size(); ++k) {
    double val = 1.0;
    for (int i = 0; i != data.size(); ++i) {
      if (i == k) {
        continue;
      }
      val *= (tarX - data[i].first) / (data[k].first - data[i].first);
    }
    tarVal += val * data[k].second;
  }
  return tarVal;
}

/**
 * @brief using lagrange interpolation formula to interpolate
 *
 * @param x the nodes
 * @param y the function values
 * @param tarX the target node
 * @return double the result
 */
double lagrange(const std::vector<double> &x, const std::vector<double> &y, const double &tarX) {
  double tarVal = 0.0;
  for (int k = 0; k != x.size(); ++k) {
    double val = 1.0;
    for (int i = 0; i != x.size(); ++i) {
      if (i == k) {
        continue;
      }
      val *= (tarX - x[i]) / (x[k] - x[i]);
    }
    tarVal += val * y[k];
  }
  return tarVal;
}

int main(int argc, char const *argv[]) {
  std::vector<std::pair<double, double>> data{{0, 1}, {1, 0}, {2, 1}};
  for (float val = 0.0; val < 2.0; val += 0.1) {
    std::cout << val << ',' << lagrange(data, val) << std::endl;
  }
  return 0;
}
