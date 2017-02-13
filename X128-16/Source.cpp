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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
struct mode_tracker {
	double the_number{ 0 };
	int repeat_count{ 1 };
};

double get_max(vector<double>& l);
double get_min(vector<double>& l);
double get_mean(vector<double>& l);
double get_median(vector<double>& l);
void print_list(vector<double>& l);

bool get_mode(vector<double>& l, vector<mode_tracker>& mt);
bool is_single_mode(vector<mode_tracker> & mt);
bool is_uniform_distribution(vector<mode_tracker> & mt);
int get_the_modes(vector<mode_tracker> & mt, vector<double>& lom);

bool UDGreater(mode_tracker elem1, mode_tracker elem2) {
	return elem1.repeat_count > elem2.repeat_count;
};

//  Start the main loop - continue until user says quit

int main() {
	double user_input_number{ 0.0 };
	char user_input_char{ 'A' };
	bool multi_modal{ false };
	bool uniform_distribution{ true };
	int temp_mode_index{ 0 };
	int number_of_modes{ 0 };

	vector<double> number_list;				// original number list
	vector<double> sorted_number_list;		// copied to here and then sorted
	vector<int> mode_indexes;				// to be used to keep track of 
	vector<mode_tracker> the_modes;
	vector<double> list_of_modes;


	//	Loop to get the numbers - put them in a vector
	//  minimal error handling - check for error on reading input if fail check to see if exit code
	//	Do the calculations using a set of functions all which take a reference to number_list
	//	Output the list tab separated ten values per row
	//	Ask if wants to enter another list

	do
	{
		if (number_list.size() != 0) number_list.clear();      // clear vectors if they are not empty
		if (sorted_number_list.size() != 0) sorted_number_list.clear();
		if (mode_indexes.size() != 0) mode_indexes.clear();
		if (the_modes.size() != 0) the_modes.clear();
		if (list_of_modes.size() != 0) list_of_modes.clear();

		cout << "Enter the list of values [any char to terminate data entry]: ";
		do  {
			cin >> user_input_number;
			number_list.push_back(user_input_number);
			cout << "number is " << user_input_number << "\tbadbit is " << cin.fail() << "\n";
		} while (cin.fail() == false);		

		number_list.pop_back();  //burn the last number entered as it gets added to the list twice
		cin.clear();

		print_list(number_list);

		// copy number_list to sorted_number_list
		for (int i = 0; i < number_list.size(); ++i) {
			sorted_number_list.push_back(number_list[i]);
		}
		cout << "copy of list: \n";
		print_list(sorted_number_list);

		//sort the copied list
		sort(sorted_number_list.begin(), sorted_number_list.end());

		cout << "sorted copy of list:\n";
		print_list(sorted_number_list);

		cout << "Max\tMin\tMean\tMedian\n";
		cout << get_max(number_list) << "\t";
		cout << get_min(number_list) << "\t";
		cout << get_mean(number_list) << "\t";
		cout << get_median(sorted_number_list) << "\t";
		cout << "\n";

		//  mode has to be handled differently since the list may have more than one mode or it may have no modes

		get_mode(sorted_number_list, the_modes);

		if (is_uniform_distribution(the_modes)) {
			cout << "Sequence is a uniform distribution. \n";
			continue;
		}
		
		if (is_single_mode(the_modes)) {
			cout << "Sequence is mono-modal.  Mode is " << the_modes[0].the_number << "\n";
			continue;
		}

		cout << "Sequence is multi-modal, modes are: \n";
		number_of_modes = get_the_modes(the_modes, list_of_modes);
		for (int i = 0; i < number_of_modes; ++i) {
			cout << "\n Mode: " << list_of_modes[i];
		}

	keep_window_open();

	} while (yes_no("\nDo you want to do another? "));
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

bool get_mode(vector<double>& l, vector<mode_tracker>& mt)  // return true if multi-modal, false if single mode
{
	int count{ 1 };
	int uber_count{ 0 };
	int temp_mode_index{ 0 };

	int m_count{ 0 };
	int m_max_count{ 0 };
	int m_count_index{ 0 };

	mode_tracker temp_mt;

	// loop goes through list and checks each number for the number of times it is repeated (count)
	// starts at 1 - so actually counts the number of times a number is repeated in the list

	for (int i = 0; i < l.size(); ++i) {
		temp_mt.the_number = l[i];
		if (i < l.size() - 1 && l[i] == l[i + 1]) temp_mt.repeat_count += 1;
		else {
			mt.push_back(temp_mt);
			temp_mt.repeat_count = 1;
		}
	}

	cout << "unsorted mode tracker: \n";
	for (int k = 0; k < mt.size(); ++k) {
		cout << "Number is \t" << mt[k].the_number << "Repeat count\t" << mt[k].repeat_count << "\n";
	}
	sort(mt.begin(), mt.end(), UDGreater);

	cout << "unsorted mode tracker: \n";
	for (int k = 0; k < mt.size(); ++k) {
		cout << "Number is \t" << mt[k].the_number << "Repeat count\t" << mt[k].repeat_count << "\n";
	}
	
	if (m_count == 1) return false;
	else return true;
}

double get_mean(vector<double>& l)
{
	double sum{ 0 };
	for (int i = 0; i < l.size();++i) {
		sum += l[i];
	}
	return sum/l.size();
}

double get_median(vector<double>& l)
{
	double mid_point_index{ 0 };
	mid_point_index = (l.size() / 2.0) - 1;
//	cout << "midpoint index = " << mid_point_index << "\ttrunc = " << trunc(mid_point_index) << "\n";
	if (mid_point_index == trunc(mid_point_index)) return (l[mid_point_index] + l[mid_point_index + 1]) / 2;
	else return l[mid_point_index + 1];
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
bool is_single_mode(vector<mode_tracker> & mt) {
	// assumes vector of mdes has been sorted in decending order by number of repeats so will be single mode
	// the repeat count of the second element does not eaqual the repeat count of the first.

	if (mt[0].repeat_count != mt[1].repeat_count) return true;
	else return false;
}
bool is_uniform_distribution(vector<mode_tracker> & mt) {
	// assumes vector of mdes has been sorted in decending order by number of repeats so will be uniform if 
	// the repeat count of all elements are the same
	int tester{ 0 };
	tester = mt[0].repeat_count;
	for (int i = 0; i < mt.size() - 1;++i) {
		if (tester == mt[i].repeat_count) continue;
		else return false;
	}
	return true;
}
int get_the_modes(vector<mode_tracker> & mt, vector<double>& lom) {
	int previous_value{ 0 };
	int count_of_modes{ 1 };
	previous_value = mt[0].repeat_count;
	lom.push_back(mt[0].the_number);
	for (int i = 1; i < mt.size(); ++i) {
		if (previous_value == mt[i].repeat_count) {
			lom.push_back(mt[i].the_number);
			count_of_modes += 1;
			continue;
		}
		else return(count_of_modes);
	}
	return(count_of_modes);
}