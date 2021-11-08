
/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 30/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 4.1 : Iterative Lengthening in Romanian Problem
 * ---------------------------------------------------------------------------
 * Question:
 *   1. Implement Iterative Lengthening Algorithm on Romanian Travelling problem.
 *   2. Compare the algorithm's performance between uniform-cost search and Iterative Lengthening search, 
 *      and comment on your results.   
 * ---------------------------------------------------------------------------
 * Input text file : input_Graph_83.txt
 *  20
 *  Arad    Bucharest
 *  500
 *  Arad              0   75    0  118    0    0    0  140    0    0    0    0    0    0    0    0    0    0    0    0
 *  Zerind           75    0   71    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 *  Oradea            0   71    0    0    0    0    0  151    0    0    0    0    0    0    0    0    0    0    0    0
 *  Timisoara       118    0    0    0  111    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 *  Lugoj             0    0    0  111    0   70    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 *  Mehadia           0    0    0    0   70    0   75    0    0    0    0    0    0    0    0    0    0    0    0    0
 *  Dobreata          0    0    0    0    0   75    0    0    0    0  120    0    0    0    0    0    0    0    0    0
 *  Shibiu          140    0  151    0    0    0    0    0   80    0    0   99    0    0    0    0    0    0    0    0
 *  Rimnicu-Vilcea    0    0    0    0    0    0    0   80    0   97  146    0    0    0    0    0    0    0    0    0
 *  Pitesti           0    0    0    0    0    0    0    0   97    0  138    0  101    0    0    0    0    0    0    0
 *  Craiova           0    0    0    0    0    0  120    0  146  138    0    0    0    0    0    0    0    0    0    0
 *  Fagaras           0    0    0    0    0    0    0   99    0    0    0    0  211    0    0    0    0    0    0    0
 *  Bucharest         0    0    0    0    0    0    0    0    0  101    0  211    0   90   85    0    0    0    0    0
 *  Giurgiu           0    0    0    0    0    0    0    0    0    0    0    0   90    0    0    0    0    0    0    0
 *  Urziceni          0    0    0    0    0    0    0    0    0    0    0    0   85    0    0  142    0    0   98    0
 *  Vaslui            0    0    0    0    0    0    0    0    0    0    0    0    0    0  142    0   92    0    0    0
 *  Iasi              0    0    0    0    0    0    0    0    0    0    0    0    0    0    0   92    0   87    0    0
 *  Neamt             0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0   87    0    0    0
 *  Hirsova           0    0    0    0    0    0    0    0    0    0    0    0    0    0   98    0    0    0    0   86
 *  Eforie            0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0   86    0
 * ---------------------------------------------------------------------------
 * Compilation sequence: javac IterativeLengthening_Ass4_SoumitriChattopadhyay.java
 * ---------------------------------------------------------------------------
 * Execution sequence: java IterativeLengthening_Ass4_SoumitriChattopadhyay
 * ---------------------------------------------------------------------------
 * Output:
 * Source city: Arad
 * Destination city: Bucharest
 * Cost of optimal path: 500.0
 * 
 * For cost limit: 0.0
 * No Path Found
 * For cost limit: 0.0
 * No Path Found
 * For cost limit: 75.0
 * No Path Found
 * For cost limit: 118.0
 * No Path Found
 * For cost limit: 140.0
 * No Path Found
 * For cost limit: 146.0
 * No Path Found
 * For cost limit: 220.0
 * No Path Found
 * For cost limit: 229.0
 * No Path Found
 * For cost limit: 239.0
 * No Path Found
 * For cost limit: 299.0
 * No Path Found
 * For cost limit: 317.0
 * No Path Found
 * For cost limit: 366.0
 * No Path Found
 * For cost limit: 374.0
 * No Path Found
 * For cost limit: 418.0
 * 
 * Path Taken:
 * [Arad] -> [Shibiu] -> [Rimnicu-Vilcea] -> [Pitesti] -> [Bucharest]
 * -------------------------------------------------------------------------
 */

import java.io.*;
import java.util.*;

class IterativeLengthening_Ass4_SoumitriChattopadhyay {

    // edge class storing the city names and connecting edge weight
    static class Edge implements Comparable<Edge> {
        public double weight; // weight
        public final int u; // city 1
        public final int v; // city 2

        Edge(int u, int v, double weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge n) {
            return Double.compare(this.weight, n.weight);
        }
    }

    private int[][] adjMatrix;
    private String[] names;
    private double currLimit;
    private double nextLimit;
    private double num_iter;

    IterativeLengthening_Ass4_SoumitriChattopadhyay(int[][] arr, String[] names) {
        adjMatrix = arr;
        this.names = names;
        this.num_iter = 0;
    }

    // function to perform the Uniform Cost Search Algorithm
    public ArrayList<Integer> search_UCS(String source, String destination, double max_limit) {

        int src = indexOf(source); // index of source city
        int dest = indexOf(destination); // index of destination city
        // check error
        if (src == -1 || dest == -1) {
            System.out.println("Node is out of range");
            System.exit(0);
        }

        int noOfNodes = adjMatrix.length;
        boolean[] visited = new boolean[noOfNodes];
        int edgeTo[] = new int[noOfNodes];

        PriorityQueue<Edge> pq = new PriorityQueue<>(); // stores edges in order of their weights
        ArrayList<Integer> path = new ArrayList<>(); // stores path

        pq.add(new Edge(-1, src, 0));

        while (!pq.isEmpty()) {
            this.num_iter++;

            Edge n = pq.poll();

            // check if the edge is visited
            if (visited[n.v]) {
                continue;
            } else if (n.weight > currLimit) {
                nextLimit = Double.min(nextLimit, n.weight);
                continue;
            }

            edgeTo[n.v] = n.u;
            visited[n.v] = true;

            // destination city reached
            if (n.v == dest) {
                int i = n.v;
                while (i != src) {
                    path.add(i);
                    i = edgeTo[i];
                }
                path.add(src);
                Collections.reverse(path); // reversing the order of path from source to destination
                return path;
            }

            for (int i = 0; i < noOfNodes; i++) {
                if (!visited[i] && adjMatrix[n.v][i] != 0) {
                    // add edge to priority queue where weight is equals previous weight and current
                    // weight
                    pq.add(new Edge(n.v, i, n.weight + adjMatrix[n.v][i]));
                }
            }
        }
        return null;
    }

    // function performing the Iterative Lengthening Search algorithm
    public ArrayList<Integer> search_ILS(String source, String destination, double max_cost) {
        ArrayList<Integer> path = null;
        this.currLimit = 0;
        while (currLimit < max_cost) {
            System.out.println("For cost limit: " + currLimit);
            path = this.search_UCS(source, destination, currLimit); // call Uniform Cost Search function
            if (path != null) {
                break;
            }
            System.out.println("No Path Found");
            currLimit = nextLimit;
            nextLimit = Double.POSITIVE_INFINITY;
        }
        return path;
    }

    // function to convert city name to corresponding indices
    private int indexOf(String s) {
        for (int i = 0; i < this.names.length; i++)
            if (this.names[i].equals(s))
                return i;
        return -1;
    }

    // function to print the path between source and destination
    public void printPath(String source, String dest, double max_cost) {
        ArrayList<Integer> path = this.search_ILS(source, dest, max_cost); // calling Iterative Lengthening method

        if (path != null) {
            // printing path
            System.out.print("\nPath Taken:\n");
            for (int i = 0; i < path.size(); i++) {
                String postfix = (i == path.size() - 1) ? "" : " -> ";
                System.out.print("[" + this.names[path.get(i)] + "]" + postfix);
            }
            System.out.println("\n");
        }
    }

    public static void main(String[] args) throws FileNotFoundException {

        Scanner sc = new Scanner(new File("input_Graph_83.txt"));

        int dimension = sc.nextInt(); // number of cities
        String source, destination;

        source = sc.next(); // source name
        destination = sc.next(); // destination name
        double max_cost = sc.nextDouble(); // maximum cost
        String[] names = new String[dimension]; // city name array

        int[][] adjacencyMatrix = new int[dimension][dimension]; // adjacency matrix

        for (int i = 0; i < dimension; i++) {
            names[i] = sc.next(); // name input
            for (int j = 0; j < dimension; j++) {
                adjacencyMatrix[i][j] = sc.nextInt(); // graph connections input
            }
        }
        IterativeLengthening_Ass4_SoumitriChattopadhyay search = new IterativeLengthening_Ass4_SoumitriChattopadhyay(
                adjacencyMatrix, names);

        // outputs
        System.out.println("\nSource city: " + source);
        System.out.println("Destination city: " + destination);
        System.out.println("Cost of optimal path: " + max_cost);

        System.out.println();
        // path from source to destination
        search.printPath(source, destination, max_cost);
    }
}