# Develop

## Code Guidelines

Assume the reader does not know the library, and he must evaluate it. So add many comments in the code, describing the library approach/philosohpy. 

## Git Commands for Collaborating with Other Developers

Create a develop branch, locally and on GitHub

    git checkout -b some-feature-branch
    git push --set-upstream origin some-feature-branch
    git push some-feature-branch

Develop. Then commit, and send to remote branch, for interacting with other developers.

    git commit -a -m "..."
    git push

When it is ok the feature can be merged to the master branch, deleting intermediate changes.

    git checkout master
    git merge --squash some-feature-branch
    git commit

Delete locally and remotely the branch

    git branch -D some-feature-branch
    git push origin :some-feature-branch

# Discussions

This file, other README files, and source files, are used also like temporary discussions scratchpad.

Temporary annotations, inspired from De Bono "Six Thinking Hats", that can be used for commenting the changes in source-code are:
* TODO 
* MAYBE
* DONE 
* FACT (white hat)
* POSSIBLE-DECISION (blue hat)
* DECISION (blue hat)
* PROBLEM (black hat)
* INSPIRATION (red hat)
* POSSIBLE-SOLUTION (green hat)
* OPPORTUNITY (yellow hat) 
* CANCELLED 

# Projects to Consider

## Functional-like MVC for non-Haskell projects

In order of priority:
* TODO https://github.com/glazedlists/glazedlists for Java
* TODO http://todomvc.com/
* TODO http://www.parsonsmatt.org/2015/10/03/elm_vs_purescript.html

# Tasks / Issues

TODO add a nix build script for every project

TODO write the code in the spirit of literate programming for documenting the philosphy of each approach



