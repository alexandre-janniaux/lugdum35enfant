#pragma once

struct ScreenMessage {
	enum Action {Push, Pop, Clear};

	static ScreenMessage Push(int id) {
		action = Push;
		screen = id;
	}

	static ScreenMessage Pop() {
		action = Pop;
		screen = -1;
	}

	static ScreenMessage Clear() {
		action = Clear;
		screen = -1;
	}

	int screen;
	Action action;
};
