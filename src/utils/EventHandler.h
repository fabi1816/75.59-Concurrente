#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_


namespace utils {
	
	class EventHandler {
		public:
			virtual int handleSignal(int signum) = 0;
			virtual ~EventHandler() = default;
	};

}

#endif
