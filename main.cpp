#include <iostream>
#include <string>
#include <cstdlib>
#include "Weapon.cpp"
#include "Player.cpp"

using namespace std;


//typedef enum{intro, weapon_choice, chck_encounter, encount_gen, event_gen, boss1, boss2, boss3, event1, event2, event3, easy_fight, mid_fight, hard_fight}
int random(int numb)
{
	int rand_gen = (rand()% numb) + 1; //find random number within limit given as input
	return rand_gen;
}

int main()
{
	Player player1 = Player("player1") //create the player object so that game uses player1 as name regardless of player input
	Weapon pistols = Weapon(pistols, 4, 10, 3); //create the different weapon choices with their given stats
	Weapon shotgun = Weapon(shotgun, 10, 2, 4);
	Weapon rifle = Weapon(rifle, 6, 8, 7);
	Weapon crossbow = Weapon(crossbow, 5, 3, 10);
	string BoG;
	string pinput;
	string pinput2;
	int lives = 2;

	string test = "intro";
	switch(test)
	{
		case "intro":
		{
			cout << "Welcome to Choice" << endl;
			cout << "A game where you will have to make choices" << endl;
			cout << "Choose: boy or girl?" << endl;
			cin >> BOG;
			cout << "Choose a name:" << endl;
			cin >> pinput;
			player1.setP_Name(pinput);
			case = "weapon_choice";
			break;
		}

		case "weapon_choice":
		{
			cout << "Choose: pistols, shotgun, rifle, or crossbow" << endl;
			cin >> pinput2;
			while((pinput2 != "pistols") || (pinput2 != "shotgun") || (pinput2 != "rifle") || (pinput2 != "crossbow"))
				{
					cout << "Choose: pistols, shotgun, rifle, or crossbow" << endl;
					cin >> pinput2;
				}
			if (pinput2 == "pistols")
			{
				player1.setP_Power(pistols.getPower()); //sets the player's stats equal to the chosen weapon's stats
				player1.setP_Accuracy(pistols.getAccuracy());
				player1.setP_Agility(pistols.getAgility());
			}
			if(pinput2 == "shotgun")
			{
				player1.setP_Power(shotgun.getPower());
				player1.setP_Accuracy(shotgun.getAccuracy());
				player1.setP_Agility(shotgun.getAgility());
			}
			if(pinput2 == "rifle")
			{
				player1.setP_Power(rifle.getPower());
				player1.setP_Accuracy(rifle.getAccuracy());
				player1.setP_Agility(rifle.getAgility());
			}
			if(pinput2 == "crossbow")
			{
				player1.setP_Power(crossbow.getPower());
				player1.setP_Accuracy(crossbow.getAccuracy());
				player1.setP_Agility(crossbow.getAgility());
			}
		}

	}

}
