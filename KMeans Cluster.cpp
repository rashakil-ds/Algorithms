#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>

struct Point {
    double x, y; // Coordinates

    double distance(const Point& p) const {
        return std::sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
};

class KMeans {
private:
    int K, maxIterations;
    std::vector<Point> centroids;

public:
    KMeans(int K, int maxIterations) : K(K), maxIterations(maxIterations) {}

    int getClosestCentroidIndex(const Point& point) {
        double minDistance = std::numeric_limits<double>::max();
        int index = 0;

        for (int i = 0; i < K; ++i) {
            double dist = point.distance(centroids[i]);
            if (dist < minDistance) {
                minDistance = dist;
                index = i;
            }
        }

        return index;
    }

    void run(std::vector<Point>& points) {
        // Random K initial centroids
        for (int i = 0; i < K; ++i) {
            centroids.push_back(points[rand() % points.size()]);
        }

        std::vector<std::vector<Point>> clusters;
        clusters.resize(K);

        bool converged = false;
        int iteration = 0;

        while (!converged && iteration < maxIterations) {
   
            for (auto& cluster : clusters) {
                cluster.clear();
            }

         
            for (const auto& point : points) {
                int centroidIndex = getClosestCentroidIndex(point);
                clusters[centroidIndex].push_back(point);
            }

         
            converged = true;
            for (int i = 0; i < K; ++i) {
                Point newCentroid = {0, 0};
                for (const auto& point : clusters[i]) {
                    newCentroid.x += point.x;
                    newCentroid.y += point.y;
                }
                newCentroid.x /= clusters[i].size();
                newCentroid.y /= clusters[i].size();

                if (newCentroid.distance(centroids[i]) > 0.001) {
                    centroids[i] = newCentroid;
                    converged = false;
                }
            }

            iteration++;
        }
    }

    void printCentroids() {
        std::cout << "Centroids:\n";
        for (const auto& centroid : centroids) {
            std::cout << "(" << centroid.x << ", " << centroid.y << ")\n";
        }
    }
};

int main() {
    std::vector<Point> points = {{1, 2}, {1, 4}, {1, 0},
                                 {10, 2}, {10, 4}, {10, 0}};

    KMeans kmeans(2, 100);
    kmeans.run(points);
    kmeans.printCentroids();

    return 0;
}
