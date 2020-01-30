#pragma once
#include "GameState.h"
#include <stack>

class StateMachine {
	public:	
		StateMachine();
		StateMachine(GameState* state);

	public:
		GameState* getCurrentState();
		void changeState(GameState* state);
		void pushState(GameState* state);
		GameState* pop();
		GameState* top();
		bool isRunning();
		int getSize();
		GameState* getAt(int i);
		void clear();

	private:
		std::vector<GameState*> states;
};