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
	srand(numb);
	return rand_gen;
}

int damage(int ppower)//function for caclulation battle damage
{
	int dealt = (ppower - 5)*((ppower)/4);
	if(dealt <= 0)
	{
		dealt = 2;
	}
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
struct weaponnamepred
{
	string name;
	weaponnamepred(string name)
	{
		this->name = name;
	}
	bool operator()(Weapon thing)
	{
		return thing.getName() == name;
	}
};

int main()
{
	Player player1("player1");//player object
	Player playerImage("playerImage");
	Player bandit("bandit");//enemy player objects
	Player bounty_hunter("bounty_hunter");
	Player hitman("hitman");
	Player boss("boss");
	Weapon fight("fight",0,0,0);
	Weapon run("run",0,0,0);
	vector<Weapon> weaponlist = {Weapon("pistols",5, 10 , 3), Weapon("shotgun", 10, 2, 4), Weapon("rifle", 7, 8 ,7), Weapon("crossbow", 5, 3, 10)};
	vector<Weapon> fightOrRun = {Weapon("fight",0,0,0), Weapon("run",0,0,0)};
	vector<Weapon> bosschoice = {Weapon("1",1,0,0), Weapon("2",2,0,0), Weapon("3",3,0,0), Weapon("4",4,0,0), Weapon("5",5,0,0)};
	string BOG;//input strings
	string pinput;
	string pinput2;
	int courage = 3;//count of character courage
	int lives = 2;//number of lives per game
	int playerlvl = 1;//player starting level
	int statinc = 1;
	int healthinc = 1;
	int phealth = 100;
	int ehealth = 100;
	int bhealth = 250;
	int bosscount = 0;//count for boss encouter
	int wincount = 0;//count for number of wins
	states test = intro;
	while(test != empty)
	{
		switch(test)
		{
			case intro:/*introduction case*/
			{
				cout << "Welcome to Choice" << endl;
				cout << "A game where you will have to make choices" << endl;
				while(BOG != "boy" || BOG != "girl")
				{
					cout << "Choose: boy or girl" << endl;
					getline(cin,BOG);
					if(BOG == "boy" || BOG == "girl")
					{
						break;
					}
				}
				cout << "Choose a name:" << endl;
				cin >> pinput;
				player1.setP_Name(pinput);
				test = weapon_choice;
				break;
			}

			case weapon_choice://player chooses weapon and recieves base stats for game
			{
				cout << "Choose: " << weaponLister(weaponlist) << endl;
				cin >> pinput2;
				auto it = find_if(weaponlist.begin(),weaponlist.end(),weaponnamepred(pinput2));
				if(it != weaponlist.end())
				{
					player1.setP_Power(it->getPower());
					player1.setP_Accuracy(it->getAccuracy());
					player1.setP_Agility(it->getAgility());
					playerImage.setP_Power(it->getPower());
					playerImage.setP_Accuracy(it->getAccuracy());
					playerImage.setP_Agility(it->getAgility());

				}
				else
				{
					test = weapon_choice;
					break;
				}
			}
			case enemymake://randomly pick between weak, medium, and strong enemy
			{
				if((playerlvl == 10)||(playerlvl == 18)||(playerlvl ==25))
				{
					test = boss1;
					break;
				}
				//int m = random(playerlvl);
				if((playerlvl >= 1)&&(playerlvl < 7))
				{
					test = enemy1;
					break;
				}
				if((playerlvl> 7)&&(playerlvl < 15))
				{
					test = enemy2;
					break;
				}
				if((playerlvl > 15)&&(playerlvl < 25))
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
					bandit.setP_Agility(playerImage.getP_Agility() - (statinc + 1));
					bandit.setP_Power(playerImage.getP_Power() - (statinc + 1));
					bandit.setP_Accuracy(playerImage.getP_Accuracy() - (statinc + 1));
				}
				else if(randstat == 1)
				{
					bandit.setP_Agility(playerImage.getP_Agility() - statinc);
					bandit.setP_Power(playerImage.getP_Power()  - statinc);
					bandit.setP_Accuracy(playerImage.getP_Accuracy() - statinc);
				}
				test = fight1;
				break;
			}
			case enemy2://create medium enemy
			{
				int randchck = random(1);
				if(randchck == 0)
				{
					bounty_hunter.setP_Agility(playerImage.getP_Agility() -statinc);
					bounty_hunter.setP_Power(playerImage.getP_Power() - statinc);
					bounty_hunter.setP_Accuracy(playerImage.getP_Accuracy() - statinc);
				}
				else if(randchck == 1)
				{
					bounty_hunter.setP_Agility(bandit.getP_Agility()+ statinc);
					bounty_hunter.setP_Power(bandit.getP_Power());
					bounty_hunter.setP_Accuracy(bandit.getP_Accuracy() + statinc);
				}
				test = fight2;
				break;
			}
			case enemy3://create strong enemy
			{
				int randchck3 = random(1);
				if(randchck3 == 0)
				{
					hitman.setP_Agility(bandit.getP_Agility() - statinc);
					hitman.setP_Power(bandit.getP_Power() - statinc);
					hitman.setP_Accuracy(bandit.getP_Accuracy() - statinc);
				}
				else if(randchck3 == 1)
				{
					hitman.setP_Agility(bounty_hunter.getP_Agility());
					hitman.setP_Power(bounty_hunter.getP_Power() + statinc);
					hitman.setP_Accuracy(bounty_hunter.getP_Accuracy() + statinc);
				}
				test = fight3;
				break;
			}
			case fight1://fight against weak enemy
			{
				cout << "You have encountered a bandit" << endl;
				cout << "Choose: fight or run" << endl;
				cin >> pinput2;
				auto it = find_if(fightOrRun.begin(),fightOrRun.end(),weaponnamepred(pinput2));
				if(it == fightOrRun.end())
				{
					test = fight1;
					break;
				}
				if(it->getName() == fight.getName())
				{
					int pdealt = damage(player1.getP_Power());
					int edealt = damage(bandit.getP_Power());
					while(phealth > 0)
					{
						if(player1.getP_Agility() >=  bandit.getP_Agility())
						{
							ehealth = ehealth - pdealt;
							if(ehealth <= 0)
							{
								cout << "You dealt " << pdealt << " damage" << endl;
								cout << "You finished off the enemy" << endl;
								test = winfight;
								break;
							}
							else
							{
								cout << "You dealt damage." << " The bandit has " << ehealth << " health left" << endl;
								phealth = phealth - edealt;
								cout << "The bandit dealt damage." << " You have " << phealth << " health left" << endl;
							}
						}
						else if(player1.getP_Agility() < bandit.getP_Agility())
						{
							if(ehealth <= 0)
							{
								cout << "You dealt " << pdealt << " damage" << endl;
								cout << "You finished off the enemy" << endl;
								test = winfight;
								break;
							}
							phealth = phealth - edealt;
							if(phealth <= 0)
							{
								test = gameover;
								break;
							}
							cout << "The bandit dealt damage." << "You have " << phealth << " health left" << endl;
							ehealth = ehealth - pdealt;
							cout << "You dealt damage." << "The bandit has " << ehealth << " health left" << endl;

						}
					}
					if(ehealth <= 0 )
					{
						test = winfight;
						break;
					}
					if(phealth <= 0)
					{
						test = gameover;
						break;
					}
				}
				if(it->getName() == run.getName())
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
				auto it = find_if(fightOrRun.begin(),fightOrRun.end(),weaponnamepred(pinput2));
				if(it == fightOrRun.end())
				{
					test = fight2;
					break;
				}
				if(it->getName() == fight.getName())
				{
					int pdealt = damage(player1.getP_Power());
					int edealt = damage(bounty_hunter.getP_Power());
					while(phealth > 0)
					{
						if(player1.getP_Agility() >=  bounty_hunter.getP_Agility())
						{
							ehealth = ehealth - pdealt;
							if(ehealth <= 0)
							{
								cout << "You dealt " << pdealt << " damage" << endl;
								cout << "You finished off the enemy" << endl;
								test = winfight;
								break;
							}
							else
							{
								cout << "You dealt damage." << " The bounty hunter has " << ehealth << " health left" << endl;
								phealth = phealth - edealt;
								cout << "The bounty hunter dealt damage." << " You have " << phealth << " health left" << endl;
							}
						}
						else if(player1.getP_Agility() < bounty_hunter.getP_Agility())
						{
							if(ehealth <= 0)
							{
								cout << "You dealt " << pdealt << " damage" << endl;
								cout << "You finished off the enemy" << endl;
								test = winfight;
								break;
							}
							phealth = phealth - edealt;
							if(phealth <= 0)
							{
								test = gameover;
								break;
							}
							cout << "The bounty hunter dealt damage." << "You have " << phealth << " health left" << endl;
							ehealth = ehealth - pdealt;
							cout << "You dealt damage." << "The bounty hunter has " << ehealth << " health left" << endl;
							}
						}
						if(ehealth <= 0 )
						{
							test = winfight;
							break;
						}
						if(phealth <= 0)
						{
							test = gameover;
							break;
						}
					}
					if(it->getName() == run.getName())
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
				auto it = find_if(fightOrRun.begin(),fightOrRun.end(),weaponnamepred(pinput2));
				if(it == fightOrRun.end())
				{
					test = fight3;
					break;
				}
				if(it->getName() == fight.getName())
				{
					int pdealt = damage(player1.getP_Power());
					int edealt = damage(hitman.getP_Power());
					while((phealth > 0)||(ehealth > 0))
					{
						if(player1.getP_Agility() >  hitman.getP_Agility())
						{
							ehealth = ehealth - pdealt;
							if(ehealth <= 0)
							{
								cout << "You dealt " << pdealt << " damage" << endl;
								cout << "You finished off the enemy" << endl;
								test = winfight;
								break;
							}
							else
							{
								cout << "You dealt damage." << "The hitman has " << ehealth << " health left" << endl;
								phealth = phealth - edealt;
								cout << "The hitman dealt damage." << "You have " << phealth << " health left" << endl;
							}
						}
						else if(player1.getP_Agility() <= hitman.getP_Agility())
						{
							if(ehealth <= 0)
							{
								cout << "You dealt " << pdealt << " damage" << endl;
								cout << "You finished off the enemy" << endl;
								test = winfight;
								break;
							}
							phealth = phealth - edealt;
							if(phealth <= 0)
							{
								test = gameover;
								break;
							}
							else
							{
								cout << "The hitman dealt damage." << "You have " << phealth << " health left" << endl;
								ehealth = ehealth - pdealt;
								cout << "You dealt damage." << "The hitman has " << ehealth << " health left" << endl;
							}
						}
					}
					break;
				}
				if(it->getName() == run.getName())
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
				cout << "You have encountered a boss" << endl;
				bosscount += 1;
				int bstat = (playerlvl);
				boss.setP_Power(playerImage.getP_Power() + bstat);
				boss.setP_Accuracy(playerImage.getP_Accuracy() + bstat);
				boss.setP_Agility(playerImage.getP_Agility() + bstat);
				while((phealth > 0) || (bhealth > 0))
				{
					cout << "Choose: 1, 2, 3, 4, or 5 " << endl;
					cin >> pinput2;
					auto it = find_if(bosschoice.begin(),bosschoice.end(),weaponnamepred(pinput2));
					if(it == bosschoice.end())
					{
						test = boss1;
						break;
					}
					int power = random(5);
					int power2 = random(6);
					if(power2 == 6)
					{
						power2 -= 1;
					}
					if(power == power2)
					{
						int power3 = random(6);
						if(power3 == 6)
						{
							power3 -=1;
						}
						power2 = power3;
					}
					if(it->getPower() == power)
					{
						cout << "Bad Choice: You take damage" << endl;
						phealth = phealth - 10;
						if(phealth <= 0)
						{
							test = gameover;
							break;
						}
						else
						{
							cout << "You have " << phealth << " health left" << endl;
						}
					}
					if(it->getPower() == power2)
					{
						cout << "Good Choice: The boss takes damage" << endl;
						bhealth -= 10;
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
								wincount = playerlvl;
								bosscount +=1;
								break;
							}
						}
						else
						{
							cout << "The boss has " << bhealth << " health left" << endl;
						}
					}
					else
					{
						int bdealt = damage(boss.getP_Power());
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
							test = gameover;
							break;
						}
						else
						{
							cout << "The boss dealt damage. You have " << phealth << " health left" << endl;
							int pdealt = damage(player1.getP_Power());
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
									bosscount +=1;
									wincount = playerlvl;
									test = winfight;
									break;
								}
							}
							else
							{
								cout << "You damaged the boss.  It has " << bhealth << " health left" << endl;
							}
						}
					}
				}
				break;
			}
			case winfight://after winning a fight can possibly level up
			{
				if((bosscount == 2)||(bosscount == 1))
				{
					playerImage.setP_Power(player1.getP_Power() + 1);
					playerImage.setP_Agility(player1.getP_Agility() + 1);
					playerImage.setP_Accuracy(player1.getP_Accuracy() + 1);
					bhealth = (200)*(1+(healthinc/3));
				}
				wincount += 1;
				cout << "You win the fight.  You survive another day." << endl;
				if ( wincount >= playerlvl/2)
				{
					playerlvl +=1;
					statinc +=1;
					healthinc +=1;
					player1.setP_Power(player1.getP_Power()+2);
					player1.setP_Agility(player1.getP_Agility() +2);
					player1.setP_Accuracy(player1.getP_Accuracy()+2);
					cout << "Congradulations " << player1.getP_Name() << ", you managed to level up." << endl;
					cout << "You are now level " << playerlvl << endl;
					wincount = 0;
					phealth = (100)*(1+(healthinc/5));
					ehealth = (100)*(1+(healthinc/4));
				}
				test = enemymake;
				break;

			}
			case gameover://gameover messages
			{
				lives -=1;
				if(lives <=0)
				{
					cout << "You lost your last life." << endl;
					cout << "GAME OVER" << endl;
					test = empty;
					break;
				}
				else if (lives > 0)
				{
					cout << "You died in battle." << endl;
					cout << "You have lost a life." << endl;
					cout << "You awake where you fell in battle." << endl;
					cout << "The next enemy approachest." << endl;
					test = enemymake;
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
				break;
			}
			case empty:
			{
				cout << "Please recompile if you would like to play again." << endl;
			}
		}
	  }
	return 0;
}