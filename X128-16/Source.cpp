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
bool get_mode(vector<double>& l, vector<int>& mi);
double get_mean(vector<double>& l);
double get_median(vector<double>& l);
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
	bool multi_modal{ false };
	int temp_mode_index{ 0 };

	vector<double> number_list;
	vector<int> mode_indexes;


	//	Loop to get the numbers - put them in a vector
	//  minimal error handling - check for error on reading input if fail check to see if exit code

	//	Do the calculations using a set of functions all which take a reference to number_list

	//	Output the list tab separated ten values per row

	//	Ask if wants to enter another list

	do
	{
		if (number_list.size() != 0) number_list.clear();      // clear vectors if they are not empty
		if (mode_indexes.size() != 0) mode_indexes.clear();

		cout << "Enter the list of values [any char to terminate data entry]: ";
		do  {
			cin >> user_input_number;
			number_list.push_back(user_input_number);
			cout << "number is " << user_input_number << "\tbadbit is " << cin.fail() << "\n";
		} while (cin.fail() == false);
		number_list.pop_back();  //burn the last nimber entered as it gets added to the list twice
		cin.clear();
		print_list(number_list);
		cout << "Max\tMin\tMean\tMedian\n";
		cout << get_max(number_list) << "\t";
		cout << get_min(number_list) << "\t";
		cout << get_mean(number_list) << "\t";
		cout << get_median(number_list) << "\t";
		cout << "\n";
		if (!get_mode(number_list, mode_indexes)) {
			for (int i = 0;i < mode_indexes.size() - 1;++i) {
				if (mode_indexes[i] > mode_indexes[i + 1]) {
					temp_mode_index = i;
				}
			}
			cout << "Sequence is mono-modal.  Mode is " << number_list[temp_mode_index] << "\n";
		}
		else {
			cout << "Sequence is multi-modal, modes are: \n";
			for (int i = 0;i < mode_indexes.size() - 1;++i) {
				if (mode_indexes[i] > mode_indexes[i + 1]) {
					temp_mode_index = i;
				}
			}
			for (int i = 0;i < mode_indexes.size();++i) {
				if (mode_indexes[i] == mode_indexes[temp_mode_index]) {
					cout << "\t Mode: " << number_list[i];
				}
			}
			cout << "\n";
		}
		keep_window_open();

	} while (yes_no("Do you want to do another? "));
}

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
	int temp = l[0];
	for (int i = 1; i < l.size(); ++i) {
		if (temp > l[i]) temp = l[i];
		else continue;
	}
	return temp;
}

bool get_mode(vector<double>& l, vector<int>& mi)
{
	int count{ 1 };
	int uber_count{ 0 };
	int temp_mode_index{ 0 };

	int m_count{ 0 };
	int m_max_count{ 0 };
	int m_count_index{ 0 };
	for (int i = 0; i < l.size(); ++i) {
		temp_mode_index = i;
		for (int j = temp_mode_index + 1;j < (l.size()-1);++j) {
			if (l[i] == l[j]) {
				count += 1;
			}
			else continue;
		}
		
		mi.push_back(count);						// record the count of repeats
		if (count > uber_count) {
			uber_count = count;
			count = 1;
			temp_mode_index = i;
		}
		else {
			count = 1;
			continue;
		}
	}
	// check to see if single mode
	for (int i = 0;i < mi.size() - 1;++i) {
		if (mi[i] > mi[i + 1]) {
			m_max_count = mi[i];
		}
	}
	for (int i = 0;i < mi.size() ;++i) {
		if (mi[i] == m_max_count) m_count += 1;
	}
	if (m_count == 1) return false;
	else return true;

	// otherwise we are bi- or multi-modal


	return l[temp_mode_index];
}

double get_mean(vector<double>& l)
{
	int sum{ 0 };
	for (int i = 0; i < l.size();++i) {
		sum += l[i];
	}
	return sum/l.size();
}

double get_median(vector<double>& l)
{
	double mid_point_index{ 0 };
	mid_point_index = l.size() / 2;
	if (mid_point_index == trunc(mid_point_index)) return l[mid_point_index];
	else return (l[mid_point_index] + l[mid_point_index + 1]) / 2;
}

void print_list(vector<double>& l)
{
	for (int i = 0; i < l.size();++i) {
		if (i % 10 == 0  && i != 0 ) cout << "\n";
		else cout << l[i] << "\t";
	}
	cout << "\n";
	return;
}
