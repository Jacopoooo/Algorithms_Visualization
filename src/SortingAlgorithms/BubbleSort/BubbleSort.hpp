#pragma once

#include "SortingAlgorithms/SortingAlgorithm.hpp"
#include "Parabola.hpp"
#include "BSElement.hpp"

class BubbleSort : public SortingAlgorithm<BSElement>{
public:
	BubbleSort(sf::RenderWindow& window, const sf::Vector2f& elements_size, const sf::Vector2u& values_range, const sf::Color elements_color, sf::Font& font, size_t array_size);
	void Play() override;
	
private:
	sf::Vector2f elements_size;
	void Init() override;
	void SwapElements(BSElement first, BSElement second) const override;
	void HandleMovement(float& pos_x, const float final_pos, float& delta_x, BSElement& element, const Parabola& parabola) const;
	bool AdjustMovement(float& delta_x, float final_x_pos, float pos_x) const;
};
