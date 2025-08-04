#pragma once

#include <string>

class Player
{
public:
	Player(const std::string& name);
	virtual ~Player();

	const std::string& GetName() const;

private:
	std::string name;
};