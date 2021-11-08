
/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 13/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 1 : BFS Code in Java
 * ---------------------------------------------------------------------------
 * Assignment : 
 *   1. You have to consider an adjacency matrix of your own choice. 
 *      (minimum number of node is 7).
 *   2. Matrix will be written in a File and will be given as input.
 *   3. There will be one source node and one destination node as input.
 *   4. The output will be the path from source to destination following BFS.
 * ---------------------------------------------------------------------------
 * Input file : input_Roll83.txt
 *  7
 * 0010000
 * 0001000
 * 1000110
 * 0100100
 * 0011010
 * 0010101
 * 0000010
 * 1
 * 2
 * ---------------------------------------------------------------------------
 * Compilation: javac BFS_AI_Ass1_Roll83.java
 * ---------------------------------------------------------------------------
 * Execution: java BFS_AI_Ass1_Roll83
 * ---------------------------------------------------------------------------
 * Output:
 * Path from Node 1 to Node 2 is:
 * 1 --> 3 --> 4 --> 2
 * ---------------------------------------------------------------------------
 */

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class BFS_AI_Ass1_Roll83 {

    private static void bfs(int adjMatrix[][], int src, int dest, int v) {

        // trivial case: if source and destination nodes are the same
        if (src == dest) {
            System.out.println("Source and destination overlap !!");
            return;
        }

        // initialize array to keep track of visited nodes
        boolean[] visited = new boolean[v];
        Arrays.fill(visited, false);

        // initializing queue for BFS
        Queue<Integer> q = new LinkedList<>();

        // pushing the source node
        q.add(src);

        // initializing array for parent nodes
        int parent[] = new int[v];
        for (int i = 0; i < v; i++) {
            parent[i] = i;
        }

        // set parent of source node as -1 (as we don't need its parent)
        parent[src] = -1;

        // source node already visited, so mark as true
        visited[src] = true;
        int vis;
        boolean flag = false;

        // BFS code starts here
        while (!q.isEmpty()) {

            // poll top of queue
            vis = q.poll();

            // traverse through all connected nodes
            for (int i = 0; i < v; i++) {
                // if edge exists and node unvisited, add node to queue
                if (adjMatrix[vis][i] == 1 && (!visited[i])) {
                    q.add(i);
                    visited[i] = true;
                    parent[i] = vis;

                    // check if destination is reached
                    if (i == dest) {
                        flag = true;
                        break;
                    }
                }
            }
            if (flag == true) {
                break;
            }
        }

        // if flag is still false, it means no path present => return from function
        if (flag == false) {
            System.out.println("No path present !!");
            return;
        }

        // to generate the path from source to destination
        ArrayList<Integer> result = new ArrayList<>();
        while (parent[dest] != -1) {
            result.add(dest);
            dest = parent[dest];
        }
        result.add(src);

        // reverse the list to get path in proper direction
        Collections.reverse(result);

        // print path
        for (int i = 0; i < result.size(); i++) {
            System.out.print(result.get(i));
            if (i < result.size() - 1)
                System.out.print(" --> ");
        }
        System.out.println();
    }

    // Driver code
    public static void main(String[] args) throws Exception {
        // read the text file containing input
        File file = new File("./input_Roll83.txt");
        Scanner sc = new Scanner(file);

        // set delimiter for file parsing
        sc.useDelimiter("\\n");

        // get the size of adjacency matrix
        int N = Integer.parseInt(sc.nextLine());

        // initialize adjacency matrix
        int adjMatrix[][] = new int[N][N];
        int idx = 0;

        // parse the text file
        while (sc.hasNext()) {
            // extract each line of the adjacency matrix
            String str = sc.nextLine();
            char arr[] = str.toCharArray();

            // construct the adjacency matrix
            for (int i = 0; i < N; i++) {
                adjMatrix[idx][i] = arr[i] - '0';
            }
            idx++;

            // if adjacency matrix is parsed, exit
            if (idx == N) {
                break;
            }
        }

        // parse the source and destination nodes
        int src = Integer.parseInt(sc.nextLine());
        int dest = Integer.parseInt(sc.nextLine());

        System.out.println("Path from Node " + src + " to Node " + dest + " is:");

        // call BFS function for getting path
        bfs(adjMatrix, src, dest, N);

        sc.close();
    }
}