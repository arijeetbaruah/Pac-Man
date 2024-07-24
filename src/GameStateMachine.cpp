#include "../include/GameStateMachine.hpp"
#include "../include/GameGameState.hpp"
#include "../include/BaseState.hpp"
#include "../include/Game.hpp"

GameStateMachine::GameStateMachine(Game* aGame): game(aGame), currentState(0)
{
	gameGameState = std::make_shared<GameGameState>(game);

	setState(gameGameState);
}

std::shared_ptr<BaseState> GameStateMachine::getState() const
{
	return currentState;
}

void GameStateMachine::handleInput(sf::Event& event)
{
	if (currentState != NULL)
	{
		currentState->handleInput(event);
	}
}

void GameStateMachine::update(sf::Time& elapsed)
{
	if (currentState != NULL)
	{
		currentState->onUpdate(elapsed);
	}
}

void GameStateMachine::render()
{
	if (currentState != NULL)
	{
		currentState->onRender();
	}
}

void GameStateMachine::setState(std::shared_ptr<BaseState> state)
{
	if (currentState != NULL)
	{
		currentState->onExit();
	}
	currentState = state;
	if (currentState != NULL)
	{
		currentState->onEntry();
	}
}
