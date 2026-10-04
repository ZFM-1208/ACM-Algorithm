import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BigInteger n = sc.nextBigInteger();
        BigInteger x = BigInteger.ONE;
        for(int i = 1; i <= n.intValue(); i++){
            x.multiply(BigInteger.valueOf(i));
        }
        BigInteger y = n;
        for(int i = 1; i <= n.intValue(); i++){
            y.multiply(n);
        }    
        // System.out.println(x);
        // System.out.println(y);
        System.out.println(x.multiply(x).divide(y));    
    }
}