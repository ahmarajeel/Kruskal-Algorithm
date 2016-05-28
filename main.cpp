#include <iostream>
#include <fstream>
using namespace std;

class graphNode
{
	public:
	
		int nodeID;
		graphNode* next;
		
		graphNode(int id)
		{
			nodeID = id;
			next = NULL;
		}
		~graphNode()
		{
			delete next;
		}
};

class undirectedEdge
{
	public:
		undirectedEdge* next;
		int edgeCost;   // should be positive
		int Ni;
		int Nj;
		
		undirectedEdge(int from, int to, int cost)
		{
			Ni = from;
			Nj = to;
			edgeCost = cost;		
			next = NULL;
		} 
		
		void printEdge(ofstream& outFile)
		{
			outFile << Ni << "\t" << Nj << "\t" << edgeCost << endl;
		}
};

class KruskalMST
{
	public:
		int numNodes;
		int* inWhichSet;
		int numSets;
		int totalCost;
		undirectedEdge* edgeListHead;
		undirectedEdge* MST;
		
		KruskalMST(int num)
		{
			numNodes = num;
			inWhichSet = new int[num+1];
			numSets = num;
			totalCost = 0;
			for(int i = 0; i <= num; i++)
			{
				inWhichSet[i] = i;  // initializing it to itself
			}
			edgeListHead = new undirectedEdge(999,999,999);
			MST = new undirectedEdge(999,999,999);
		}
		
		void printList(ofstream &outFile)
		{
			undirectedEdge* current;
			current = edgeListHead->next;
			while(current != NULL)
			{
				current->printEdge(outFile);
				current = current->next;
			}
			outFile << endl;
		}	
	
	void printMST(ofstream &outFile)
		{
			undirectedEdge* current;
			current = MST->next;
			while(current != NULL)
			{
				current->printEdge(outFile);
				current = current->next;
			}
			outFile << endl;
		}	
			
		void mergeTwoSets(int N1, int N2)
		{
			int min, max, index;
			if(N1 <= N2)
			{
				min = N1;
				max = N2;
			}
			else
			{
				min = N2;
				max = N1;
			}
			index = min;
			while(index <= numNodes)
			{
				if(inWhichSet[index] == max)
				{
					inWhichSet[index] = min;
				}
				index++;	
			}	
		}
	
		undirectedEdge* findSpot(int item)
		{
			undirectedEdge* spot = edgeListHead;
			while(spot->next != NULL && spot->next->edgeCost < item)
			{
				spot = spot->next;
			}
			return spot;
		}
		
		void listInsert(int from, int to, int cost)
		{
			undirectedEdge* spot;	
			spot = findSpot(cost);
			undirectedEdge* newNode;
			newNode = new undirectedEdge(from, to, cost);
			newNode->next = spot->next;
			spot->next = newNode;
		}
		
		undirectedEdge* findSpot1(int cost)
		{
			undirectedEdge* spot = MST;
			while(spot->next != NULL && spot->next->edgeCost < cost)
			{
				spot = spot->next;
			}
			return spot;
		}
		
		void listInsert1(int from, int to, int cost)
		{
			undirectedEdge* spot;	
			spot = findSpot1(cost);
			undirectedEdge* newNode;
			newNode = new undirectedEdge(from, to, cost);
			newNode->next = spot->next;
			spot->next = newNode;
		}
		
		void deleteEdge()
		{
			undirectedEdge* temp = edgeListHead->next;
			edgeListHead->next = edgeListHead->next->next;
			delete temp;
		}
		
		void print_1D(int *ary, ofstream& outFile2)
		{
			for(int i = 1; i <= numNodes; i++)
			{
				outFile2 << ary[i] << " ";
			}
			outFile2 << endl;
		}
		
		void KruskalAlg(ifstream& inFile, ofstream& outFile1, ofstream& outFile2)
		{
			int from, to, cost;
			while(inFile >> from >> to >> cost)
			{
				listInsert(from, to, cost);
			}
		
			undirectedEdge* minEdge;
			outFile2 << "Sorted input edges:\n\n";
			outFile2 << "Ni\tNj\tcost" << endl; 
			printList(outFile2);
			while(numSets > 1)
			{
				minEdge = new undirectedEdge(edgeListHead->next->Ni, edgeListHead->next->Nj, edgeListHead->next->edgeCost);
				deleteEdge();
				if(inWhichSet[minEdge->Ni] == inWhichSet[minEdge->Nj])
				{
					continue;
				}
				else
				{
					listInsert1(minEdge->Ni, minEdge->Nj, minEdge->edgeCost);
					totalCost += minEdge->edgeCost;
					mergeTwoSets(minEdge->Ni, minEdge->Nj);
					numSets--;
					outFile2 << "MST Edges:\n";
					outFile2 << "Ni\tNj\tcost" << endl; 
					printMST(outFile2);
					outFile2 << "InWhichSet array: ";
					print_1D(inWhichSet, outFile2);	
					outFile2 << "\n\n";
				}	 	
			}
			outFile1 << "Number of Nodes is: " << numNodes << endl << endl;
			outFile1 << "Ni\tNj\tcost" << endl; 
			printMST(outFile1);	
			
			outFile1 << "Total cost is: " << totalCost;		
		}		
};

int main(int argc, char* argv[])
{
	int item;
	ifstream inFile;
	ofstream outFile1, outFile2;
	outFile1.open(argv[2]);
	inFile.open(argv[1]);
	outFile2.open(argv[3]);
	inFile >> item;
	KruskalMST edgeList(item);
	edgeList.KruskalAlg(inFile, outFile1, outFile2);	
	
	inFile.close();
	outFile1.close();
	outFile2.close();	
}









