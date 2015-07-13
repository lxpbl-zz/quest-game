#include "application.h"

#include <iostream>

void player::say(const std::string& text) const {
	std::cout << text << std::endl;
}

action player::interact(item& item) {
	action act = action::ITEM_LEAVED;

	reaction re = item.react();
	switch (re.type) {
	case reaction_type::HEALING:
		if (this->pos == item.get_pos()) {
			this->health += re.value;
			this->say("Oh, I think, I can drink that!");
			act = action::ITEM_GRABBED;
		}
		else if (this->pos.distance_to(item.get_pos()) < 2) {
			this->say("Hm, smells good here...");
		}
		break;
	case reaction_type::HURTING:
		if (this->pos == item.get_pos()) {
			this->health -= re.value;
			this->say("OH, FUCK!");
			act = action::ITEM_GRABBED;
		}
		else if (this->pos.distance_to(item.get_pos()) < 2) {
			this->say("Something is going wrong here...");
		}
		break;
	case reaction_type::SHINING:
		int prev_dist = int(this->prev_pos.distance_to(item.get_pos()));
		if (this->pos == item.get_pos()) {
			this->say("I found it! I can go from this place.At last.");
			act = action::ITEM_GRABBED;
		}
		else {
			int dist = int(this->pos.distance_to(item.get_pos()));
			switch (dist) {
			case 1:
				this->say("Threasure is right next to me, I feel it!");
				break;
			case 2:
				switch (prev_dist) {
				case 1:
					this->say("No. Definetly not here.");
					break;
				case 2:
					this->say("The shine is still the same. No closer than at a distance");
					break;
				case 3:
					this->say("The shine became stronger, seems, I'm on the right way!");
					break;
				}
				break;
			case 3:
				switch (prev_dist) {
				case 2:
					this->say("The shine became weaker again. Oh well.");
					break;
				case 3:
					this->say("The shine is still visible.");
					break;
				case 4:
					this->say("I can see a shine. Maybe, it is it?");
					break;
				}
				break;
			case 4:
				if (prev_dist == 3)
					this->say("Fuck, it's dark again.");
				break;
			}
			prev_pos = pos;
		}
		break;
	}
	return act;
}

void player::go(const dir& dir) {
	switch (dir) {
	case dir::FORW:
		if (this->pos.y != FORW_BORDER)
			this->pos.y--;
		else
			this->say("Wall. Can't go though it.");
		break;
	case dir::BACK:
		if (this->pos.y != BACK_BORDER)
			this->pos.y++;
		else
			this->say("Wall. Can't go though it.");
		break;
	case dir::LEFT:
		if (this->pos.x != LEFT_BORDER)
			this->pos.x--;
		else
			this->say("Wall. Can't go though it.");
		break;
	case dir::RIGHT:
		if (this->pos.x != RIGHT_BORDER)
			this->pos.x++;
		else
			this->say("Wall. Can't go though it.");
		break;
	}
}