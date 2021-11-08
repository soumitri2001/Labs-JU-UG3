
/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 15/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 2 : DFS Code in Java
 * ---------------------------------------------------------------------------
 * Question:
 *   1. Draw a graph (Minimum node is 10)
 *   2. Generate adjacency matrix of the graph.
 *   3. Matrix will be written in a File and will be given as input.
 *   4. There will be one source node and one destination node as input.
 *   5. The output will be the path from source to destination following DFS
 * 
 * Submission: 
 *   1. Graph you have considered
 *   2. Input Adjacency Matrix
 *   3. Display the output of the path in the program execution
 *   4. Mark the path in the graph
 *   5. Java files
 * ---------------------------------------------------------------------------
 * Input file : input_DFS_AI_Ass2.txt
 * 10
 * 0100000000
 * 1010000000
 * 0100000101
 * 0000100000
 * 0001010001
 * 0000101000
 * 0000010110
 * 0010001000
 * 0000001000
 * 0010100000
 * 4
 * 8
 * ---------------------------------------------------------------------------
 *  Compilation: javac DFS_AI_Ass2_SoumitriChattopadhyay.java
 * ---------------------------------------------------------------------------
 * Execution: java DFS_AI_Ass2_SoumitriChattopadhyay
 * ---------------------------------------------------------------------------
 * Output:
 * Path from Node 4 to Node 8 is:
 * 4 --> 9 --> 2 --> 7 --> 6 --> 8
 * ---------------------------------------------------------------------------
 */

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.ArrayDeque;
import java.util.Scanner;

class DFS_AI_Ass2_SoumitriChattopadhyay {

    private static void dfs(int adjMatrix[][], int src, int dest, int N) {

        // trivial case: if source and destination nodes are the same
        if (src == dest) {
            System.out.println("Source and destination overlap");
            return;
        }

        // initialize array to keep track of visited nodes
        boolean[] visited = new boolean[N];
        Arrays.fill(visited, false);

        // initializing stack for DFS
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        stack.push(src);

        // initializing array for parent nodes
        int parent[] = new int[N];
        for (int i = 0; i < N; i++) {
            parent[i] = i;
        }

        // set parent of source node as -1 (as we don't need its parent
        parent[src] = -1;

        // marking source node as visited
        visited[src] = true;
        int vis;
        boolean flag = false;

        // DFS code starts here
        while (!stack.isEmpty()) {

            // process current node
            vis = stack.pop();
            visited[vis] = true;

            // iterate through the neighbor nodes
            for (int i = 0; i < N; i++) {
                // visit node if edge exists and is unvisited
                if (adjMatrix[vis][i] == 1 && (!visited[i])) {
                    stack.push(i);
                    parent[i] = vis;

                    // check if destination node is reached
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

        // check if path is still not found
        if (flag == false) {
            System.out.println("No Path Exists!");
            return;
        }

        // to generate the path from source to destination
        ArrayList<Integer> result = new ArrayList<>();
        while (parent[dest] != -1) {
            result.add(dest);
            dest = parent[dest];
        }
        result.add(src);

        // reverse result as we need the path from the source to the dest
        Collections.reverse(result);

        // printing the result
        for (int i = 0; i < result.size(); i++) {
            System.out.print(result.get(i));
            if (i < result.size() - 1)
                System.out.print(" --> ");
        }
        System.out.println();
    }

    public static void main(String[] args) throws Exception {

        // open the file which has the adjacency matrix and the source and destination
        File file = new File("./input_DFS_AI_Ass2.txt");
        Scanner sc = new Scanner(file);

        // delimiter for parsing
        sc.useDelimiter("\\n");

        // get the size of adjacency matrix
        int N = Integer.parseInt(sc.nextLine());

        // initialize adjacency matrix
        int adjMatrix[][] = new int[N][N];
        int index = 0;

        // reading from the file and storing it into the input matrix
        while (sc.hasNext()) {
            // extract each line of the adjacency matrix
            String str = sc.nextLine();
            char arr[] = str.toCharArray();

            // construct the adjacency matrix
            for (int i = 0; i < N; i++) {
                adjMatrix[index][i] = arr[i] - '0';
            }
            index++;

            // if adjacency matrix is parsed, exit
            if (index == N) {
                break;
            }
        }

        // parse the source and destination nodes
        int src = Integer.parseInt(sc.nextLine());
        int dest = Integer.parseInt(sc.nextLine());

        System.out.println("The Path from Node " + src + " to Node " + dest + " is:");

        // call DFS function to find the path
        dfs(adjMatrix, src, dest, N);

        sc.close();
    }
}
