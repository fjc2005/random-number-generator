#include <opencv2/opencv.hpp>
#include <random>
#include <iostream>
#include <chrono>

"""
    In this cpp file, we run such program to verify that:
    the algorithm we use could produce random numbers,
    and the numbers are fairly distributed.
"""

using namespace std;
using namespace cv;
using namespace chrono;

int main() {
    const int range = 40; // large of the number list
    const int epoch = 10000; // number of epochs
    const int computeTime = 10; // number of times that we run a same code

    Mat m = Mat::zeros(Size(256, 20), CV_32FC1); // matrix to compute
    Mat n = Mat::zeros(Size(256, 256), CV_32FC1);
    int a[range] = { 0 };

    for (int i = 0; i < epoch; i++) {
        int num = 0;
        for (int j = 0; j < 3; j++) {
            num *= 10;
            system_clock::time_point time_point_now = system_clock::now();
            system_clock::duration duration_since_epoch = time_point_now.time_since_epoch();
            time_t microseconds_since_epoch
                = duration_cast<microseconds>(duration_since_epoch).count();

            // we run the same Matrix multiplication for 'computeTime' times
            for (int j = 0; j < computeTime; j++) {
                Mat _ = m * n;
            }

            // we count the time cost by the multiplication upon
            system_clock::time_point time_point_a = system_clock::now();
            system_clock::duration duration_since_a = time_point_a.time_since_epoch();
            time_t microseconds_since_a
                = duration_cast<microseconds>(duration_since_a).count();
            
            int gap = microseconds_since_a - microseconds_since_epoch;
            // we get a number from the time gap
            int num_last = gap % 10;
            num += num_last;
        }
        // we've generated a number in 0 - 999 by the 'for' loop upon
        num = num % 40;
        // we count the frequency of 'num'
        a[num] += 1;
    }

    for (int i = 0; i < range; i++) {
        cout << "Frequency of " << i << " : " << (double)a[i] / epoch << endl;
    }

    return 0;
}
