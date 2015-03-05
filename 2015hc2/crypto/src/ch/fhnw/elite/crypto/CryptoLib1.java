package ch.fhnw.elite.crypto;

import java.io.FileInputStream;

/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class CryptoLib1 {
 
        public static void main(String[] args) throws java.io.FileNotFoundException {
        	int N; // number of test cases
            boolean correct_ans;
            int password_to_check; 
            java.util.Scanner fin = null;
            
            try {
	            fin = new java.util.Scanner(new FileInputStream("testdata1.in"));
	            
	            N = fin.nextInt();
	            
	            for (int i = 0; i < N; i++) {
	            	password_to_check = fin.nextInt();
	            	System.out.println(password_to_check);
	            	if (fin.nextInt() == 0) {
	            		correct_ans = false;
	            	} else {
	            		correct_ans = true;
	            	}
	            	
	            	if (Crypto1.isPasswordCorrect(password_to_check) != correct_ans) {
	            		System.out.println("INCORRECT");
	            		return;
	            	}
	            }
	            System.out.println("Looks pretty good");
            } finally {
            	if (fin != null) fin.close();
            }
        }
}
