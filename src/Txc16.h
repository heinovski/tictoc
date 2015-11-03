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

#ifndef TXC16_H_
#define TXC16_H_

#include <csimplemodule.h>
#include <tictoc13_m.h>

class Txc16: public cSimpleModule {
public:
    Txc16();
    virtual ~Txc16();
private:
    simsignal_t arrivalSignal;
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void forwardMessage(TicTocMsg13 *msg);
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual TicTocMsg13* generateMessage();
};
#endif /* TXC16_H_ */
