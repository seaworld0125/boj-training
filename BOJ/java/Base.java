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

class Base {
  public static void main(String[] args) {

    try {
      readGradeInfos()
          .stream()
          .sorted(Comparator.reverseOrder())
          .forEach(System.out::println);
    } catch(IOException e) {
      System.out.println("I/O 오류 발생: cause %s".formatted(e.getMessage()));
    } catch(NumberFormatException e) {
      System.out.println("입력 정보 파싱 오류 발생: cause %s".formatted(e.getMessage()));
    }
  }

  static List<GradeInfo> readGradeInfos() throws IOException {
    List<GradeInfo> gradeInfos = new ArrayList<>();

    try(var reader = new BufferedReader(new InputStreamReader(System.in))) {
      while(true) {
        var stringTokenizer = new StringTokenizer(reader.readLine());
        if(stringTokenizer.countTokens() != 4) {
          break;
        }
        var name = stringTokenizer.nextToken();
        var languageScore = Double.parseDouble(stringTokenizer.nextToken());
        var mathScore = Double.parseDouble(stringTokenizer.nextToken());
        var englishScore = Double.parseDouble(stringTokenizer.nextToken());

        gradeInfos.add(new GradeInfo(name, languageScore, mathScore, englishScore));
      }
    }
    return gradeInfos;
  }

  record GradeInfo(
      String name,
      double languageScore,
      double mathScore,
      double englishScore
  ) implements Comparable<GradeInfo> {

    @Override
    public int compareTo(GradeInfo o) {
      var totalScoreCompareResult = Double.compare(this.getTotalScore(), o.getTotalScore());
      if (totalScoreCompareResult != 0) {
        return totalScoreCompareResult;
      }

      var languageScoreCompareResult = Double.compare(this.languageScore(), o.languageScore());
      if (languageScoreCompareResult != 0) {
        return languageScoreCompareResult;
      }

      var mathScoreCompareResult = Double.compare(this.mathScore(), o.mathScore());
      if (mathScoreCompareResult != 0) {
        return mathScoreCompareResult;
      }

      var englishScoreCompareResult = Double.compare(this.englishScore(), o.englishScore());
      if (englishScoreCompareResult != 0) {
        return englishScoreCompareResult;
      }

      return this.name().compareTo(o.name()) * -1;
    }

    public double getTotalScore() {
      return languageScore + mathScore + englishScore;
    }

    @Override
    public String toString() {
      return name + " " + languageScore + " " + mathScore + " " + englishScore;
    }
  }
}
