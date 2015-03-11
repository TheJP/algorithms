package ch.fhnw.elite.crypto;

public class Crypto3Test {

	private static final char[] ALPHABET = "_abcdefghijklmnopqrstuvwxyz".toCharArray();
	private static int charIndex(char c) {
		return (c == '_') ? 0 : c - 'a' + 1;
	}
	//Modulo with positive result needed
	private static int mod(int x, int m){
		while(x < 0){ x += m; }
		return x % m;
	}

	public static void examples(){
		//Test with known key and known cyphertext
		char[][] cyphertexts = new char[][]{
			"owgoopj".toCharArray(),
			"uwrnsb".toCharArray(),
			"cqrkj".toCharArray() //the test data contains an error here <- results in 'azcow' instead of 'a_cow'
		};
		char[] key = "brownie".toCharArray();
		for(int i = 0; i < cyphertexts.length; ++i){
			System.out.println(cyphertexts[i]);
			char[] clear = new char[cyphertexts[i].length];
			for(int j = 0; j < clear.length; ++j){
				clear[j] = ALPHABET[
				    mod(charIndex(cyphertexts[i][j]) - charIndex(key[j]), 27)
				];
			}
			System.out.println(new String(clear));
			System.out.println();
		}
	}

	public static void possibilities(){
		for(int a = 0; a < ALPHABET.length; ++a){
			for(int b = 0; b < ALPHABET.length; ++b){
				System.out.println(String.format("%c%c = %c\t%d+%d = %d", ALPHABET[a], ALPHABET[b], ALPHABET[(a+b) % ALPHABET.length], a, b, (a+b)%ALPHABET.length));
			}
		}
	}

	public static void possibilities2(){
		for(int a = 0; a < ALPHABET.length; ++a){
			for(int b = 0; b < ALPHABET.length; ++b){
				System.out.println(String.format("%c%c = %c\t%d-%d = %d", ALPHABET[a], ALPHABET[b], ALPHABET[mod(a-b, ALPHABET.length)], a, b, mod(a-b, ALPHABET.length)));
			}
		}
	}

	public static void unfairSolver(){
		char[] cyphertext = "svivofbkwuhdalkarbqkcahemoofwuyuoplogudhuhfizepvydsroboeeyjuoeafbzchemzgkqyagbei".toCharArray();
		char[] cleartext = "hxamkxcsstotoxhcp_cvtlhacxkezdbofhheisymnvyypmxyovqxpouprdzniknejamdcasgtwwu_prg".toCharArray();
		char[] key = new char[cyphertext.length];
		for(int i = cyphertext.length - 1; i >= 0; --i){
			key[i] = ALPHABET[mod(charIndex(cyphertext[i]) - charIndex(cleartext[i]), ALPHABET.length)];
		}
		System.out.println(new String(key));
	}

	public static void main(String[] args) {
		possibilities2();
	}

}
