package ch.fhnw.elite.crypto;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class CryptoLib2 {

  private static final String ALPHABET = "_abcdefghijklmnopqrstuvwxyz";

  private static void check(boolean v) {
    if (!v) {
      System.out.println("assertion failed");
      System.err.println("assertion failed");
      System.exit(0);
    }
  }

  private static boolean isValidKey(String k) {
    char[] elements = k.toCharArray();
    Arrays.sort(elements);
    return Arrays.equals(elements, ALPHABET.toCharArray());
  }

  private static boolean isValidCleartext(String s) {
    if (!s.matches("[_a-z]+")) return false;
    for (int i = 0; i < ALPHABET.length(); ++i) {
      if (s.indexOf(ALPHABET.charAt(i)) < 0) return false;
    }
    return true;
  }

  private static int charIndex(char c) {
    return (c == '_') ? 0 : c - 'a' + 1;
  }

  private static String encrypt(String message, String key) {
    char[] output = new char[message.length()];
    for (int i = 0; i < output.length; ++i) {
      output[i] = key.charAt(charIndex(message.charAt(i)));
    }
    return String.valueOf(output);
  }

  public static void main(String[] args) {
      BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

      String cleartext = null, cyphertext = null;
      try {
          cleartext = in.readLine();
          cyphertext = in.readLine();
      } catch (IOException e) {
          e.printStackTrace();
          System.exit(1);
      }
      while (cleartext != null) {
          try {
              check(in.readLine().isEmpty());
          } catch (IOException e) {
              e.printStackTrace();
              System.exit(1);
          }
          check(cyphertext != null);
          check(cleartext.length() == cyphertext.length());
          check(isValidCleartext(cleartext));
          check(isValidCleartext(cyphertext));

          String key = Crypto2.findKey(cleartext, cyphertext);
          if (!isValidKey(key)) {
              System.err.println(1);
              System.out.println("Incorrect");
              return;
          }
          if (!cyphertext.equals(encrypt(encrypt(cleartext, key), key))) {
              System.err.println(2);
              System.out.println("Incorrect");
              return;
          }

          try {
              cleartext = in.readLine();
              cyphertext = in.readLine();
          } catch (IOException e) {
              e.printStackTrace();
              System.exit(1);
          }
      }

      System.out.println("Looks pretty good");
  }
}
