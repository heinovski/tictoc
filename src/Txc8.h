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

#ifndef TXC8_H_
#define TXC8_H_

#include <csimplemodule.h>

class Tic8: public cSimpleModule {
    public:
        Tic8();
        virtual ~Tic8();
    private:
        simtime_t timeout;  // timeout
        cMessage *timeoutEvent;  // holds pointer to the timeout self-message
    protected:
        // The following redefined virtual function holds the algorithm.
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

class Toc8: public cSimpleModule {
    protected:
        virtual void handleMessage(cMessage *msg);
};

#endif /* TXC8_H_ */
