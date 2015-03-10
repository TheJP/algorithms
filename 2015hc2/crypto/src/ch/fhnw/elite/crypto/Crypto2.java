package ch.fhnw.elite.crypto;

import java.util.ArrayList;
import java.util.List;


public class Crypto2 {

	private static final char[] ALPHABET = "_abcdefghijklmnopqrstuvwxyz".toCharArray();

	private static int charIndex(char c) {
		return (c == '_') ? 0 : c - 'a' + 1;
	}

	private static char[] getGeneralKey(String plaintext, String cyphertext){
		char[] result = new char[ALPHABET.length];
		for(int i = ALPHABET.length - 1; i >= 0; --i){
			for(int x = plaintext.length() - 1; x >= 0; --x){
				if(plaintext.charAt(x) == ALPHABET[i]){
					result[i] = cyphertext.charAt(x);
				}
			}
		}
		return result;
	}

	private static char[] sqrtKey(char[] key){
		//Cycle recognition
		int[] visited = new int[ALPHABET.length];
		List<List<Integer>> cycles = new ArrayList<>();
		int c = 0;
		for(int i = 0; i < ALPHABET.length; ++i){
			if(visited[i] == 0){
				++c;
				List<Integer> cycle = new ArrayList<>();
				int x = i;
				while(visited[x] == 0){
					visited[x] = c;
					cycle.add(x);
					x = charIndex(key[x]); //Iterate
				}
				cycles.add(cycle);
			}
		}
		//Distribute cycles to generate the actual key
		char[] result = new char[ALPHABET.length];
		int ncycles = cycles.size();
		while(ncycles > 0){
			List<Integer> cycle = cycles.remove(--ncycles);
			int n = cycle.size();
			if(n % 2 == 0){ //If n % 2 == 0 (n even)
				//the only possible solution is to combine the cycle with a cycle of equal length
				int i = 0;
				while(i < ncycles && cycles.get(i).size() != n){ ++i; }
				if(i >= ncycles){ throw new IllegalStateException("No solution possible"); }
				//Found a possible solution:
				List<Integer> cycle2 = cycles.remove(i); --ncycles;
				for(i = 0; i < n; ++i){
					result[cycle.get(i)] = ALPHABET[cycle2.get(i)];
					result[cycle2.get(i)] = ALPHABET[cycle.get((i+1) % n)];
				}
			} else if(n == 1){ //Special case n == 1
				result[cycle.get(0)] = ALPHABET[cycle.get(0)];
			} else { //All other cases with n >= 3 && n % 2 == 1
				int a = 0;
				int b = ((int)(n / 2)) + 1;
				while(b < n){
					result[cycle.get(a)] = ALPHABET[cycle.get(b)];
					++a;
					result[cycle.get(b)] = ALPHABET[cycle.get(a)];
					++b;
				}
				result[cycle.get(a)] = ALPHABET[cycle.get(0)];
			}
		}
		return result;
	}

//Brute force solution:
//	private static char[] sqrtKey(char[] key){
//		char[] solution = new char[ALPHABET.length];
//		if(!findSolution(key, solution, 0)){
//			throw new IllegalStateException("Not solvable");
//		}
//		return solution;
//	}
//
//	private static boolean findSolution(char[] key, char[] solution, int from){
//		if(from >= ALPHABET.length){ return true; }
//		char toc = key[from]; //char to place in solution
//		if(solution[from] != 0 && toc == solution[charIndex(solution[from])]){
//			//Already solved this char, next char
//			return findSolution(key, solution, from+1);
//		} else {
//			//Find a solution, which works for this char
//			if(solution[from] != 0){
//				//1. Step is fixed (find if 2. step is possible)
//				int x = charIndex(solution[from]);
//				if(solution[x] != 0){
//					//current solution is not 0 and is false: this branch is not solvable
//					return false;
//				} else {
//					//Only one possible way to go: Try to solve with this solution
//					solution[x] = toc;
//					if(findSolution(key, solution, from+1)){
//						return true;
//					} else {
//						solution[x] = 0; //Restore previous state
//					}
//				}
//			} else {
//				//1. Step is still open (find a possible 2 step path)
//				for(int pos = 0; pos < ALPHABET.length; ++pos){
//					//Try middle char (x) = pos
//					if(solution[pos] == 0){
//						if(pos != from || ALPHABET[pos] == toc){
//							solution[from] = ALPHABET[pos];
//							solution[pos] = toc;
//							if(findSolution(key, solution, from+1)){
//								return true;
//							}
//							solution[from] = 0;
//							solution[pos] = 0;
//						}
//					}
//				}
//			}
//		}
//		return false;
//	}


	// Returns a key such that applying the key twice to encrypt the plaintext
	// results in the cyphertext.
	public static String findKey(String plaintext, String cyphertext) {
		return new String(sqrtKey(getGeneralKey(plaintext, cyphertext)));
	}
}
