#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <iomanip>

#define infi 99                 // CONSTANT TO DEFINE INFINITY FOR PROGRAM

using namespace std;

class Graph{

	int station;                	// VERTICES
	int route;                  	// EDGES
	int weight;                 	// WEIGHTED-DIRECTED GRAPH
	int **myMatrix; 		// 2D ARRAY FOR IF ROUTE
	int **floydMatrix;  		// 2D ARRAY FOR SHORTEST PATH
	int **reconstructMatrix;	// 2D ARRAY FOR PATH RECONSTRUCTION 
	string *stationColors;  	// ARRAY FOR NAMES OF COLORS

	vector<int> trainPath;		// A VECTOR FOR PRINTING THE RECONSTRUCTED PATH ( IN printPath() FUNCTION )

	public:

	//CONSTRUCTOR
	Graph(int stations, int routes);

	void printMatrix();
	void addRoute(int from, int to, int weight);
	bool isRoute(int from, int to);                 
	void deleteMatrix();				// DELETES ALL THE ALLOCATED ARRAYS FROM THE CLASS
	void calcShortestRoutes();                      // RUN THE F-W ALGORITHM
	int shortestRoute(string src, string dst);	// RETURN SHORTEST ROUTE FROM THE FLOYD-WARSHALL MATRIX
	bool checkColors(string src); 			// CHECK IF THE COLORS ARE LEGITMATE ENTRIES
	void printPath(string src, string dst);         // PRINT PATH FROM RECONSTRUCTION MATRIX

	//GETTERS AND SETTERS
	int getStationId(string color);                 // PASS IN COLOR TO GET ID
	string getStationColors(int id);                // GET STATION COLOR FROM ARRAY
	void setStationColors(int id, string color);    // SET STATION COLOR FOR ARRAY

};

Graph::Graph(int stations, int routes){

	//ARRAY FOR THE STATION NAMES (DYNAMICALLY SIZED) 
	stationColors = new string[stations]; 

	station = stations;
	route = routes; 

	myMatrix = new int* [station];

	for(int i = 0; i<station; i++)
	{
		myMatrix[i] = new int[station];

		for(int j = 0; j < station; j++)
		{
			myMatrix[i][j] = 0;  
		}						
	}

	/* INITIALIZE A SECOND MATRIX FOR FLOYD WARSHALL
	   THIS IS A COPY TO RUN THE ALGORITHM ON AND
	   ALLOW THE 1ST MATRIX TO RETAIN ITS INFORMATION */
	floydMatrix = new int* [station];

	for(int i = 0; i<station; i++)
	{
		floydMatrix[i] = new int[station];

		for(int j = 0; j < station; j++)
		{
			floydMatrix[i][j] = infi; //infi = 99
		}
	}  

	// INITIALIZE A THRID MATRIX TO BE USED
	// FOR PATH RECONSTRUCTION
	reconstructMatrix = new int* [station];

	for(int i = 0; i<station; i++)
	{
		reconstructMatrix[i] = new int[station];

		for(int j = 0; j < station; j++)
		{
			reconstructMatrix[i][j] = -1; 
		}
	}  


}

void Graph::printMatrix(){

	cout << "-----Adjacency Matrix-----" << endl;

	for(int i = 0; i < station; i++)
	{
		for(int j = 0; j < station; j++)
		{	
			cout << setw(2) << myMatrix[i][j] << "  ";
		}

		cout << endl;
	}

	cout << "-----Floyd-Warshall Matrix-----" << endl;

	for(int i = 0; i < station; i++)
	{
		for(int j = 0; j < station; j++)
		{	
			cout << setw(2) << floydMatrix[i][j] << "  ";
		}

		cout << endl;
	}

	cout << "-----Reconstruction Matrix-----" << endl;

	for(int i = 0; i < station; i++)
	{
		for(int j = 0; j < station; j++)
		{	
			cout << setw(2) << reconstructMatrix[i][j] << "  ";
		}

		cout << endl;
	}
	cout << endl; 
}

// ADDS THE ROUTES TO BOTH THE ADJACENCY MATRIX & FLOYD-WARSHALL MATRIX
void Graph::addRoute(int from, int to, int weight){

	myMatrix[from][to] = weight; 

	floydMatrix[from][to] = weight;

	reconstructMatrix[from][to] = to;  
}

bool Graph::isRoute(int from, int to)  
{
	bool isPath = false;
	bool visited[station]; // DECLARED DYNAMICALLY WITH PROGRAM VARIABLE
	queue<int> vertices;

	//INITIALIZE  visited[ ]
	for(int i = 0; i < station ; i++){
		visited[i] = false;
	}

	visited[from] = true;  // MARK START INDEX AS VISITED
	vertices.push(from);   // ADD START INDEX TO QUEUE TO ENTER LOOP

	while(!vertices.empty() && isPath == false )
	{
		int currentInQueue;

		currentInQueue = vertices.front();                  
		vertices.pop();										

		cout << "Checking " << currentInQueue << endl;				

		for(int temp = 0; temp < station ; temp++)
		{
			
			//CHECK FOR 0 (empty nodes) SKIP IF 0
			if(myMatrix[currentInQueue][temp] != 0){       
															  
				//IF THIS NODE IS THE NUMBER WE ARE LOOKING FOR
				if(temp == to)
				{
					isPath = true;
					break;
				}
				//THIS IS NOT THE NODE BUT HAS THIS NODE BEEN VISITED?
				if(visited[temp] == false){ 				  

					//MARK AS VISITED
					visited[temp] = true;				    
					//ADD TO QUEUE
					vertices.push(temp);                    
				}

			}
		}
	}

	return isPath;
}

void Graph::calcShortestRoutes(){ 

	int i,j,k;

	for(k = 0; k < station; k++){

		for(i = 0; i < station; i++){

			for(j = 0; j < station; j++){
				
				if(floydMatrix[i][j] > floydMatrix[i][k] + floydMatrix[k][j]){

					floydMatrix[i][j] = floydMatrix[i][k] + floydMatrix[k][j];
					reconstructMatrix[i][j] = reconstructMatrix[i][k];  //RECONSTRUCTION MATRIX

				}

				//PREVIOUS CODE- ALTERNATE WAY 
				//if(i == j) continue;
				//floydMatrix[i][j]= min( floydMatrix[i][j], (floydMatrix[i][k] + floydMatrix[k][j]) );
			}
		}
	}
}

int Graph::shortestRoute(string src, string dst)
{
	int a = getStationId(src);
	int b = getStationId(dst);

	return floydMatrix[a][b];  

}

bool Graph::checkColors(string src)
{
	for( int i = 0; i < station; i++ ){ 

		if(stationColors[i] == src ){
			return true;
		}
	}
	return false;
}

void Graph::printPath(string src, string dst)
{
	/*  We are passing in strings.  These need to be converted to
	    ints.  The getStationId() function will accomplish this */
	int a = getStationId(src);
	int b = getStationId(dst);

	// the trainPath vector is initialized with 1 node to begin
	trainPath = vector<int>(1,0); 

	if(reconstructMatrix[a][b] == -1)
	{
		return; //?
	}

	trainPath[0] = a; // Initialize the first node

	while( a != b ){
		
		a = reconstructMatrix[a][b];
		trainPath.push_back(a);
	}

	cout << "Your path will be ";

	for( int i = 0 ; i < trainPath.size() ; i++ ){

		cout << getStationColors( trainPath[i] );

		 // DONT PRINT AN ARROW IF IT IS THE LAST NODE
		 if( i < trainPath.size() - 1){

		 		cout << "->" ;  
		 }		 	
	}
	cout << endl;
}

int Graph::getStationId(string color)
{
	int id = 0; //ID STARTS AT O FOR INDEX[0] IN ARRAY

	for( int i = 0; i < station; i++ ){  

		if(stationColors[i] == color){
			return id;
		}
		//INCREMENT ONLY IF NOT OUT OF BOUNDS OF ARRAY SIZE
		if(id < station)
		{
			id++; 
		}
	}
}

string Graph::getStationColors(int id){

	return stationColors[id];
}

void Graph::setStationColors(int id, string color){

	stationColors[id] = color;
}

//NEED TO DELETE DYNAMICALLY ALLOCATED MEMORY!
void Graph::deleteMatrix()
{
	for( int i=0 ; i < station ; i++ ){
		delete myMatrix[i];
	}

	delete myMatrix;

	for( int i=0 ; i < station ; i++ ){
		delete floydMatrix[i];
	}

	delete floydMatrix;

	for( int i=0 ; i < station ; i++ ){
		delete reconstructMatrix[i];
	}

	delete reconstructMatrix;


	delete[] stationColors;
	stationColors = NULL;

}
//----------------------------------------------------

int main( int argc, char **argv)
{

	//OPEN 1ST File------------------------------------------
	ifstream file;
	file.open("/home/mikecrbenton/Desktop/graph.txt"); //ORIGINAL PATH FROM ASSIGNMENT
	
	if(!file.is_open()){
		cout << "File Error";
		return -1;
	}

	int afile;
	int bfile;
	int cfile;

	file >> afile >> bfile;

	Graph mainMtrx = Graph(afile,bfile);

	while (file >> afile >> bfile >> cfile ){

		mainMtrx.addRoute(afile, bfile, cfile );
		//cout<< afile << " " << bfile << " " << cfile << endl;
	}

	//OPEN 2ND FILE---------------------------------------------
	ifstream file2;
	file2.open("/home/mikecrbenton/Desktop/names.txt"); //ORIGINAL PATH FROM ASSIGNMENT

	if(!file2.is_open()){
		cout << "File Error";
		return -1;
	}

	int num;
	string color;
	
	while ( file2 >> num >> color ){

		mainMtrx.setStationColors(num,color);
		//cout << num << color <<endl;
	}

	/* ONCE THE GRAPH BEING USED FOR THE FLOYD-WARSHALL ALGORITHM
	   HAS BEEN INITIALIZED( IN CONSTRUCTOR ) THE ALGORITHM NEEDS
	   TO BE RUN TO PRODUCE THE CORRECT  */
	mainMtrx.calcShortestRoutes();

	int choice = 1; //INITIALIZE TO ENTER WHILE LOOP

	while(choice == 1)
	{
		cout << "-- Menu --" << endl;

		cout << "     0 -> Exit" << endl;		
		cout << "     1 -> Print Menu" << endl;
		cout << "     2 -> Check if path exists" << endl;
		cout << "     ENTER: ";

		cin >> choice;

		if(choice == 0)
		{
			break;
		}

		if(choice == 2)
		{
			string source;
			string destination;

			cout << "\nFrom what station are you leaving: Red , Green , Blue , Purple, Yellow ?\n";
			cin >> source;

			//RUN A CHECK ON USER INPUT
			while(mainMtrx.checkColors(source) == false){
				cout << source << " is not a valid name- please enter again: ";
				cin >> source;
			}

			cout << "\nTo what station are you traveling: Red, Green, Blue Purple, Yellow ?\n";
			cin >> destination;

			//RUN A CHECK ON USER INPUT
			while(mainMtrx.checkColors(destination) == false){
				cout << destination << " is not a valid name- please enter again: ";
				cin >> destination;
			}
			

			//INTEGERS TO STORE SRC AND DST FOR GRAPH
			int a = mainMtrx.getStationId(source);
			int b = mainMtrx.getStationId(destination);

			//IF THERE IS A ROUTE 
			if( mainMtrx.isRoute(a,b) ){

				//RUN SHORTEST ROUTE
				int minRoute = mainMtrx.shortestRoute(source, destination);

				mainMtrx.printMatrix();
				cout << "There is a route between " << source << " and " << destination << " with a minimum distance of " << minRoute << " miles." << endl;
				mainMtrx.printPath(source, destination);
				cout << endl;
				choice = 1;
			}
			else{

				mainMtrx.printMatrix();
				cout << "There is no route between " << source << " and " << destination << endl;
				cout << endl;
				choice = 1;
			}
		}
	}

	mainMtrx.deleteMatrix();

	file.close();
	file2.close();

	return 0;
}

