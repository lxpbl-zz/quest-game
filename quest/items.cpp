#include "application.h"

reaction health_item::react() {
	return reaction(reaction_type::HEALING, BOTTLE_ADD_HEAL_POINTS);
}

reaction bomb_item::react() {
	return reaction(reaction_type::HURTING, BOMB_REMOVE_HEAL_POINTS);
}

reaction treasure_item::react() {
	return reaction(reaction_type::SHINING, 100);
}