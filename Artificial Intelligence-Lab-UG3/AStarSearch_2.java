
/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 30/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 4.2 : Best FS to solve 8 puzzle problem
 * ---------------------------------------------------------------------------
 * Question: Use BFS (Best FS) to solve 8 puzzle problems.
 * 
 * Where Goal State is:
 * 1 2 3
 * 8 0 4
 * 7 6 5
 * 
 * Start State is:
 * 1 2 3
 * 8 6 4
 * 7 5 0
 * 
 * Other example states can be:
 * 5 4 0
 * 6 1 8
 * 7 3 2
 * 
 * Heuristic cost functions can be:
 * h1(N) = Number of misplaced tiles (doesn't include empty tile)
 * e.g. h1(s) = 7
 * h2(N) = Number of tiles out of rows + Number of tiles out of columns
 * h3(N) = Sum of the (Manhattan) distances of every tile to its goal position (doesn't include empty tile)
 * e.g. h3(s) = 4 + 2 + 2 + 2 + 2 + 0 + 3 + 3 = 18
 * h4(N) = Sum of Eucledian distances of the tiles from their goal positions (doesn't include empty tile)
 * ---------------------------------------------------------------------------
 * Compilation: javac BestFirstSearch_Ass4_SoumitriChattopadhyay.java
 * ---------------------------------------------------------------------------
 * Execution: java BestFirstSearch_Ass4_SoumitriChattopadhyay
 * ---------------------------------------------------------------------------
 * Output:
 * The path from starting state to goal state is:
 * 
 * -----
 * 1 2 3 
 * 8 6 4 
 * 7 5 0 
 * -----
 *   |  
 *   |  
 *   V  
 * -----
 * 1 2 3 
 * 8 6 4 
 * 7 0 5 
 * -----
 *   |  
 *   |  
 *   V  
 * -----
 * 1 2 3 
 * 8 0 4 
 * 7 6 5 
 * -----
 *
 * The Path length from starting state to goal state using BestFS is: 2
 * ---------------------------------------------------------------------------
 */

import java.util.*;

public class AStarSearch_2 {

    public static void print(int matrix[][]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void printIntermediateStates(ArrayList<int[][]> matrix) {
        System.out.println("\nThe path from starting state to goal state is:\n");
        for (int i = 0; i < matrix.size(); i++) {
            System.out.println("-----");
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    System.out.print(matrix.get(i)[j][k] + " ");
                }
                System.out.println();
            }
            System.out.println("-----");
            if (i != matrix.size() - 1) {
                System.out.println("  |  ");
                System.out.println("  |  ");
                System.out.println("  V  ");
            }
        }
    }

    public static void findCurrPosZero(int matrix[][], int arr[]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matrix[i][j] == 0) {
                    arr[0] = i;
                    arr[1] = j;
                    break;
                }
            }
        }
    }

    static class Pair {
        int x, y;

        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static HashMap<Integer, Pair> stateCoordinates = new HashMap<>(), goalCoordinates = new HashMap<>();

    public static int getHeuristicValue(int A[][], int B[][]) {
        int heuristic = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                stateCoordinates.put(A[i][j], new Pair(i, j));
                goalCoordinates.put(B[i][j], new Pair(i, j));
            }
        }
        for (Integer key : stateCoordinates.keySet()) {
            if (goalCoordinates.containsKey(key)) {
                heuristic += Math.abs(stateCoordinates.get(key).x - goalCoordinates.get(key).x)
                        + Math.abs(stateCoordinates.get(key).y - goalCoordinates.get(key).y);
            }
        }

        return heuristic;
    }

    public static int[][] copyMatrix(int matrix[][]) {
        int temp[][] = new int[3][3];
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                temp[i][j] = matrix[i][j];
            }
        }
        return temp;
    }

    public static int[][] swapTiles(int mat[][], int currX, int currY, int tempX, int tempY) {
        // swap zero with non-zero tile
        int temp[][] = new int[3][3];
        temp = copyMatrix(mat);
        int tmp = mat[currX][currY];
        temp[currX][currY] = temp[tempX][tempY];
        temp[tempX][tempY] = tmp;
        return temp;
    }

    public static void main(String[] args) {

        // Declaring the starting and goal states (as given in question)
        int[][] startState = { { 4, 1, 3 }, { 7, 6, 8 }, { 5, 2, 0 } };
        int[][] goalState = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } };

        int curr_distance = getHeuristicValue(startState, goalState);

        int[] dx = { -1, 0, 1, 0 };
        int[] dy = { 0, -1, 0, 1 };

        int next[][] = new int[3][3];
        int temp[][] = new int[3][3];
        int curr[][] = new int[3][3];
        curr = copyMatrix(startState);

        int temp_distance, min_distance, state_from_src = 0, currX = -1, currY = -1;

        int[] arr = new int[2];
        arr[0] = currX;
        arr[1] = currY;

        findCurrPosZero(curr, arr);
        currX = arr[0];
        currY = arr[1];

        ArrayList<int[][]> path = new ArrayList<>();

        path.add(startState);

        while (getHeuristicValue(curr, goalState) > 0) {
            min_distance = Integer.MAX_VALUE;
            arr[0] = currX;
            arr[1] = currY;
            findCurrPosZero(curr, arr);
            currX = arr[0];
            currY = arr[1];

            ++state_from_src;

            for (int i = 0; i < 4; i++) {
                int tempX = currX + dx[i];
                int tempY = currY + dy[i];
                if (tempX >= 0 && tempX < 3 && tempY >= 0 && tempY < 3) {
                    temp = swapTiles(curr, currX, currY, tempX, tempY);
                    temp_distance = state_from_src + getHeuristicValue(temp, goalState);
                    if (temp_distance < min_distance) {
                        min_distance = temp_distance;
                        next = temp;
                    }
                }
            }
            curr_distance = min_distance;
            curr = next;
            path.add(curr);
        }

        printIntermediateStates(path);
        int value = path.size() - 1;
        System.out.println("\nThe Path length from starting state to goal state using A* Search is: " + value + "\n");
    }
}
