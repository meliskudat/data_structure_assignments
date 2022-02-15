#include <iostream>
#include <fstream>
#include "Hashtable.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;


int main()
{
	string filename_toread = "compout.txt"; // the compressed numbers are in there
    string filename_towrite = "decompout.txt"; // the output will be shown in here
	ifstream input;
	ofstream out;
	input.open(filename_toread.c_str());
	out.open(filename_towrite.c_str());
	if (input.is_open())
	{
		Part Holder;
		HashTable<Part> hash_table(Holder, 4096);

		for (int valueofascii = 0; valueofascii < 256; valueofascii++) // to insert 0-256 to hash_table
		{
			string string_equivalent_of_ascii = string(1, char(valueofascii)); // take the string equivalent of the ascii number between 1-256
			Part to_be_inserted_until_(string_equivalent_of_ascii, valueofascii); // a part object to be inserted to hash table
			hash_table.insert(to_be_inserted_until_); // inserting that "part" object to hash table
		}



		vector <int> Numbers_in_File; // creating a vector with the numbers inside "compout.txt"
		int index = 256; 
		int number;
		while (input >> number) {
			if (number > 4096)//the codes cannot be greater than 4096
				return 0;
			Numbers_in_File.push_back(number);
		}

		int size = Numbers_in_File.size();
		
		int count = 1;

		Part empty; // to create an empty part object

		int first_of_vector = Numbers_in_File[0];
		string string_equivalent_of_firstvector = string(1, char(first_of_vector));
		//string first_to_insert = string_equivalent_of_firstvector + string_equivalent_of_firstvector;
		int currentindex = 256;
		out << string_equivalent_of_firstvector;
		//hash_table.insert(Part(first_to_insert, currentindex));

		while (count < size)
		{
			if (hash_table.findByCode(Numbers_in_File[count]) == empty) // not in the hash table
			{
				string previous_one = hash_table.findByCode(Numbers_in_File[count - 1]).key_value;
				char first_index_of_current_one = previous_one[0];
				string firstchar(1, first_index_of_current_one);
				string insertion = previous_one + firstchar;
				hash_table.insert(Part(insertion, currentindex));
				out << hash_table.find(Part(insertion, currentindex)).key_value;
		
				

			}
			else // in the hash table
			{
				out << hash_table.findByCode(Numbers_in_File[count]).key_value;
				string previous_one = hash_table.findByCode(Numbers_in_File[count - 1]).key_value;
				string current_one = hash_table.findByCode(Numbers_in_File[count]).key_value;
				char first_index_of_current_one = current_one[0];
				string firstchar(1, first_index_of_current_one);
				string insertion = previous_one + firstchar;
				hash_table.insert(Part(insertion, currentindex));
				
			}
			currentindex += 1;
			count += 1;

		}




	}
	input.close();
	out.close();

	return 0;




}

