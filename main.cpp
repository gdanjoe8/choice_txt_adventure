#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "Weapon.h"
#include "Player.h"

using namespace std;

enum states{empty, intro, weapon_choice, enemymake, enemy1, enemy2, enemy3, boss1, fight1, fight2, fight3, winfight, gameover, victory};

int random(int numb)//function for random numbers
{
	int rand_gen = (rand()% numb) + 1;
	return rand_gen;
}

int damage(int ppower, int epower)//function for caclulation battle damage
{
	int dealt = abs((((ppower*(6/10)) - (epower*(4/10)))*(random(5))));
	return dealt;
}
string weaponLister(vector<Weapon> list)
{
	string weaponout;
	for(auto it = list.begin(); it != list.end(); ++it)
	{
		weaponout += it->getName();
		if(it+1 != list.end())
		{
			weaponout += ", ";
		}
		
	}
	return weaponout;
}
struct weaponnamepred{
	string name;
	weaponnamepred(string name){
		this->name = name;
	}
	bool operator()(Weapon thing){
		return thing.getName() == name;
	}
};
		
int main()
{
	Player player1("player1");//player object
	Player bandit("bandit");//enemy player objects
	Player bounty_hunter("bounty_hunter");
	Player hitman("hitman");
	Player boss("boss");
	vector<Weapon> weaponlist = {Weapon("pistols",4, 10 , 3), Weapon("shotgun", 10, 2, 4), Weapon("rifle", 6, 8 ,7), Weapon("crossbow", 5, 3, 10)};
	string BOG;//input strings
	string pinput;
	string pinput2;
	int courage = 3;//count of character courage
	int lives = 2;//number of lives per game
	int playerlvl = 1;//player starting level
	int bosscount = 0;//count for boss encouter
	int wincount = 0;//count for number of wins

	states test = intro;
	while(test != empty)
	{
		switch(test)
		{
			case intro://introduction case
			{
				cout << "Welcome to Choice" << endl;
				cout << "A game where you will have to make choices" << endl;
				cout << "Choose: boy or girl?" << endl;
				cin >> BOG;
				cout << "Choose a name:" << endl;
				cin >> pinput;
				player1.setP_Name(pinput);
				test = weapon_choice;
				break;
			}

			case weapon_choice://player chooses weapon and recieves base stats for game
			{
				cout << "Choose:" << weaponLister(weaponlist) << endl;
				cin >> pinput2;
				auto it = find_if(weaponlist.begin(),weaponlist.end(),weaponnamepred(pinput2));
				if(it != weaponlist.end())
				{
					player1.setP_Power(it->getPower());
					player1.setP_Accuracy(it->getAccuracy());
					player1.setP_Agility(it->getAgility());
					
				}
				else
				{
					test = weapon_choice;
					break;
				}
			
				test = enemymake;
				break;
			}
			case enemymake://randomly pick between weak, medium, and strong enemy
			{
				if((playerlvl == 10)||(playerlvl == 18)||(playerlvl ==25))
				{
					test = boss1;
					break;
				}
				int m = random(playerlvl);
				if((m >= 1)&&(m < 10))
				{
					test = enemy1;
					break;
				}
				if((m > 10)&&(m < 18))
				{
					test = enemy2;
					break;
				}
				if((m > 18)&&(m < 25))
				{
					test = enemy3;
					break;
				}
			}
			case enemy1://create weak enemy
			{
				int randstat = random(1);
				if(randstat == 0)
				{
					bandit.setP_Agility(player1.getP_Agility() - 1);
					bandit.setP_Power(player1.getP_Power() - 1);
					bandit.setP_Accuracy(player1.getP_Accuracy() - 1);
				}
				else if(randstat == 1)
				{
					bandit.setP_Agility(player1.getP_Agility() + 1);
					bandit.setP_Power(player1.getP_Power() + 1);
					bandit.setP_Accuracy(player1.getP_Accuracy() + 1);
				}
				test = fight1;
				break;
			}
			case enemy2://create medium enemy
			{
				int randchck = random(1);
				int randstat2 = random(5);
				if(randchck == 0)
				{
					bounty_hunter.setP_Agility(player1.getP_Agility() - randstat2);
					bounty_hunter.setP_Power(player1.getP_Power() - randstat2);
					bounty_hunter.setP_Accuracy(player1.getP_Accuracy() - randstat2);
				}
				else if(randchck == 1)
				{
					bounty_hunter.setP_Agility(player1.getP_Agility() + randstat2);
					bounty_hunter.setP_Power(player1.getP_Power() + randstat2);
					bounty_hunter.setP_Accuracy(player1.getP_Accuracy() + randstat2);
				}
				test = fight2;
				break;
			}
			case enemy3://create strong enemy
			{
				int randchck3 = random(1);
				int randstat3 = random(8);
				if(randchck3 == 0)
				{
					hitman.setP_Agility(player1.getP_Agility() - randstat3);
					hitman.setP_Power(player1.getP_Power() - randstat3);
					hitman.setP_Accuracy(player1.getP_Accuracy() - randstat3);
				}
				else if(randchck3 == 1)
				{
					hitman.setP_Agility(player1.getP_Agility() + randstat3);
					hitman.setP_Power(player1.getP_Power() + randstat3);
					hitman.setP_Accuracy(player1.getP_Accuracy() + randstat3);
				}
				test = fight3;
				break;
			}
			case fight1://fight against weak enemy
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
					while((phealth > 0) ||(ehealth > 0))
					{
						if(player1.getP_Agility() >  bandit.getP_Agility())
						{
							int dealt = damage(player1.getP_Power(), bandit.getP_Power());
							ehealth = ehealth - dealt;
							if(ehealth <= 0)
							{
								test = winfight;
								break;
							}
							else
							{
								cout << "You dealt damage." << "The bandit has " << ehealth << " health left" << endl;
								int edealt = damage(bandit.getP_Power(), player1.getP_Power());
								phealth = phealth - edealt;
								cout << "The bandit dealt damage." << "You have " << phealth << " health left" << endl;
							}
						}
						else if(player1.getP_Agility() <= bandit.getP_Agility())
						{
							if((phealth <= 0)&& (lives <= 0))
							{
								test = gameover;
								break;
							}
							int endealt = damage(bandit.getP_Power(), player1.getP_Power());
							phealth = phealth - endealt;
							if((phealth <= 0)&& (lives <= 0))
							{
								test = gameover;
								break;
							}
							if((phealth <= 0)&&(lives >0))
							{
								lives -= 1;
								test = weapon_choice;
								break;
							}
							else
							{
								cout << "The bandit dealt damage." << "You have " << phealth << " health left" << endl;
								int pdealt = damage(player1.getP_Power(), bandit.getP_Power());
								ehealth = ehealth - pdealt;
								cout << "You dealt damage." << "The bandit has " << ehealth << " health left" << endl;
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
						test = gameover;
						break;
					}
				}
				test = enemymake;
				break;
			}
			case fight2://fight against medium enemy
			{
				cout << "You have encountered a bounty hunter" << endl;
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
					while((phealth > 0) ||(ehealth > 0))
					{
						if(player1.getP_Agility() >  bounty_hunter.getP_Agility())
						{
							int dealt = damage(player1.getP_Power(), bounty_hunter.getP_Power());
							ehealth = ehealth - dealt;
							if(ehealth <= 0)
							{
								test = winfight;
								break;
							}
							else
							{
								cout << "You dealt damage." << "The bounty hunter has " << ehealth << " health left" << endl;
								int edealt = damage(bounty_hunter.getP_Power(), player1.getP_Power());
								phealth = phealth - edealt;
								cout << "The bounty hunter dealt damage." << "You have " << phealth << " health left" << endl;
							}
						}
						else if(player1.getP_Agility() <= bounty_hunter.getP_Agility())
						{
							if(ehealth <= 0)
							{
								test = winfight;
								break;
							}
							int endealt = damage(bounty_hunter.getP_Power(), player1.getP_Power());
							phealth = phealth - endealt;
							if((phealth <= 0)&& (lives <= 0))
							{
								test = gameover;
								break;
							}
							if((phealth <= 0)&&(lives >0))
							{
								lives -= 1;
								test = weapon_choice;
								break;
							}
							else
							{
								cout << "The bounty hunter dealt damage." << "You have " << phealth << " health left" << endl;
								int pdealt = damage(player1.getP_Power(), bounty_hunter.getP_Power());
								ehealth = ehealth - pdealt;
								cout << "You dealt damage." << "The bounty hunter has " << ehealth << " health left" << endl;
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
						test = gameover;
						break;
					}
				}
				test = enemymake;
				break;
			}
			case fight3://fight strong enemy
			{
				cout << "You have encountered a hitman" << endl;
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
					while((phealth > 0)||(ehealth > 0))
					{
						if(player1.getP_Agility() >  hitman.getP_Agility())
						{
							int dealt = damage(player1.getP_Power(), hitman.getP_Power());
							ehealth = ehealth - dealt;
							if(ehealth <= 0)
							{
								test = winfight;
								break;
							}
							else
							{
								cout << "You dealt damage." << "The hitman has " << ehealth << " health left" << endl;
								int edealt = damage(hitman.getP_Power(), player1.getP_Power());
								phealth = phealth - edealt;
								cout << "The hitman dealt damage." << "You have " << phealth << " health left" << endl;
							}
						}
						else if(player1.getP_Agility() <= hitman.getP_Agility())
						{
							if(ehealth <= 0)
							{
								test = winfight;
								break;
							}
							int endealt = damage(hitman.getP_Power(), player1.getP_Power());
							phealth = phealth - endealt;
							if((phealth <= 0)&& (lives <= 0))
							{
								test = gameover;
								break;
							}
							if((phealth <= 0)&&(lives >0))
							{
								lives -= 1;
								test = weapon_choice;
								break;
							}
							else
							{
								cout << "The hitman dealt damage." << "You have " << phealth << " health left" << endl;
								int pdealt = damage(player1.getP_Power(), hitman.getP_Power());
								ehealth = ehealth - pdealt;
								cout << "You dealt damage." << "The hitman has " << ehealth << " health left" << endl;
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
						test = gameover;
						break;
					}
				}
				test = enemymake;
				break;
			}
			case boss1://fight boss, after 3rd time fighting him will win game
			{
				bosscount += 1;
				int phealth = 100;
				int bhealth = 200;
				int input;
				int bstat = random(15);
				boss.setP_Power(player1.getP_Power() + bstat);
				boss.setP_Accuracy(player1.getP_Accuracy() + bstat);
				boss.setP_Agility(player1.getP_Agility() + bstat);
				while((phealth > 0) || (bhealth > 0))
				{
					cout << "Choose: 1, 2, 3, 4, or 5 " << endl;
					cin >> input;
					while((input != 1)||(input != 2)||(input != 3)||(input != 4)||(input != 5))
					{
						cout << "Choose: 1, 2, 3, 4, or 5 " << endl;
						cin >> input;
					}
					int power = random(5);
					int power2 = random(5);
					while(power == power2)
					{
						power2 = random(5);
					}
					if(input == power)
					{
						cout << "Bad Choice: You take damage" << endl;
						phealth = phealth - 10;
						if((phealth <= 0)&& (lives <= 0))
						{
							test = gameover;
							break;
						}
						if((phealth <= 0)&&(lives > 0))
						{
							lives -=1;
							test = weapon_choice;
							break;
						}
						else
						{
							cout << "You have " << phealth << " health left" << endl;
						}
					}
					if(input == power2)
					{
						cout << "Good Choice: The boss takes damage" << endl;
						bhealth = bhealth - 10;
						if(bhealth <= 0 )
						{
							if(bosscount == 3)
							{
								test = victory;
								break;
							}
							else
							{
								test = winfight;
								break;
							}
						}
						else
						{
							cout << "The boss has " << bhealth << "health left" << endl;
						}
					}
					else
					{
						int bdealt = damage(boss.getP_Power(), player1.getP_Power());
						phealth -= bdealt;
						if((phealth <= 0)&&(lives <= 0))
						{
							cout << "The boss has finished you off" << endl;
							test = gameover;
							break;
						}
						if((phealth <= 0)&&(lives > 0))
						{
							lives -= 1;
							cout << "The boss has finished you off" << endl;
							test = weapon_choice;
							break;
						}
						else
						{
							cout << "The boss dealt damage. You have " << phealth << " health left" << endl;
							int pdealt = damage(player1.getP_Power(), boss.getP_Power());
							bhealth -= pdealt;
							if(bhealth <= 0)
							{
								if(bosscount == 3)
								{
									cout << "You finished off the boss" << endl;
									test = victory;
									break;
								}
								else
								{
									cout << "You finished off the boss" << endl;
									test = winfight;
									break;
								}
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
			case winfight://after winning a fight can possibly level up
			{
				wincount += 1;
				cout << "You win the fight.  You survive another day." << endl;
				if ( wincount >= playerlvl)
				{
					playerlvl +=1;
					player1.setP_Power(player1.getP_Power()+1);
					player1.setP_Agility(player1.getP_Agility() +2);
					player1.setP_Accuracy(player1.getP_Accuracy()+2);
					cout << "Congradulations " << player1.getP_Name() << ", you managed to level up." << endl;
					cout << "You are now level " << playerlvl << endl;
				}
				test = enemymake;
				break;

			}
			case gameover://gameover messages
			{
				if(lives <=0)
				{
					cout << "You lost your last live." << endl;
					cout << "GAME OVER" << endl;
					test = empty;
					break;
				}
				else
				{
					cout << "Your choices were too much of a burden." << endl;
					cout << "GAME OVER" << endl;
				test = empty;
				break;
				}
			}
			case victory://victory condition messages
			{
				cout << "Congradulations " << player1.getP_Name() <<", you beat the final boss" << endl;
				cout << "Your choices lead you to victory. " << endl;
				test = empty;
			}
			case empty:
			{
				cout << "Congradulations. Please recompile if you would like to play again." << endl;
			}

		}
	  }
	return 0;
	}
