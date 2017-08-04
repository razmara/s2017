# What is this?

This is my quick setup/reference directory.

Note: This is based off arch-linux, where the package manager is `pacman`, and there is a utility `makepkg`, which will make a package for pacman.

I use both for setting it up, pacman should be more/less replaceable with any other package manager (Except, that it *always* includes the dev files, (Debain sometimes has them seperated out.))


# Setting it up:

1. Get a Arch-linux install (The wiki is good for this). Arch linux derivatives should also work.
2. Install git and helpfull commands: `sudo pacman -S git openssh sudo`
3. Edit /etc/makepkg.cfg : You need to remove the -fno-plt in C\_FLAGS and CXX\_FLAGS. (Also edit the makeflags -j2 line, to be the number of cpu's you have for faster compiling)
4. Clone this repo: `git@github.com:ttoocs/s2017.git` (Note: to use the git@ urls, (which is what I use), you need to setup your ssh-key with github. `ssh-keygen` generates the key in ~/.ssh/.
5. Run `s2017/setup/setup.sh` - This will first install all the basic packages, then install all the local/forked packages. (All but ER are system-wide installed)

