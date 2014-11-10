#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class tuples
{
	public:
		string word;
		float ham_count;
		float ham_probability;
		float spam_count;
		float spam_probability;
		static bool compare(tuples a, tuples b) {
		return (a.word < b.word);}
};

int main()
{
	ifstream file;
	vector<tuples> words;
	vector<tuples> spam_words;
	string word;
	float count;
	float word_count =0;
	float smooth=0.5;

	// Add all words from HAM to words
	file.open("HAM.txt");
	while (!file.eof())
	{
		file >> word;
		file >> count;
		tuples *obj = new tuples;
		obj->word = word;
		obj->ham_count = count;
		words.push_back(*obj);
		word_count += count;
	}
	file.close();
	words.pop_back();
	word_count-=count;
	/* DEBUGGING *

	for (vector<tuples>::iterator it = words.begin();it !=words.end();++it)
	{
		cout << it->word << " " << it->ham_count << " " << endl;
	} 
	/* END DEBUGGING */

	file.open("SPAM.txt");
	while (!file.eof())
	{
		file >> word;
		file >> count;
		tuples *obj = new tuples;
		obj->word = word;
		obj->spam_count = count;
		spam_words.push_back(*obj);
	}
	file.close();
	spam_words.pop_back();
	
	/* DEBUGGING *
	cout << word_count << endl;
	/* END DEBUGGING */

	// This is where the actual merging happens
	bool exist = false;
	
	for(vector<tuples>::iterator spam_it = spam_words.begin();spam_it!=spam_words.end();++spam_it)
	{
		for(vector<tuples>::iterator ham_it=words.begin();ham_it!=words.end();++ham_it)
		{
			if (spam_it->word == ham_it->word)
			{
				//cout << "FOUND ONE!" << endl;
				exist = true;
				ham_it->spam_count = spam_it->spam_count;
				word_count += spam_it->spam_count;
			}
		}
		if (!exist)
		{
			tuples *obj = new tuples;
			obj->word = spam_it->word;
			obj->spam_count = spam_it->spam_count;
			word_count += spam_it->spam_count;
			words.push_back(*obj);
		}
		// resetting exist
		exist = false;
	}

	// Smoothing for probabilities
	for(vector<tuples>::iterator it=words.begin();it!=words.end();++it)
	{
		it->ham_count+=smooth;
		it->spam_count+=smooth;
		word_count+=2*smooth;
	}

	// Calculating probabilities
	for(vector<tuples>::iterator it=words.begin();it!=words.end();++it)
	{
		it->ham_probability=it->ham_count/word_count;
		it->spam_probability=it->spam_count/word_count;
	}

	// Remove Smoothing
	for(vector<tuples>::iterator it=words.begin();it!=words.end();++it)
	{
		it->ham_count-=smooth;
		it->spam_count-=smooth;
		word_count-=2*smooth;
	}

	/* DEBUGGING *
	for(vector<tuples>::iterator it=words.begin();it!=words.end();++it)
	{
		cout << it->word << endl;
	}
	cout << word_count << endl;
	/* END DEBUGGING */

	// Sorting
	sort(words.begin(),words.end(),tuples::compare);

	// Write to model.txt
	ofstream ofs ("model.txt",ofstream::out);
	float test=0;
	int i = 0;
	for(vector<tuples>::iterator it=words.begin();it!=words.end();++it)
	{
		ofs << ++i << "   ";
		ofs << it->word << "   ";
		ofs << it->ham_count << "   " << it->ham_probability << "   ";
		ofs << it->spam_count << "   " << it->spam_probability << endl;
		test += it->ham_probability + it->spam_probability;
	}
	ofs.close();
	
	/* DEBUGGING */
	cout << test << endl;
	/* END DEBUGGING */
	return 0;
}
