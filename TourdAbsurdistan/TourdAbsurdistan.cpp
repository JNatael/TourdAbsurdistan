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

//Brute force it, because it's at most 8 cities so it's doable
void test_paths(int city_count, int visited_count, int current_city, long long total_distance, int **distances, int cities_visited_order[8],
    bool cities_visited[8], long long &min_distance, int (&final_cities_visited_list)[8]) {
    if (visited_count == city_count) { //If we've visited everywhere
        total_distance += distances[current_city][0]; //Add distance back to 0 to this route
        if (total_distance < min_distance) { //If the distance of this route is shorter than the total
            min_distance = total_distance; //Set the min to this current total
                for (int i = 1; i < city_count; i++) { //Skip 0 as it's always the same
                    final_cities_visited_list[i] = cities_visited_order[i]; //Rewrite the order of visiting to this list
                }
                return;
        }
    }

    //Iterate through the cities
    for (int i = 1; i < city_count; i++) { //Start from 1 because we begin in city 0
        if (!cities_visited[i] && i != current_city) { //If this city is a new one
            //Set up variables to pass in to recursion based on this city
            int next_city = i; //Initialize next city    
            int new_visited_count = visited_count + 1;
            long long new_total_distance = total_distance + distances[current_city][i];
            int new_cities_visited_order[8];
            bool new_cities_visited[8];
            for (int j = 0; j < city_count; j++) { //Copy already visited cities into array
                new_cities_visited_order[j] = cities_visited_order[j];
                new_cities_visited[j] = cities_visited[j]; //Copy cities visited into bool array
            }
            new_cities_visited_order[visited_count] = next_city;
            new_cities_visited[next_city] = true; //Mark next city visited
            test_paths(city_count, new_visited_count, next_city, new_total_distance, distances, new_cities_visited_order, new_cities_visited, min_distance, final_cities_visited_list);
        }
    }
    return;
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
        int cities_visited_order[8];

        // Iterate over inputs
        for (int j = 0; j < n; j++) {
            distances[j] = new int[n]; //Initialize array rows
            readlineofints(n,distances[j]); //Read inputs into said rows
            cities_visited[j] = false;
        }

        int current_city = 0; //Initialize starting city
        int total_cities_visited = 1; //Initialize visited count at 1 (starting city)
        cities_visited_order[0] = 0; //Set first city to 0
        cities_visited[0] = true; //Note that we've been to the starting city
        long long min_distance = 9223372036854775807; //Initialize min distance to max long long value
        int final_cities_visited_list[8]; //Initialize list of cities visited
        final_cities_visited_list[0]=0; //Start the list with the starting city
        long long total_distance = 0;
        //Recurse
        test_paths(n,total_cities_visited,current_city,total_distance, distances, cities_visited_order,cities_visited, min_distance, final_cities_visited_list); //Check the cities visited

        //Delete the heap arrays
        for (int i = 0; i < n; ++i) {
            delete[] distances[i];
        }
        delete[] distances;

        //Print output
        std::cout << "Case #" << i << ": ";
        for (int i = 0; i < n;i++) {
            std::cout << final_cities_visited_list[i]+1 << " "; //Increment to offset for indexing
        }        
        std::cout << std::endl;
    }
    return 0;
}