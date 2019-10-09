#include "StateMachine.h"

StateMachine::StateMachine() {
}

StateMachine::StateMachine(GameState* state) {
	this->states.push_back(state);
}

void StateMachine::changeState(GameState* state) {
	this->states.pop_back();
	this->states.push_back(state);
}

void StateMachine::pushState(GameState* state) {
	this->states.push_back(state);
}

GameState* StateMachine::pop() {
	if (!(this->states.size() > 0))
		return NULL;

	GameState* state = this->states[this->states.size() - 1];
	this->states.pop_back();
	return state;
}

GameState* StateMachine::top() {
	return this->states[this->states.size() - 1];
}

GameState* StateMachine::getCurrentState() {
	return this->top();
}

bool StateMachine::isRunning() {
	return (this->states.size() > 0);
}

int StateMachine::getSize() {
	return this->states.size();
}

GameState* StateMachine::getAt(int i) {
	return this->states[i];
}

void StateMachine::clear() {
	for (int i = 0; i < this->getSize(); i++)
		delete this->pop();
	this->states.clear();
}