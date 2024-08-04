#include "ArrayElement.hpp"

ArrayElement::ArrayElement(const sf::Vector2f& size, const sf::Vector2f& position, size_t value, sf::Color color) : RectangleShape(size), value(value) {
	setFillColor(color);
	setPosition(position);
}

ArrayElement::ArrayElement() {
	LOG("ArrayElement default constructor called");
	setSize(sf::Vector2f(100, 100));
	setPosition(sf::Vector2f(0, 0));
	setValue(0);
	setFillColor(sf::Color::Black);
}

size_t ArrayElement::getValue() const {
	return value;
}

void ArrayElement::setValue(size_t new_value) {
	value = new_value;
}

void ArrayElement::SetPosition(const sf::Vector2f& new_pos) {
	setPosition(new_pos);
}

void ArrayElement::SetPosition(const float x, const float y) {
	setPosition(x, y);
}

void ArrayElement::Draw(sf::RenderWindow& window) const {
	window.draw(*this);
};