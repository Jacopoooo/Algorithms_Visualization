#pragma once 

#include "ArrayElement.hpp"
#include <vector>
#include <random>

template<typename T>
class SortingAlgorithm{
	static_assert(std::is_base_of<ArrayElement, T>::value, "Array type must derive from ArrayElement");

public:
	SortingAlgorithm(sf::RenderWindow& window, sf::Font& font, const sf::Color elements_color, size_t array_size, sf::Vector2u values_range = sf::Vector2u(1, 10));
	virtual void Play() = 0;
	

protected:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Vector2u values_range;
	sf::Color elements_color;
	std::vector<T> array;
	size_t array_size;

	virtual void Init() = 0;
	void InitElementsWithRandomValues();

	void DisplayWhileSwapping(T& first, T& second) const;
	void DisplayElements() const;

	virtual void SwapElements(T first, T second) const = 0;

	void AlgorithmCompleted(const sf::String& text_string) const;
};


template<typename T>
SortingAlgorithm<T>::SortingAlgorithm(sf::RenderWindow& window, sf::Font& font, const sf::Color elements_color, size_t array_size, sf::Vector2u values_range)
	: window(window), font(font), array_size(array_size), values_range(values_range), elements_color(elements_color) {
	array.resize(array_size);
}


template<typename T>
void SortingAlgorithm<T>::InitElementsWithRandomValues() {

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(values_range.x, values_range.y);

	for (size_t i = 0; i < array_size; i++) {
		size_t value = distribution(generator);

		for (size_t j = 0; j < i; j++) {
			if (array[j].getValue() == value) {
				value = distribution(generator);
				j = -1;
			}
		}
		array[i].setValue(value);
	}
}


template<typename T>
void SortingAlgorithm<T>::AlgorithmCompleted(const sf::String& text_string) const {

	SLEEP(2000);
	sf::Text text;
	text.setString(text_string);
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);
	sf::FloatRect text_bounds = text.getLocalBounds();
	float x_text = (SCREEN_WIDTH - text_bounds.width) / 2;
	float y_text = (SCREEN_HEIGHT - text_bounds.height) / 2;
	text.setPosition(sf::Vector2f(x_text, y_text));
	window.clear(sf::Color::White);
	window.draw(text);
	window.display();
	SLEEP(2000);

}


template<typename T>
void SortingAlgorithm<T>::DisplayElements() const {
	window.clear(sf::Color::White);
	for (size_t i = 0; i < array_size; i++) {
		array[i].Draw(window);
	}
	window.display();
}


template<typename T>
void SortingAlgorithm<T>::DisplayWhileSwapping(T& first, T& second) const {
	window.clear(sf::Color::White);
	for (size_t i = 0; i < array_size; i++) {
		if (array[i].getValue() == first.getValue()) {
			first.Draw(window);
		}
		else if (array[i].getValue() == second.getValue()) {
			second.Draw(window);
		}
		else {
			array[i].Draw(window);
		}
	}
	window.display();
	
}




template class SortingAlgorithm<ArrayElement>;