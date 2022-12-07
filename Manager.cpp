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
	if(load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
		
	if(!fin)
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}
	
	string buf;

	while(!fin.eof()) {
		getline(fin, buf);
		if (buf.find("LOAD") != string::npos) {
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf);
			LOAD(buf);
		}
		else if (buf == "PRINT") {
			PRINT();	
		}
		else if (buf.find("BFS") != string::npos) {
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf);
			mBFS(stoi(buf));
		}
		else if (buf.find("DFS") != string::npos) {
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf);
			mDFS(stoi(buf));
		}
		else if (buf.find("DFS_R") != string::npos) {
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf);
			mDFS_R(stoi(buf));
		}
		else if (buf == "KRUSKAL") {
			mKRUSKAL();
		}
		else if (buf.find("DIJKSTRA") != string::npos) {
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf);
			mDIJKSTRA(stoi(buf));
		}
		else if (buf.find("BELLMANFORD") != string::npos) {
			int opt1;
			stringstream ss(buf);
			getline(ss, buf, ' ');
			getline(ss, buf, ' ');
			opt1 = stoi(buf);
			getline(ss, buf);
			mBELLMANFORD(opt1, stoi(buf));
		}
		else if (buf == "FLOYD") {
			mFLOYD();
		}
		else if (buf == "EXIT") {

		}
	}

	fin.close();
}

bool Manager::LOAD(string filename)
{
	ifstream fgraph(filename);
	if (!fgraph.is_open()) {
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
	if (filename == "graph_L.txt" && buf == "L") {
		type = 0;
		getline(fgraph, buf);
		size = stoi(buf);
		graph = new ListGraph(type, size);
		getline(fgraph, buf);
		from = stoi(buf);
		for (int i = 0; i < size; i++) {
			while (i < size) {
				getline(fgraph, buf);
				if (buf.find(' ') == string::npos) { // fail to find tab
					from = stoi(buf);
					break;
				}
				stringstream ss(buf);
				getline(ss, buf, ' ');
				to = stoi(buf);
				getline(ss, buf);
				weight = stoi(buf);
//				printf("%d\t%d\t%d\n", from, to, weight);
				graph->insertEdge(from, to, weight);
			}
		}
	}
	else if (filename == "graph_M.txt" && buf == "M") {
		type = 1;
		getline(fgraph, buf);
		size = stoi(buf);
		graph = new MatrixGraph(type, size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (j == size - 1) 
					getline(fgraph, buf);
				else
					getline(fgraph, buf, ' ');
				weight = stoi(buf);
				if (weight != 0) {
					graph->insertEdge(i, j, weight);
//					printf("%d\t%d\t%d\n", i, j, weight);
				}
			}
		}
	}

	fout<<"======== LOAD ========\n";
	fout<< "Success\n";
	fout<<"======================\n";

	return true;
}

bool Manager::PRINT()
{
	if(graph == nullptr) { // graph doesn't exist
		printErrorCode(200);
		return false;
	}
	graph->printGraph(&fout);
	map <int, int> *m;
	graph->getAdjacentEdges(2, m);
	return true;
}

bool Manager::mBFS(int vertex)
{
}

bool Manager::mDFS(int vertex)
{

}


bool Manager::mDFS_R(int vertex)
{

}

bool Manager::mDIJKSTRA(int vertex)
{

}

bool Manager::mKRUSKAL()
{

}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{

}

bool Manager::mFLOYD()
{

}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========\n";
	fout << n << "\n";
	fout<<"=======================\n";
}
