# Haskell

This directory contains one or more attempt to implement the GUI using Haskell.

## Haskell MVC Packages

In order of priority:
* TODO https://github.com/Gabriel439/Haskell-MVC-Library
* TODO http://www.haskellforall.com/2014/04/model-view-controller-haskell-style.html
* TODO https://github.com/keera-studios/keera-hails
* TODO https://wiki.haskell.org/Phooey
* TODO https://github.com/Gabriel439/Haskell-Typed-Spreadsheet-Library

## Research Existing Approaches

Requirements:
* understand their philosophy
* check if they can support MVC, and the grid example

### "Can GUI Programming Be Liberated From The IO Monad"

SOURCE: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.167.3926&rep=rep1&type=pdf

It uses wxHaskell as low level GUI library.

It uses OFRP and wxFroot as FRP engine. The FRP library is ArrowBased. It maps all wxHaskell objects to the FRP world. OFRP is a bridge between FRP and the OO world.

OO objects are destroyed when there is a switch in the FRP model, and the objects are not any more accessibles. So initializations and finalizations are implicit in OFRP.

Containers (parent of a child object) are explicit in OFRP: they must be always specified. In other frameworks like QML the parent is implicit, by the point where a component is defined.

PROBLEM: FRP framework is push based: the signals are generated and processed. But in case of MVC widget, the Grid widget should ask to the Model component the data to display, so it is also PULL based. But a Grid widget, must be also advised from its model if there are changes. So the interaction is also PUSH based. It seems that OFRP manage only PUSH-based GUIs.

PROBLEM: all the widgets of the GUI can interact together and there is no a clear distinction between Models and Views.

FACT: it uses a modified version of YAMPA, but Netwire is probably now better.

### Haskell-MVC-Library

SOURCE: https://github.com/Gabriel439/Haskell-MVC-Library

SOURCE: http://www.haskellforall.com/2014/04/model-view-controller-haskell-style.html

SOURCE: http://www.haskellforall.com/2014/06/spreadsheet-like-programming-in-haskell.html

It introduces a clear distinction between:
* Model: pure streaming transformation from controller inputs to view outupts, according its state
* View: specify which are the view commands of the GUI, in a declarative way.
* Controller: specify which are the inputs to the Model, in a declarative way.
* Managed: manage IO resources, and create Controller signals from mouse and keyboard events, and dispaly View commands on the screen

In this approach the Managed can be changed with something of different that do not use the IO, but only tests the GUI in a declarative fashion. Infact Model, View and Controller are declarative specifications, and they are associated to a low level implementation/effect, only through the Managed function.

MAYBE In this approach the Model plays a lower level role, respect traditional MVC frameworks, because it manages directly the state, and because its produce directly View commands. Internally it can be probably layered in order to create a more high-level distinction between pure data model, and a widget, but part of the widget functionality is probably (check) in the Model.

The function for running the GUI is

    runMVC
      :: s
      --^ Initial state
      -> Model s a b
      --^ Program logic: a Model with state s,
      --  accepting controller input a,
      --  and outputting view desription b 
      -> Managed (View b, Controller a)
      --^ Impure output and input
      -> IO s
      --^ Returns final state

Some nice things about this:
* the `View b` accept a fixed `b` as output language, because it is the same `b` used in the Model, but during Testing the View component can not display the GUI but perform other actions. The same is true for the `Controller a` that can be some test-code.

TODO check where stays the description of the GUI: Managed or View or Model?

TODO check if the Model transform state `s` and controller `a` commands, into a View `b`. In this case it is a pure transformation approach from Model to GUI. See if a attribute-grammar transformations are better instead.

MAYBE use a Actor/Erlang like library for Models, for answering to questions about the Model. Check if this is feasible and enough Haskell-like, or there is an impendance mismatch problem.

TODO for comprehending the source code study also these classes:
*  https://hackage.haskell.org/package/contravariant-1.4/docs/Data-Functor-Contravariant.html#t:Contravariant
* http://hackage.haskell.org/package/foldl-1.0.7/docs/Control-Foldl.html
* https://hackage.haskell.org/package/managed-1.0.1/docs/Control-Monad-Managed.html#t:Managed

FACT Managed is a generic Haskell class for managing IO resources:
* acquire
* work
* release lock

The SDL example:
* specify inside the Managed the actions to perform for displaying the View objects.
* it's very dense and not much readable/understable.
* uses a lot the pipes for input events (controller), and output events (Model). Pipes are transformed in controllers using functions like `produce`, and in Views from other functions.
* Model is defined in this example, through a Pipe accepting the input from the controller, and outputing a a result. The `asPipe` function transforms the Pipe into a correct Model.
* the `sdl` Managed function transforms the `View` data received from the Model into IO commands for SDL, using the `asSink` function that transforms a IO action into a View
* the `sdl` Managed function create Controller, using the wrapping function `producer` that take a Buffered Pipe in IO, and return the events
* the Model knows how to manage the events from the controller, and which views generate in response. The `sdl` manage maps only Views to real commands, and map external events to controller events.

The SDL example decouple the IO actions for interacting from the external, from the Model and View.

View and Controllers are Monoids, so `mconcat :: [View a] -> View a`. This is the main composability approach followed by the library: all views and controllers are merged into only one and sent to `runMVC` function. A curious things justify functors:
* by default we can compose with `<>` only `View SomeType` of the same `SomeType`
* but we can use a Function, creating Views of type `View (Either TypeA TypeB)` and then we can take advantage of `fmap f (c1 <> c2) = fmap f c1 <> fmap f c2`

SOURCE: http://www.haskellforall.com/2014/06/spreadsheet-like-programming-in-haskell.html

In this example it creates a spreadsheet like application:
* create a pipe converting input cells into output cells
* create a Managed that creates Gtk widgets
* uses MVC.Udpdates for creating updatable Gtk widgets (like in a FRP approach)
* Updatable values are Monoid, so they are composable

Also in code like this

    lastLine :: Updatable (Maybe String)
    lastLine = debug "lastLine" (on last stdinLines)

the idea of Haskell is not writing imperative code, but to transform `stdinLines` into an `Updatable` version, using the `on` function. So it is a transformation based approach also in the low-level code, and not only on the data. But in Haskell functions are first-class citzien, so if data can be easily transformed, so also code. So this code expanded says something like this:
* take a `stdinLines` thas is a pipe reading from the standard input
* transform to an Updatable value using `on last`
* transform to an Updatable action using `debug` that write to the stdout

PROBLEM in the long run a highly applicative-like code in Haskell seems a forth code, where the programmer must expand the functions, and the types for understanding its meaning. For sure a good IDE making this type of expansion (for readibility) or helping transforming data (during writing) can help. For example during application writing one starts describing the initial data to transform, and then the IDE suggests the functions transforming the data to something of similar to the function final type. During reading of code, the IDE can describe the intermediate types of each transformation passage. 

PROBLEM the spreadsheet example create buttons according View commands. There is no yet a full intermediate layer mapping each Gtk widget to an intermediate View counterpart.

MAYBE in mvc-library maybe the solution is putting in the Model the data, and then having a command creating the Widget. It is the Managed that creates a proxy model for the Widget world. So it is not the Model being PULL based, but it is an intermediate object created from the Manage. The Managed creates for each linked part of the Model, a Widget linked using the approach of the underlying Widget library. In case it seems that for each wx widget there is in wxhaskell a low-level proxy object. So I can use low-level WX library, and discard high-level mapping to Haskell, because I will use mvc-library approach, and Managed will use under the hood the low level mapping.

TODO continue reading the papers for understanding the approach

TODO how can I integrate already implemented widgets libraries (wxhaskell / hsGtk / ...) with this approach

TODO how it compares against traditional FRP approaches



