#pragma once

#include "SFML/Graphics.hpp"
#include "Constants.hpp"
#include <random>

#define INT_MAX 2147483647

class Line {
public:
	Line(const sf::Vector2f p1, const sf::Vector2f p2);

	const float GetXGivenY(const float y) const;
	const float GetYGivenX(const float x) const;

	const float GetM() const;
	void SetM(const float new_m);

	const sf::Vector2f& GetP1() const;
	const sf::Vector2f& GetP2() const;

	void ConvertToPerpendicular(const sf::Vector2f point);

	bool IsParallelToYAxis() const;
	bool IsParallelToXAxis() const;

private:
	const sf::Vector2f _p1;
	const sf::Vector2f _p2;
	float _m;
	float _q;
	bool _is_parallel_to_y_axis = false;
	bool _is_parallel_to_x_axis = false;
};