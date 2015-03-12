package ch.fhnw.elite.spy;

//////////////////////
// SUBMIT THIS FILE //
//////////////////////

class Spy1 {
	/**
   * Runs in Heidi's process
   * This function is called to indicate that the marmot with the given ID is
   * diligent. It should call SpyLib1.sendHint to communicate this information 
   * to the marmots.
   * It can also read SpyLib1.nScans to find out how many scans there will be 
   * in total
   * (i.e., the value N in the problem statement)
   */
  static void scanMarmot(long id){
	  byte prevHint = (byte)(id & 0xff);
	  byte hint = (byte)((id>>>8) & 0xff);
	  SpyLib1.sendHint(prevHint);
	  SpyLib1.sendHint(hint);
  }

  private static boolean hasPrevHint = false;
  private static byte prevHint = 0;
  private static boolean[] isMarmot = new boolean[66000];

  /**
   * Runs in the marmots' process
   * This function is called whenever SpyLib1.sendHint was called. It receives 
   * the information that was passed to sendHint.
   */
  static void receiveHint(byte hint){
	  if(!hasPrevHint){
		  prevHint = hint;
	  } else {
		  int id = ((((int)hint) & 0xff)<<8) | (((int)prevHint) & 0xff);
		  isMarmot[id] = true;
	  }
	  hasPrevHint = !hasPrevHint;
  }

  /**
   * Runs in the marmots' thread
   * This function should return whether the marmot with the given ID is a spy,
   * or not. It must decide based on information received through receiveHint.
   */
  static boolean isSpy(long id){
	  return !isMarmot[(int) id];
  }
};
