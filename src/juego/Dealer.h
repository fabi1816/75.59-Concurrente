#ifndef DEALER_H
#define DEALER_H


#include <stack>
#include <vector>


namespace game {
	
	class Dealer {
		public:
			static std::vector< std::stack<int> > getPilas(int cantPilas);
	};
}

#endif

