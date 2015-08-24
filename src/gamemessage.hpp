#pragma once
#include <SFML/System/Vector2.hpp>
#include "entitypool.hpp"

struct QuitMessage {};

struct ScreenMessage {
	enum Action {PUSH, POP, CLEAR};

	static ScreenMessage Push(int id) {
	    return {PUSH, id};
	}

	static ScreenMessage Pop() {
	    return {POP,-1};
	}

	static ScreenMessage Clear() {
	    return {CLEAR,-1};
	}

	Action action;
	int screen;
};

struct SetEntitySpeedMessage {
	Entity entity;
	sf::Vector2f speed;
};

struct SetEntityPositionMessage {
	Entity entity;
	sf::Vector2f position;
};
