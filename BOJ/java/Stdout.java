/*
 * Click `Run` to execute the snippet below!
 */

import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.regex.Pattern;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

class Stdout {

  /**
   * 입출력 연습
   */
  public static void main(String[] args) {

    // try(var scanner = new Scanner(System.in)) {
    //   var str = scanner.nextLine();
    //   sout(str);
    // }
    String str = null;

    try(var reader = new BufferedReader(new InputStreamReader(System.in))) {

      // "2025-05-01 00:02:03"
      str = reader.readLine();
      var parsed = LocalDateTime.parse(str, DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
      sout(parsed);

      // "a,b,c"
      str = reader.readLine();
      var strTokenizer = new StringTokenizer(str, ",");
      while(strTokenizer.hasMoreTokens()) {
        sout(strTokenizer.nextToken());
      }

      // "ID:12345 NAME:taekyoung SCORE:100 ID:12346 NAME:jidam SCORE:90"
      str = reader.readLine();
      var pattern = Pattern.compile("(?<id>ID:(\\d+)) (?<name>NAME:(\\w+)) (?<score>SCORE:(\\d+))", Pattern.CANON_EQ);
      var matcher = pattern.matcher(str);

      while(matcher.find()) {
        var res = matcher.toMatchResult();
        sout(res.group("id"));
        sout(res.group("name"));
        sout(res.group("score"));
      }

    } catch(IOException e) {
      System.out.println(e.getMessage());
    }
  }

  static void sout(Object arg) {
    System.out.println(arg);
  }
}
