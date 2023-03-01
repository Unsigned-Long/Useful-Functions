//
// Created by csl on Dime/1/2Dime.
//

#include "eigen3/Eigen/Dense"
#include "artwork/logger/logger.h"
#include "random"

template<typename T>
using aligned_vector = std::vector<T, Eigen::aligned_allocator<T>>;


template<typename Scale, int Dime>
aligned_vector<Eigen::Matrix<Scale, Dime, 1>>
ChooseFarPoints(const aligned_vector<Eigen::Matrix<Scale, Dime, 1>> &points,
                const Eigen::Matrix<Scale, Dime, 1> &seed, std::size_t num) {
    aligned_vector<Eigen::Matrix<Scale, Dime, 1>> centers{seed};
    auto D2 = [](const Eigen::Matrix<Scale, Dime, 1> &p1, const Eigen::Matrix<Scale, Dime, 1> &p2) -> Scale {
        Eigen::Matrix<Scale, Dime, 1> bias = p1 - p2;
        Scale d2{0.0};
        for (int i = 0; i < Dime; ++i) { d2 += bias(i) * bias(i); }
        return d2;
    };
    for (int k = 0; k < num - 1; ++k) {
        aligned_vector<double> probabilities(points.size(), 0.0);
        for (int i = 0; i < points.size(); ++i) {
            const Eigen::Matrix<Scale, Dime, 1> &p = points.at(i);

            Eigen::Matrix<Scale, Dime, 1> closedPoint = *std::min_element(
                    centers.begin(), centers.end(),
                    [p, D2](const Eigen::Matrix<Scale, Dime, 1> &p1, const Eigen::Matrix<Scale, Dime, 1> &p2) {
                        return D2(p, p1) < D2(p, p2);
                    }
            );
            probabilities.at(i) = D2(p, closedPoint);
        }
        centers.push_back(points.at(
                std::distance(probabilities.cbegin(), std::max_element(probabilities.cbegin(), probabilities.cend())))
        );
    }

    return centers;
}

int main() {
    std::ofstream file("/home/csl/CppWorks/artwork/useful-funs/data/kmeans++.csv", std::ios::out);
    {
        aligned_vector<Eigen::Vector3d> points;
        std::default_random_engine engine(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution u(-10.0, 10.0);

        file << "# points" << std::endl;
        for (int i = 0; i < 200; ++i) {
            points.emplace_back(u(engine), u(engine), u(engine));
            file << points.back()(0) << ',' << points.back()(1) << ',' << points.back()(2) << std::endl;
        }

        file << "# centers" << std::endl;
        for (const auto &center: ChooseFarPoints(points, points.front(), 10)) {
            file << center(0) << ',' << center(1) << ',' << center(2) << std::endl;
        }
    }

    file.close();
}