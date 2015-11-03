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
#include <Txc7.h>

// The module class needs to be registered with OMNeT++
Define_Module(Txc7);

Txc7::Txc7() {
    // Set the pointer to NULL, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    event = tictocMsg = NULL;
}

Txc7::~Txc7() {
    // Dispose of dynamically allocated the objects
    cancelAndDelete(event);
    delete tictocMsg;
}

void Txc7::initialize() {
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be 'tic'.

    // Create the event object we'll use for timing -- just any ordinary message.
    event = new cMessage("event");

    if (strcmp("tic", getName()) == 0) {
        EV << "Scheduling first send to t=5.0s\n";
        scheduleAt(5.0, event);
        tictocMsg = new cMessage("tictocMsg");
    }
}

void Txc7::handleMessage(cMessage *msg) {
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate 'out'. Because both 'tic' and 'toc' do the same, the message
    // will bounce between the two.

    // There are several ways of distinguishing messages, for example by message
    // kind (an int attribute of cMessage) or by class using dynamic_cast
    // (provided you subclass from cMessage). In this code we just check if we
    // recognize the pointer, which (if feasible) is the easiest and fastest
    // method.
    if (msg == event) {
        // The self-message arrived, so we can send out tictocMsg and NULL out
        // its pointer so that it doesn't confuse us later.
        EV << "Wait period is over, sending back message\n";
        send(tictocMsg, "out");
        tictocMsg = NULL;
    } else {
        // If the message we received is not our self-message, then it must
        // be the tic-toc message arriving from our partner. We remember its
        // pointer in the tictocMsg variable, then schedule our self-message
        // to come back to us in 1s simulated time.

        // "Lose" the message with 0.1 probability:
        if (uniform(0, 1) < 0.1) {
            EV << "\"Losing\" message\n";
            delete msg;
        } else {
            // The "delayTime" module parameter can be set to values like
            // "exponential(5)" (tictoc7.ned, omnetpp.ini), and then here
            // we'll get a different delay every time.
            simtime_t delay = par("delayTime");

            EV << "Message arrived, starting to wait " << delay << " secs...\n";
            tictocMsg = msg;
            scheduleAt(simTime() + delay, event);
        }
    }
}
