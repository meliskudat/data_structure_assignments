
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;



bool CheckIfEdge(string first_word, string second_word)
{


	if (first_word.length() == second_word.length()) // meaning two words have same length
	{
		int count = 0;
		for (int i = 0; i < first_word.length(); i++)
		{
			if (first_word[i] == second_word[i])
				count += 1;
		}
		int first_word_length = first_word.length();
		if (count == first_word_length - 1)
		{
			return true;
		}
		return false;

	}

	else if ((first_word.length() - second_word.length()) == 1) // first word is longer
	{
		string x = "";
		if (first_word.find(second_word) != string::npos)
			return true;

		for (int i = 0; i < first_word.length(); i++)
		{
			if (second_word[i] == first_word[i])
			{

			}
			else
			{
				x = first_word.substr(0, i) + first_word.substr(i + 1);
				break;
			}

		}
		if (x == second_word)
			return true;

		return false;
	}
	else if ((second_word.length() - first_word.length()) == 1) // second word is longer
	{
		string x = "";
		if (second_word.find(first_word) != string::npos)
			return true;
		for (int i = 0; i < first_word.length(); i++)
		{
			if (second_word[i] == first_word[i])
			{

			}
			else
			{
				x = second_word.substr(0, i) + second_word.substr(i + 1);
				break;
			}

		}
		if (x == first_word)
			return true;

	}
	return false;



}


unordered_map<string, string> findPath(const unordered_map<string, vector<string>>& graph, const string& first, const string& second)
{
	unordered_map<string, string> previousWord;
	queue<string> q;

	q.push(first);

	while (!q.empty())
	{
		string current = q.front();
		q.pop();
		auto itr = graph.find(current);

		const vector<string>& adj = itr->second;
		for (int i = 0; i < adj.size(); i++) {
			string str = adj[i];
			if (previousWord[str] == "")
			{
				previousWord[str] = current;
				q.push(str);
			}
		}
	}

	previousWord[first] = "";

	return previousWord;
}


void Difference(string first, string second)
{
	if (second.length() > first.length()) // means insertion
	{
		if (second.find(first) != string::npos) // insertion is either from the beginning or to the end
		{
			if (second[0] == first[0]) // inserted to the end
				cout << second << "	(insert " << second[second.length() - 1] << " after position " << first.length() << ")" << endl;
			else // inserted to the beginning
				cout << second << "	(insert " << second[0] << " after position 0)" << endl;
		}
		else // insertion is in the middle 
		{
			int index = 0;
			while (index < first.length())
			{
				if (first[index] == second[index])
				{
				}
				else
					break;
				index += 1;
			}
			cout << second << "	(insert " << second[index] << " after position " << index << ")" << endl;
		}

	}

	else if (first.length() > second.length()) // means deletion
	{
		if (first.find(second) != string::npos) // deletion is at the beginning or the end
		{
			if (first[0] == second[0]) // deletion is at the end
				cout << second << "	(delete " << first[first.length() - 1] << " at position " << first.length() << ")" << endl;
			else  // deletion is at the beginning
				cout << second << "	(delete " << first[0] << " at position 0)" << endl;
		}
		else // if deletion is in the middle
		{
			int index = 0;
			while (index < second.length())
			{
				if (first[index] == second[index])
				{
				}
				else
					break;
				index += 1;
			}
			cout << second << "	(delete " << first[index] << " at position " << index + 1 << ")" << endl;


		}
	}
	else if (first.length() == second.length()) // means change
	{
		int i;
		for (i = 0; i < first.size(); i++)
		{
			if (first[i] != second[i])
				break;
		}
		cout << second << "	(change " << first[i] << " at position " << i + 1 << " to " << second[i] << ")" << endl;
	}


}



void ShortestPath(const unordered_map<string, vector<string>>& graph, const string& first, const string& second)
{
	unordered_map<string, string > temp = findPath(graph, first, second);
	vector<string> result;
	auto& prev = const_cast<unordered_map<string, string> &>(temp);

	for (string current = second; current != ""; current = prev[current])
		result.push_back(current);

	reverse(begin(result), end(result));

	if (result.size() > 1)
	{
		cout << result[0] << endl;
		for (int i = 0; i < result.size() - 1; i++)
		{
			Difference(result[i], result[i + 1]);
		}
	}

	else
		cout << "No possible way from " << first << " to " << second << endl;



}






int main()
{


	unordered_map<string, vector<string> > graph;
	string filename = "words.txt";
	ifstream input(filename);
	string line;
	vector<string> words_list;
	while (getline(input, line))
	{
		graph[line];
		words_list.push_back(line);
	}





	for (int i = 0; i < words_list.size(); i++)
	{
		for (int j = 0; j < words_list.size(); j++)
		{
			if (words_list[i] != words_list[j])
			{
				if (CheckIfEdge(words_list[i], words_list[j]) == true)
				{
					graph[words_list[i]].push_back(words_list[j]);
				}
			}
		}
	}

	string first_word, second_word;
	cout << "Please enter the words: ";
	cin >> first_word >> second_word;
	while (first_word[0] != '*')
	{
		int check = 0;
		for (int k = 0; k < words_list.size(); k++)
		{
			if (words_list.at(k) == first_word || words_list.at(k) == second_word)
				check += 1;
		}
		if (check != 2)
		{
			cout << "One/Both of the words cannot be found in the list." << endl;
			cout << endl;
		}
		else {
			ShortestPath(graph, first_word, second_word);
			cout << endl;
		}
		cout << "Please enter the words: ";
		cin >> first_word >> second_word;
	}
	return 0;

}