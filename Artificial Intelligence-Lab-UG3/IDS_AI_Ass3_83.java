
/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 25/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 3 : Iterative Deepening Search
 * ---------------------------------------------------------------------------
 * Question:
 * Please use the following graph for the assignment.
 * Things to do:
 * 1. Implement the iterative deepening algorithm
 * 2. Execute the implementation on the attached graph with depth 5
 * 3. Execute the previously implemented DFS with depth 5 on the same graph 
 *    presented here.
 * 4. For both points 2 and 3, the graph will be written in a file and 
 *    not in the program implementation
 * 5. Write a document based on your observations of output 2 and the 
 *    difference between the outputs of points 2 and 3.
 * ---------------------------------------------------------------------------
 * Input file : input_AI_Ass3_83.txt
 *   12
 *   4
 *   S 011100000000
 *   p 000010000000
 *   e 000001100000
 *   d 000000001100
 *   q 000000000000
 *   h 010010000000
 *   r 000000010000
 *   f 000000000101
 *   b 000000000010
 *   c 000000000010
 *   a 000000000000
 *   G 000000000000
 *   S
 *   G
 * ---------------------------------------------------------------------------
 *  Compilation: javac IDS_AI_Ass3_83.java
 * ---------------------------------------------------------------------------
 * Execution: java IDS_AI_Ass3_83
 * ---------------------------------------------------------------------------
 * Output:
 * 
 * Finding the Path from Source [S] to Destination [G] using IDS [max depth = 4] ...

 * At Depth 0:     [S]
 * At Depth 1:     [S] -> [p] -> [e] -> [d]
 * At Depth 2:     [S] -> [p] -> [q] -> [e] -> [h] -> [r] -> [d] -> [b] -> [c]
 * At Depth 3:     [S] -> [p] -> [q] -> [e] -> [h] -> [p] -> [q] -> [r] -> [f] -> [d] -> [b] -> [a] -> [c] -> [a]
 * At Depth 4:     [S] -> [p] -> [q] -> [e] -> [h] -> [p] -> [q] -> [q] -> [r] -> [f] -> [c] -> [G]
 * 
 * Destination [G] Found at depth 4
 * ---------------------------------------------------------------------------
 */

import java.util.*;
import java.io.*;

public class IDS_AI_Ass3_83 {
    private ArrayDeque<Integer> stack;
    private int N;
    private int currDepth;
    private int maxDepth;
    private int depthLimit = 4; // as specified in question
    private boolean destFound_flag;

    public IDS_AI_Ass3_83() {
        stack = new ArrayDeque<Integer>();
    }

    public void iterativeDeepeningSearch(int adjMatrix[][], char nodeNames[], int source, int destination) {
        N = adjMatrix[0].length;
        while (!destFound_flag) {
            depthLimitedSearch(adjMatrix, nodeNames, 0, destination);
            maxDepth++;
            if (destFound_flag) {
                System.out.println("\n\nDestination [G] Found at depth " + currDepth);
                return;
            }
            if (maxDepth > depthLimit) {
                return;
            }
        }
        // if(destFound_flag == false)
        // System.out.println("\n\nDestination [G] NOT found with given max depth value
        // of " + depthLimit);
    }

    private void depthLimitedSearch(int adjMatrix[][], char nodeNames[], int source, int destination) {
        int element, currNode = 0;
        int[] visited = new int[N];
        stack.push(source);
        currDepth = 0;
        System.out.print("\nAt Depth " + maxDepth + ":\t");
        System.out.print("[" + nodeNames[source] + "]");

        while (!stack.isEmpty()) {
            element = stack.peek();
            while (currNode < N) {
                if (currDepth < maxDepth) {
                    if (adjMatrix[element][currNode] == 1) {
                        stack.push(currNode);
                        visited[currNode] = 1;
                        System.out.print(" -> [" + nodeNames[currNode] + "]");
                        currDepth++;
                        if (destination == currNode) {
                            destFound_flag = true;
                            return;
                        }
                        element = currNode;
                        currNode = 0;
                        continue;
                    }
                } else {
                    break;
                }
                currNode++;
            }
            currNode = stack.pop() + 1;
            currDepth--;
        }
    }

    public static void main(String args[]) throws Exception {
        File file = new File("./input_AI_Ass3_83.txt");
        Scanner sc = new Scanner(file);

        // delimiter for file parsing
        sc.useDelimiter("\\n");
        int N = Integer.parseInt(sc.nextLine().trim());
        int maxDepth = Integer.parseInt(sc.nextLine().trim());
        int adjMatrix[][] = new int[N][N];
        char nodeNames[] = new char[N];
        HashMap<Character, Integer> nodeIndex = new HashMap<>();
        int index = 0;

        // reading from the file and storing it into the input adjMatrix
        while (sc.hasNext()) {

            String str[] = sc.nextLine().trim().split(" ");
            char node = str[0].charAt(0);
            char arr[] = str[1].toCharArray();
            nodeNames[index] = node;
            nodeIndex.put(node, index);
            for (int i = 0; i < N; i++) {
                adjMatrix[index][i] = arr[i] - '0';
            }
            index++;
            if (index == N) {
                break;
            }
        }

        // for (int i = 0; i < N; i++) {
        // System.out.print(nodeNames[i] + ": ");
        // for (int j = 0; j < N; j++) {
        // System.out.print(adjMatrix[i][j] + " ");
        // }
        // System.out.println();
        // }

        char src = sc.nextLine().trim().charAt(0); // source
        char dest = sc.nextLine().trim().charAt(0); // destination

        // convert to node indices for searching
        int source = nodeIndex.get(src), destination = nodeIndex.get(dest);

        System.out.println(
                "\nFinding the Path from Source [S] to Destination [G] using IDS [max depth = " + maxDepth + "] ...");

        IDS_AI_Ass3_83 ob = new IDS_AI_Ass3_83();

        // setting the initial attributes
        ob.depthLimit = maxDepth;
        ob.destFound_flag = false;
        ob.N = adjMatrix[0].length;

        ob.iterativeDeepeningSearch(adjMatrix, nodeNames, source, destination);

        if (ob.destFound_flag == false) {
            System.out.println("\n\nDestination [G] NOT found with given max depth value of " + ob.depthLimit);
        }

        sc.close();
    }
}
