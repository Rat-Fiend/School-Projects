#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void change_to_coins(int change, int &qs, int &ds, int &ns, int &ps);
void change_to_coins(int change, int &qs, int &ds, int &ns, int &ps) {

	qs = change / 25;
	change = change % 25;

	ds = change / 10;
        change = change % 10;

	ns = change / 5;
        change = change % 5;

	ps = change;

	return;
}

void print_coins(int change, int qs, int ds, int ns, int ps);
void print_coins(int change, int qs, int ds, int ns, int ps) {

	cout << change << " cents breaks down into:" << endl;
	cout << qs << " quarters, " << ds << " dimes, " << ns << " nickels, and " << ps << " pennies." << endl;

	return;
}

void ask_user_for_change(int &change);
void ask_user_for_change(int &change) {

	cout << "Please enter an amount of change. (1 - 99)" << endl;
        cin >> change;
        while ( !( (change >= 1) && (change <= 99) )) {
                cout << "Invalid number, please enter a valid integer. (1 - 99)" << endl;
                cin >> change;
        }

	return;
}

int main() {

int change = 0, num_qs = 0, num_ds = 0, num_ns = 0, num_ps = 0;

	for (int i=0; i<2; ++i) {
		 ask_user_for_change(change);

		change_to_coins(change, num_qs, num_ds, num_ns, num_ps);

		print_coins(change, num_qs, num_ds, num_ns, num_ps);
	}
	return 0;
}
