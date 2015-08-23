#pragma once

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
