#include "Weapon.h"
#include <string>

using namespace std;

Weapon::Weapon(string name, int power, int agil, int accur)
{
		weapon_name = name;
		weapon_power = power;
		weapon_agility = agil;
		weapon_accuracy = accur;
}

void Weapon::setPower(int power)
{
        weapon_power = power;
}

int Weapon::getPower()
{
        return weapon_power;
}

void Weapon::setAgility(int agil)
{
        weapon_agility = agil;
}

int Weapon::getAgility
()
{
        return weapon_agility;
}

void Weapon::setAccuracy(int accur)
{
        weapon_accuracy = accur;
}

int Weapon::getAccuracy()
{
        return weapon_accuracy;
}
