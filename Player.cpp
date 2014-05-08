#include "Player.h"
#include <string>

using namespace std::

Player::Player(string name)
{
	play_name = name;
	player_name = "";
	player_power = 0;
	player_agility = 0;
	player_accuracy = 0;
}

void Player::setP_Name(string name)
{
	player_name = name;
}

void Player::setP_Power(int power)
{
	player_power = power;
}

void Player::setP_Agility(int agil)
{
	player_agility = agil;
}

void Player::setP_Accuracy(int accur)
{
	player_accuracy = accur;
}

int Player::getP_Power()
{
	return player_power;
}

int Player::getP_Accuracy()
{
	return player_accuracy;
}

int Player::getP_Agility()
{
	return player_agility;
}

string Player::getP_Name()
{
	return player_name;
}