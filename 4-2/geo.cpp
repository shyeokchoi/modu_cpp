#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using combinations = std::vector<std::tuple<int, int>>;

void combination_2(int min, int max, combinations& res)
{
    if (min == max) {
        return;
    }

    for (int i = min + 1; i <= max; ++i) {
        res.push_back({ min, i });
    }
    combination_2(min + 1, max, res);
}

class Point
{
    int x, y;

public:
    Point(int pos_x, int pos_y)
    {
        x = pos_x;
        y = pos_y;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    int distance_to(const Point& other)
    {
        int dx = other.getX() - x;
        int dy = other.getY() - y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

class Geometry
{
public:
    Geometry()
    {
        num_points = 0;
    }

    void AddPoint(const Point& point)
    {
        point_array[num_points++] = new Point(point.getX(), point.getY());
    }

    // 모든 점들 간의 거리를 출력하는 함수 입니다.
    void PrintDistance();

    // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
    // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
    // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
    // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
    void PrintNumMeets();

private:
    // 점 100 개를 보관하는 배열.
    Point* point_array[100];
    int num_points;
};

void Geometry::PrintDistance()
{
    combinations combinations;
    combination_2(0, num_points - 1, combinations);

    int distance = 0;
    for (auto combination : combinations) {
        int fst = std::get<0>(combination);
        int snd = std::get<1>(combination);
        Point fst_point = *point_array[fst];
        Point snd_point = *point_array[snd];

        distance += fst_point.distance_to(snd_point);
    }
    std::cout << "sum of distance between every points: " << distance << std::endl;
}

void Geometry::PrintNumMeets()
{
}

int main()
{
    combinations combinations;
    combination_2(0, 10, combinations);
    for (auto combination : combinations) {
        std::cout << "(" << std::get<0>(combination) << ", " << std::get<1>(combination) << ")" << std::endl;
    }
}
