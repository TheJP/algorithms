import java.math.BigInteger;
import java.util.Scanner;

/**
 *
 * @author JP
 */
public class Main{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try(Scanner s = new Scanner(System.in)){
	        BigInteger max, a, x, y, two = BigInteger.valueOf(2);
	        for (int i = 0; i < 10; i++) {
	            max = s.nextBigInteger();
	            a = s.nextBigInteger();
	            y = max.subtract(a).divide(two);
	            x = y.add(a);
	            System.out.println(x);
	            System.out.println(y);
	        }
        }
    }
}

