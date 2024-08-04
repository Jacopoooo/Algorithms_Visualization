#include "Line.hpp"

Line::Line(const sf::Vector2f p1, const sf::Vector2f p2) : _p1(p1), _p2(p2)
{
    if (p1.y == p2.y) {
        _m = 0; // m == 0 per le rette parallele all'asse x
        _q = p1.y;
        _is_parallel_to_x_axis = true;
    }
    else if (p1.x == p2.x) {
        _m = INT_MAX; // m e q che tendono all'infinito per le rette parallele all'asse y
        _q = INT_MAX;
        _is_parallel_to_y_axis = true;
    }
    else {
        _m = -(p1.y - p2.y) / (p1.x - p2.x);
        _q = p1.y - _m * p1.x;
    }
}



const float Line::GetXGivenY(const float y) const
{
    if (_is_parallel_to_x_axis) {
        LOG("This line is parallel to x axis, so there are infinite x coordinates given a y coordinate. This function will return a random number between -INT_MAX and INT_MAX");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(-INT_MAX, INT_MAX);

        return distribution(gen);
    } 

    if (_is_parallel_to_y_axis) return _p1.x;
    else return (y - _q) / _m;
    
}

const float Line::GetYGivenX(const float x) const
{
    if (_is_parallel_to_y_axis) {
        LOG("This line is parallel to y axis, so there are infinite y coordinates given an x coordinate. This function will return a random number between -INT_MAX and INT_MAX");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(-INT_MAX, INT_MAX);

        return distribution(gen);
    }

    if (_is_parallel_to_x_axis) return _p1.y;
    else return _m * x + _q;
}

const float Line::GetM() const
{
    return _m;
}

void Line::SetM(const float new_m)
{
    _m = new_m;
}

const sf::Vector2f& Line::GetP1() const
{
    return _p1;
}

const sf::Vector2f& Line::GetP2() const
{
    return _p2;
}

void Line::ConvertToPerpendicular(const sf::Vector2f point)
{
    _m = 1 / _m;
    _q = -_m * point.x + point.y;

}

bool Line::IsParallelToYAxis() const
{
    return _is_parallel_to_y_axis;
}

bool Line::IsParallelToXAxis() const
{
    return _is_parallel_to_x_axis;
}
