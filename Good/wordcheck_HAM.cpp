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
		int count;
	
};

int main()
{
	// Open file_names.txt
	// Because file_names.txt contain the list of all file names in HAM
	// for now
	ifstream file; //pour output -- ofstream
    string fname;
    string fword;
	file.open("file_names.txt");
	// Store every entry in a vector
    vector<string> file_names;
	vector<tuples> word_vector;
    
    while (!file.eof()){
        file >> fname;
        file_names.push_back(fname);
        //cout << fname << endl;
    }
    file_names.pop_back();
    file.close();

    

    for (vector<string>::iterator file_it = file_names.begin() ; file_it != file_names.end(); ++file_it)
    {
        
        string place_holder = *file_it;
        file.open(place_holder.c_str());

// Open each single file in vector
 while(file >> fword)
{
    bool isagoodword = true;
    int len = fword.length();
    //cout << "This is the the word : " << fword << " This is the length: " << len << endl;
    
    
      {
          if(len < 4 || 20 < len){
              isagoodword = false;
          }
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
		
          
        if(isagoodword){
            // Check if word is good
            // Assumptions goes here
            
		transform(fword.begin(),fword.end(),fword.begin(), ::tolower);

            bool isnew = true;
            for (vector<tuples>::iterator word_it = word_vector.begin() ; word_it != word_vector.end(); ++word_it) {    // Check if word is in word_vector
               
               
                if(word_it->word == fword){// If word is in word_vector
                    word_it-> count++;
                    //cout << "This is the word that has been found: " << fword << endl;
                    //cout << "Word count of the word that appears more than once: " << endl;
                    //cout << word_it->count << endl;// Increment its count
                    isnew =  false;
                                       }
                
                    
            }
            if(isnew){
                    tuples *obj = new tuples;// else word is not in word_vector
                    obj->word = fword;
                    obj-> count =1;
                    word_vector.push_back(*obj);
            }
            
            
        }}}
    
                    
                    file.close();// close file, proceed to next file}
    }
    

    {
        ofstream outputfile;
        outputfile.open("HAM.txt");
        for (vector<tuples>::iterator word_it = word_vector.begin() ; word_it != word_vector.end(); ++word_it){
       
        outputfile << word_it->word << " ";
        outputfile << word_it->count << endl;
        }
    return 0;
}

//output statistics to the file.

}
