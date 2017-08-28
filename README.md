## What is this
This is my (Scott Saunders) collection of things regarding summer 2017 research.

This is the main-level work directory for me during the summer 2017 research project. The folders at the top level are for my commonly used programs/utilities/scripts/text files.

Most of the directories here are git submodules, linking to other gits.

## How to run:

# Initial Setup:
The script `setup/setup.sh` assumes the user is running Arch Linux, and will attempt to install/update all needed dependencies. 

The key dependencies for Elastic Reconstruction:
  * PCL built with kinfu. (Requires Cuda, OpenNI1, VTK... and more)
  * g2o (The default homebrew version of it for MacOSX doesn't quite work, building from source does though. Note: Currently put at a fixed version, as an updated caused segfaults)

# Running:

`source setup_path.sh` will setup the PATH environment variable for use with most utilities in the folder.
`source pipeline.sh` will setup the PATH environment and bash functions to run the Elastic Reconstruction pipeline locally from this folder. (It is also sourced from setup\_path.sh)

At this point, you need to change directory (`cd`) to a folder with data, where you can then run `Pipeline` (defined in pipeline.sh) to run the whole pipeline. Assuming everything works, and meshlab is also installed, you will be left a mesh.ply in a mesh folder in the current directory. Without meshlab, this folder will be empty, and the final results will be in integrate as either go\_world.pcd (Always present) or fo\_world.pcd (Only sometimes present)


## Submodule Quick use:
# New method: setup/submodules.sh

# Old method:
1. cd ./someFolderThatIsAGitSubmodule
2. git submodule init ./
3. git submodule update --remote ./
4. git checkout master ./
5. Then use that directory as a regular git directory.

# Highlights (files):
* todo.txt, is my todo,
* todone.txt, is what I have done.
* pipeline.sh, is how I run the elastic reconstruction pipeline.
* setup_path.sh is a bash `source`-able file, which sets up my $PATH.
* windows_bins.sh - Downloads the windows bins and examples and puts them in a winbin folder.
* testdata.sh - obsolete way of running the pipeline. (How I was doing it initially)
  
# Sub-modules:
 *   pcl - my fork of PCL
 *   spcl - The Stanford PCL fork. (I also have one, but this does not reference it, mine only has a dos2unix run on it.)
 *   libfreenect2 - The same, but for libfreenect2
 *   openni2 - The same, but for Openni2...
 *   ER_port - git submodule of the Elastic Reconstruction port.
 *   ER_myfork - a reference to my fork of it (unused, but will be a clone of ER_port)
 *   GraphOptimizerTest - Eriks GO-tester.
 *   StSTK - Structure SDK
 *   3D-re - Erik's 3D-reconstruction program (it just records data.)
 *   openCV_Traj - A simple program (and shell files) for using OpenCV to generate inital trajectories.    
# Directories:
 *   setup - my partal setup scripts.
 *   misc - misc programs/related projects.
 *   notes - misc notes.
 *   utils - misc utilities.
 *   freenect2 - incomplete attempt to apply image registration using the libfreenect2 library.
 *   oni_stuff - Has my own OpenNI utilities. ni2Recorder (What I use to record data.) ni1Recorder/ni1Reader/ni2Reader (Readers very simply try to access data)
              - Has a converter submodule, this is my Oni2 -> Oni1 converting library.



