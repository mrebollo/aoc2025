/*
    Advent of Code 2025 - Day 9 (1)
    Find four farthers points that maximize rectangle area
*/


#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

//#define DEBUG 1


void load_points( vector<pair<int,int>>& points, int &rows, int &cols) {
    ifstream input("input.txt");
    int x,y;
    char aux;
    rows = 0;
    cols = 0;
    while(input >> x >> aux >> y) {
        points.push_back({x,y});
        if (y > rows) rows = y;
        if (x > cols) cols = x;
    }
    input.close();
}

void mark_points( vector<string>& grid, const vector<pair<int,int>>& points) {
    for (const auto& p : points) {
        grid[p.second][p.first] = '#';
    }
#ifdef DEBUG
    for (const auto& row : grid) {
        cout << row << endl;
    }
#endif
}

double dist(const pair<int,int>& a, const pair<int,int>& b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx*dx + dy*dy);
}

long long area(const pair<int,int>& a, const pair<int,int>& b) {
    long long d1 = abs(a.first - b.first + 1);
    long long d2 = abs(a.second - b.second + 1);
    return (d1 * d2);
}

long long maxArea(const vector<pair<int,int>>& points) {
    long long max_area = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            long long area_ij = area(points[i], points[j]);
            if (area_ij > max_area) max_area = area_ij;
        }
    }
    return max_area;
}

int main(){
    vector<pair<int,int>> points;
    int rows, cols;
    load_points(points, rows, cols);
#ifdef DEBUG
    vector<string> grid(rows+2, string(cols+3, '.'));
    mark_points(grid, points);
#endif
    long long res = maxArea(points);
    cout << "Max area: " << res << endl;
    return 0;
}