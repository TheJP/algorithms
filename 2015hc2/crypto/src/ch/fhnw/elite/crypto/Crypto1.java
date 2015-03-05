package ch.fhnw.elite.crypto;

///////////////////////////////////////////
// THIS IS THE ONLY FILE YOU WILL SUBMIT //
///////////////////////////////////////////

public class Crypto1 {

	private static final int MAX_PRIM = (int) Math.ceil(Math.sqrt(100000000));
	private static boolean[] nonprim = new boolean[MAX_PRIM+1];

	private static int s = 2;

	private static void sieb(long max){
		nonprim[1] = true;
		for(; s <= max; ++s){
			if(!nonprim[s]){
				int x = s+s;
				while(x <= MAX_PRIM){
					nonprim[x] = true;
					x += s;
				}
			}
		}
	}

	private static int countF(long x){
		int n = 0;
		for(long i = 2; x >= 1 && i <= x; ++i){
			while(x % i == 0){
				x /= i;
				++n;
			}
		}
		return n;
	}

	public static boolean isPasswordCorrect(int password) {
		int f = countF(password);
		sieb((int)Math.ceil(Math.sqrt(f)));
		return !nonprim[f];
	}

}
