#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
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
	int dealt = abs(int((((ppower*0.6) - (epower*0.4))(random(5)))));
	return dealt;
}

int main()
{
	Player player1 = Player("player1");
	Player bandit = Player("bandit");
	Player bounty_hunter = Player("bounty_hunter");
	Player hitman = Player("hitman");
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
				player1.setP_Power(4);
				player1.setP_Accuracy(3);
				player1.setP_Agility(10);
			}
			if(pinput2 == "shotgun")
			{
				player1.setP_Power(10);
				player1.setP_Accuracy(4);
				player1.setP_Agility(2);
			}
			if(pinput2 == "rifle")
			{
				player1.setP_Power(6);
				player1.setP_Accuracy(7);
				player1.setP_Agility(8);
			}
			if(pinput2 == "crossbow")
			{
				player1.setP_Power(5);
				player1.setP_Accuracy(10);
				player1.setP_Agility(3);
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
			if(randstat == 0)
			{
				bandit.setAgility(player1.getAgility() - 1);
				bandit.setPower(player1.getPower() - 1);
			}	bandit.setAccuracy(player1.getAccuracy() - 1);
			else if(randstat == 1)
			{
				bandit.setAgility(player1.getAgility() + 1);
				bandit.setPower(player1.getPower() + 1);
				bandit.setAccurcay(player1.getAccuracy() + 1);
			}
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
		case "boss":
		{	
			int phealth = 100;
			int bhealth = 200;
			int input;
			bstat = random(15);
			boss.setPower(player1.getPower() + bstat);
			boss.setAccuracy(player1.getAccuracy() + bstat);
			boss.setAgility(player1.getAgility() + bstat);
			while((phealth <= 0) || (bhealth <= 0))
			{
				cout << "Choose: 1 2 3 4 5 " << endl;
				cin >> pinput2;
				while((input != 1)||(input != 2)||(input != 3)||(input != 4)||(input != 5))
				{
					cout << "Choose: 1 2 3 4 5 " << endl;
					cin >> input;
				}
				int power = random(5);
				int power2 = random(5);
				while(power == power2)
				{
					power2 = random(5);
				}
				if(input = power)
				{
					cout << "Bad Choice: You take damage" << endl;
					phealth = phealth - 10;
					if(phealth <= 0)
					{
						test = "gameover";
						break;
					}
					else
					{
						cout << "You have " << phealth << " health left" << endl;
					}
				}
				if(input = power2)
				{
					cout << "Good Choice: The boss takes damage" << endl;
					bhealth = bhealth - 10;
					if(bhealth <= 0 )
					{
						test = "winfight";
						break;
					}
					else
					{
						cout << "The boss has " << bhealth << "health left" << endl;
					}
				}
				else
				{
					int bdealt = damage(boss.getPower(), player1.getPower());
					phealth -= bdealt;
					if(phealth < = 0)
					{
						cout << "The boss has finished you off" << endl;
						test = "gameover";
						break;
					}
					else
					{
						cout << "The boss dealt damage. You have " << phealth << " health left" << endl;
						int pdealt = damage(player1.getPower(), boss.getPower());
						bhealth -= pdealt;
						if(bhealth <= 0)
						{
							cout << "You finished off the boss" << endl;
							test = "winfight";
							break;
						}
						else
						{
							cout << "The boss takes damage.  It has " << bhealth << " health left" << endl;
						}
					}
				}	
			}
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
