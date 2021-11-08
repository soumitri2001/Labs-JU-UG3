/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3
 * Semester: 5
 * Date: 30/09/2021
 * ---------------------------------------------------------------------------
 * Subject: A.I. Lab Assignment 4.2 : UCS to solve 8 puzzle problem
 * ---------------------------------------------------------------------------
 * Question: Use UCS to solve 8 puzzle problems.
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
 * h3(N) = Sum of the (getManhattanDist) distances of every tile to its goal position (doesn't include empty tile)
 * e.g. h3(s) = 4 + 2 + 2 + 2 + 2 + 0 + 3 + 3 = 18
 * h4(N) = Sum of Eucledian distances of the tiles from their goal positions (doesn't include empty tile)
 * ---------------------------------------------------------------------------
 * Compilation: javac UniformCostSearch_Ass4_SoumitriChattopadhyay.java
 * ---------------------------------------------------------------------------
 * Execution: java UniformCostSearch_Ass4_SoumitriChattopadhyay
 * ---------------------------------------------------------------------------
 * Output:
 * 
 * Using UCS to solve 8 puzzle
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
 * Number of steps to reach goal state using UCS: 2 
 * ---------------------------------------------------------------------------
 */

package EightPuzzle;

import java.util.*;
import java.io.*;

public class UniformCostSearch_Ass4_SoumitriChattopadhyay {

    private ArrayList<Board> path = null;

    static class Board {
        private static final int[] dx = { -1, 0, 1, 0 };
        private static final int[] dy = { 0, 1, 0, -1 };

        private final int[][] tiles;
        private final int n;

        public Board(int[][] tiles) {
            if (tiles == null)
                throw new IllegalArgumentException("Array cannot be null!");
            n = tiles.length;
            this.tiles = tiles.clone();
        }

        @Override
        public String toString() {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    s.append(tiles[i][j] + " ");
                }
                s.append("\n");
            }
            return s.toString();
        }

        public int getManhattanDist(Board goal) {
            int total_dist = 0;
            HashMap<Integer, Integer> map = new HashMap<>();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (tiles[i][j] == 0)
                        continue;
                    map.put(tiles[i][j], i * n + j);
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (goal.tiles[i][j] == 0)
                        continue;
                    int idx = map.get(goal.tiles[i][j]);
                    int dist = Math.abs(i - (idx / n));
                    dist += Math.abs(j - (idx % n));
                    total_dist += dist;
                }
            }
            return total_dist;
        }

        public boolean isGoal() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == n - 1 && j == n - 1) {
                        return (tiles[i][j] == 0);
                    } else if (tiles[i][j] != (i * n + j + 1)) {
                        return false;
                    }
                }
            }
            return true;
        }

        public boolean equals(Object y) {
            if (y == null)
                return false;
            if (!y.getClass().equals(this.getClass()))
                return false;
            if (this == y)
                return true;

            Board b = (Board) y;
            if (this.n != b.n)
                return false;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (this.tiles[i][j] != b.tiles[i][j])
                        return false;

            return true;
        }

        public Iterable<Board> neighbors() {
            ArrayList<Board> list = new ArrayList<>();
            int x = -1, y = -1;
            for (int i = 0; i < n && x == -1; i++) {
                for (int j = 0; j < n && x == -1; j++) {
                    if (tiles[i][j] == 0) {
                        x = i;
                        y = j;
                    }
                }
            }

            for (int k = 0; k < dx.length; k++) {
                int i = x + dx[k];
                int j = y + dy[k];
                if (i < 0 || i >= n || j < 0 || j >= n)
                    continue;
                int[][] copy = copyTiles();
                copy[x][y] = copy[i][j];
                copy[i][j] = 0;
                list.add(new Board(copy));
            }

            return list;
        }

        public Board copyBoard() {
            int[][] copy = copyTiles();

            int one = copy[0][0];
            int two = copy[0][1];
            int three = copy[1][0];

            if (one == 0) {
                copy[1][0] = two;
                copy[0][1] = three;
            } else if (two == 0) {
                copy[0][0] = three;
                copy[1][0] = one;
            } else {
                copy[0][0] = two;
                copy[0][1] = one;
            }

            return new Board(copy);
        }

        private int[][] copyTiles() {
            int[][] copy = new int[n][n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    copy[i][j] = tiles[i][j];
                }
            }
            return copy;
        }
    }

    static class BoardNode implements Comparable<BoardNode> {
        final Board board;
        final int moves;
        final int priority;
        final BoardNode prev;

        BoardNode(Board board, int moves, BoardNode prev) {
            this.board = board;
            this.moves = moves;
            this.prev = prev;
            this.priority = moves;
        }

        @Override
        public int compareTo(BoardNode node) {
            return Integer.compare(this.priority, node.priority);
        }
    }

    public UniformCostSearch_Ass4_SoumitriChattopadhyay(Board start, Board goal) {
        PriorityQueue<BoardNode> pq = new PriorityQueue<>();
        pq.add(new BoardNode(start, 0, null));

        PriorityQueue<BoardNode> copyBoard_pq = new PriorityQueue<>();
        copyBoard_pq.add(new BoardNode(start.copyBoard(), 0, null));

        while (!pq.isEmpty()) {
            BoardNode cur = pq.poll();

            if (cur.board.equals(goal)) {
                path = new ArrayList<>();
                for (BoardNode i = cur; i != null; i = i.prev)
                    path.add(i.board);
                Collections.reverse(path);
                break;
            }

            for (Board neighbor : cur.board.neighbors()) {
                if (cur.prev == null || !neighbor.equals(cur.prev.board)) {
                    pq.offer(new BoardNode(neighbor, cur.moves + 1, cur));
                }
            }

            cur = copyBoard_pq.poll();

            if (cur.board.equals(goal)) {
                break;
            }

            for (Board neighbor : cur.board.neighbors()) {
                if (cur.prev == null || !neighbor.equals(cur.prev.board)) {
                    copyBoard_pq.offer(new BoardNode(neighbor, cur.moves + 1, cur));
                }
            }
        }
    }

    public boolean hasPath() {
        return path != null;
    }

    public List<Board> path() {
        return path;
    }

    public int moves() {
        if (path == null)
            return -1;
        return path.size() - 1;
    }

    public static void main(String args[]) throws FileNotFoundException {

        // start and goal states as given in question
        int[][] startState = { { 1, 2, 3 }, { 8, 6, 4 }, { 7, 5, 0 } };
        int[][] endState = { { 1, 2, 3 }, { 8, 0, 4 }, { 7, 6, 5 } };

        System.out.println("Using UCS to solve 8 puzzle\n");
        UniformCostSearch_Ass4_SoumitriChattopadhyay ucs = new UniformCostSearch_Ass4_SoumitriChattopadhyay(
                new Board(startState), new Board(endState));
        if (ucs.hasPath()) {
            int ctr = 0;
            for (Board b : ucs.path) {
                ctr++;
                System.out.print("-----\n");
                System.out.print(b);
                System.out.print("-----\n");
                if (ctr != ucs.path.size()) {
                    System.out.println("  |   ");
                    System.out.println("  |   ");
                    System.out.println("  V   ");
                }
            }
            System.out.println("\nNumber of steps to reach goal state using UCS: " + ucs.moves());
        } else {
            System.out.println("The puzzle be solved");
        }
    }
}
