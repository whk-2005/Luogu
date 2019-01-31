import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        BigInteger a = new BigInteger(cin.next());
        BigInteger b = new BigInteger(cin.next());
        System.out.println(a.gcd(b));
    }
}