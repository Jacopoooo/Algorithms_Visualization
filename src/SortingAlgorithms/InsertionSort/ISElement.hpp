#include "SortingAlgorithms/ArrayElement.hpp"

class ISElement : public ArrayElement {
public:
	ISElement(const sf::Vector2f& size, const sf::Vector2f& position, size_t value, sf::Color color);
	ISElement();

	size_t getValue() const override;
	void setValue(size_t new_value) override;
};