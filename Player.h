#include <string>

using namespace std;

class Player
{
private:
	string play_name;
	string player_name;
	int player_power;
	int player_accuracy;
	int player_agility;
public:
	Player(string);
	void setP_Name(string);
	void setP_Power(int);
	void setP_Agility(int);
	void setP_Accuracy(int);
	int getP_Power();
	int getP_Agility();
	int getP_Accuracy();
	int getP_Name();
}
