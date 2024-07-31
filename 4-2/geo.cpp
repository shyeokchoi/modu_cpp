#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using combinations = std::vector<std::tuple<int, int>>;

void Combination2(int min, int max, combinations& res)
{
    if (min == max) {
        return;
    }

    for (int i = min + 1; i <= max; ++i) {
        res.push_back({ min, i });
    }
    Combination2(min + 1, max, res);
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

    int GetX() const
    {
        return x;
    }

    int GetY() const
    {
        return y;
    }

    int DistanceTo(const Point& other)
    {
        int dx = other.GetX() - x;
        int dy = other.GetY() - y;
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
        point_array[num_points++] = new Point(point.GetX(), point.GetY());
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
    Combination2(0, num_points - 1, combinations);

    int distance = 0;
    for (auto combination : combinations) {
        int fst = std::get<0>(combination);
        int snd = std::get<1>(combination);
        Point fst_point = *point_array[fst];
        Point snd_point = *point_array[snd];

        distance += fst_point.DistanceTo(snd_point);
    }
    std::cout << "sum of distance between every points: " << distance << std::endl;
}

void Geometry::PrintNumMeets()
{
    int num_meets = 0;

    for (int i = 0; i < num_points; ++i) {
        for (int j = i + 1; j < num_points; ++j) {
            int a = point_array[j]->GetY() - point_array[i]->GetY();
            int b = point_array[i]->GetX() - point_array[j]->GetX();
            int c = point_array[j]->GetX() * point_array[i]->GetY() - point_array[i]->GetX() * point_array[j]->GetY();

            int pos_side = 0, neg_side = 0;

            for (int k = 0; k < num_points; ++k) {
                if (k == i || k == j)
                    continue;

                int value = a * point_array[k]->GetX() + b * point_array[k]->GetY() + c;

                if (value > 0)
                    pos_side++;
                else if (value < 0)
                    neg_side++;
            }

            if (pos_side > 0 && neg_side > 0)
                num_meets++;
        }
    }

    std::cout << "Number of intersections: " << num_meets << std::endl;
}
