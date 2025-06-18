/*
 * Click `Run` to execute the snippet below!
 */

import java.io.*;
import java.util.*;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

class BFS {

  public static void main(String[] args) {
    int N, M, V; // 정점수, 간선수, 탐색 시작 위치

    boolean[] visited = new boolean[1001];
    Node[] nodes = new Node[1001];

    try (var scanner = new Scanner(System.in)) {

      N = scanner.nextInt();
      M = scanner.nextInt();
      V = scanner.nextInt();

      for (int i = 0; i < N; i++) {
        nodes[i + 1] = new Node();
      }

      for (int i = 0; i < M; i++) {
        int a = scanner.nextInt();
        int b = scanner.nextInt();

        nodes[a].addEdge(b);
        nodes[b].addEdge(a);
      }
    }
    catch (Exception e) {
      System.out.println(e.getMessage());
      return;
    }

    var dfsResults = new ArrayList<Integer>();
    DFS(visited.clone(), nodes, V, dfsResults);
    System.out.println();

    var bfsResults = new ArrayList<Integer>();
    BFS(visited.clone(), nodes, V, bfsResults);
    printResults(bfsResults);
  }

  static class Node {
    private final List<Integer> edges = new ArrayList<>();

    void addEdge(int node) {
      edges.add(node);
    }

    List<Integer> getSortedEdges() {
      return edges.stream()
          .sorted()
          .toList();
    }
  }

  static void BFS(boolean[] visited, Node[] nodes, int V, List<Integer> results) {
    var queue = new ArrayDeque<Integer>();
    queue.add(V);

    while (!queue.isEmpty()) {
      int next = queue.poll();
      if(visited[next]) {
        continue;
      }

      visited[next] = true;
      System.out.printf("%d ", next);
      queue.addAll(nodes[next].getSortedEdges());
    }
  }

  static void DFS(boolean[] visited, Node[] nodes, int now, List<Integer> results) {
    visited[now] = true;
    System.out.printf("%d ", now);

    var pq = new PriorityQueue<>(nodes[now].edges);
    while (!pq.isEmpty()) {

      var next = pq.poll();
      if(visited[next]) {
        continue;
      }
      DFS(visited, nodes, next, results);
    }
  }

  static void printResults(List<Integer> results) {
    var it = results.iterator();

    while(it.hasNext()) {
      System.out.print(it.next());
      if(it.hasNext()) {
        System.out.print(" ");
      }
    }
  }
}
