#include <iostream>
#include <string>
#include <cstdlib>
#include "Weapon.cpp"
#include "Player.cpp"

using namespace std::


//typedef enum{intro, weapon_choice, chck_encounter, encount_gen, event_gen, boss1, boss2, boss3, event1, event2, event3, easy_fight, mid_fight, hard_fight}
int random(int numb)
{
	int rand_gen = (rand()% numb) + 1;
	return rand_gen;
}

int damage(int ppower, int epower)
{
	int dealt = (((ppower*0.6) - (epower*0.4))(random(5)));
	return dealt;
}

int main()
{
	Player player1 = Player("player1");
	Player bandit = Player("bandit");
	Player bounty_hunter = Player("bounty_hunter");
	Player hitman = Player("hitman");
	Weapon pistols = Weapon(pistols, 4, 10, 3);
	Weapon shotgun = Weapon(shotgun, 10, 2, 4);
	Weapon rifle = Weapon(rifle, 6, 8, 7);
	Weapon crossbow = Weapon(crossbow, 5, 3, 10);
	string BOG;
	string pinput;
	string pinput2;
	int courage = 3;
	int lives = 2;
	int playerlvl = 1;

	string test = "intro";
	while(test != ""){
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
			while((pinput2 != "pistols") || (pinput2 != "shotgun")||(pinput2 != "rifle")||(pinput2 != "crossbow"))
			{
				cout << "Choose: pistols, shotgun, rifle, or crossbow" << endl;
				cin >>pinput2;
			}
			if (pinput2 == "pistols")
			{
				player1.setP_Power(pistols.getPower());
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
			test = "fight";
			break;
		}
		case "encounter":
		{
			int chck = random(1);
			if(chck == 0)
			{
				test = "eventmake";
				break;
			}
			if(chck == 1)
			{
				test = "enemymake";
				break;
			}
			else
			{
				test = "encounter";
			}
		}
		case "enemymake":
		{
			if((playerlvl == 10)||(playerlvl == 18)||(playerlvl ==25))
			{
				test = "boss";
				break;
			}
			int m = random(playerlvl);
			if((m >= 1)&&(m < 10))
			{
				test = "enemy1";
				break;
			}
			if((m > 10)&&(m < 18))
			{
				test = "enemy2";
				break;
			}
			if((m > 18)&&(m < 25))
			{
				test = "enemy3";
				break;
			}
		}
		case "enemy1":
		{
			int randstat = random(1);
			bandit.setAgility(player1.getAgility()+ randstat);
			bandit.setPower(player1.getPower() + randstat);
			bandit.setAccuracy(player1.getAccuracy() + randstat);
			test = "fight1";
			break;
		}
				
		case "fight1":
		{
			cout << "You have encountered a bandit" << endl;
			cout << "Choose: fight or run" << endl;
			cin >> pinput2;
			while((pinput2 != "fight")||(pinput2 != "run"))
			{
				cout << "Choose: fight or run" << endl;
				cin >> pinput2;
			}
			if(pinput2 == "fight")
			{
				int phealth = 100;
				int ehealth = 100;
				while((phealth <= 0) ||(ehealth <= 0))
				{
					if(player1.getAgility() >  bandit.getAgility())
					{
						int dealt = damage(player1.getPower(), bandit.getPower());
						ehealth = ehealth - dealt;
						if(ehealth <= 0)
						{
							test = "winfight";
							break;
						}
						else
						{
							int edealt = damage(bandit.getPower(), player1.getPower());
							phealth = phealth - edealt;
						}
					}
					else if(player1.getAgility() <= bandit.getAgility())
					{
						int endealt = damage(bandit.getPower(), player1.getPower());
						phealth = phealth - endealt;
						if(phealth <= 0)
						{
							test = "gameover";
							break;
						}
						else
						{
							int pdealt = damage(player1.getPower(), bandit.getPower());
							ehealth = ehealth - pdealt;
						}
					}
				}
				break;
			}
			if(pinput2 == "run")
			{
				courage -=1;
				if (courage <=0)
				{
					test = "gameover";
					break;
				}
			}
			test = "encounter";
			break;
		}
		case "gameover":
		{
			cout << "Your choices were too much of a burden." << endl;
			cout << "GAME OVER" << endl;
			test = "";
			break;
		}

	}
   }
return 0;
}
