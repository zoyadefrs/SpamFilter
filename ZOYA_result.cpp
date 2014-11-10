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

class tuples
{
public:
    string t_word;
    float t_ham_freq;
    float t_ham_probability;
    float t_spam_freq;
    float t_spam_probability;
};


class files
{
	public:
		string filename;
        string file_word;
		float ham_probability;
		float spam_probability;
        double add_score = log10(0.5);
        float ham_score = add_score ;
        float spam_score = add_score ;
        bool ham;
		files(string s){
		filename = s;
		ham_probability = 0;
		spam_probability = 0;
		ham = false;
		}
};

int main(int argc, char *argv[]){
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
    vector<tuples> word_model;
    string fword;
	string word;
    int freqham;
    float probham;
    int freqspam;
    float probspam;

	infile.open("filename.txt");
	while (!infile.eof()) {
		infile >> word;
		files *obj = new files(word);
		filenames.push_back(*obj);
	}
	infile.close();

	/* DEBUGGING *
	for(vector<files>::iterator it=filenames.begin();it!=filenames.end();++it)
	{
		cout << it->filename << endl;
	}
	/* END DEBUGGING */

    // Open model.txt and store all the words and their associated frequencies and probabilities in a vector called word_model
    infile.open("model.txt");
    while (!infile.eof())
    {
        infile >> word;
        infile >> freqham;
        infile >> probham;
        infile >> freqspam;
        infile >> probspam;
        tuples *obj = new tuples;
        obj->t_word = word;
        obj->t_ham_freq = freqham;
        obj->t_ham_probability = probham;
        obj->t_spam_freq = freqspam;
        obj->t_spam_probability = probspam;
        word_model.push_back(*obj);
        
    }
    infile.close();
    
	// Iterate through all files in filename.txt
	for(vector<files>::iterator file_it=filenames.begin();file_it!=filenames.end();++file_it)
	{
            // For each file
            // Open the file
        string place_holder = file_it->filename;
        infile.open(place_holder.c_str());
        
            //Use assumption made on words for comparison
        while(infile >> fword )
        {
            
            bool isagoodword = true;
            int len = fword.length();
            
                if(len < 4 || 20 < len){
                    isagoodword = false;
                }
                
                if(isagoodword && len < 20){
                    for(string::iterator char_it = fword.begin(); char_it != fword.end(); ++char_it) {
                        char c = *char_it;
                    if(!(isalpha(c))){isagoodword = false;}
                    }}
            
            if(isagoodword)
                {
        
                    // For each word
                    // Find P(word|HAM) and P(word|SPAM) -- if the word exists in word_model
            
            for (vector<tuples>::iterator word_it = word_model.begin() ; word_it != word_model.end(); ++word_it)
            {
                
                 if(word_it->t_word == fword)
                {
                    file_it->file_word= word_it->t_word;
                    
                        //Start adding the probabilities of each word into ham_/spam_ score (in log base10)
                    double temp_prob = word_it->t_ham_probability;
                    double ham_res= log10(temp_prob);
                    file_it->ham_probability = ham_res;
                    file_it->ham_score += ham_res;
                    
                    temp_prob = word_it-> t_spam_probability;
                    double spam_res = log10(temp_prob);
                    file_it->spam_probability = spam_res;
                    file_it->spam_score +=spam_res;
                }
            }}
            
            
        
            //Decide whether it is likely to be a ham or spam based on score
        if(file_it->ham_score > file_it->spam_score)
        {
            file_it->ham = true;
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
		outFile << it->ham_score << "   ";
		outFile << it->spam_score << endl;
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
    }}
