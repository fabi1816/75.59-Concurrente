#ifndef DEALER_H
#define DEALER_H


#include <stack>
#include <vector>
#include <algorithm>


namespace game {
	
	class Dealer {
		public:
			static std::vector< std::stack<int> > getPilas(int cantPilas);
			static std::stack<int> mergeAndShuffle(std::stack<int> a, std::stack<int> b);

		private:

			static std::vector<int> buildMazo();
	};
}

#endif

