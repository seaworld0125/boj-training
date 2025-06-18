/*
 * Click `Run` to execute the snippet below!
 */

import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

class Sort {

  /**
   * 정렬 구현 연습
   */
  public static void main(String[] args) {

    List<Integer> testList;

     testList = generateIntegerList(100);
     bubbleSort(testList);
     sout(testList);

    testList = generateIntegerList(100);
    sout(mergeSort(0, testList.size() - 1, testList));

    testList = generateIntegerList(100);
    insertSort(testList);
    sout(testList);
  }

  /**
   * 머지소트(재귀) 원소가 하나가 남을때까지 리스트를 반씩(logN) 나누어 (분할) - (정복) - (병합)
   * 시간복잡도: O(NlogN)
   */
  static List<Integer> mergeSort(int i, int j, List<Integer> ref) {
    if(i == j) {
      return List.of(ref.get(i));
    }

    int mid = i + (j - i) / 2;
    List<Integer> aList = mergeSort(i, mid, ref);
    List<Integer> bList = mergeSort(mid + 1, j, ref);
    List<Integer> res = new ArrayList<>();

    int k = 0, l = 0;
    while(k < aList.size() && l < bList.size()) {
      int a = aList.get(k);
      int b = bList.get(l);
      if (a <= b) {
        res.add(a);
        k++;
      }
      else {
        res.add(b);
        l++;
      }
    }

    while(k < aList.size()) {
      res.add(aList.get(k));
      k++;
    }

    while(l < bList.size()) {
      res.add(bList.get(l));
      l++;
    }
    return res;
  }

  /**
   * 버블소트(가장 기본적인 비교 정렬)
   * 시간복잡도: O(N^2)
   */
  static void bubbleSort(List<Integer> ref) {
    for(int i = 0; i < ref.size(); i++) {
      for(int j = 0; j < i; j++) {
        if(ref.get(i) < ref.get(j)) {
          swap(i, j, ref);
        }
      }
    }
  }

  /**
   * 인서트소트
   * */
  static void insertSort(List<Integer> ref) {
    for (int i = 1; i < ref.size(); i++) {
      int tmp = ref.get(i);
      int prev = i - 1;

      while (prev >= 0 && ref.get(prev) > tmp) {
        ref.set(prev + 1, ref.get(prev));
        prev--;
      }
      ref.set(prev + 1, tmp);
    }
  }

  static void swap(int idx1, int idx2, List<Integer> ref) {
    int temp = ref.get(idx1);
    ref.set(idx1, ref.get(idx2));
    ref.set(idx2, temp);
  }

  static List<Integer> generateIntegerList(int size) {
    var random = new Random();
    return Stream.generate(() -> random.nextInt(100))
        .limit(size)
        .collect(Collectors.toList());
  }

  static void sout(Object arg) {
    System.out.println(arg);
  }

  static <T> void sout(List<T> list) {
    System.out.println(Arrays.toString(list.toArray()));
  }
}
