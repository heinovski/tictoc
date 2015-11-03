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

#ifndef TXC12_H_
#define TXC12_H_

#include <csimplemodule.h>

class Txc12: public cSimpleModule {
    public:
        Txc12();
        virtual ~Txc12();
    private:
        simtime_t timeout;  // timeout
        cMessage *timeoutEvent;  // holds pointer to the timeout self-message
        int seq;  // message sequence number
        cMessage *message;  // message that has to be re-sent on timeout
    protected:
        // The following redefined virtual function holds the algorithm.
        virtual void forwardMessage(cMessage *msg);
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};
#endif /* TXC12_H_ */
