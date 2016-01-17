# Develop

## Code Guidelines

Assume the reader does not know the library, and he must evaluate it. So add many comments in the code, describing the library approach/philosohpy. 

## Git Commands for Collaborating with Other Developers

Create a develop branch, locally and on GitHub

    git checkout -b some-feature-branch
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

# Projects to Consider

## Haskell MVC

In order of priority:
* TODO https://github.com/Gabriel439/Haskell-MVC-Library
* TODO http://www.haskellforall.com/2014/04/model-view-controller-haskell-style.html
* TODO https://github.com/keera-studios/keera-hails
* TODO https://wiki.haskell.org/Phooey
* TODO https://github.com/Gabriel439/Haskell-Typed-Spreadsheet-Library

## Functional-like MVC

In order of priority:
* TODO https://github.com/glazedlists/glazedlists for Java
* TODO http://todomvc.com/
* TODO http://www.parsonsmatt.org/2015/10/03/elm_vs_purescript.html



    

