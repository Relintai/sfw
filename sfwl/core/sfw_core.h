
#ifndef SFW_CORE_H
#define SFW_CORE_H

class SFWCore {
public:
	static void setup();
	static void cleanup();

protected:
	static bool _initialized;
};

#endif
