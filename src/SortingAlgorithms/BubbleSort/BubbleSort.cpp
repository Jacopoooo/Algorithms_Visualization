#include "BubbleSort.hpp"


BubbleSort::BubbleSort(sf::RenderWindow& window, const sf::Vector2f& elements_size, const sf::Vector2u& values_range, const sf::Color elements_color, sf::Font& font, size_t array_size) : 
	SortingAlgorithm(window, font, elements_color, array_size, values_range) {
	Init();
	InitElementsWithRandomValues();
}

void BubbleSort::Init() {
	const float margin = 100;
	const float blank_space = (SCREEN_WIDTH - 2 * margin) - elements_size.x * array_size;
	const float space_between_elements = (blank_space + (margin + elements_size.x)) / array_size - 1;

	for (size_t i = 0; i < array_size; i++) {
		float x_position = margin + i * (space_between_elements + elements_size.x);
		sf::Vector2f position = sf::Vector2f(x_position, SCREEN_HEIGHT / 2);

		array[i] = BSElement(elements_size, position, 0, elements_color, font);
	}
}

void BubbleSort::SwapElements(BSElement first, BSElement second) const {
	float first_x_pos = first.getPosition().x;
	float second_x_pos = second.getPosition().x;

	const float first_final_pos = second_x_pos;
	const float second_final_pos = first_x_pos;

	const float parabola_height = 400;

	const sf::Vector2f p1 = first.getPosition();
	const sf::Vector2f p2 = second.getPosition();

	Parabola parabola_first;
	Parabola parabola_second;

	if (first_x_pos > second_x_pos) {

		parabola_first = Parabola::GetParabolaPath(p1, p2, parabola_height, true);
		parabola_second = Parabola::GetParabolaPath(p1, p2, parabola_height, false);

	}
	else {
		parabola_first = Parabola::GetParabolaPath(p1, p2, parabola_height, false);
		parabola_second = Parabola::GetParabolaPath(p1, p2, parabola_height, true);

	}

	float delta_x = 1.0f;

	while (first.getPosition().x != first_final_pos || second.getPosition().x != second_final_pos) {

		HandleMovement(first_x_pos, first_final_pos, delta_x, first, parabola_first);
		HandleMovement(second_x_pos, second_final_pos, delta_x, second, parabola_second);

		DisplayWhileSwapping(first, second);
	}
}

void BubbleSort::HandleMovement(float& pos_x, const float final_pos, float& delta_x, BSElement& element, const Parabola& parabola) const {
	if (pos_x < final_pos) {
		if (AdjustMovement(delta_x, final_pos, pos_x)) {
			element.SetPosition(final_pos, parabola.GetY(final_pos));
		}
		else {
			pos_x += delta_x;
			element.SetPosition(pos_x, parabola.GetY(pos_x));
		}

	}
	else if (pos_x > final_pos) {
		if (AdjustMovement(delta_x, final_pos, pos_x)) {
			element.SetPosition(final_pos, parabola.GetY(final_pos));
		}
		else {
			pos_x -= delta_x;
			element.SetPosition(pos_x, parabola.GetY(pos_x));
		}
	}
}


bool BubbleSort::AdjustMovement(float& delta_x, float final_x_pos, float pos_x) const {
	if (abs(pos_x - final_x_pos) < delta_x) {
		if (delta_x != 0.1f) delta_x = 0.1f;
		else return true;
	}
	return false;
}

void BubbleSort::Play() {
	for (size_t i = 0; i < array_size; i++) {
		for (size_t j = 0; j < array_size - i - 1; j++) {
			if (array[j].getValue() > array[j + 1].getValue()) {
				SwapElements(array[j], array[j + 1]);
				size_t temp = array[j].getValue();
				array[j].setValue(array[j + 1].getValue());
				array[j + 1].setValue(temp);

				DisplayElements();
				SLEEP(500);
			}
		}
	}
	AlgorithmCompleted("Sorting Completed");
}
