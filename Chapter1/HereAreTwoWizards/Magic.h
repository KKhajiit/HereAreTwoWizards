#pragma once

#include "Game2D.h"

namespace jm
{
	class Magic
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.5f, 0.5f);
		double distance = 0;
		double cos, sin;
		float time = 0.0f;
		float gap_cos, gap_sin;


		void draw()
		{
			beginTransformation();
			followingEffect(Colors::purple_1, 0.05f, 0.025f, 0.0f);
			followingEffect(Colors::purple_2, 0.04f, 0.02f, 0.6f);
			followingEffect(Colors::purple_3, 0.03f, 0.015f, 2.0f);
			followingEffect(Colors::purple_4, 0.025f, 0.0125f, 3.0f);
			followingEffect(Colors::purple_5, 0.025f, 0.0125f, 4.0f);
			followingEffect(Colors::purple_6, 0.025f, 0.0125f, 5.0f);
			endTransformation();
		}

		void followingEffect(RGB color, const float & outer_radius, const float & inner_radius, float gap)
		{
			beginTransformation();
			translate(center.x - gap * gap_cos, center.y - gap * gap_sin);
			rotate(time);
			drawFilledStar(color, outer_radius, inner_radius);
			endTransformation();
		}

		void update(const float& dt)
		{
			center.x += velocity.x * dt * cos;
			center.y += velocity.y * dt * sin;
			distance = sqrt(center.x * center.x + center.y * center.y);
			time += 300.0f * dt;
			gap_cos = dt * cos;
			gap_sin = dt * sin;
		}
	};
}