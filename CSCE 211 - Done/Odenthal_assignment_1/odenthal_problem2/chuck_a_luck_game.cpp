// Entire code written by Quinton Odenthal

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int calculate_winning_dice(int d1, int d2, int d3, int user_num) { // counts how many dice match user's number
                int winning_dice = 0;

                if (d1 == user_num) winning_dice++;
                if (d2 == user_num) winning_dice++;
                if (d3 == user_num) winning_dice++;

                return winning_dice;
        }

int roll_die() { // gets random number 1 - 6
                return (rand() % 6) + 1;
                }

int main() {
	int w, n, user_money;
	int d1, d2, d3, winning_dice;
	char p;
	user_money = 100;

	int calculate_winning_dice(int d1, int d2, int d3, int user_num);
	int roll_die();

	srand(time(NULL));

	cout << "Hello user, would you like to play a game of Chuck-a-luck? (y for yes / else for no)" << endl;
	cin >> p;
	while (p == 'y') {

		cout << "Alright, you have $" << user_money << // asks for wager from user (int)
		". Place your wager. (more than zero and less than or equal to $" << user_money << '.' << endl;
		cin >> w;
		while ( !(w > 0 && w <= user_money)) { // checks if user's input is in range
			cout << "Invalid wager. Please enter a valid wager." << endl;
			cin >> w; // PROBLEM asks user to try again, works just fine with integer inputs, but starts
				  // infinite loop when entering some sort of decimal, idk what is up
		}

		cout << "Pick your number. (1, 2, 3, 4, 5, or 6)" << endl; // asks for int from user
                cin >> n;
		n = n / 1;
                while ( !(n >= 1 && n <= 6)) {
                        cout << "Invalid number. Please enter a valid number." << endl;
                        cin >> n; // has the same problem as above
                }

                cout << "Now roll the dice. (r to roll / else to cancel)" << endl;
		cin >> p;
                if (p == 'r') { // asks user to roll dice, works great
			user_money = user_money - w;

			d1 = roll_die();
			d2 = roll_die();
			d3 = roll_die();

			cout << "  _____   _____   _____  " << endl; // prints dice results
			cout << " |     | |     | |     | " << endl;
			cout << " |  " << d1 << "  | |  " << d2 << "  | |  " << d3 << "  | " << endl;
			cout << " |_____| |_____| |_____| " << endl;

			winning_dice = calculate_winning_dice(d1, d2, d3, n);

			switch (winning_dice) { // personalized messages for different dice results
				case 0:
					cout << "Darn, you didn't get any winning dice. Better luck next time." << endl;
					break;
				case 1:
                                        cout << "You got one winning die, and recieve $" << winning_dice * w << "." << endl;
					user_money += winning_dice * w;
                                        break;
				case 2:
                                        cout << "You got two winning dice, and recieve $" << winning_dice * w << "." << endl;
                                        user_money += winning_dice * w;
                                        break;

				case 3:
                                	cout << "Horray! You won all three dice and recieve $" << winning_dice * w << "." << endl;
                                        user_money += winning_dice * w;
                                        break;
				}
                }
		if (user_money == 0) { // breaks the while loop if user has run out of funds
			cout << "You have run out of money." << endl;
			break;
		}
		else {
			cout << "Would you like to play again? (y for yes / else for no)" << endl;
			cin >> p;
		}
	}
	cout << "Have a nice day." << endl;

	return 0;
}
