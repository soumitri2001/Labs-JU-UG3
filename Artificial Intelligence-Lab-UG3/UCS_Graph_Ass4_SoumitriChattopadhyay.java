
/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 29/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 4.1 : UCS in Romanian Problem
 * ---------------------------------------------------------------------------
 * Question:
 *   1. Implement Uniform Cost Search on Romanian Travelling problem.
 *   2. Compare the algorithm's performance between uniform-cost search and Iterative Lengthening search, 
 *      and comment on your results. 
 * ---------------------------------------------------------------------------
 *  Compilation: javac UCS_Graph_Ass4_SoumitriChattopadhyay.java
 * ---------------------------------------------------------------------------
 * Execution: java UCS_Graph_Ass4_SoumitriChattopadhyay
 * ---------------------------------------------------------------------------
 * Input file: input_UCS_83.txt
 * 20
 * 0   75    0  118    0    0    0  140    0    0    0    0    0    0    0    0    0    0    0    0
 * 75    0   71    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 * 0   71    0    0    0    0    0  151    0    0    0    0    0    0    0    0    0    0    0    0
 * 118    0    0    0  111    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 * 0    0    0  111    0   70    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 * 0    0    0    0   70    0   75    0    0    0    0    0    0    0    0    0    0    0    0    0
 * 0    0    0    0    0   75    0    0    0    0  120    0    0    0    0    0    0    0    0    0
 * 140    0  151    0    0    0    0    0   80    0    0   99    0    0    0    0    0    0    0    0
 * 0    0    0    0    0    0    0   80    0   97  146    0    0    0    0    0    0    0    0    0
 * 0    0    0    0    0    0    0    0   97    0  138    0  101    0    0    0    0    0    0    0
 * 0    0    0    0    0    0  120    0  146  138    0    0    0    0    0    0    0    0    0    0
 * 0    0    0    0    0    0    0   99    0    0    0    0  211    0    0    0    0    0    0    0
 * 0    0    0    0    0    0    0    0    0  101    0  211    0   90   85    0    0    0    0    0
 * 0    0    0    0    0    0    0    0    0    0    0    0   90    0    0    0    0    0    0    0
 * 0    0    0    0    0    0    0    0    0    0    0    0   85    0    0  142    0    0   98    0
 * 0    0    0    0    0    0    0    0    0    0    0    0    0    0  142    0   92    0    0    0
 * 0    0    0    0    0    0    0    0    0    0    0    0    0    0    0   92    0   87    0    0
 * 0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0   87    0    0    0
 * 0    0    0    0    0    0    0    0    0    0    0    0    0    0   98    0    0    0    0   86
 * 0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0   86    0
 * 0
 * 12
 * ---------------------------------------------------------------------------
 * Output:
 * 
 * The Path between Arad and Bucharest is [Arad] ---> [Shibiu] ---> [Rimnicu-Vilcea] ---> [Pitesti] ---> [Bucharest]
 * The Distance between source and destination is 418.0
 * --------------------------------------------------------------------------- 
 */

import java.util.*;
import java.io.*;

public class UCS_Graph_Ass4_SoumitriChattopadhyay {

    static class Node implements Comparator<Node> {
        public int node;
        public int cost;

        public Node() {

        }

        public Node(int node, int cost) {
            this.node = node;
            this.cost = cost;
        }

        @Override
        public int compare(Node node1, Node node2) {
            if (node1.cost < node2.cost)
                return -1;
            if (node1.cost > node2.cost)
                return 1;
            if (node1.node < node2.node)
                return -1;
            return 0;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj instanceof Node) {
                Node node = (Node) obj;
                if (this.node == node.node) {
                    return true;
                }
            }
            return false;
        }
    }

    private PriorityQueue<Node> pq;
    private Set<Integer> settled;
    private int distances[];
    private int numberOfNodes;
    private int adjMatrix[][];
    private LinkedList<Integer> path;
    private int[] parent;
    private int source, destination;
    public static final int MAX_VALUE = 99999;

    public UCS_Graph_Ass4_SoumitriChattopadhyay(int numberOfNodes) {
        this.numberOfNodes = numberOfNodes;
        this.settled = new HashSet<Integer>();
        this.pq = new PriorityQueue<>(numberOfNodes, new Node());
        this.distances = new int[numberOfNodes + 1];
        this.path = new LinkedList<Integer>();
        this.adjMatrix = new int[numberOfNodes + 1][numberOfNodes + 1];
        this.parent = new int[numberOfNodes + 1];
    }

    public int uniformCostSearch(int adjMatrix[][], int source, int destination) {
        int evaluationNode;
        this.source = source;
        this.destination = destination;

        for (int i = 1; i <= numberOfNodes; i++) {
            distances[i] = MAX_VALUE;
        }

        for (int src = 1; src <= numberOfNodes; src++) {
            for (int dest = 1; dest <= numberOfNodes; dest++) {
                this.adjMatrix[src][dest] = adjMatrix[src][dest];
            }
        }

        pq.add(new Node(source, 0));
        distances[source] = 0;

        while (!pq.isEmpty()) {
            evaluationNode = getNodeWithMinDistance();
            System.out.println("The eval Node is " + evaluationNode);
            if (evaluationNode == destination) {
                return distances[destination];
            }
            settled.add(evaluationNode);
            addFrontiersToQueue(evaluationNode);
        }
        return distances[destination];
    }

    private void addFrontiersToQueue(int evaluationNode) {
        for (int dest = 1; dest <= numberOfNodes; dest++) {
            if (!settled.contains(dest)) {
                if (adjMatrix[evaluationNode][dest] != MAX_VALUE) {
                    if (distances[dest] > adjMatrix[evaluationNode][dest] + distances[evaluationNode]) {
                        distances[dest] = adjMatrix[evaluationNode][dest] + distances[evaluationNode];
                        parent[dest] = evaluationNode;
                    }

                    Node node = new Node(dest, distances[dest]);
                    if (pq.contains(node)) {
                        pq.remove(node);
                    }
                    pq.add(node);
                }
            }
        }
    }

    private int getNodeWithMinDistance() {
        Node node = pq.remove();
        return node.node;
    }

    public void printPath() {
        path.add(destination);
        boolean found = false;
        int vertex = destination;
        while (!found) {
            if (vertex == source) {
                found = true;
                continue;
            }
            path.add(parent[vertex]);
            vertex = parent[vertex];
        }

        System.out.println("The Path between " + source + " and " + destination + " is ");
        Iterator<Integer> iterator = path.descendingIterator();
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + "\t");
        }
    }

    public static void main(String args[]) throws Exception {
        int adjMatrix[][];
        int number_of_vertices;
        int source = 0;
        int destination = 0;
        int distance;
        Scanner sc = new Scanner(new File("input_UCS_83.txt"));
        try {
            // System.out.println("Enter the number of vertices");
            number_of_vertices = Integer.parseInt(sc.nextLine());

            adjMatrix = new int[number_of_vertices + 1][number_of_vertices + 1];
            // System.out.println("Enter the Weighted Matrix for the graph");
            for (int i = 1; i <= number_of_vertices; i++) {
                for (int j = 1; j <= number_of_vertices; j++) {
                    adjMatrix[i][j] = Integer.parseInt(sc.next());
                    if (i == j) {
                        adjMatrix[i][j] = 0;
                        continue;
                    }
                    if (adjMatrix[i][j] == 0) {
                        adjMatrix[i][j] = MAX_VALUE;
                    }
                }
            }

            // System.out.println("Enter the source ");
            source = Integer.parseInt(sc.nextLine());

            // System.out.println("Enter the destination");
            destination = Integer.parseInt(sc.nextLine());

            UCS_Graph_Ass4_SoumitriChattopadhyay uniformCostSearch = new UCS_Graph_Ass4_SoumitriChattopadhyay(
                    number_of_vertices);
            distance = uniformCostSearch.uniformCostSearch(adjMatrix, source, destination);
            uniformCostSearch.printPath();

            System.out.println(
                    "\nThe Distance between source " + source + " and destination " + destination + " is " + distance);

        } catch (InputMismatchException inputMismatch) {
            System.out.println("Wrong Input Format");
        }
        sc.close();
    }
}
