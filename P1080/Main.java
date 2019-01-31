import java.math.*;
import java.util.*;

class Minister {

    private int left;
    private int right;

    public Minister(int left, int right) {
        this.left = left;
        this.right = right;
    }

    public int getLeft() {
        return left;
    }

    public void setLeft(int left) {
        this.left = left;
    }

    public int getRight() {
        return right;
    }

    public void setRight(int right) {
        this.right = right;
    }

}

public class Main {
    int n;
    Minister ministers[];
    Scanner scanner = new Scanner(System.in);

    public void input() {
        n = scanner.nextInt();
        ministers = new Minister[n + 10];
        for (int i = 0; i <= n; i++) {
            ministers[i] = new Minister(scanner.nextInt(), scanner.nextInt());
        }
    }

    public void process() {
        Arrays.sort(ministers, 1, n + 1, new Comparator<Minister>() {
            @Override
            public int compare(Minister o1, Minister o2) {
                return (o1.getLeft() * o1.getRight() - o2.getLeft() * o2.getRight());
            }
        });
        BigInteger prev = new BigInteger(String.valueOf(ministers[0].getLeft()));
        BigInteger max = BigInteger.ZERO;
        for (int i = 1; i <= n; i++) {
            if (prev.compareTo(new BigInteger(String.valueOf(ministers[i].getRight()))) < 0) {
                if (new BigInteger("1").compareTo(max) > 0) {
                    max = new BigInteger("1");
                }
            } else {
                BigInteger int1 = prev.divide(new BigInteger(String.valueOf(ministers[i].getRight())));
                if (int1.compareTo(max) > 0) {
                    max = int1;
                }
            }
            prev = prev.multiply(new BigInteger(String.valueOf(ministers[i].getLeft())));
        }
        System.out.println(max);
    }

    public static void main(String[] args) {
        Main app = new Main();
        app.input();
        app.process();
    }
}