#pragma once

#include "application.h"

enum reaction_type { SHINING, HURTING, HEALING };
struct reaction {

	reaction_type type;
	int value;

	reaction() {}

	reaction(reaction_type type, int value) {
		this->type = type;
		this->value = value;
	}

};


class item abstract {

protected:

	position pos;

public:

	item() {};
	item(position& pos) { this->pos = pos; };

	position get_pos() const { return this->pos; }

	virtual reaction react() = 0;

};


class health_item : public item {

public:

	health_item(position& pos) : item(pos) {}

	virtual reaction react();

};


class bomb_item : public item {

public:

	bomb_item(position& pos) : item(pos) {}

	virtual reaction react();

};


class treasure_item : public item {

public:

	treasure_item(position& pos) : item(pos) {}

	virtual reaction react();

};