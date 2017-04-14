#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//*******************************************************************************************************************
struct node;

int readFileAndCreateListOfNeighbours(node **&LN);
int readFileAndCreateListOfEdges(node *&LE);
void AddToListOfNeighbours(node* &LN, int dist, int too, node* &tail);
void AddToListOfEdges(node* &LE, int from, int too, int dist, node* &tail);
int** ConvertLNToNA(node **LN, int size_of_array);
int** ConvertLEToEA(node *LE, int size_of_array);
node* kruskalsAlgorithm(node *LE, int size);
int ConvertEAToLN(int ** array_of_edges, int size_of_array, node ** &LN);
int createArrayOfNeighboursFromFile(int ** &array_of_neighbours);
int createArrayOfEdgesFromFile(int ** &array_of_edges);
int ConvertLNToLE(node **LN, node *&LE, int size_neighbours_array);
int ConvertListOfedgesToListOfNeighbours(node *LE, node** &LN, int size_edges_array);
int ConvertLNToEA(node **LN, int ** &array_of_edges, int size_neighbours_array);
int ConvertNAToLE(int ** array_of_neighbours, int size_neighbours_array, node *&LE);
int ConvertNAToEA(int ** array_of_neighbours, int size_neighbours_array, int ** &array_of_edges);
int ConvertLEToNA(node *LE, int ** &array_of_neighbours, int size_edges_array);
int ConvertEAToNA(int** array_of_edges, int size_edges_array, int **&array_of_neighbours);
int** DijkstrasAlgorithm(node **LN, int size_neighbours_array, int vertex);
node *PrimsAlgorithm(node ** LN, int size_neighbours_array);
void showTheWayFromXToY(int from, int too, int** Dijkstras_array, node** LN, int size_neighbours_array);
void deleteListOfEdges(node* &Head);
string createFileName();

//functions used in Kruskal's, Prim's and Dijkstra's Algorithms
void bubbleBumperSort(node* &LE); //kruskal
bool IsOneForest(int *forest, int size);
int setForest(int *forest, int from, int too, int color_zwrot, int size);
int setColor(int *color, int from, int too);

int checkColor(int *color, int from, int too);//prim
void setColorPrim(int *color, int from, int too);

bool allBlackDijkstra(int **array, int size);//dijkstra
void addValuesToArray(int **array, int too, int dist, int prev, int color, bool relaksacja);
int findClosest(int **array, int size);
void PrintRoute(int indeks, int** Dijkstras_array, int &distance);

node* kruskalsAlgorithmOnLN(node **LN, int size); //kruskal_on_LN
bool oneForestOnLN(int *forest, int size);
int setForestOnLN(int *forest, int from, int too, int color_zwrot, int size);
int setColorOnLN(int *color, int from, int too);
node *nearest(node **&LN, int size, int &indeks);


//*******************************************************************************************************************

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                   
struct node
{
	int from, too, dist;
	node* next;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//*******************************************************************************************************************
                                                                                                               
int main()
{
	node **LN = NULL;
	node *LE = NULL;
	node *LEW = NULL;
	node *LER = NULL;
	int** Dijkstras_array = NULL;
	int **array_of_neighbours = NULL;
	int **array_of_edges = NULL;
	int size_neighbours_array;
	int size_edges_array;
	int choice;
	do
	{
		cout << "1. Plik -> LN" << endl
			<< "2. Plik -> LE" << endl
			<< "3. Kruskal's algorithm" << endl
			<< "4. LN -> MN" << endl
			<< "5. LE -> ME" << endl
			<< "6. Delete LE" << endl
			<< "7. ME -> LN" << endl
			<< "8. File -> MN" << endl
			<< "9. File -> ME" << endl
			<< "10. LN -> LE" << endl
			<< "11. LE -> LN" << endl
			<< "12. LN -> ME" << endl
			<< "13. MN -> LE" << endl
			<< "14. MN -> ME" << endl
			<< "15. LE -> MN" << endl
			<< "16. ME -> MN" << endl
			<< "17. Prim's algorithm" << endl
			<< "18. Dijkstra's algorithm" << endl
			<< "19. Show the shortest way from X to Y" << endl
			<< "20. Kruskal's algorithm on List of neighbours" << endl
			<< "0. Exit" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			size_neighbours_array = readFileAndCreateListOfNeighbours(LN);
			break;

		case 2:
			size_edges_array = readFileAndCreateListOfEdges(LE);
			break;

		case 3:
			LEW = kruskalsAlgorithm(LE, size_neighbours_array);
			break;

		case 4:
			array_of_neighbours = ConvertLNToNA(LN, size_neighbours_array);
			for (int i = 0; i < size_neighbours_array; i++)
				for (int j = 0; j < size_neighbours_array; j++)
				{
					cout << array_of_neighbours[i][j] << "\t";

					if (j == (size_neighbours_array - 1))
						cout << endl;
				}
			break;

		case 5:
			array_of_edges = ConvertLEToEA(LE, size_edges_array);
			for (int j = 0; j < size_edges_array; j++)
				for (int i = 0; i < 3; i++)
				{
					cout << array_of_edges[i][j] << ' ';

					if (i == 2)
						cout << endl;
				}
			break;

		case 6:
			deleteListOfEdges(LE);
			break;

		case 7:
			size_neighbours_array = ConvertEAToLN(array_of_edges, size_edges_array, LN);   
			break;

		case 8:
			size_neighbours_array = createArrayOfNeighboursFromFile(array_of_neighbours);
			for (int i = 0; i < size_neighbours_array; i++)
				for (int j = 0; j < size_neighbours_array; j++)
				{
					cout << array_of_neighbours[i][j] << "\t";

					if (j == (size_neighbours_array - 1))
						cout << endl;
				}
			break;

		case 9:
			size_edges_array = createArrayOfEdgesFromFile(array_of_edges); 
			for (int j = 0; j < size_edges_array; j++)
				for (int i = 0; i < 3; i++)
				{
					cout << array_of_edges[i][j] << ' ';

					if (i == 2)
						cout << endl;
				}
			break;

		case 10:
			size_edges_array = ConvertLNToLE(LN,LE, size_neighbours_array);
			break;

		case 11:
			size_neighbours_array = ConvertListOfedgesToListOfNeighbours(LE,LN,size_edges_array);
			break;

		case 12:
			size_edges_array =  ConvertLNToEA(LN, array_of_edges, size_neighbours_array);
			for (int j = 0; j < size_edges_array; j++)
				for (int i = 0; i < 3; i++)
				{
					cout << array_of_edges[i][j] << ' ';

					if (i == 2)
						cout << endl;
				}
			break;

		case 13:
			size_edges_array = ConvertNAToLE(array_of_neighbours,size_neighbours_array,LE);
			break;

		case 14:
			size_edges_array = ConvertNAToEA(array_of_neighbours, size_neighbours_array, array_of_edges);
			for (int j = 0; j < size_edges_array; j++)
				for (int i = 0; i < 3; i++)
				{
					cout << array_of_edges[i][j] << ' ';

					if (i == 2)
						cout << endl;
				}
			break;

		case 15:
			size_neighbours_array = ConvertLEToNA(LE, array_of_neighbours, size_edges_array);
			for (int i = 0; i < size_neighbours_array; i++)
				for (int j = 0; j < size_neighbours_array; j++)
				{
					cout << array_of_neighbours[i][j] << "\t";

					if (j == (size_neighbours_array - 1))
						cout << endl;
				}
			break;

		case 16:
			size_neighbours_array = ConvertEAToNA(array_of_edges, size_edges_array, array_of_neighbours);
			for (int i = 0; i < size_neighbours_array; i++)
				for (int j = 0; j < size_neighbours_array; j++)
				{
					cout << array_of_neighbours[j][i] << "\t";

					if (j == (size_neighbours_array - 1))
						cout << endl;
				}
			break;

		case 17:
			LER = PrimsAlgorithm(LN, size_neighbours_array);
			break;

		case 18:
			cout << "From which node would you like to count distance: ";
			int vertex;
			cin >> vertex;
			Dijkstras_array = DijkstrasAlgorithm(LN, size_neighbours_array, vertex);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < size_neighbours_array; j++)
				{
					cout << Dijkstras_array[j][i] << "\t";
				}
				cout << endl;
			}
			break;

		case 19:
			cout << "From which node would you like to set out route: ";
			int x;
			cin >> x;
			cout << "In which node should route end: ";
			int y;
			cin >> y;
			showTheWayFromXToY(x, y, Dijkstras_array, LN, size_neighbours_array);
			break;

		case 20:
			LEW = kruskalsAlgorithmOnLN(LN, size_neighbours_array);
			break;
		}

	} while (choice != 0);
}

//*******************************************************************************************************************
			
string createFileName()
{
	string fileName;
	string filePath = "D:\\AGH University of Science and Technology\\Rok I Semestr II\\Algorytmy i struktury danych\\laboratoria\\AiSD_Graph\\";
	cout << "Enter file map name, which you want to open: ";
	cin >> fileName;
	filePath += fileName + ".txt";
	return filePath;
}

//*******************************************************************************************************************

int readFileAndCreateListOfNeighbours(node **&LN)
{
	node *tail = NULL;
	int size, value;
	fstream read;
	read.open(createFileName(), ios::in);
	if (read.good() == true)
	{
		read >> size;

		LN = new node *[size];

		for (int i = 0; i < size; i++)
			LN[i] = NULL;

		for (int i = 0; i < size; i++)
		{
			tail = NULL;                        
			for (int j = 0; j < size; j++)
			{
				read >> value;
				if (value != NULL)
					AddToListOfNeighbours(LN[i], value, j, tail);
			}
		}

		return size;
	}

	else
	{
		cout << "Error reading file" << endl;
		return 0;
	}
}

//*******************************************************************************************************************
                                                                                      
void AddToListOfNeighbours(node* &LN, int dist, int too, node * &tail)
{
	node *tmp = new node;
	tmp->too = too;
	tmp->dist = dist;
	if (LN == NULL)
	{
		tmp->next = LN;
		LN = tmp;
		tail = LN;
	}

	else
	{
		tail->next = tmp;
		tail = tail->next;
		tmp->next = NULL;
	}
}

//*******************************************************************************************************************
                                                                                           
int readFileAndCreateListOfEdges(node* &LE)
{
	node *tail;
	int edges_count, from, too, dist;
	fstream read;
	read.open(createFileName(), ios::in);

	if (read.good() == true)
	{
		read >> edges_count;
		int size_array = edges_count;
		tail = NULL;
		while (edges_count)
		{
			read >> from;
			read >> too;
			read >> dist;
			AddToListOfEdges(LE, from, too, dist, tail);
			edges_count--;
		}

		return size_array;
	}

	else
	{
		cout << "Error reading file" << endl;
		return 0;
	}
}
//*******************************************************************************************************************

void AddToListOfEdges(node* &LE, int from, int too, int dist, node* &tail)

{
	node *tmp = new node;
	tmp->from = from;
	tmp->too = too;
	tmp->dist = dist;

	if (LE == NULL)
	{
		tmp->next = LE;
		LE = tmp;
		tail = tmp;
	}

	else
	{
		tail->next = tmp;
		tail = tmp;
		tmp->next = NULL;
	}
}

//*******************************************************************************************************************

int** ConvertLNToNA(node **LN, int size_of_array)
{
	int **NA = new int *[size_of_array];
	for (int i = 0; i < size_of_array; i++)
		NA[i] = new int[size_of_array];
	

	for (int i = 0; i < size_of_array; i++)
	{
		node *tmp = LN[i];
		for (int j = 0; j < size_of_array; j++)
		{
			if (tmp != NULL)
			{
				if (tmp->too == j)
				{
					NA[i][j] = tmp->dist;
					tmp = tmp->next;
				}

				else
					NA[i][j] = 0;
			}

			else
				NA[i][j] = 0;
		}
	}

	return NA;
}

//*******************************************************************************************************************

int** ConvertLEToEA(node *LE, int size_of_array)
{
	int **array_of_edges = new int *[3];
	for (int i = 0; i < 3; i++)
		array_of_edges[i] = new int[size_of_array];

	node *tmp = LE;

	for (int j = 0; j < size_of_array; j++)
	{		
			array_of_edges[0][j] = tmp->from;
			array_of_edges[1][j] = tmp->too;
			array_of_edges[2][j] = tmp->dist;
			tmp = tmp->next;
	}
	
	return array_of_edges;
}

//*******************************************************************************************************************
                                                                                            
void bubbleBumperSort(node* &LE)
{
	if (LE != NULL && LE->next != NULL)
	{
		bool isSorted = false;
		node *tmp = LE;
		node *front_bumper = NULL;

		do
		{
			isSorted = false;
			node *tmp_prev = NULL;

			while ((tmp != front_bumper))
			{
				if ((tmp->next != NULL) && (tmp->dist > tmp->next->dist))
				{
					if (tmp == LE)
					{
						LE = LE->next;
						tmp->next = LE->next;
						LE->next = tmp;
						tmp_prev = LE;
						isSorted = true;
					}

					else
					{
						node *tmp_next = tmp->next;
						tmp_prev->next = tmp_next;
						tmp->next = tmp_next->next;
						tmp_next->next = tmp;
						tmp_prev = tmp_prev->next;
						isSorted = true;
					}
				}

				else
				{
					tmp_prev = tmp;
					tmp = tmp->next;
				}
			}

			front_bumper = tmp_prev;
			tmp = LE;

		} while (isSorted == true);
	}
}

//*******************************************************************************************************************
                                                                                                          
void deleteListOfEdges(node* &Head)
{
	while (Head != NULL)
	{
		node *tmp = Head;
		Head = Head->next;
		delete tmp;
	}
}
	
//*******************************************************************************************************************
                                                                                 
int ConvertEAToLN(int ** array_of_edges,int size_edges_array, node ** &LN)
{
	node *tail = NULL;
	int node_amount = 0, from ,too, dist;

	for (int j = 0; j < size_edges_array; j++)
		if (node_amount < array_of_edges[0][j])
			node_amount = array_of_edges[0][j];
	
	node_amount += 1;

	LN = new node *[node_amount];

	for (int i = 0; i < node_amount; i++)
		LN[i] = NULL;

	for (int j = 0; j < size_edges_array; j++)
	{
		from = array_of_edges[0][j];
		too = array_of_edges[1][j];
		dist = array_of_edges[2][j];
		AddToListOfNeighbours(LN[from], dist, too, tail);
	}

	return node_amount;
}	

//*******************************************************************************************************************
                                                                                    
int createArrayOfNeighboursFromFile(int ** &array_of_neighbours)
{
	fstream read;
	int size_of_array, value;
	read.open(createFileName(), ios::in);

	if (read.good() == true)
	{
		read >> size_of_array;

		array_of_neighbours = new int *[size_of_array];
		for (int i = 0; i < size_of_array; i++)
			array_of_neighbours[i] = new int[size_of_array];

		for (int j = 0; j < size_of_array; j++)
			for (int i = 0; i < size_of_array; i++)
			{
				read >> value;
				array_of_neighbours[i][j] = value;
			}

		return size_of_array;
	}

	else 
		return 0;
}

//*******************************************************************************************************************
                                                                                
int createArrayOfEdgesFromFile(int ** &array_of_edges)
{
	fstream read;
	int size_of_array, value;

	read.open(createFileName(), ios::in);

	if (read.good() == true)
	{
		read >> size_of_array;

		array_of_edges = new int *[3];
		for (int i = 0; i < 3; i++)
			array_of_edges[i] = new int[size_of_array];

		for (int j = 0; j < size_of_array; j++)
			for (int i = 0; i < 3; i++)
			{
				read >> value;
				array_of_edges[i][j] = value;
			}

		return size_of_array;
	}

	else
		return 0;
}
//*******************************************************************************************************************

int ConvertLNToLE(node **LN, node *&LE, int size_neighbours_array)
{
	int size_of_array = 0;
	node *tail = NULL;
	for (int i = 0; i < size_neighbours_array; i++)
	{
		node *tmp_LN = LN[i];
		while (tmp_LN != NULL)
		{
			AddToListOfEdges(LE, i , tmp_LN->too, tmp_LN->dist, tail);
			size_of_array++;
			tmp_LN = tmp_LN->next;
		}
	}
	return size_of_array;
}

//*******************************************************************************************************************

int ConvertListOfedgesToListOfNeighbours(node *LE, node** &LN, int size_edges_array)
{
	node * tmp = LE;
	int node_amount = 0;

	while (tmp != NULL)
	{
		if (node_amount < tmp->from)
			node_amount = tmp->from;
		
		tmp = tmp->next;
	}

	node_amount += 1;

	LN = new node *[node_amount];

	for (int i = 0; i < node_amount; i++)
		LN[i] = NULL;

	tmp = LE;

	node *tail = NULL;

	while (tmp != NULL)
	{
		AddToListOfNeighbours(LN[tmp->from], tmp->dist, tmp->too, tail);
		tmp = tmp->next;
	}

	return node_amount;
}

//*******************************************************************************************************************

int ConvertLNToEA(node **LN, int ** &array_of_edges, int size_neighbours_array)
{
	int size_of_array = 0;

	for (int i = 0; i < size_neighbours_array; i++)
	{
		node *tmp = LN[i];
		while (tmp != NULL)
		{
			size_of_array++;
			tmp = tmp->next;
		}
	}

	array_of_edges = new int *[3];
	for (int i = 0; i < 3; i++)
		array_of_edges[i] = new int[size_of_array];
	
	int j = 0;
	for (int i = 0; i < size_neighbours_array; i++)
	{
		node *tmp = LN[i];
		while(tmp != NULL)
		{
			array_of_edges[0][j] = i;
			array_of_edges[1][j] = tmp->too;
			array_of_edges[2][j] = tmp->dist;
			tmp = tmp->next;
			j++;
		}
	}
	return size_of_array;
}

//*******************************************************************************************************************

int ConvertNAToLE(int ** array_of_neighbours, int size_neighbours_array, node *&LE)
{
	int size_edges_array = 0;

	node *tail = NULL;
	for (int i = 0; i < size_neighbours_array; i++)
		for (int j = 0; j < size_neighbours_array; j++)
		{
			if (array_of_neighbours[i][j] != 0)
			{
				AddToListOfEdges(LE, i, j, array_of_neighbours[i][j], tail);
				size_edges_array++;
			}
		}

	return size_edges_array;
}

//*******************************************************************************************************************

int ConvertNAToEA(int ** array_of_neighbours, int size_neighbours_array, int ** &array_of_edges)
{
	int size_edges_array = 0;
	for (int i = 0; i < size_neighbours_array; i++)
		for (int j = 0; j < size_neighbours_array; j++)
			if (array_of_neighbours[i][j] != 0)
				size_edges_array++;

	array_of_edges = new int *[3];
	for (int i = 0; i < 3; i++)
		array_of_edges[i] = new int[size_edges_array];

	int k = 0;
	for (int i = 0; i < size_neighbours_array; i++)
		for (int j = 0; j < size_neighbours_array; j++)
			if (array_of_neighbours[i][j] != 0)
			{
				array_of_edges[0][k] = i;
				array_of_edges[1][k] = j;
				array_of_edges[2][k] = array_of_neighbours[i][j];
				k++;
			}

	return size_edges_array;
}

//*******************************************************************************************************************

int ConvertLEToNA(node *LE, int ** &array_of_neighbours, int size_edges_array)
{
	node * tmp = LE;
	int node_amount = 0;

	while (tmp != NULL)
	{
		node_amount = tmp->from;
		tmp = tmp->next;
	}

	tmp = LE;

	node_amount += 1;

	array_of_neighbours = new int *[node_amount];
	for (int i = 0; i < node_amount; i++)
		array_of_neighbours[i] = new int[node_amount];

	for (int i = 0; i < node_amount; i++)
		for (int j = 0; j < node_amount; j++)
		{
			if (tmp != NULL && i == tmp->from && j == tmp->too)
			{
				array_of_neighbours[i][j] = tmp->dist;
				tmp = tmp->next;
			}
			else
				array_of_neighbours[i][j] = 0;
		}

	return node_amount;
}

//*******************************************************************************************************************

int ConvertEAToNA(int** array_of_edges, int size_edges_array, int **&array_of_neighbours)
{
	int array_of_neighbours_size = 0;
	for (int i = 0; i < size_edges_array; i++)
		if (array_of_neighbours_size < array_of_edges[0][i])
			array_of_neighbours_size = array_of_edges[0][i];

	array_of_neighbours_size++;

	array_of_neighbours = new int *[array_of_neighbours_size];
	for (int i = 0; i < size_edges_array; i++)
		array_of_neighbours[i] = new int[array_of_neighbours_size];

	int k = 0;

	for (int i = 0; i < array_of_neighbours_size; i++)
		for (int j = 0; j < array_of_neighbours_size; j++)
		{
			if (i == array_of_edges[0][k] && j == array_of_edges[1][k])
			{
				array_of_neighbours[i][j] = array_of_edges[2][k];
				k++;
			}

			else
				array_of_neighbours[i][j] = 0;
		}

	return array_of_neighbours_size;

}

//*******************************************************************************************************************
                                                                                                     
node* PrimsAlgorithm(node ** LN, int size_neighbours_array)
{
	node* LER = NULL;
	int *color = new int[size_neighbours_array];
	for (int i = 0; i < size_neighbours_array; i++)
		color[i] = 0;

	color[0] = 1; 

	node* closest = NULL;
	node* tail = NULL;
	int color_zwrot = 0;
	int from = 0;

	for (int licznik = 0; licznik < (size_neighbours_array - 1); licznik++)
	{
		int i = 0;
		closest = NULL;
		while (i < size_neighbours_array)
		{
			color_zwrot = checkColor(color, i, i);
			if (color_zwrot == 1) 
			{
				node *tmp = LN[i];
				while (tmp != NULL)
				{
					color_zwrot = checkColor(color, i, tmp->too);
					if (color_zwrot == 1)
					{
						if (closest == NULL)
						{
							closest = tmp;
							from = i;
						}

						if (closest->dist > tmp->dist)
						{
							closest = tmp;
							from = i;
						}
					}
					tmp = tmp->next;
				}
			}
			i++;
		}

		setColorPrim(color, from, closest->too);
		AddToListOfEdges(LER, from, closest->too, closest->dist, tail);
	}

	return LER;
}

//***********************************************************************************************

int checkColor(int *color, int from, int too)
{	
	if (from == too)
	{
		if (color[from] == 0)
			return 0;

		if (color[from] == 1)
			return 1;
	}

	if ((color[from] == 1 && color[too] == 0))
		return 1;

	if (color[from] == 1 && color[too] == 1)
		return 2;

	else
		return 0;

	// 0 two white // 1 grey white	// 2 both grey
}

//*********************************************************************************************

void setColorPrim(int *color, int from, int too)
{
	color[from] = 1;
	color[too] = 1;
}

//*******************************************************************************************************************
                                                                                                  
node* kruskalsAlgorithm(node *LE, int size)
{
	int *color = new int[size];
	int *forest = new int[size];
	for (int i = 0; i < size; i++)
	{
		color[i] = 0;
		forest[i] = 0;
	}
	
	node *tmp = LE;
	bubbleBumperSort(tmp);

	node *LEW = NULL;
	node *tail = NULL;
	bool one_forest_zwrot = false;

	while (one_forest_zwrot == false)
	{
		int color_zwrot = setColor(color, tmp->from, tmp->too);
		int forest_zwrot = setForest(forest, tmp->from, tmp->too, color_zwrot, size);

		if (forest_zwrot == 0 || forest_zwrot == 1)
			AddToListOfEdges(LEW, tmp->from, tmp->too, tmp->dist, tail);
		

		tmp = tmp->next;

		one_forest_zwrot = IsOneForest(forest, size);
	}

	return LEW;
}

//***********************************************************************************************

int setColor(int *color, int from, int too)
{
	int returnedValue = 0;

	if (color[from] == 0 && color[too] == 0)
		returnedValue = 0; // 0 two white

	if ((color[from] == 0 && color[too] == 1) || (color[from] == 1 && color[too] == 0))
		returnedValue = 1; // 1 white grey

	if (color[from] == 1 && color[too] == 1)
		returnedValue = 2; // 2 grey

	color[from] = 1;
	color[too] = 1;
	return returnedValue;
}

//***********************************************************************************************

int setForest(int *forest, int from, int too, int color_zwrot, int size)
{
	static int which_forest = 1;
	//0 new forest
	//1 forest connected or attached
	//2 node has been deleted
	if (color_zwrot == 0)
	{
		forest[from] = which_forest;
		forest[too] = which_forest;
		which_forest++;
		return 0;
	}

	if (color_zwrot == 1)
	{
		int first_forest = forest[from];
		int second_forest = forest[too];
		
		if (first_forest == 0 && second_forest != 0)
		{
			forest[from] = which_forest;
			for (int i = 0; i < size; i++)			
				if (forest[i] == second_forest)
					forest[i] = which_forest;

			which_forest++;
			return 1;
		}

		if (first_forest != 0 && second_forest == 0)
		{
			forest[too] = which_forest;
			for (int i = 0; i < size; i++)				
				if (forest[i] == first_forest)
					forest[i] = which_forest;
			
			which_forest++;
			return 1;
		}
	}

	if (color_zwrot == 2)
	{
		int first_forest = forest[from];
		int second_forest = forest[too];

		if (first_forest == second_forest)
		{
			which_forest++;
			return 2;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (forest[i] == first_forest || forest[i] == second_forest)
					forest[i] = which_forest;
			}
			which_forest++;
			return 1;
		}
	}
}

//***********************************************************************************************

bool IsOneForest(int *forest, int size)
{
	int one_forest = forest[0];
	for (int i = 0; i < size; i++)
		if (one_forest != forest[i] || one_forest == 0)
			return false;
	

	return true;
}

//*******************************************************************************************************************
                                                                                            
node* kruskalsAlgorithmOnLN(node **LN, int size)
{
	int index = -1;
	int *color = new int[size];
	for (int i = 0; i < size; i++)
		color[i] = 0;

	int *forest = new int[size];
	for (int i = 0; i < size; i++)
		forest[i] = 0;

	node *tmp = NULL;
	for (int i = 0; i < size; i++)
	{
		tmp = LN[i];
		bubbleBumperSort(tmp);
		LN[i] = NULL;
		LN[i] = tmp;
	}

	node *LEW = NULL;
	node *tail = NULL;

	bool one_forest_returned_value = false;

	while (one_forest_returned_value == false)
	{
		tmp = nearest(LN, size, index);
		int color_returned_value = setColorOnLN(color, index, tmp->too);
		int forest_returned_value = setForestOnLN(forest, index, tmp->too, color_returned_value, size);

		if (forest_returned_value == 0 || forest_returned_value == 1)
		{
			AddToListOfEdges(LEW, index, tmp->too, tmp->dist, tail);
		}

		tmp = tmp->next;

		one_forest_returned_value = oneForestOnLN(forest, size);
	}

	return LEW;
}

//***********************************************************************************************

node *nearest(node ** &LN, int size, int &indeks)
{
	node *closest = NULL;
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (closest == NULL)
		{
			closest = LN[i];
			index = i;
		}

		else if (closest->dist > LN[i]->dist)
		{
			closest = LN[i];
			index = i;
		}
	}

	indeks = index;
	LN[index] = LN[index]->next;

	return closest;
}

//***********************************************************************************************
int setColorOnLN(int *color, int from, int too)
{
	int returned_value = 0;
	if (color[from] == 0 && color[too] == 0)
		returned_value = 0;

	if ((color[from] == 0 && color[too] == 1) || (color[from] == 1 && color[too] == 0))
		returned_value = 1;

	if (color[from] == 1 && color[too] == 1)
		returned_value = 2;

	color[from] = 1;    // 0 two white
	color[too] = 1;     // 1 white grey
						// 2 two grey
	return returned_value;
}

//***********************************************************************************************

int setForestOnLN(int *forest, int from, int too, int color_returned_value, int size)
{
	static int which_forest = 1;
	//0 new forest
	//1 forests connected or attached
	//2 node has been deleted
	if (color_returned_value == 0)
	{
		forest[from] = which_forest;
		forest[too] = which_forest;
		which_forest++;
		return 0;
	}

	if (color_returned_value == 1)
	{
		int first_forest = forest[from];
		int second_forest = forest[too];

		if (second_forest != 0 && first_forest != 0)
		{
			for (int i = 0; i < size; i++)
			{
				if (forest[i] == first_forest || forest[i] == second_forest)
					forest[i] = which_forest;
			}
			which_forest++;
			return 1;
		}

		if (first_forest == 0 && second_forest != 0)
		{
			for (int i = 0; i < size; i++)
			{
				forest[from] = which_forest;
				if (forest[i] == second_forest)
					forest[i] = which_forest;
			}
			which_forest++;
			return 1;
		}

		if (first_forest != 0 && second_forest == 0)
		{
			for (int i = 0; i < size; i++)
			{
				forest[too] = which_forest;
				if (forest[i] == first_forest)
					forest[i] = which_forest;
			}
			which_forest++;
			return 1;
		}
	}

	if (color_returned_value == 2)
	{
		int first_forest = forest[from];
		int second_forest = forest[too];

		if (first_forest == second_forest)
		{
			which_forest++;
			return 2;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (forest[i] == first_forest || forest[i] == second_forest)
					forest[i] = which_forest;
			}
			which_forest++;
			return 1;
		}
	}
}

//***********************************************************************************************

bool oneForestOnLN(int *forest, int size)
{
	int one_forest = forest[0];
	for (int i = 0; i < size; i++)
	{
		if (one_forest != forest[i] || one_forest == 0)
			return false;
	}

	return true;
}

//*******************************************************************************************************************
                                                                                                  
int** DijkstrasAlgorithm(node **LN, int size_neighbours_array, int vertex)
{
	int** array = new int *[size_neighbours_array];
	for (int i = 0; i < size_neighbours_array; i++)
		array[i] = new int[3];

	for (int i = 0; i < size_neighbours_array; i++)
	{
		array[i][0] = 0;
		array[i][1] = -1;
		array[i][2] = -1;
	}

	array[vertex][0] = 1; //setting as grey node from which distance will be counted
	array[vertex][1] = 0; //setting distance for this node equal to 0
	array[vertex][2] = -1;//predecessor for this node doesn't exist

	bool stop = false;

	while (stop == false)
	{
		node *tmp_LN = LN[vertex];

		while (tmp_LN != NULL)
		{
			if (array[tmp_LN->too][0] != 2)
			{
				if (array[tmp_LN->too][0] == 0)
					addValuesToArray(array, tmp_LN->too, (array[vertex][1]+tmp_LN->dist), vertex, 1, false);
	
				else if (array[tmp_LN->too][1] > (array[vertex][1] + tmp_LN->dist))//relaxation
					addValuesToArray(array, tmp_LN->too, array[vertex][1] + tmp_LN->dist, vertex, 1, true);
			}
			
			tmp_LN = tmp_LN->next;
		}

		addValuesToArray(array, vertex, 0, -1, 2, false);//ustawianie wierzcholka jako czarnego
		
		vertex = findClosest(array, size_neighbours_array);//znajdowanie najblizszego wierzcholka sposrod szarych

		stop = allBlackDijkstra(array, size_neighbours_array);
	}

	return array;
}

//***********************************************************************************************

bool allBlackDijkstra(int **array, int size)
{
	for (int i = 0; i < size; i++)
		if (array[i][0] != 2)
			return false;

	return true;
}

//***********************************************************************************************

int findClosest(int **array, int size)
{
	int index = -1;
	int dist = -1;

	for (int i = 0; i < size; i++)
	{
		if (array[i][0] == 1)
		{
			if (index == -1)
			{
				index = i;
				dist = array[i][1];
			}
			else if (dist > array[i][1])
			{
				index = i;
				dist = array[i][1];
			}
		}
	}

	return index;
}

//***********************************************************************************************

void addValuesToArray(int **array, int too, int dist, int prev, int color, bool relaxation) 
{
	array[too][0] = color;

	if (array[too][1] == -1)
		array[too][1] = 0;

	if (relaxation == false)
		array[too][1] += dist;

	else
		array[too][1] = dist;

	if( prev != -1 )
		array[too][2] = prev;
}

//*******************************************************************************************************************
                                                                                           
void showTheWayFromXToY(int from, int too, int** Dijkstras_array, node** LN, int size_neighbours_array)
{
	Dijkstras_array = DijkstrasAlgorithm(LN, size_neighbours_array, from);
	int distance = 0;
	PrintRoute(too, Dijkstras_array, distance);
	cout << "\nDistance between two nodes is equal to:: " << distance << endl;
}

//***********************************************************************************************
                                   
void PrintRoute(int indeks, int ** Dijkstras_array, int &distance)
{
	if (Dijkstras_array[indeks][2] != -1)
	{
		PrintRoute(Dijkstras_array[indeks][2], Dijkstras_array, distance);
		cout << "->";
	}

	distance += Dijkstras_array[indeks][1];
	cout << indeks;
}

//*******************************************************************************************************************


