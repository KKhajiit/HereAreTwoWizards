#pragma once

#include "Game2D.h"
#include "Map.h"
#include "Player.h"
#include "Magic.h"

namespace jm
{
	class MyGameExample : public Game2D
	{
	public:
		
		Map map;
		Player player1, player2;
		Magic *magic1 = nullptr, *magic2 = nullptr;
		vec2 mouse_pos = getCursorPos(true);
		double PI = 3.14159265358979323846;
		float time = 0.0f;
		bool start_flag = false;

	

		MyGameExample()
			: Game2D("There were two wizards", 1024, 768, false)
		{
			player2.center = -player1.center;
			player2.wand_center = -player1.wand_center;
			player2.wand_tip.x = -player1.wand_tip.x;
			player2.player_color = Colors::blue;
			player2.wand_color = Colors::blue;
			map.spf = this->getTimeStep();
		}

		~MyGameExample()
		{
			if (magic1 != nullptr) delete magic1;
		}

		void update() override
		{
			map.draw();
			
			mouse_pos = getCursorPos(true);
			if (start_flag == false)
			{
				if (mouse_pos.x > -0.25f && mouse_pos.x < 0.25f
					&& mouse_pos.y > -0.625f && mouse_pos.y < -0.375f)
				{
					map.startKeyReady();
					if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
						start_flag = true;
				}
				else
					map.startKey();
			}
			

			if(start_flag == true)
				time += 0.001f;
			
			if(map.radius > 0 && player1.life && player2.life)
				map.radius -= time * this->getTimeStep() * 0.01f;
			// move player1
			if (isKeyPressed(GLFW_KEY_A))	player1.center.x -= 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_D))	player1.center.x += 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_W))	player1.center.y += 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_S))	player1.center.y -= 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_F))	player1.direction.x += 50.0f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_G))	player1.direction.x -= 50.0f * getTimeStep();

			//move player2
			if (isKeyPressed(GLFW_KEY_LEFT))	player2.center.x -= 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	player2.center.x += 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		player2.center.y += 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	player2.center.y -= 0.2f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_KP_4))	player2.direction.x += 50.0f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_KP_5))	player2.direction.x -= 50.0f * getTimeStep();
			
			//player1 shoot a shooting star
			if (isKeyPressedAndReleased(GLFW_KEY_H) && player1.coolTime == false)
			{
				if (magic1 == nullptr)
				{
					magic1 = new Magic;
					
				}
					magic1->center = player1.center;
					magic1->cos = cos(player1.direction.x * PI / 180.0f);
					magic1->sin = sin(player1.direction.x * PI / 180.0f);
			}
			if (magic1 != nullptr)
			{
				magic1->update(getTimeStep());
				player1.coolTime = true;
			}

			//player2 shoot a shooting star
			if (isKeyPressedAndReleased(GLFW_KEY_KP_6))
			{
				if (magic2 == nullptr)
				{
					magic2 = new Magic;
				}
				magic2->center = player2.center;
				magic2->cos = -cos(player2.direction.x * PI / 180.0f);
				magic2->sin = -sin(player2.direction.x * PI / 180.0f);
			}
			if (magic2 != nullptr)
			{
				magic2->update(getTimeStep());
				player2.coolTime = true;
			}

			// rendering
//			if(player1.life == true)
				player1.draw(player1.player_color, player1.wand_color);
			if (magic1 != nullptr) magic1->draw();

	//		if (player2.life == true)
				player2.draw(player2.player_color, player2.wand_color);
			if (magic2 != nullptr) magic2->draw();


			// magic disapears when it's gets out of the map
			if (magic1 != nullptr && magic1->distance > map.radius + 0.05f)
			{
				magic1 = nullptr;
				delete magic1;
				player1.coolTime = false;
			}
			if (magic2 != nullptr && magic2->distance > map.radius + 0.1f)
			{
				magic2 = nullptr;
				delete magic2;
				player2.coolTime = false;
			}
			
			// when a player lose
			// 1.went out of the map
			if (player1.distance > map.radius + 0.1f)
				player1.life = false;
			if (player2.distance > map.radius + 0.1f)
				player2.life = false;

			// 2.hit by magic
			if (magic2 != nullptr)
			{
				if (abs(player1.center.x - magic2->center.x) < 0.1f && abs(player1.center.y - magic2->center.y) < 0.1f)
					player1.life = false;
			}
			if (magic1 != nullptr)
			{
				if (abs(player2.center.x - magic1->center.x) < 0.1f && abs(player2.center.y - magic1->center.y) < 0.1f)
					player2.life = false;
			}
			// check players life flag
			if (player1.life == false)
			{
				player1.player_color = player1.lose_color;
				player1.wand_color = player1.lose_color;
				player2.player_color = player2.win_color;
				player2.wand_color = player2.win_color;
			}
			else if (player2.life == false)
			{
				player2.player_color = player2.lose_color;
				player2.wand_color = player2.lose_color;
				player1.player_color = player1.win_color;
				player1.wand_color = player1.win_color;
			}
		}
	};
}