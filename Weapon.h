#include <string>

using namespace std;

class Weapon {
private:
	string weapon_name;
	int weapon_power;
	int weapon_agility;
	int weapon_accuracy;
public:
	Weapon(string, int, int ,int);
	void setPower(int);
	int getPower();
	void setAgility(int);
	int getAgility(int);
	void setAccuracy(int);
	int getAccuracy(int);

};
