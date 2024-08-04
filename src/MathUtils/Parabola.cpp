#include "Parabola.hpp"

Parabola::Parabola() {}
Parabola::Parabola(float a, float b, float c) : a(a), b(b), c(c) {}
Parabola::Parabola(std::vector<float> coefficients) {
	if (coefficients.size() == 3) {
		a = coefficients[0];
		b = coefficients[1];
		c = coefficients[2];
	}
	else {
		a = b = c = 0;
	}
}




std::vector<float> Parabola::GetCoefficients() const {
	std::vector<float> coefficients(3);
	coefficients[0] = a;
	coefficients[1] = b;
	coefficients[2] = c;

	return coefficients;
}

Vector3f Parabola::solveLinearSystem(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {

	// Normalizzare i coefficienti
	float x_scale = std::max({ std::abs(p1.x), std::abs(p2.x), std::abs(p3.x) });
	float y_scale = std::max({ std::abs(p1.y), std::abs(p2.y), std::abs(p3.y) });

	Matrix<float, 3, 3> matrix;
	Vector3f vector;

	matrix << (p1.x / x_scale) * (p1.x / x_scale), p1.x / x_scale, 1,
		(p2.x / x_scale)* (p2.x / x_scale), p2.x / x_scale, 1,
		(p3.x / x_scale)* (p3.x / x_scale), p3.x / x_scale, 1;

	vector << p1.y / y_scale, p2.y / y_scale, p3.y / y_scale;

	Vector3f normalized_solution = matrix.colPivHouseholderQr().solve(vector);

	// De-normalizzare i coefficienti
	float a = normalized_solution[0] * (y_scale / (x_scale * x_scale));
	float b = normalized_solution[1] * (y_scale / x_scale);
	float c = normalized_solution[2] * y_scale;

	return Vector3f(a, b, c);
}

Parabola const Parabola::GetParabolaWith3Points(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
	Vector3f solution = solveLinearSystem(p1, p2, p3);

	std::cout << "Parabola coefficients: a=" << solution[0] << ", b=" << solution[1] << ", c=" << solution[2] << std::endl;

	return Parabola(solution[0], solution[1], solution[2]);
}

const Parabola Parabola::GetParabolaPath(sf::Vector2f p1, sf::Vector2f p2, const uint16_t parabola_height, bool inverse_path) {
	sf::Vector2f p3;

	if (inverse_path) p3 = sf::Vector2f((p1.x + p2.x) / 2, p1.y + parabola_height);
	else p3 = sf::Vector2f((p1.x + p2.x) / 2, p1.y - parabola_height);

	return Parabola::GetParabolaWith3Points(p1, p2, p3);
}


float Parabola::GetY(float x) const {
	return a * x * x + b * x + c;
}

