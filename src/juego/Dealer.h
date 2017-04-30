#ifndef DEALER_H
#define DEALER_H


#include <stack>


namespace game {
	
	class Dealer {
		public:
			explicit Dealer(int cantPilas);

			std::stack<int> getPila(int numPila);

		private:
			int m_cantPilas;
	};
}

#endif

