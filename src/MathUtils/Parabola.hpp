#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace Eigen;

class Parabola {
public:
	Parabola();
	Parabola(float a, float b, float c);
	Parabola(std::vector<float> coefficients);

	std::vector<float> GetCoefficients() const;
	static const Parabola GetParabolaWith3Points(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
	static const Parabola GetParabolaPath(sf::Vector2f p1, sf::Vector2f p2, const uint16_t parabola_height, bool inverse_path);
	float GetY(float x) const;

private:
	float a, b, c;
	static Vector3f solveLinearSystem(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
};
