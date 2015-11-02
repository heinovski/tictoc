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
#include <Txc3.h>

// The module class needs to be registered with OMNeT++
Define_Module(Txc3);

Txc3::Txc3() {

}

Txc3::~Txc3() {

}

void Txc3::initialize() {
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be 'tic'.

    // Initialize counter to ten. We'll decrement it every time and delete
    // the message when it reaches zero.
    counter = 10;

    // The WATCH() statement below will let you examine the variable under
    // Tkenv. After doing a few steps in the simulation, double-click either
    // `tic' or `toc', select the Contents tab in the dialog that pops up,
    // and you'll find "counter" in the list.
    WATCH(counter);

    // Am I Tic or Toc?
    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbirtrary string which will be the name of the message object.
        cMessage *msg = new cMessage("tictocMsg");
        EV << "Sending initial message\n";
        send(msg, "out");
    }
}

void Txc3::handleMessage(cMessage *msg) {
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate 'out'. Because both 'tic' and 'toc' do the same, the message
    // will bounce between the two.
    // Increment counter and check value.
    counter--;
    if (counter==0)
    {
       // If counter is zero, delete message. If you run the model, you'll
       // find that the simulation will stop at this point with the message
       // "no more events".
       EV << getName() << "'s counter reached zero, deleting message\n";
       delete msg;
    }
    else
    {
       EV << getName() << "'s counter is " << counter << ", sending back message\n";
       send(msg, "out");
    }
}
