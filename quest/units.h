#pragma once

#include "application.h"

#include <string>

enum action { ITEM_GRABBED, ITEM_LEAVED };

class unit abstract {

protected:

	position pos;
	int health;

public:

	unit() {}
	unit(position pos, int health) {
		this->pos = pos;
		this->health = health;
	}

	int get_health()	const { return this->health; }
	position get_pos()	const { return this->pos; }
	
	virtual void say(const std::string& text) const = 0;
	virtual action interact(item& item) = 0;
	virtual void go(const dir& dir) = 0;
};


class player : public unit {
private:
	
	position prev_pos;

public:

	player(position pos, int health) : unit(pos, health) { this->prev_pos = pos; }

	virtual void say(const std::string& text) const;
	virtual action interact(item& item);
	virtual void go(const dir& dir);

};