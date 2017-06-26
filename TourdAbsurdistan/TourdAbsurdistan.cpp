//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<int> readlineofints(int count) {
    // Input values
    vector<int> linevalues(count);
    for (int j = 0; j < count; j++) {
        int val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}

/*
This function reads a line of int values into an int array that's already been initialized and which is taken as an input.
*/
void readlineofints(int count, int *array) {
    // Input values
    for (int j = 0; j < count; j++) {
        int val;
        cin >> val;
        array[j] = val;
    }
}


void test_paths(int city_count,int visited_count,int **distances, bool cities_visited[8],long long &min_distance, int &cities_visited_list) {   
    for (int i = 0; i < city_count; i++) {
        int shortest_next_dist = 10000; //Initialized to effective infinity (based on problem inputs)
        int next_city = -1; //Initialize next city
    }
    
    while (total_cities_visited < n) { //While we haven't visited all cities
        
        for (int k = 0; k < n; k++) {
            //If we haven't visited the next city, and the distance there is shorter than the current shortest
            if (k != current_city && !cities_visited[k] && distances[current_city][k] < shortest_next_dist) {
                shortest_next_dist = distances[current_city][k]; //Set shortest distance to this city
                next_city = k; //Mark this city as the next one
            }
        }
        //After finding shortest distance, go to that city and mark it visited
        current_city = next_city; //Go to next city
        cities_visited[next_city] = true; //Mark it visited
        cities_visited_list.push_back(next_city); //Log it as the next city
        total_cities_visited++; //Increment cities visited
    }

}


int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    // loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<int> params = readlineofints(1);
        int n = params[0];
        

        int** distances = new int*[n]; //Initialize array columns
        bool cities_visited[8];

        // Iterate over inputs
        for (int j = 0; j < n; j++) {
            distances[j] = new int[n]; //Initialize array rows
            readlineofints(n,distances[j]); //Read inputs into said rows
            cities_visited[j] = false;
        }

        int current_city = 0; //Initialize starting city
        int total_cities_visited = 1; //Initialize visited count at 1 (starting city)
        cities_visited[0] = true; //Note that we've been to the starting city
        long long min_distance = 9223372036854775807; //Initialize min distance to max long long value
        int cities_visited_list[8]; //Initialize list of cities visited
        cities_visited_list[0]=0; //Start the list with the starting city
        test_paths(n,total_cities_visited, distances, cities_visited, min_distance, cities_visited_list); //Check the cities visited

        //Delete the heap arrays
        for (int i = 0; i < n; ++i) {
            delete[] distances[i];
        }
        delete[] distances;

        //Print output
        std::cout << "Case #" << i << ": ";
        for(auto city : cities_visited_list){
            std::cout << city+1 << " "; //Increment to offset for indexing
        }        
        std::cout << std::endl;
    }
    return 0;
}