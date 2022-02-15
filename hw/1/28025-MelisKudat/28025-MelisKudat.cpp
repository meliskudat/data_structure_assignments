#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <vector>
#include <fstream>
using namespace std;



struct Process
{
	string process_name;
	vector <string> moves;
	int index = 0;
	int current_queue_number;
	int total_execution_number;
};

struct Queues
{
	int queue_number;
	queue <Process> A;

};


int main()
{
	int queue_number, S_value, process_number;
	string folder_, line1, line2, line3;
	cout << "Please enter the process folder name: ";
	cin >> folder_;
	cout << "When all processes are completed, you can find execution sequence in  " + folder_ + "/output.txt" << endl;
	cout << endl;
	cout << "Given Files for the Sample Run :" << endl;
	cout << folder_ + "/ configuration.txt:" << endl;


	ifstream file;
	file.open("./" + folder_ + "/configuration.txt");
	getline(file, line1);
	queue_number = stoi(line1);
	getline(file, line2);
	process_number = stoi(line2);
	getline(file, line3);
	S_value = stoi(line3);
	cout << queue_number << endl;
	cout << process_number << endl;
	cout << S_value << endl;

	vector<Process> process_folder; // to keep track of all processes 
	// the first one we push is the first process...

	for (int i = 1; i <= process_number; i++) // filling process's info with files given
	{
		Process processes;
		processes.process_name = "PC" + to_string(i);
		processes.current_queue_number = queue_number;
		ifstream for_process;
		for_process.open("./" + folder_ + "/p" + to_string(i) + ".txt");
		string lines;
		int x = 0;
		while (getline(for_process, lines))
		{
			processes.moves.push_back(lines);
			x += 1;
		}
		cout << folder_ + "/p" + to_string(i) + ".txt" << endl;
		x = x - 1;
		processes.total_execution_number = x;

		for (int i = 0; i < processes.moves.size(); i++)
		{
			string x = processes.moves[i];
			cout << x << endl;
		}
		processes.moves.pop_back();
		process_folder.push_back(processes);
		for_process.close();

	}

	vector < Queues> queues_folder;

	for (int a = 1; a <= queue_number; a++)
	{
		Queues q;
		q.queue_number = a;
		queues_folder.push_back(q);
	}


	for (int i = 1; i <= process_number; i++) // putting all processes to the top
	{
		int size = queues_folder.size();
		queues_folder[size - 1].A.push(process_folder[i - 1]);
	}

	int termination_count = 0;
	int s_count = 0;
	int a = queues_folder.size();
	ofstream out;
	out.open("./" + folder_ + "/output.txt");

	while (termination_count != process_number) 
	{
		if (s_count == S_value)
		{
			for (int i = a - 2; i >= 0; i--)
			{

				while (!(queues_folder[i].A.empty()))
				{
					Process process_ = queues_folder[i].A.front();
					process_.current_queue_number = queue_number;
					queues_folder[i].A.pop();
					int sizex = queues_folder.size();
					queues_folder[sizex - 1].A.push(process_);
					cout << "B, " << process_.process_name << ", Q" << queue_number << endl;
					out << "B, " << process_.process_name << ", Q" << queue_number << endl;
				}

			}
			s_count = 0;
		}


		for (int i = a - 1; i >= 0; i--)
		{
			if (!(queues_folder[i].A.empty())) // for upper queues , checking if they are empty or not, if empty we will go lower queues
			{
				Process process_compiling = queues_folder[i].A.front();
				if (process_compiling.index != (process_compiling.total_execution_number - 1)) // no termination will happen, we will check if it is 0 or 1
				{
					int index_a = process_compiling.index;
					if (process_compiling.moves[index_a] == "0")
					{

						process_compiling.index += 1;
						process_compiling.current_queue_number = process_compiling.current_queue_number;
						queues_folder[i].A.pop();
						queues_folder[i].A.push(process_compiling);

						cout << "0, " << process_compiling.process_name << ", Q" << process_compiling.current_queue_number << endl;
						out << "0, " << process_compiling.process_name << ", Q" << process_compiling.current_queue_number << endl;
						s_count += 1;
						break;
					}

					else if (process_compiling.moves[index_a] == "1")
					{
						if (i == 0)
						{
							process_compiling.index += 1;
							process_compiling.current_queue_number = process_compiling.current_queue_number;
							queues_folder[i].A.pop();
							queues_folder[i].A.push(process_compiling);

							cout << "1, " << process_compiling.process_name << ", Q" << process_compiling.current_queue_number << endl;
							out << "1, " << process_compiling.process_name << ", Q" << process_compiling.current_queue_number << endl;
							s_count += 1;
							break;

						}
						else {
							process_compiling.index += 1;
							process_compiling.current_queue_number = process_compiling.current_queue_number - 1;
							queues_folder[i].A.pop();
							queues_folder[i - 1].A.push(process_compiling);

							cout << "1, " << process_compiling.process_name << ", Q" << process_compiling.current_queue_number << endl;
							out << "1, " << process_compiling.process_name << ", Q" << process_compiling.current_queue_number << endl;
							s_count += 1;
							break;
						}
					}

				}
				else if (process_compiling.index == (process_compiling.total_execution_number - 1))
				{
					process_compiling.index += 1;
					queues_folder[i].A.pop();
					cout << "E, " << process_compiling.process_name << ", QX" << endl;
					out << "E, " << process_compiling.process_name << ", QX" << endl ;
					termination_count += 1;
					s_count += 1;
					break;

				}


			}
		}


	}
	out.close();
	return 0;


}