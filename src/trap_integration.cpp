//
// Created by csl on 3/7/23.
//
#include "eigen3/Eigen/Dense"
#include "artwork/logger/logger.h"

template<typename Scale, int Dime>
Eigen::Matrix<Scale, Dime, 1>
TrapIntegrationOnce(const std::vector<std::pair<Scale, Eigen::Matrix<Scale, Dime, 1>>> &data) {
    for (const auto &item: data) {
        LOG_VAR(item.first, item.second.transpose())
    }
    Eigen::Matrix<Scale, Dime, 1> sum = Eigen::Matrix<Scale, Dime, 1>::Zero();
    for (int i = 0; i < data.size() - 1; ++i) {
        int j = i + 1;
        const auto &di = data.at(i);
        const auto &dj = data.at(j);
        sum += (di.second + dj.second) * (dj.first - di.first) * Scale(0.5);
    }
    return sum;
}

template<typename Scale, int Dime>
Eigen::Matrix<Scale, Dime, 1>
TrapIntegrationTwice(const std::vector<std::pair<Scale, Eigen::Matrix<Scale, Dime, 1>>> &data) {
    std::vector<std::pair<Scale, Eigen::Matrix<Scale, Dime, 1>>> dataOnce;
    Eigen::Matrix<Scale, Dime, 1> sum = Eigen::Matrix<Scale, Dime, 1>::Zero();
    for (int i = 0; i < data.size() - 1; ++i) {
        int j = i + 1;
        const auto &di = data.at(i);
        const auto &dj = data.at(j);
        sum += (di.second + dj.second) * (dj.first - di.first) * Scale(0.5);
        dataOnce.push_back({(dj.first + di.first) * Scale(0.5), sum});
    }
    return TrapIntegrationOnce(dataOnce);
}

int main() {
    const std::vector<std::pair<double, Eigen::Vector3d>> data = {
            {0, {0, 0, 1}},
            {1, {0, 0, 4}},
            {3, {0, 0, 2}}
    };
    auto resultOnce = TrapIntegrationOnce(data);
    auto resultTwice = TrapIntegrationTwice(data);
    LOG_VAR(resultOnce, resultTwice)
    return 0;
}