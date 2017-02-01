// find FInd the mean mode max median and average for a set of numbers

// Start standsard opening

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

inline void keep_window_open() { char ch; cin >> ch; }

inline void simple_error(string s)	// write ``error: s and exit program
{
	cerr << "error: " << s << '\n';
	keep_window_open();		// for some Windows environments
	exit(1);
}

// End standard opening

// declarations
bool yes_no(string s) {
	char response{ 'X' };
	cout << s << " (y/n): ";
	cin >> response;
	switch (response)
	{
	case 'y':
		return true;
	case 'n':
		return false;
	default:
		return false;
	}
};

//	Declarations
double get_max(vector<double>& l);
double get_min(vector<double>& l);
double get_mode(vector<double>& l);
double get_mean(vector<double>& l);
double get_median(vector<double>& l);
double get_average(vector<double>& l);
void print_list(vector<double>& l);

//  Start the main loop - continue until user says quit

int main() {
	double user_input_number{ 0.0 };
	char user_input_char{ 'A' };
	double max_of_list{ 0 };
	double min_of_list{ 0 };
	double mode_of_list{ 0 };
	double mean_of_list{ 0 };
	double median_of_list{ 0 };
	double average_of_list{ 0 };

	vector<double> number_list;
}

//	Loop to get the numbers - put them in a vector
//  minimal error handling - check for error on reading input if fail check to see if exit code

//	Do the calculations using a set of functions all which take a reference to number_list

//	Output the list tab separated ten values per row

//	Ask if wants to enter another list

double get_max(vector<double>& l)
{
	int temp{ 0 };
	for (int i = 0; i < l.size(); ++i) {
		if(temp < l[i]) temp = l[i];
		else continue;
	}
	return temp;
}

double get_min(vector<double>& l)
{
	int temp{ 0 };
	for (int i = 0; i < l.size(); ++i) {
		if (temp > l[i]) temp = l[i];
		else continue;
	}
	return temp;
}

double get_mode(vector<double>& l)
{
	int count{ 0 };
	int uber_count{ 0 };
	int temp_mode_index{ 0 };
	for (int i = 0; i < l.size(); ++i) {
		temp_mode_index = i;
		for (int j = temp_mode_index + 1;j < l.size();++j) {
			if (l[i] == l[j]) {
				count += 1;
			}
			else continue;
		}
		if (count > uber_count) {
			uber_count = count;
			temp_mode_index = i;
		}
		else continue;
	}
	return l[temp_mode_index];
}
