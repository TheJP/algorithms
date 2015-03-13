package ch.fhnw.elite.spy;

import java.util.*;
import java.io.*;

class SpyLib2_2{

  /** Call this method from your Heidi code, to send a hint to the marmots.
   *  It causes the Marmot's receiveHint method to be called. */
  public static void sendHint(byte hint){
  	if (_remainingHints <= 0) {
      System.out.println("Incorrect -- Heidi used too many hints");
      System.exit(0);
    }
    
    try {
    	_marmotProcess.write(new Byte(hint));
    } catch(IOException e){
    	System.out.println("Uh-oh! Can't find marmot process!");
    	System.out.println(e.getMessage());
    	System.exit(1);
    }
    _remainingHints -= 1;
  }
  
  /** Call this methods to receive the total number of scans
   *  (i.e., the value N from the problem statement) 
   */
  public static int nScans(){
  	return _nScans;
  }
  
  // Implementation details follow...
  
  /** 
   * This class runs the marmot behavior, and calls the isSpy and receiveHint 
   * methods. 
   */
  static class Marmot {
    public Marmot() throws IOException, ClassNotFoundException {
      System.err.println("Marmot process started...");

      ObjectOutputStream out = new ObjectOutputStream(System.out);
      ObjectInputStream in = new ObjectInputStream(System.in);

      while (true) {
        try {
          Object o = in.readObject();
          if (o instanceof Long) {
            Long id = (Long) o;
            System.err.print("Marmot received query for " + id);
            boolean answer = Spy2_2.isSpy(id);
            System.err.println(", answering " + answer);
            out.writeObject(new Boolean(answer));
          } else if (o instanceof Byte) {
            Byte info = (Byte) o;
            System.err.println("Marmot received hint " + info);
            Spy2_2.receiveHint(info.byteValue());
          } else {
            System.out.println("Heidi must not send gibberish");
            System.exit(1);
          }
        } catch (EOFException e) {
          System.err.println("Marmot exiting.");
          break;
        }
      }
    }
  }

  /** This class runs Heidi, and calls the scanMarmot method. */
  static class Heidi {
  	
    boolean testMarmot(long id) throws IOException, ClassNotFoundException {
      System.err.println("Heidi testing Marmot " + id);
      _marmotProcess.write(new Long(id));
      Object response = _marmotProcess.read();
      if (response instanceof Boolean){
      	Boolean result = (Boolean) response;
      	return result.booleanValue();
      }
      System.out.println("Marmot must not send gibberish");
      System.exit(1);
      return false;
    }
    
    public Heidi() throws IOException, ClassNotFoundException {
      System.err.println("Heidi process started...");
      Scanner s = null;
      try {
        s = new Scanner(new FileInputStream("testdata02.in"));
        _nScans = s.nextInt();
        int nTests = s.nextInt();
        _remainingHints = 2 * _nScans;

        for (int i = 0; i < _nScans + nTests; ++i) {
          int op = s.nextInt();
          long id = s.nextLong();
          boolean solution = s.nextInt() != 0;

          switch (op) {
          case 0:
            boolean answer = testMarmot(id);
            if (answer != solution) {
              System.out.println("Incorrect -- Marmot confused spy and loyal fellow");
              System.exit(0);
            }
            break;
          case 1:
            System.err.println("Heidi scanning Marmot " + id);
            Spy2_2.scanMarmot(id);
            break;
          default:
            throw new AssertionError("Illegal operation in input file");
          }
        }

        System.out.println("Looks pretty good");
      } finally {
        if (s != null) {
          s.close();
        }
      }
    }
  }

  /** This class encapsulates the marmot thread, running in its own process. */
  static class MarmotProcess{
  	private ObjectOutputStream stdin;
  	private ObjectInputStream stdout;

    public MarmotProcess() throws IOException {
      System.err.println("About to launch a new marmot");
      ProcessBuilder pb = new java.lang.ProcessBuilder("java", "-cp", "bin", "ch.fhnw.elite.spy.SpyLib2_2", "marmot");
      pb.redirectError(java.lang.ProcessBuilder.Redirect.INHERIT);
      Process p = pb.start();

      stdin = new java.io.ObjectOutputStream(p.getOutputStream());
      stdout = new java.io.ObjectInputStream(p.getInputStream());

      System.err.println("Marmot launched.");
    }
    
    void write(Object o) throws IOException{
      stdin.writeObject(o);
      stdin.flush();
    }
    
    Object read() throws IOException, ClassNotFoundException{
      return stdout.readObject();
    }
  }

  private static MarmotProcess _marmotProcess;
  private static int _remainingHints;
  private static int _nScans;
  
  // or should the exceptions be caught?
  public static void main(String[] args) throws IOException,
  		ClassNotFoundException{
    System.err.println("In main");
  	if (args.length > 0 && args[0].equals("marmot")) {
      new Marmot();
    } else {
      _marmotProcess = new MarmotProcess();
      new Heidi();
    }
  }
}
