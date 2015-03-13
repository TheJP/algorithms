package ch.fhnw.elite.spy;

import java.util.LinkedList;
import java.util.Queue;

//////////////////////
// SUBMIT THIS FILE //
//////////////////////

class Spy2 {
	/**
	 * Runs in Heidi's process This function is called to indicate that the
	 * marmot with the given ID is diligent. It should call SpyLib2.sendHint to
	 * communicate this information to the marmots. It can also read
	 * SpyLib2.nScans to find out how many scans there will be in total (i.e.,
	 * the value N in the problem statement)
	 */
	static void scanMarmot(long id) {
		int s = 21; // 1. shift right
		boolean force = false;
		while (s >= 0) {
			byte send = (byte) ((id >>> s) & 0x7f);
			if (s == 0) { send = (byte) (send | 0x80); }
			if (force || send != 0) { SpyLib2.sendHint(send); force = true; }
			s -= 7;
		}
	}

	private static boolean[] isMarmot = new boolean[17000000];
	private static final Queue<Byte> bytes = new LinkedList<>();

	/**
	 * Runs in the marmots' process This function is called whenever
	 * SpyLib2.sendHint was called. It receives the information that was passed
	 * to sendHint.
	 */
	static void receiveHint(byte hint) {
		if((hint & 0x80) == 0){
			bytes.offer(hint);
		} else {
			int id = 0;
			while(!bytes.isEmpty()){
				byte b = bytes.poll();
				id = (id << 7) | b;
			}
			id = (id << 7) | (hint & 0x7f);
			isMarmot[id] = true;
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
