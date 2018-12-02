#pragma once

#include "Game2D.h"

namespace jm
{
	class Map
	{
	public:
		float time = 0.0f, spf = 0.0f;
		float radius = 1.0f;
		/*RGB outer_wall_color;
		RGB inner_wall_color;*/
		RGB ground_color = Colors::brown_bright;
		RGB inner_edge_color = Colors::brown_dark;
		RGB outer_edge_color = Colors::brown_darker;

		void magma_texture()
		{
			vec2 magma_size(0.5f, 0.5f);
			RGB magma_color[5]{ Colors::magma_1,Colors::magma_2 ,Colors::magma_3 ,Colors::magma_4 ,Colors::magma_5 };
			for (int i = 0; i < 5; i++)
			{
				drawFilledBox(magma_color[4 - i], magma_size.x - 0.08f * i, magma_size.y);
			}
		}

		void magma_wave()
		{
			float dx = 0.25f, dy = 0.5f;
			float time = 0.0f;
			
			for (int row = 0; row < 5; row++)
			{
				for (int column = 0; column < 12; column++)
				{
					beginTransformation();
					translate(-1.42f + dx * column, 1.25f - dy * row);
					magma_texture();
					endTransformation();
				}
			}
		}

		void startKey()
		{
			beginTransformation();
			translate(0.0f, -0.5f);
			drawFilledBox(Colors::gray, 0.5f, 0.25f);
			endTransformation();
		}

		void startKeyReady()
		{
			beginTransformation();
			translate(0.0f, -0.5f);
			drawFilledBox(Colors::red, 0.5f, 0.25f);
			endTransformation();
		}

		void draw()
		{
			time += 0.1f;
			//draw background(magma)
			beginTransformation();
			translate(time * 0.1f * spf, 0.0f);
			magma_wave();
			endTransformation();
			if (time * 0.1f * spf >= 0.25f) time = 0;

			//draw outer edge
			float theta = 0.0f;
			for (int i = 0; i < 360; i++)
			{
				beginTransformation();
				rotate(theta);
				translate(radius + 0.06f, 0.0f);
				drawFilledPentagon(outer_edge_color, 0.04f);
				endTransformation();
				theta += 1.0f;
			}

			//draw inner edge
			theta = 0.0f;
			for (int i = 0; i < 360; i++)
			{
				beginTransformation();
				rotate(theta);
				translate(radius, 0.0f);
				drawFilledPentagon(inner_edge_color, 0.06f);
				endTransformation();
				theta += 1.0f;
			}

			//draw ground
			drawFilledCircle(ground_color, radius);

			

			/*drawFilledBox(ground_color, 4.0f, 4.0f);
			beginTransformation();
			{
				translate(vec2(0.0f, -2.0f));
				for (int i = 0; i < 160; i++)
				{
					translate(vec2(0.0f, 0.025f));
					drawFilledPentagon(inner_edge_color, 0.08f);
				}
			}
			endTransformation();

			beginTransformation();
			{
				translate(vec2(0.0f, -2.0f));
				for (int i = 0; i < 160; i++)
				{
					translate(vec2(0.0f, 0.025f));
					drawFilledPentagon(outer_edge_color, 0.06f);
				}
			}
			endTransformation();

			beginTransformation();
			{
				translate(vec2(0.0f, -2.0f));
				for (int i = 0; i < 160; i++)
				{
					translate(vec2(0.0f, 0.025f));
					drawFilledPentagon(deepest_color, 0.04f);
				}
			}
			endTransformation();*/
		}

	};
}