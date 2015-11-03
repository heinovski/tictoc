//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTxcULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <omnetpp.h>
#include <Txc12.h>

Define_Module(Txc12);

Txc12::Txc12() {

}

Txc12::~Txc12() {

}

void Txc12::initialize() {
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}

void Txc12::handleMessage(cMessage *msg) {
    if (getIndex() == 3) {
        // Message arrived.
        EV << "Message " << msg << " arrived.\n";
        delete msg;
    } else {
        // We need to forward the message.
        forwardMessage(msg);
    }
}

void Txc12::forwardMessage(cMessage *msg) {
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.
    int n = gateSize("gate");
    int k = intuniform(0, n - 1);
//    if (!(msg->isSelfMessage())) {
//        EV << "Message " << msg << " is a not a self message.";
//        cGate *gate = msg->getArrivalGate()->getIndex();
//        EV << "Message arrived at gate index " << arrival << endl;
//        while (k == arrival) {
//            k = intuniform(0,n-1);
//            EV << "Chose forward gate index " << k << endl;
//        }
//    }

    EV << "Forwarding message " << msg << " on port out[" << k << "]\n";
    send(msg, "gate$o", k);
}
