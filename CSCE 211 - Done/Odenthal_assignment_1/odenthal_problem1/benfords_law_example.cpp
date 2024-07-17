// Entire code authored by Quinton Odenthal

#include <iostream>
#include <random>
using namespace std;
int main()
{
	int x;
	int num1s, num2s, num3s, num4s, num5s, num6s, num7s, num8s, num9s;
	num1s = num2s = num3s = num4s = num5s = num6s = num7s = num8s = num9s = 0;
	for(int i=0; i <= 3295; ++i) {
		// cin >> x;
                x = rand();

		while(x > 9) {x = x / 10;}

		switch(x) {
			case 1:
				++num1s;
				break;
                        case 2:
                                ++num2s;
                                break;
                        case 3:
                                ++num3s;
                                break;
                        case 4:
                                ++num4s;
                                break;
                        case 5:
                                ++num5s;
                                break;
                        case 6:
                                ++num6s;
                                break;
                        case 7:
                                ++num7s;
                                break;
                        case 8:
                                ++num8s;
                                break;
                        case 9:
                                ++num9s;
                                break;
			}
	}
	cout << " Number | Occurances | Frequency | Benfords law prediction " << endl;
	cout << "   1    |   " << num1s << "   |     " << (num1s * 100)  / 3295 << "%    |            30%         " << endl;
	cout << "   2    |   " << num2s << "   |     " << (num2s * 100)  / 3295 << "%    |            18%         " << endl;
	cout << "   3    |   " << num3s << "   |     " << (num3s * 100)  / 3295 << "%    |            13%         " << endl;
	cout << "   4    |   " << num4s << "   |     " << (num4s * 100)  / 3295 << "%    |            10%         " << endl;
	cout << "   5    |   " << num5s << "   |     " << (num5s * 100)  / 3295 << "%    |            8%         " << endl;
	cout << "   6    |   " << num6s << "   |     " << (num6s * 100)  / 3295 << "%    |            7%         " << endl;
	cout << "   7    |   " << num7s << "   |     " << (num7s * 100)  / 3295 << "%    |            6%         " << endl;
	cout << "   8    |   " << num8s << "   |     " << (num8s * 100)  / 3295 << "%    |            5%         " << endl;
	cout << "   9    |   " << num9s << "   |     " << (num9s * 100)  / 3295 << "%    |            5%         " << endl;

	return 0;
}
