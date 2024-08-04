#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.hpp"

static const float PI = 3.14159265358979323846;

class Spiral {
public:
	Spiral(const float a, const float b, const size_t num_points, const float space_between_elements);

	const std::vector<sf::Vector2f>& GetDrawable() const;
	float GetRadius() const;
	size_t GetNumPoints() const;
	float GetSpaceBetweenElements() const;
	void _InitElementsNumberInLastTurn();
	size_t GetElementsNumberInLastTurn() const;
	float GetTheta() const;
	const sf::FloatRect GetSize() const;

private:
	void _InitDrawable();
	
	const float _a;
	const float _b;
	const float _dr;
	const float _space_between_elements;
	float _elements_in_last_turn;
	const size_t _num_points;
	float _radius = 0;
	float _theta;
	std::vector<sf::Vector2f> _drawable;
};