/*** ASSUMPTIONS ***

	1. 50%-50% chance of either HAM or SPAM
	2. All and only emails to test are in the specified directory
	3. All emails' real classification are known beforehand and specified

*** /ASSUMPTIONS ***/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class files
{
	public:
		string filename;
		float ham_probability;
		float spam_probability;
		bool ham;
		files(string s){
		filename = s;
		ham_probability = 0;
		spam_probability = 0;
		ham = 0;
		}
};

class tuples
{
	public:
		string word;
		float ham_prob;
		float spam_prob;
		tuples(string s, float f1, float f2)
		{
			word = s;
			ham_prob = f1;
			spam_prob = f2;
		}
};

bool good(string fword)
{
	bool isagoodword = true;
	int len = fword.length();    
	if(len < 4 || 20 < len) isagoodword = false;

	size_t found;
	found = fword.find("@");
	if (found != string::npos) isagoodword = false;

	found = fword.find("$");
	if (found != string::npos) isagoodword = false;

	found = fword.find("[");
	if (found != string::npos) isagoodword = false;

	found = fword.find("]");
	if (found != string::npos) isagoodword = false;

	found = fword.find("{");
	if (found != string::npos) isagoodword = false;

	found = fword.find("}");
	if (found != string::npos) isagoodword = false;

	found = fword.find(";");
	if (found != string::npos) isagoodword = false;

	found = fword.find(":");
	if (found != string::npos) isagoodword = false;

	found = fword.find("(");
	if (found != string::npos) isagoodword = false;

	found = fword.find(")");
	if (found != string::npos) isagoodword = false;

	found = fword.find(".");
	if (found != string::npos) isagoodword = false;

	found = fword.find(",");
	if (found != string::npos) isagoodword = false;

	found = fword.find("=");
	if (found != string::npos) isagoodword = false;

	found = fword.find("+");
	if (found != string::npos) isagoodword = false;

	found = fword.find("\"");
	if (found != string::npos) isagoodword = false;

	found = fword.find("\'");
	if (found != string::npos) isagoodword = false;

	found = fword.find("!");
	if (found != string::npos) isagoodword = false;

	found = fword.find("?");
	if (found != string::npos) isagoodword = false;

	found = fword.find("*");
	if (found != string::npos) isagoodword = false;

	found = fword.find("1");
	if (found != string::npos) isagoodword = false;

	found = fword.find("2");
	if (found != string::npos) isagoodword = false;

	found = fword.find("3");
	if (found != string::npos) isagoodword = false;

	found = fword.find("4");
	if (found != string::npos) isagoodword = false;

	found = fword.find("5");
	if (found != string::npos) isagoodword = false;

	found = fword.find("6");
	if (found != string::npos) isagoodword = false;

	found = fword.find("7");
	if (found != string::npos) isagoodword = false;

	found = fword.find("8");
	if (found != string::npos) isagoodword = false;

	found = fword.find("9");
	if (found != string::npos) isagoodword = false;

	found = fword.find("0");
	if (found != string::npos) isagoodword = false;

	found = fword.find("--");
	if (found != string::npos) isagoodword = false;

	found = fword.find("localhost");
	if (found != string::npos) isagoodword = false;

	found = fword.find("<");
	if (found != string::npos) isagoodword = false;

	found = fword.find(">");
	if (found != string::npos) isagoodword = false;

	found = fword.find("/");
	if (found != string::npos) isagoodword = false;

	found = fword.find("\\");
	if (found != string::npos) isagoodword = false;

	found = fword.find("__");
	if (found != string::npos) isagoodword = false;

	found = fword.find("#");
	if (found != string::npos) isagoodword = false;

	found = fword.find("-_");
	if (found != string::npos) isagoodword = false;

	found = fword.find("^");
	if (found != string::npos) isagoodword = false;

	return isagoodword;

};

int main(int argc, char *argv[]){

	// Checking for the right arguments
	if (argc != 3)
	{
		cout << "Usage is: ./result [file_name] [ham|spam]" << endl;
		return 1;
	}

	string real = argv[2];
	transform(real.begin(),real.end(),real.begin(), ::tolower);

	if (real != "ham" && real != "spam")
	{
		cout << "Usage is: ./result [file_name] [ham|spam]" << endl;
		return 2;
	}

	// Creating filename.txt
	string command ="ls ";
	string argument = argv[1];
	command = command.append(argument).append(" > filename.txt");
	system(command.c_str());

	// Store all files in filenames.txt in a vector
	ifstream infile;
	vector<files> filenames;
	string word;

	infile.open("filename.txt");
	while (!infile.eof()) 
	{
		infile >> word;
		files *obj = new files(word);
		filenames.push_back(*obj);
	}
	filenames.pop_back();
	infile.close();

	/* DEBUGGING *
	for(vector<files>::iterator it=filenames.begin();it!=filenames.end();++it)
	{
		cout << it->filename << endl;
	}
	/* END DEBUGGING */

	// Reading model.txt into a vector
	vector<tuples> model;

	infile.open("model.txt");
	string s;
	float f1;
	float f2;

	while (!infile.eof()) 
	{
		infile >> f1;
		infile >> s;
		infile >> f1;
		infile >> f1;
		infile >> f2;
		infile >> f2;
		tuples *tuple = new tuples(s,f1,f2);
		model.push_back(*tuple);
	}
	model.pop_back();
	infile.close();

	/* DEBUGGING *
	for(vector<tuples>::iterator it=model.begin();it!=model.end();++it)
	{
		cout << it->word << endl;
	}
	/* END DEBUGGING */

	bool inModel = false;

	// Iterate through all files in filename.txt
	for(vector<files>::iterator it=filenames.begin();it!=filenames.end();++it)
	{
		// For each file,
		string place_holder = it->filename;
		argument = argv[1];
		argument.append(place_holder);
		infile.open(argument.c_str());
		while (!infile.eof())
		{
			// For each word
			infile >> s;
			if (good(s))
			{
				// Calculate probability of HAM
				for(vector<tuples>::iterator word_it=model.begin();word_it!=model.end();++word_it)
				{
					if (word_it->word == s)
					{
						inModel = true;
						it->ham_probability += log10(word_it->ham_prob);
						it->spam_probability += log10(word_it->spam_prob);
					}
				}

				// Find P(word|HAM)
				// Find Log(base 10) of the probability
				// Add them all up
				// Find 10^(log_sum) to revert back to probability

				// Calculate probability of SPAM
				// Find P(word|SPAM)
				// Find Log(base 10) of the probability
				// Add them all up
				// Find 10^(log_sum) to revert back to probability
			}
		}

		// Decide whether it's HAM or SPAM
		// If ham_probability > spam probability, it's probably HAM
		// If ham_probability < spam probability, it's probably SPAM
		
		/* DEBUGGING *
		cout << it->ham_probability << endl;
		/* END DEBUGGING */

		if (it->ham_probability > it->spam_probability)
		{
			it->ham = true;
		}
		else
		{
			it->ham = false;
		}
		infile.close();
	}

	// Print result
	int i = 0;
	ofstream outFile ("result.txt",ofstream::out);
	for(vector<files>::iterator it=filenames.begin();it!=filenames.end();++it)
	{
		outFile << ++i << "   ";
		outFile << it->filename << "   ";
		if (it->ham)
		{
			outFile << "ham   ";
		}
		else
		{
			outFile << "spam   ";
		}
		outFile << it->ham_probability << "   ";
		outFile << it->spam_probability << endl;
	}
	outFile.close();

	// Print analysis
	i = 0;
	int correct_count = 0;
	int incorrect_count = 0;
	outFile.open("analysis.txt",ofstream::out);
	for(vector<files>::iterator it=filenames.begin();it!=filenames.end();++it)
	{
		outFile << ++i << "   ";
		outFile << it->filename << "   ";
		if (it->ham)
		{
			outFile << "ham   ";
		}
		else
		{
			outFile << "spam   ";
		}
		outFile << real << "  ";
		if ((it->ham && real =="ham")||(!it->ham && real == "spam"))
		{
			outFile << "correct" << endl;
			++correct_count;
		}
		else
		{
			outFile << "incorrect" << endl;
			++incorrect_count;
		}
	}
	outFile << "***************" << endl;
	outFile << "Number of correct classifications made my classifier: " << correct_count << endl;
	outFile << "Classifier accuracy: " << fixed << setprecision(2) << (float)correct_count/(float)(correct_count + incorrect_count)*100 << "%" << endl;
	outFile << "Confusion matrix:" << endl;
	// INSERT CONFUSION MATRIX HERE
	outFile.close();
	
	return 0;
}
