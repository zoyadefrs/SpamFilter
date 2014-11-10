--------------------------------------------------------
-							-
-	   Steps to take to produce model.txt		-
-							-
--------------------------------------------------------

1. Create a file that contains the list of all file names in HAM or SPAM. Name this file "file_names.txt". (In UNIX, navigate to the HAM or SPAM directory and run bash command "ls > file_names.txt".
2. Compile “wordcheck_HAM.cpp" and run the executable in the easy_ham_2 directory, which contains files from 0 to 1000.
3. Compile “wordcheck_SPAM.cpp" and run the executable in the spam_2 directory, which contains files from 0 to 1000.
4. Move HAM.txt and SPAM.txt to a common directory.
5. Compile "merge.cpp" and run the executable in the same directory as HAM.txt and SPAM.txt. and produces the model.txt

--------------------------------------------------------
-							-
-	       Assumptions for model.txt		-
-							-
--------------------------------------------------------

[Assumptions have been updated from Deliverable 1]
 
1. We assumed that any words less than 4 characters is not relevant.
2. We assumed that any word beyond 19 characters is not relevant. 
3. We assumed that any word that contains character that is not part of the english alphabet is not relevant.
4. We assumed any word containing “localhost” is not relevant. 
5. We converted all the words to lowercase to compare them on the same level.
6. We assume a string and its substring are not the same word.

--------------------------------------------------------
-							-
- Steps to take to produce result.txt and analysis.txt	-
-							-
--------------------------------------------------------
1. We use model.txt that has been produced from above
2. Compile “result.cpp” 
3. Run the bash command ./result [path_to_file_name] [ham|spam] 

//[ham|spam] will be useful for the production of analysis.txt to know whether we made a correct classification or not
 
--------------------------------------------------------
-							-
-     Assumptions for result.txt and analysis.txt	-
-							-
--------------------------------------------------------

1. 50%-50% chance of either HAM or SPAM
2. All and only emails to test are in the specified directory
3. All emails' real classification are known beforehand and specified

--------------------------------------------------------
-							-
-     		     Confusion Matrix 			-
-							-
--------------------------------------------------------

The way our classifier has been designed did not allow use to produce the confusion matrix in the analysis.txt but below is the way it should have been produced :

      | Spam | Ham |
——————————————— 
Spam  |  
————————————-
Ham   |
