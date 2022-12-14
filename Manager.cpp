#include "Manager.h"
#include <sstream>

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if (load) {
		delete graph;
	}
	fout.close();
}

void Manager::run(const char *command_txt)
{
	ifstream fin;
	fin.open(command_txt);

	if (!fin)
	{
		fout << "[ERROR] command file open error!" << endl;
		return;
	}

	string buf;

	while (!fin.eof())
	{
		getline(fin, buf);
		if (buf.find("LOAD") != string::npos)
		{
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf);
			if (buf.empty()) {
				printErrorCode(100);
				continue;
			}
			LOAD(buf);
		}
		else if (buf.find("PRINT") != string::npos)
		{
			PRINT();
		}
		else if (buf.find("BFS") != string::npos)
		{
			stringstream ss(buf);
			getline(ss, buf, ' ');
			if (buf.empty()) {
				printErrorCode(300);
				continue;
			}
			getline(ss, buf);
			if (buf.empty() || !(buf[0] <= '9' && buf[0] >= '0')) {
				printErrorCode(300);
				continue;
			}
			mBFS(stoi(buf));
		}
		else if (buf.find("DFS_R") != string::npos)
		{
			stringstream ss(buf);
			getline(ss, buf, ' ');
			if (buf.empty()) {
				printErrorCode(500);
				continue;
			}
			getline(ss, buf);
			if (buf.empty() || !(buf[0] <= '9' && buf[0] >= '0')) {
				printErrorCode(500);
				continue;
			}
			mDFS_R(stoi(buf));
		}
		else if (buf.find("DFS") != string::npos)
		{
			stringstream ss(buf);
			getline(ss, buf, ' ');
			if (buf.empty()) {
				printErrorCode(400);
				continue;
			}
			getline(ss, buf);
			if (buf.empty() || !(buf[0] <= '9' && buf[0] >= '0')) {
				printErrorCode(400);
				continue;
			}
			mDFS(stoi(buf));
		}
		else if (buf.find("KRUSKAL") != string::npos)
		{
			mKRUSKAL();
		}
		else if (buf.find("DIJKSTRA") != string::npos)
		{
			stringstream ss(buf);
			getline(ss, buf, ' ');
			if (buf.empty()) {
				printErrorCode(700);
				continue;
			}
			getline(ss, buf);
			if (buf.empty() || !(buf[0] <= '9' && buf[0] >= '0')) {
				printErrorCode(700);
				continue;
			}
			mDIJKSTRA(stoi(buf));
		}
		else if (buf.find("BELLMANFORD") != string::npos)
		{
			int opt1;
			stringstream ss(buf);
			getline(ss, buf, ' ');
			if (buf.empty()) {
				printErrorCode(800);
				continue;
			}
			getline(ss, buf, ' ');
			if (buf.empty() || !(buf[0] <= '9' && buf[0] >= '0')) {
				printErrorCode(800);
				continue;
			}
			opt1 = stoi(buf);
			getline(ss, buf);
			if (buf.empty() || !(buf[0] <= '9' && buf[0] >= '0')) {
				printErrorCode(800);
				continue;
			}
			mBELLMANFORD(opt1, stoi(buf));
		}
		else if (buf.find("FLOYD") != string::npos)
		{
			mFLOYD();
		}
		else if (buf.find("EXIT") != string::npos)
		{
			fin.close();
			return;
		}
	}
	fin.close();
}

bool Manager::LOAD(string filename)
{
	ifstream fgraph(filename);
	if (!fgraph.is_open())
	{
		printErrorCode(100);
		return false;
	}
	string buf;
	int type; // 0 == list, 1 == matrix
	int size;
	int from;
	int to;
	int weight;
	getline(fgraph, buf);
	if (load)
		delete graph;
	if (filename == "graph_L.txt" && buf == "L")
	{
		type = 0;
		getline(fgraph, buf);
		size = stoi(buf);
		graph = new ListGraph(type, size);
		getline(fgraph, buf);
		from = stoi(buf);
		for (int i = 0; i < size; i++)
		{
			while (i < size)
			{
				getline(fgraph, buf);
				if (buf.find(' ') == string::npos)
				{ // fail to find tab
					from = stoi(buf);
					break;
				}
				stringstream ss(buf);
				getline(ss, buf, ' ');
				to = stoi(buf);
				getline(ss, buf);
				weight = stoi(buf);
				graph->insertEdge(from, to, weight);
			}
		}
	}
	else if (filename == "graph_M.txt" && buf == "M")
	{
		type = 1;
		getline(fgraph, buf);
		size = stoi(buf);
		graph = new MatrixGraph(type, size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (j == size - 1)
					getline(fgraph, buf);
				else
					getline(fgraph, buf, ' ');
				weight = stoi(buf);
				if (weight != 0)
					graph->insertEdge(i, j, weight);
			}
		}
	}
	load++; // flag whether graph is loaded or not
	fout << "======== LOAD ========\n";
	fout << "Success\n";
	fout << "======================\n\n";

	return true;
}

bool Manager::PRINT()
{
	if (graph == nullptr)
	{ // graph doesn't exist
		printErrorCode(200);
		return false;
	}
	fout << "======== PRINT ========\n";
	graph->printGraph(&fout);
	fout << "=======================\n\n";
	return true;
}

bool Manager::mBFS(int vertex)
{
	if (graph == nullptr || vertex >= graph->getSize()) 
	{
		printErrorCode(300);
		return false;
	}
	BFS(graph, vertex, &fout);
	return true;
}

bool Manager::mDFS(int vertex)
{
	if (graph == nullptr || vertex >= graph->getSize()) 
	{
		printErrorCode(400);
		return false;
	}
	DFS(graph, vertex, &fout);
	return true;
}

bool Manager::mDFS_R(int vertex)
{
	int size = graph->getSize();
	if (graph == nullptr || vertex >= size) 
	{
		printErrorCode(500);
		return false;
	}
	vector<bool> visited(size, false);
	fout << "======== DFS_R ========\n";
	fout << "startvertex : " << vertex << "\n";
	DFS_R(graph, &visited, vertex, &fout);
	fout << "=======================\n\n";
	return true;
}

bool Manager::mKRUSKAL() 
{
	if (graph == nullptr) 
	{
		printErrorCode(600);
		return false;
	}
	if (!Kruskal(graph, &fout)) { // can't make MST
		printErrorCode(600);
		return false;	
	}
	return true;
}

bool Manager::mDIJKSTRA(int vertex)
{
	if (graph == nullptr || vertex >= graph->getSize()) 
	{
		printErrorCode(700);
		return false;
	}
	if (!Dijkstra(graph, vertex, &fout)) { // negative weight!
		printErrorCode(700);
		return false;
	}
	return true;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if (graph == nullptr || s_vertex >= graph->getSize() || e_vertex >= graph->getSize())
	{
		printErrorCode(800);
		return false;
	}
	if (!Bellmanford(graph, s_vertex, e_vertex, &fout)) {
		printErrorCode(800);
		return false;
	}
	return true;
}

bool Manager::mFLOYD()
{
	if (graph == nullptr)
	{
		printErrorCode(900);
		return false;
	}
	if (!FLOYD(graph, &fout)) {
		printErrorCode(900);
		return false;
	}
	return true;
}

void Manager::printErrorCode(int n)
{
	fout << "======== ERROR ========\n";
	fout << n << "\n";
	fout << "=======================\n\n";
}
