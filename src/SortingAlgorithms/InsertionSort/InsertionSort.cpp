#include "InsertionSort.hpp"

InsertionSort::InsertionSort(sf::RenderWindow& window, const float elements_width, size_t array_size, sf::Font& font, float height_factor, const sf::Color elements_color) :
	SortingAlgorithm(window, font, elements_color, array_size), height_factor(height_factor), elements_width(elements_width) {
	values_range = sf::Vector2u(1, GetMaxValue());
	InitElementsWithRandomValues();
	Init();
}

float InsertionSort::GetHeightFactor() const { return height_factor; };
void InsertionSort::SetHeightFactor(float new_factor) {
	height_factor = new_factor;
	for (size_t i = 0; i < array_size; i++) {
		array[i].setSize(sf::Vector2f(elements_width, height_factor * array[i].getValue()));
	}
}

void InsertionSort::Init() {

	const float space_between_elements = 20.0f;

	const sf::Vector2f margins = GetMargins(space_between_elements);

	float x_pos = margins.x;

	for (size_t i = 0; i < array_size; i++) {
		size_t value = array[i].getValue();

		array[i].setSize(sf::Vector2f(elements_width, -height_factor * value));
		array[i].setPosition(sf::Vector2f(x_pos, margins.y));
		array[i].setValue(value);
		array[i].setFillColor(elements_color);

		if (i != array_size - 1) {
			x_pos += elements_width + space_between_elements;
		}
	}
}

sf::Vector2u InsertionSort::GetValuesRange() const {
	return values_range;
}

void InsertionSort::SetValuesRange(const sf::Vector2u new_values_range) {
	if (new_values_range.x < GetMaxValue() && new_values_range.y < GetMaxValue()) {
		values_range = new_values_range;
	}
	
}

size_t InsertionSort::GetMaxValue() const {
	return std::round(SCREEN_HEIGHT / (3 * height_factor));
}

const sf::Vector2f InsertionSort::GetMargins(const float space_between_elements) const {
	return sf::Vector2f(GetLeftAndRightMargin(space_between_elements), GetUpAndDownMargin());
}

float InsertionSort::GetLeftAndRightMargin(const float space_between_elements) const {
	const float occupied_space = elements_width * array_size + space_between_elements * (array_size - 1);
	return (SCREEN_WIDTH - occupied_space) / 2;
}

float InsertionSort::GetUpAndDownMargin() const {
	float max_height;

	auto max_element = std::max_element(array.begin(), array.end(),
		[](const ISElement& first, const ISElement& second) {
			return first.getValue() < second.getValue();
		});

	max_height = max_element->getValue() * height_factor;
	

	return (SCREEN_HEIGHT + max_height) / 2;
}


void InsertionSort::ColorElement(ISElement& element, const sf::Color color = sf::Color::Red) const {
	if (element.getFillColor() != color) {
		element.setFillColor(color);
		DisplayElements();
		SLEEP(300);
	}
}

void InsertionSort::SwapElements(ISElement first, ISElement second) const {
	const float first_final_pos = std::trunc(second.getPosition().x * 10) / 10;
	const float second_final_pos = std::trunc(first.getPosition().x * 10) / 10;


	const float deceleration = 600.0f;
	const float dt = 0.5f;
	const float distance = abs(first_final_pos - second_final_pos);

	const float adjuster = 10.0f;

	const float tolerance = 1.0f;

	float velocity = (distance -(0.5*(-deceleration)*dt*dt))/dt + adjuster;

	sf::Clock clock;

	while (abs(first.getPosition().x - first_final_pos) > tolerance && abs(second.getPosition().x - second_final_pos) > tolerance) {
		float delta_time = clock.restart().asSeconds();
		

		if (velocity > 0) {

			float slowdown = deceleration * delta_time;

			if (velocity < slowdown) {
				velocity = 0;
			}
			else {				
				velocity -= slowdown;
			}
		}
	
		if (first_final_pos > second_final_pos) {
			first.move(velocity * delta_time, 0);
			second.move(-velocity * delta_time, 0);
		}
		else {
			first.move(-velocity * delta_time, 0);
			second.move(velocity * delta_time, 0);
		}
		
		DisplayWhileSwapping(first, second);
	}

	first.setPosition(first_final_pos, first.getPosition().y);
	second.setPosition(second_final_pos, second.getPosition().y);
}


void InsertionSort::Play() {
	for (size_t i = 1; i < array_size; i++) {

		size_t current = array[i].getValue();
		ColorElement(array[i]);

		size_t j = i - 1;
		ColorElement(array[j]);

		while (static_cast<int>(j) > -1 && current < array[j].getValue()) {
			
			ColorElement(array[j+1]);	

			ColorElement(array[j]);

			SwapElements(array[j], array[j + 1]);

			array[j + 1].setValue(array[j].getValue());
			array[j].setValue(current);
			
			ColorElement(array[j + 1], elements_color);
			if (j != 0 && current > array[j-1].getValue() || j == 0) ColorElement(array[j], elements_color);

			j--;
		}
		array[j + 1].setValue(current);

		ColorElement(array[i], elements_color);
		if (static_cast<int>(j) > -1) ColorElement(array[j], elements_color);
	}

	AlgorithmCompleted("Sorting Completed");
}

