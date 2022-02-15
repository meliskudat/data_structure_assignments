
#include <string>
#include "Hashtable.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()

{
	string file_input = "compin.txt";
	string file_out = "compout.txt";
	ifstream input;
	ofstream out;
	out.open(file_out.c_str());

	input.open(file_input.c_str());
	if (input.is_open()) // if we can open file
	{
		char character;
		Part Holder;
		string stringversion = ""; // creating an empty string to be filled with the char in file
		HashTable<Part> hash_table(Holder, 4096); // sending an empty Dictionary 
		while (!input.eof()) //
		{
			input.get(character); // we are having all char in the file until end of the file
			stringversion += character; 
		}
		stringversion = stringversion.substr(0, stringversion.length() - 1);

		for (int valueofascii = 0; valueofascii < 256 ; valueofascii++) 
		{
			string string_equivalent_of_ascii = string(1, char(valueofascii)); // take the string equivalent of the ascii number between 1-256
			Part to_be_inserted_until_(string_equivalent_of_ascii, valueofascii); // a part object to be inserted to hash table
			hash_table.insert(to_be_inserted_until_); // inserting that "part" object to hash table
		}

		int count = 0;
		string p = stringversion.substr(0,1); // the first char of the string
		char c;
		int i = 1;
		int current_index = 256; // since we will start inserting in index 256
		Part tocheckifnotfound ;
		while (count < stringversion.length())
		{
			c = stringversion[i];
			string x(1, c);
			string p_plus_c = p + x;
			if (tocheckifnotfound == hash_table.find(Part(p_plus_c, current_index)))
			{
				out << hash_table.find(Part(p, current_index)).code << " "; // tries find the code of p in the table
				hash_table.insert(Part(p_plus_c, current_index));
				p = c;
				current_index += 1;
			}
			else
			{
				p = p_plus_c;
			}
			
			i++;
			count += 1;
		}
		//out << hash_table.find(Part(p, current_index)).code << "";
		input.close();//close the file
		out.close();//close the file

	}
	return 0;




}
