This is my (Scott Saunders) collection of things regarding summer 2017 research.

I use git-submodules for linking to other git-repos, (I don't usually update the references included in this branch, I just use it to initalize them.)

Quick use:
  cd ./someFolderThatIsAGitSubmodule
  git submodule init ./
  git submodule update --remote ./
  git checkout master 
  then use it like a normal git. (Note: do not add in the changed refrences in the s2017 git, as that _can_ cause data loss in some cases.)


