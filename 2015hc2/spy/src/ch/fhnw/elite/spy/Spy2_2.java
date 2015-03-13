package ch.fhnw.elite.spy;


//////////////////////
// SUBMIT THIS FILE //
//////////////////////

class Spy2_2 {

	//Heidis data
	private static int scans = Integer.MAX_VALUE;
	private static int maxId = Integer.MIN_VALUE;

	//Marmots data
	private static int pos = 0;

	//Shared data
	private static final boolean[] isMarmot = new boolean[17000000];

	/**
	 * Runs in Heidi's process This function is called to indicate that the
	 * marmot with the given ID is diligent. It should call SpyLib2.sendHint to
	 * communicate this information to the marmots. It can also read
	 * SpyLib2.nScans to find out how many scans there will be in total (i.e.,
	 * the value N in the problem statement)
	 */
	static void scanMarmot(long id) {
		isMarmot[(int)id] = true;
		if(id > maxId){ maxId = (int)id; }
		if(scans == Integer.MAX_VALUE){ scans = SpyLib2_2.nScans(); }
		--scans;
		if(scans <= 0){
			//send hints now
			for(int i = 0; i <= maxId; i += 8){
				byte b = 0;
				for(int j = 0; j < 8; ++j){
					if(isMarmot[i+j]){
						b = (byte) (b | (1<<j));
					}
				}
				SpyLib2_2.sendHint(b);
			}
		}
	}

	/**
	 * Runs in the marmots' process This function is called whenever
	 * SpyLib2.sendHint was called. It receives the information that was passed
	 * to sendHint.
	 */
	static void receiveHint(byte hint) {
		for(int i = 0; i < 8; ++i){
			boolean b = (hint & 1) == 1; //is a 1 bit at position 0
			isMarmot[pos++] = b;
			hint >>>= 1;
		}
	}

	/**
	 * Runs in the marmots' thread This function should return whether the
	 * marmot with the given ID is a spy, or not. It must decide based on
	 * information received through receiveHint.
	 */
	static boolean isSpy(long id) {
		return !isMarmot[(int)id];
	}
};
