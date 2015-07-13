#include "application.h"

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>

position generate_pos(int x_min, int x_max, int y_min, int y_max, int min_dist_to_init) {
	position pos = position(rand() % (x_max - x_min) + x_min, rand() % (y_max - y_min) + y_min);
	position init_pos = position(INIT_X, INIT_Y);
	if (pos.distance_to(init_pos) < min_dist_to_init)
		pos = generate_pos(x_min, x_max, y_min, y_max, min_dist_to_init);
	return pos;
}

position* generate_pos_array(int x_min, int x_max, int y_min, int y_max, int count) {
	const int total = BOMBS_COUNT + HEALTH_BOTTLES_COUNT;
	position pos_arr[total];
	for (int i = 0; i < total; i++) {
		position pos = generate_pos(x_min, x_max, y_min, y_max, 1);
		if (std::find(pos_arr, pos_arr+total, pos) == pos_arr+total)
			pos_arr[i] = pos;
		else
			i--;
	}

	return pos_arr;
}

typedef std::vector<item*> item_container;
item_container generate_item_container(int x_min, int x_max, int y_min, int y_max, int health_count, int bomb_count) {
	item_container i_c;
	
	position* pos_arr = generate_pos_array(x_min, x_max, y_min, y_max, health_count);
	for (int i = 0; i < health_count; i++) {
		i_c.push_back(new health_item(pos_arr[i]));
	}

	pos_arr = generate_pos_array(x_min, x_max, y_min, y_max, bomb_count);
	for (int i = 0; i < bomb_count; i++) {
		i_c.push_back(new bomb_item(pos_arr[i]));
	}

	return i_c;
}

void application::run() {
	srand(time(NULL));

	char dir;
	player player(position(INIT_X, INIT_Y), INIT_HEALTH);
	position prev_pos = player.get_pos();

	treasure_item treasure = treasure_item(generate_pos(LEFT_BORDER, RIGHT_BORDER, FORW_BORDER, BACK_BORDER, 4));

	item_container i_c = generate_item_container(LEFT_BORDER, RIGHT_BORDER,
												FORW_BORDER, BACK_BORDER,
												HEALTH_BOTTLES_COUNT, BOMBS_COUNT);

	std::cout << "I need to find the treasure in this absolutely dark place.\n" <<
		"It's very dangerous, but hopefully, there are some health bottles around.\n\n" << std::endl;

	for (;;) {
		std::cout.fill(' ');
		std::string caption = "Position X :" + std::to_string(player.get_pos().x) + 
							"; Position Y: " + std::to_string(player.get_pos().y) + 
							"; Health: " + std::to_string(player.get_health());		
		std::cout.width(43);
		std::cout.setf(std::ios::left);
		std::cout << caption << "|" << std::endl;

		std::cout.width(43);
		std::cout.fill('-');
		std::cout << "" << std::endl;

		int item_to_del_ind = -1;
		for (int i = 0; i < i_c.size(); i++) {
			if (player.interact(*i_c[i]) == action::ITEM_GRABBED)
				item_to_del_ind = i;
		}
		if (item_to_del_ind != -1) {
			i_c.erase(i_c.begin() + item_to_del_ind);

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			system("cls");
			continue;
		}

		if (player.get_health() <= 0) {
			std::cout << "YOU DIED." << std::endl;
			break;
		}

		if (player.interact(treasure) == action::ITEM_GRABBED)
			break;

		std::cout << "Choose direction (w - forward, s - back, a - left, d - right) [q - leave game]: ";
		dir = _getch();
		switch (dir) {
		case 'w':
			player.go(dir::FORW);
			break;
		case 's':
			player.go(dir::BACK);
			break;
		case 'a':
			player.go(dir::LEFT);
			break;
		case 'd':
			player.go(dir::RIGHT);
			break;
		case 'q':
			break;
		default:
			std::cout << "Unknown direction" << std::endl;
			break;
		}
		if (dir == 'q')
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
	}
}