//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef TXC6_H_
#define TXC6_H_

#include <csimplemodule.h>

class Txc6: public cSimpleModule {
    public:
        Txc6();
        virtual ~Txc6();
    private:
        cMessage *event; // pointer to the event object which we'll use for timing
        cMessage *tictocMsg; // variable to remember the message until we send it back
    protected:
        // The following redefined virtual function holds the algorithm.
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif /* TXC1_H_ */
