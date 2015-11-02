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

#include <omnetpp.h>
#include <Txc6.h>

// The module class needs to be registered with OMNeT++
Define_Module(Txc6);

Txc6::Txc6() {
    // Set the pointer to NULL, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    event = tictocMsg = NULL;
}

Txc6::~Txc6() {
    // Dispose of dynamically allocated the objects
    cancelAndDelete(event);
    delete tictocMsg;
}

void Txc6::initialize() {
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be 'tic'.

    // Create the event object we'll use for timing -- just any ordinary message.
    event = new cMessage("event");

    if (par("sendMsgOnInit").boolValue() == true)
    {
        // We don't start right away, but instead send an message to ourselves
        // (a "self-message") -- we'll do the first sending when it arrives
        // back to us, at t=5.0s simulated time.
        EV << "Scheduling first send to t=5.0s\n";
        tictocMsg = new cMessage("tictocMsg");
        scheduleAt(5.0, event);
    }
}

void Txc6::handleMessage(cMessage *msg) {
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate 'out'. Because both 'tic' and 'toc' do the same, the message
    // will bounce between the two.

    // There are several ways of distinguishing messages, for example by message
    // kind (an int attribute of cMessage) or by class using dynamic_cast
    // (provided you subclass from cMessage). In this code we just check if we
    // recognize the pointer, which (if feasible) is the easiest and fastest
    // method.
    if (msg==event)
    {
        // The self-message arrived, so we can send out tictocMsg and NULL out
        // its pointer so that it doesn't confuse us later.
        EV << "Wait period is over, sending back message\n";
        send(tictocMsg, "out");
        tictocMsg = NULL;
    }
    else
    {
        // If the message we received is not our self-message, then it must
        // be the tic-toc message arriving from our partner. We remember its
        // pointer in the tictocMsg variable, then schedule our self-message
        // to come back to us in 1s simulated time.
        EV << "Message arrived, starting to wait 1 sec...\n";
        tictocMsg = msg;
        scheduleAt(simTime()+1.0, event);
    }
}
