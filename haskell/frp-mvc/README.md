# frp-mvc

A demo using a proof-of-concept MVC based FRP library.

If the demo is successful, then a standalone library will be extracted.

## High Level Design

### The Problem

A FRP network is based on nodes collaborating using a PUSH approach. Each node send (PUSH) a signal to receiving nodes.

In case of QT example, the SIGNAL and SLOT pattern mimic a FRP network of objects. So Widgets in a QT application can be seen as nodes of a FRP network.

The problem it is that the MVC pattern requires also a PULL mode, because sometimes the Viewer needs to read only a subset of data from the Model, and the Model does not know this in advance. For example during initialization, a GridWidget asks to the GridModel only the rows that are in current viewport. Change notifications are sent using a PUSH model, but initialization and advanced interactions between the Model and the Viewer, are done using a PULL model. 

In case of QT example, a GridModel reference is sent to the GridWidget object, and the GridWidget calls functions of the Model for retrieving (PULLING) data from the model.

The FRP network can only work in PUSH mode. So the MVC pattern can not be modelled completely in the FRP network.

In Haskell case, we can follow the QT method, only if the GUI is implemented directly in Haskell. In this case the Viewer is a node of the FRP network, and it can receive the Model as part of the signal. Then it can extract only the relevant part from the Model, using normal Haskell functions on the Model. Normal Haskell functions works in PULL mode, while the rest of the FRP network works in a PUSH way.

But in Haskell, usually we use GUI frameworks developed in C/C++, and the GUI widgets live in a C run-time. So the run-time of the GUI library is distinct from the run-time of the Haskell application. We want to manage the Model with Haskell code, because our application logic is written in Haskell. So the Model lives in the Haskell run-time, and it can not be easily transferred to the Viewer widget.

In case of simple Widgets with simple Models, like Labels, TextBox a short model like a string is simply transferred to the external GUI widget. But in case of complex models like GridModel, we can not transfer it to the C run-time. 

### The Solution

In practice MVC applications uses very few types of Models. Usually a ListModel, a TreeModel, a GridModel and a RichTextModel. We can define a Model in the Haskell world for each of these types of Models, and we can share with the C run-time and external-widgets using a proxy object living in the C run-time, proxying requests of the GUI Widgets to the Haskell run-time.

So the Model is specified in Haskell, but it is also exposed to the external C run-time and to the other GUI widgets.

TODO continue describing how the various Models implementation are mapped to the common interface



