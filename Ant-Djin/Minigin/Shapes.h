#pragma once

#include "Transform.h"

namespace dae
{
	struct Shape
	{

		Shape(int left, int top, int width, int height) :left{ left }, top{ top }, width{ width }, height{ height } {}
		Shape() = default;


		int left;
		int	top;
		int width;
		int height;

	};

	//functions to determine if two rectangles are overlapping
	inline bool ValInRange(int val, int min, int max)
	{
		return val >= min && val <= max;
	}

	inline bool ShapesOverlapping(const Shape& shape1, glm::ivec2 worldPos1, const Shape& shape2, glm::ivec2 worldPos2)
	{
		glm::ivec2 topLeft1{ shape1.left + worldPos1.x, shape1.top + worldPos1.y };
		glm::ivec2 topLeft2{ shape2.left + worldPos2.x, shape2.top + worldPos2.y };


		bool xAligned{ ValInRange(topLeft1.x, topLeft2.x, topLeft2.x + shape2.width)
					|| ValInRange(topLeft2.x, topLeft1.x, topLeft1.x + shape1.width) };

		bool yAligned{ ValInRange(topLeft1.y, topLeft2.y, topLeft2.y + shape2.height)
					|| ValInRange(topLeft2.y, topLeft1.y, topLeft1.y + shape1.height) };


		return xAligned && yAligned;
	}


}