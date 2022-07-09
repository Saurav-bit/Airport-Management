#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include<string>
//#include<bits/stdc++.h>
using namespace std;

class Airport {
public:
    string name;

    Airport(string name) {
        this->name = name;
    }
};

typedef Airport* PAirport;
typedef pair<int, PAirport> myPair;
int flag = 0;
int bo = 0;

map<PAirport, int> dist;
map<PAirport, PAirport> parent;

class Graph
{
    map<PAirport, vector<pair<PAirport, int>>> adj;
    void printAllUtils(PAirport src, PAirport dest, map<PAirport, bool> &visit, vector<string> &path, int &);

public:
    vector<PAirport> listOfAirports;

    void addFlight(PAirport u, PAirport v, int w, bool bidirected);
    void shortestPath(PAirport s, PAirport d);
    void addAirport(PAirport a);
    void printPaths(PAirport a, PAirport b);
    void viewMap();
    void PrintAllPaths(PAirport src, PAirport dest);
    PAirport SearchAirport(string abc);
};

void Graph::PrintAllPaths(PAirport src, PAirport dest)
{
    map<PAirport, bool>visit;
    vector<string>path(100);
    int path_index = 0;

    for (auto itr : listOfAirports)
    {
        visit[itr] = false;
    }
    printAllUtils(src, dest, visit, path, path_index);
}

void Graph::printAllUtils(PAirport src, PAirport dest, map<PAirport, bool> &visit, vector<string> &path, int &path_index)
{
    visit[src] = true;
    path[path_index] = src->name;
    path_index++;


    if (src->name.compare(dest->name) == 0)
    {
        //flag++;
        for (int i = 0; i < path_index; i++)
            cout << path[i] << "->";
        cout << endl;
    }
    else
    {
        for (pair<PAirport, int> i : adj[src])
        {
            if (visit[i.first] == false)
            {
                printAllUtils(i.first, dest, visit, path, path_index);
            }
        }

    }
    path_index--;
    visit[src] = false;

}

PAirport Graph::SearchAirport(string abc)
{
    int flag = 0;
    for (auto itr : listOfAirports)
    {

        if (itr->name.compare(abc) == 0)
        {
            flag = 1;
            return itr;
        }
    }
    if (flag == 0)
    {
        return NULL;
    }
    return NULL;
}

void Graph::addFlight(PAirport u, PAirport v, int w, bool bidirected = true)
{
    if (bidirected) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    } else {
        adj[u].push_back(make_pair(v, w));
    }

}

void Graph::addAirport(PAirport a) {
    listOfAirports.push_back(a);
}

void printPath(PAirport p) {
    if (parent[p] == nullptr) {
        return;
    }

    printPath(parent[p]);

    cout << p->name << "->";
}

bool doesPathExist(PAirport dest){

    //cout<<dist[dest]<<"\n";
    return dist[dest] != INT_MAX;
}

void Graph::shortestPath(PAirport src, PAirport dest)
{
    for (auto v : listOfAirports) {
        dist[v] = INT_MAX;
    }


    priority_queue<myPair, vector<myPair>, greater<myPair>> pq;

    pq.push(make_pair(0, src));
    dist[src] = 0;
    parent[src] = nullptr;

    while (!pq.empty())
    {
        PAirport u = pq.top().second;
        pq.pop();

        for (pair<PAirport, int> i : adj[u]) {


            PAirport v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    if(doesPathExist(dest)){
        cout << endl << "Shortest Flight Distance between " << src->name << " and " << dest->name << " is " << dist[dest] << endl << endl;

        cout << "Shortest Route is: " << src->name << "->";
        printPath(dest);
        cout << endl;
    }else{
        cout << "No Path Exist between " << src->name << " and " << dest->name << endl << endl;
    }

}

void Graph::viewMap()
{
    for (auto itr : listOfAirports)
    {
        cout << "\n\n" << itr->name << "\n" << endl;
    }
}

vector<PAirport> * getSourceAndDestinationAirports(Graph &g) {
    auto len = g.listOfAirports.size();
    bool validInput = false;
    int src = -1, dest = -1;

    while (!validInput) {
        cout << "List of Source Airports" << endl;

        for (int i = 0; i < g.listOfAirports.size(); i++) {
            cout << i + 1 << " " << g.listOfAirports[i]->name << endl;
        }
        cout << "Select Source Airport(1-" << len << ") : " << endl;
        cin >> src;

        cout << "List of Destination Airports" << endl;
        for (int i = 0; i < g.listOfAirports.size(); i++) {
            cout << i + 1 << " " << g.listOfAirports[i]->name << endl;
        }
        cout << "Select Destination Airport(1-" << len << ") : " << endl;
        cin >> dest;

        if (src == dest) {
            cout << "Source and Destination cannot be same" << endl;
            validInput = false;
            continue;
        }

        if (src >= 1 && src <= len && dest >= 1 && dest <= len) {
            validInput = true;
        }
    }



    PAirport srcAirport, destAirport;
    srcAirport = g.listOfAirports[src - 1];
    destAirport = g.listOfAirports[dest - 1];

    vector<PAirport> *srcAndDest = new vector<PAirport>;
    srcAndDest->push_back(srcAirport);
    srcAndDest->push_back(destAirport);

    return srcAndDest;
}



int main()
{
    Graph g;

    PAirport a1 = new Airport("New Delhi");
    PAirport a2 = new Airport("Mumbai");
    PAirport a3 = new Airport("Lucknow");
    PAirport a4 = new Airport("Chennai");
    g.addAirport(a1);
    g.addAirport(a2);
    g.addAirport(a3);
    g.addAirport(a4);

    g.addFlight(a1, a2, 500);
    g.addFlight(a2, a3, 150);
    g.addFlight(a1, a3, 100);
    g.addFlight(a1, a4, 600);

    char choice = 'y';
    do
    {
        int ch;
        cout << "\t\t\t\t WELCOME TO TuTORIAL AIRLINES\n" << endl;
        cout << "\t 1. To Get shortest Flight Distance to your destination" << endl;
        cout << "\t 2. To Add a new Airport" << endl;
        cout << "\t 3. To View all Routes" << endl;
        cout << "\t 4  To Add a new Flight" << endl;
        cout << "\t 5. To View the Airport List" << endl;
        cout << "\t 6. To View Fare Charges" << endl;
        cout << "\t 7. To Exit\n" << endl;
        cin >> ch;
        if (ch == 7)
        {
            exit(0);
        }
        else
        {
            switch (ch)
            {
                case 1:
                {
                    system("cls");
                    vector<PAirport> *srcAndDest = getSourceAndDestinationAirports(g);
                    PAirport srcAirport = (*srcAndDest)[0];
                    PAirport destAirport = (*srcAndDest)[1];
                    g.shortestPath(srcAirport, destAirport);
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "\n\n Enter Name of the New Airport\n" << endl;
                    string st;
                    cin >> st;
                    PAirport a5 = new Airport(st);
                    g.addAirport(a5);
                   dist[a5] = INT_MAX;
                    break;
                }
                case 3:
                {


                    vector<PAirport> *srcAndDest = getSourceAndDestinationAirports(g);
                    PAirport srcAirport = (*srcAndDest)[0];
                    PAirport destAirport = (*srcAndDest)[1];

                    if(doesPathExist(destAirport)){
                            //cout<<doesPathExist(destAirport)<<"\n";
                        g.PrintAllPaths(srcAirport, destAirport);
                    }else{
                        cout << "No Path Exist between " << srcAirport->name << " and " << destAirport->name << endl;
                    }

                    break;
                }
                case 4:
                {

                    vector<PAirport> *srcAndDest = getSourceAndDestinationAirports(g);
                    PAirport srcAirport = (*srcAndDest)[0];
                    PAirport destAirport = (*srcAndDest)[1];

                    int weight;
                    cout << "\n\nEnter Distance \n" << endl;
                    cin >> weight;

                    g.addFlight(srcAirport, destAirport, weight);
                    cout << "\n\nFlight added successfully\n\n" << endl;
                    break;
                }
                case 5:
                {
                    system("cls");
                    g.viewMap();
                    break;
                }
                case 6:
                {
                    cout << "\n\nFare is 10 rupee per kilometer \n" << endl;

                    break;

                }
            }
        }
        cout << "\n\n\nDo you want to go to the main page or not?(Y/N)\n";
        cin >> choice;
        system("cls");

    } while (choice == 'y' || choice == 'Y');

    for (auto &v : g.listOfAirports) {
        delete v;
    }

    return 0;
}

