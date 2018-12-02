#pragma once

#include "Game2D.h"

namespace jm
{
	class Player
	{
	public:
		vec2 center = vec2(-1.0f, 0.0f);
		vec2 wand_center = vec2(0.08f, 0.0f);
		vec2 direction = vec2(0.0f, 0.0f);
		vec2 wand_tip = vec2(30.0f, 0.0f);
		RGB player_color = Colors::red;
		RGB wand_color = Colors::red;

		//double slope = (player_center.y - wand_center.y) / (player_center.x - wand_center.x);
		
		void draw()
		{
			beginTransformation();
			{
				translate(center);
				rotate(direction.x);
				drawFilledCircle(player_color, 0.05f);
				translate(wand_center);
				rotate(wand_tip.x);
				drawFilledTriangle(wand_color, 0.05f);
			}
			endTransformation();
		}

		void stun(float stun_time)
		{
			//can't move for stun_time seconds
		}

		void move();
		// make movement


	};
}