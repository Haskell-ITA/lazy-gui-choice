# lazy-gui-choice

The scope of the project is evaluating different GUI frameworks, comparing the code implementing a Demo Application.

## Demo Application

### Specification

There is a grid/table with two columns:
* task description
* a check-box indicating if the task is completed
* estimated minutes for completition in case the task is not done, effort in case the task is completed

Through the grid the user can:
* add tasks (mandatory)
* delete tasks (optional)
* modify tasks (mandatory)
* insert task in a certain position of the grid (optional)

The grid can be sorted on task description and on estimated minutes for completition. (optional)

The grid can be unsorted. In this case it is used the user explicit order of task insertion. (mandatory)

The grid is initializated with 100 tasks of the form <"Task 1", 1 minute>, <"Task 2", 2 minutes>, and so on.

There are two read only fields at the top of the window, with the total hours and minutes required for:
* completing all the tasks (e.g. the sum of all estimates)
* spent minutes on completed tasks (e.g. the sum of all efforts)

There is a ESTIMATE command box accepting a float value, and multiplying all the estimated minutes by the specified value.
So the command works only for tasks not already done.

There is a UNDO button, that can UNDO the command box action, for a reasonable number of times.

There is a REDO button, for invalidating the last UNDO.

The ESTIMATE command box is affected by UNDO and REDO (mandatory).

The GRID editing commands can be affected by UNDO and REDO (optional).

### Requirements

The grid does not store the data internally, but retrieves the data from an external model. 

The commands ESTIMATE, UNDO, REDO are commands accepted from the Model, and not from the Grid.

When the Model is changed by a ESTIMATE, UNDO, REDO command, it must inform the Grid that there are changes.

### Motivations

The UI represents a rather complex GUI usage scenario, where:
* changes in the Model, are signaled to the View GUI Widgets (MVC pattern)
* GUI widgets can change the Model
* Model is external to GUI widgets 
* there is a UNDO/REDO command pattern

