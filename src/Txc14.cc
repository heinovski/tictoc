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
#include <Txc14.h>
#include <tictoc13_m.h>

Define_Module(Txc14);

Txc14::Txc14() {

}

Txc14::~Txc14() {

}

void Txc14::initialize() {
    // Initialize variables
    numSent = 0;
    numReceived = 0;
    WATCH(numSent);
    WATCH(numReceived);

    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        TicTocMsg13 *msg = generateMessage();
        scheduleAt(0.0, msg);
    }
}

void Txc14::handleMessage(cMessage *msg) {
    if (ev.isGUI())
        updateDisplay();

    TicTocMsg13 *ttmsg = check_and_cast<TicTocMsg13 *>(msg);
    if (ttmsg->getDestination() == getIndex()) {
        // Message arrived.
        EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount()
                  << "hops.\n";
        numReceived++;
        bubble("ARRIVED, starting new one!");
        delete ttmsg;

        // Generate another one
        EV << "Generating another message: ";
        TicTocMsg13 *newmsg = generateMessage();
        EV << newmsg << endl;
        forwardMessage(newmsg);
        numSent++;
    } else {
        // We need to forward the message.
        forwardMessage(ttmsg);
    }
}

void Txc14::forwardMessage(TicTocMsg13 *msg) {
    // Increment hop count
    msg->setHopCount(msg->getHopCount() + 1);

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

TicTocMsg13* Txc14::generateMessage() {
    // Produce source and destination addresses.
    int src = getIndex(); // our module index
    int n = size(); // module vector size
    int dest = intuniform(0, n - 2);
    if (dest >= src)
        dest++;

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    TicTocMsg13 *msg = new TicTocMsg13(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void Txc14::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t",0,buf);
}

