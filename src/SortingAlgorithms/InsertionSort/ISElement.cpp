#include "ISElement.hpp"

ISElement::ISElement(const sf::Vector2f& size, const sf::Vector2f& position, size_t value, sf::Color color) : ArrayElement(size, position, value, color) {}

ISElement::ISElement() {
	ArrayElement();
}

size_t ISElement::getValue() const { return value; };

void ISElement::setValue(size_t new_value) {
	if (new_value != 0 && value != 0) {
		setSize(sf::Vector2f(getSize().x, (getSize().y / value) * new_value));
	}
	value = new_value;
}
