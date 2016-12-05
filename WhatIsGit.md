**Problem**: I need to move stuff from one repo to another 

#What is Git???
[Something Interactive][1]
[1]:http://ndpsoftware.com/git-cheatsheet.html#loc=workspace;
[Git Conceptual Guide][2]
[2]:https://www.sbf5.com/~cduan/technical/git/git-4.shtml
First, there's a bunch of files (maybe of a project) that we would like to manage, they belong in a directory. 

A **repository** is a data structure that stores stuff like *commit objects* and *heads* (commit objects references)

###Repositories

#### the commit object:
- {files}
- references to **parent* commit objects (CO's from previous point in time which were edited)
- an id: **SHA1 name** (a 40-char string that identifies the commit -> identical commits have the same name)

Initial commit: no parent, first commit made to the empty repository 

#### the repository:

If commit objects are nodes, then a **repository** can be represented as an acyclic (because you can't travel back in time) graph 
```
time >>>>>>>>>>>>>>
initial commit <<<<<<<<<<<< commit history
```
#### the head:
- a reference to a commit object
- every repo can have many heads, but only one *current head* **HEAD** at any given time
- e.g. ```master```
- ```head``` is used interchangeably with ```branch```, but different heads usually refer to different branches

####initialization
while in a new directory (for a project), running ```git init``` 
- initializes a repository for that directory 
- creates a ``` .git``` directory in the project directory

while coding, before the commit, we are in the "workspace", aka local checkout 
```
def workspace: 
the local checkout that you code on
```
####creating a commit
- we need to add the files we want to commit into the index

```
def index:
also known as cache, the files that you want to commit
```

```
git add
``` 
- will automatically add the files that have not changed since the last commit + whatever appends
- is recursive and ```git add .``` will add everything that's been changed
- ```-u``` adds all modified files but not new files

Now, we can run ```git commit``` , which creates a new commit object with the current HEAD as its parent
After the commit, HEAD will point to the new commit object 

####other commands for your repo:

- git log - shows log of all commit objects from HEAD back to initial commit
- git status - shows the files that have been changed between current state and HEAD
  - shows: new files that haven't been added, modified files that haven't been added, and added files
- git diff - shows the differences of current state against HEAD
  - [file] argument shows what has been changed in the file 
- git mv & git rm - like git add, mark files to be *moved* and *removed* from the index

###Branching
- so we can take copies of old commit objects and make changes to them without interfering with our current progress
- head is the most current node of our **branch** (the history of parent commit objects that precedes it) 
- to retrieve an old commit, we can do ```git log``` and get the SHA1 name of that object.

####creating a new branch:
```
git branch [somefeature] [SHA1 hash/commit object reference]
```
- a new head with name ```somefeature``` will be created, and it will point back to the referenced commit
- if no commit object is specified, it will point to the current HEAD
- assuming you are on another branch right now, you will need to do ```git checkout [somefeature]``` to switch your HEAD to the new head (somefeature)
  - remember to commit the changes in the current head before checking out to another head!
  - with git checkout, we're in the workspace and can start working again
  - after we finish with Elise, we add and commit the changes

Now, assuming that before the birth of Elise, we only had one *master* branch with commits Alice, Bob, and Carl. Our previously most-current HEAD was Carl, however, the parent of Elise is Bob. Now, there are **two** branches, each headed by Carl (master) and Elise (somefeature), and looks like this:

```
                +------------(Elise)
              /                 |
(Alice) -- (Bob) -- (Carl)  somefeature
                      |         | 
                    master     HEAD
                        
```
####other useful commands for our branch:
- git branch: lists existing heads with an * next to HEAD
- git diff master **..** somefeature: difference between Carl and Elise
- git diff master **...** somefeature: 3 dots shows difference between Elise and Bob (common ancestor of Carl and Elise)
- git **log** master **..** somefeature: change log between Elise and Bob

Usually, the **master** branch (main branch or "trunk") contains the releasable work, while other branches contain work-in-progress or new features. This allows commits to be made to ongoing-work at anytime without worrying about the quality and usability of the main project.--> Good for collaoration too!
  
###Merging Branches
After finishing a branch, you want to merge the head to the main branch (master). 

2 commands can be used:
  1. ```git merge [head]```  
  2. ```git pull . [head]```

First, let's say that we updated Carl again, so the repo now looks like:
```
                +------------(Elise)
              /                 |
(Alice) -- (Bob) ------------ (Carl) ----- (David)    
                                |             |          
                           somefeature     master  
                                              |
                                             HEAD
```
- Let's say that, we really liked what we did with Elise and we want to merge it into David (head of main)
- We'll call ```somefeature``` ```merge``` and ```master``` ```current```
- ```master``` and ```somefeature``` is shown to have the common ancestor Bob, who we'll call ```ancestor-commit```
- If ```somefeature``` is ```ancestor-commit``` (```ancestor-commit = merge```), then our job is done here because ```master``` is simply the new head of ```master```!
- If ```master``` is ```ancestor-commit```, then we do a **fast-forward merge** (more on this later)
- In our case, Bob is just Bob, so the difference between Elise aka ```merge``` and Bob aka ```ancestor-commit``` will be merged into ```current```, which is David.
- If there are no conflicts, a new commit object (head), whose parents are ```current``` and ```merge```, will be created, and ```current``` will now point to this new head.
- if there was a conflict, approperiate marks would be inserted and no commit would be made

Let's see what would happen if we ran ```git merge Elise```
```
                +------------(Elise)-----------------------+
              /                 |                           \
(Alice) -- (Bob) ----------- (Carl)---------(David)------- (Frank)
                                |                             |
                             somefeature                    master
                                                              |
                                                             HEAD
```
A new commit object named Frank would be created! This is the commit object with parents **David and Elise**, the features from Elise are now merged *into* David.

####but what if there's a conflict?

If both ```current``` and ```merge``` has a change in the same line of Bob's code, Git won't know which one to use! Therefore, edit the conflicting files, then run ```git add``` to add the resolved files. Finally, run ```git commit``` to commit the repared ```merge```. 

####now, what was a fast-forward merge again?

A fast-forward merge is an optimization for merging. It happens when ```ancestor-commit``` is the most-current head of the main branch (master), and also the parent of ```merge```. 
- in this case, no merging needs to be made! 
- Git only needs to shift the ```current``` pointer to point to ```merge```, and HEAD is still at ```current```. 
so in our case, if Carl and David never existed, we would fast-forward merge Elise into Bob.
```
           +-- Elise
          /      |
Alice -- Bob     |
          |   to-merge
       current
          |
         HEAD
``` 
becomes
```
           +-- Elise
          /      |
Alice -- Bob     |
             to-merge, current
                 |
                HEAD
``` 
####so what is the point of merging?

We typically merge a branch for two reasons. 
  1. There's a new feature that we would like to integrate into the master (the working product)
  2. While working on the feature, we have made bug fixes and other changes to the master, and we want to update our feature branch to avoid any conflicts
  
####deleting a branch (clean-up)
Once we have merged a feature branch, we probably don't need it anymore. At this point, we want to clean up our repo by deleting the branch's head (in our case, it's ```somefeature```. 
```
git branch -d [somefeature]
```
We can do this without having to worry about not being to access Elise anymore because we know we can go back to Elise from ```master```. However, if ```somefeature``` was the only head that could reach Elise, then don't delete it!! Elise can't be checked out if it's not an ancestor of ```master```, and it becomes a "**dangling commit**" with lost information.

Note: the option ```-D``` let's you forcefully delete a branch that would create a dangling commit, but use with care!

###Collaborating! (What makes Git git -> distributed version control model)
advantages of Git:
- repo is stored alongside the working copies of files
- stores the entire history of the project
- does not need an external server
- however, because you can't access the working copies at once, two developers **can't share a repository**

####Distributed Version Control 
- To share work among developers
- get a copy of their repo
- copy their changes into your own repo
- let them know your changes

Transport protocols: SSH/HTTP (remote specifications)

###getting a copy of another repo
Take this repo, *aboutme*, for example. Run:
```
git clone [remote-specification]
```
where the repo has an URL-like name (for my aboutme): ```git@github.com:wandiliu/aboutme.git```

running 
```
git clone git@github.com:wandiliu/aboutme.git
``` 
would do
  1. Create a directory named ```aboutme``` and initialize a new repo
  2. Copy all the commit objects from ```aboutme``` to the new repo
  3. Add a default **remote repository reference** named **origin** to the new repo
  4. Associate **origin** with ```aboutme``` by adding **remote heads** named **origin/[head-name]** for all the heads in ```aboutme```
  5. Add another remote head that tracks the current active head in the cloned repo with **origin/[current-head-name]**
  
  You now have a complete copy of ```aboutme```

- To make changes to a remote branch, you should set up a local tracking branch 
- ```git branch --track [new-local-branch] [remote-branch]```

Note:
  1. The ```aboutme``` repo hosted on Github is the *origin*, which is also known as the **Upstream Repository**
  2. The remote head references are updated as you update the remote repository (more on this later) 
  
####Receiving Changes from the Remote Repository 
- When changes have been made to origin by others, you want to receive those commits too. What do you do? 
- running ```git fetch [remote-repository-reference]``` will retrieve the commit objects update and add all the heads 
  - remote heads are updated at this point to reflect the origin's heads. However, your heads in your own cloned repo will remain in place 
- To update your own heads, use ```git pull [remote-repository-reference] [remote-head-name]``` 
  - usually, git pull will perform a fetch automatically - > that's why we just pull!
 
####Sending Changes to the Remote Repository 
- What's the opposite of pull? **push**!
- ```git push [remote-repository-reference] [remote-head-name]``` will
  - direct the *remote* repository to add new commit objects sent by the pushing repo (on your end)
  - the remote heads will be updated to point to where they should in the pushing repo
  - with no arguments, git push will push all the branches in the repo that are set up for tracking
  
####Pushing and Fast-Forward Merges

####Adding and Deleting Branches Remotely

####Difference between distributed vs. centralized source control system


