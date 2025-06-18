/*
 * Click `Run` to execute the snippet below!
 */

import java.io.*;
import java.math.*;
import java.util.regex.Pattern;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

/**
 * 보유 종목별 수익률과 수익금액 계산
 *
 * Input - 'ticker:RSV price:2.35$ purchasePrice:2.15$ holdQuantity:500'
 * Output - 'ticker:RSV returnRate:00% profit:00.00$'
 */

class ProfitCalc {
  public static void main(String[] args) {

    final Pattern inputPattern = Pattern.compile("ticker:(?<ticker>\\w+) price:(?<price>\\d+\\.\\d+|\\d+)\\$ purchasePrice:(?<purchasePrice>\\d+\\.\\d+|\\d+)\\$ holdQuantity:(?<holdQuantity>\\d+)$");

    try (var reader = new BufferedReader(new InputStreamReader(System.in))) {

      while(true) {
        var input = reader.readLine();
        var matcher = inputPattern.matcher(input);

        if(!matcher.find()) {
          System.out.println("input 확인 필요");
          break;
        }

        String ticker = matcher.group("ticker");
        BigDecimal price = new BigDecimal(matcher.group("price"));
        BigDecimal purchasePrice = new BigDecimal(matcher.group("purchasePrice"));
        int holdQuantity = Integer.parseInt(matcher.group("holdQuantity"));

        // System.out.printf("%s %f %f %d\n", ticker, price, purchasePrice, holdQuantity);

        var position = new Position(ticker, price, purchasePrice, holdQuantity);

        System.out.printf("ticker:%s ", ticker);

        var returnRate = position.calcReturnRate().doubleValue();
        System.out.printf("returnRate:%.2f%% ", returnRate);

        var profit = position.calcProfit().doubleValue();
        System.out.printf("profit:%.2f$\n", profit);
      }

    } catch (IOException e) {
      System.out.println(e.getMessage());
    }
  }

  static class Position {
    private final String ticker;
    private final BigDecimal price;
    private final BigDecimal purchasePrice;
    private final int holdQuantity;

    Position(String ticker, BigDecimal price, BigDecimal purchasePrice, int holdQuantity) {
      this.ticker = ticker;
      this.price = price;
      this.purchasePrice = purchasePrice;
      this.holdQuantity = holdQuantity;
    }

    /**
     * 수익률을 계산합니다. 2번째 소숫점 자릿수까지만 표현하며, 반올림 처리합니다.
     * @return price.subtract(purchasePrice)
     * .multiply(new BigDecimal("100"))
     * .divide(purchasePrice, 2, RoundingMode.HALF_UP)
     */
    BigDecimal calcReturnRate() {
      return price.subtract(purchasePrice)
          .multiply(new BigDecimal("100"))
          .divide(purchasePrice, 2, RoundingMode.HALF_UP);
    }

    /**
     * 수익금을 계산합니다.
     * @return price.subtract(purchasePrice)
     * .multiply(new BigDecimal(holdQuantity))
     */
    BigDecimal calcProfit() {
      return price.subtract(purchasePrice)
          .multiply(new BigDecimal(holdQuantity));
    }
  }
}
