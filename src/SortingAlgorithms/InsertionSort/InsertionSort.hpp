#include "SortingAlgorithms/SortingAlgorithm.hpp"
#include "ISElement.hpp"

class InsertionSort : public SortingAlgorithm<ISElement> {
public:
	InsertionSort(sf::RenderWindow& window, const float elements_width, size_t array_size, sf::Font& font, float height_factor = 5.0f, const sf::Color elements_color = sf::Color::Blue);

	float GetHeightFactor() const;
	void SetHeightFactor(float new_factor);

	void Play() override;

private:
	void Init() override;

	size_t GetMaxValue() const;
	void SetValuesRange(sf::Vector2u values_range);
	sf::Vector2u GetValuesRange() const;

	float GetLeftAndRightMargin(const float space_between_elements) const;
	float GetUpAndDownMargin() const;
	const sf::Vector2f GetMargins(const float space_between_elements) const;

	void ColorElement(ISElement& element, const sf::Color color) const;

	void SwapElements(ISElement first, ISElement second) const;

	float height_factor;
	const float elements_width;
};
