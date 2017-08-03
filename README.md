## What is this
This is my (Scott Saunders) collection of things regarding summer 2017 research.

This is the main-level work directory for me during the summer 2017 research project. The folders at the top level are for my commonly used programs/utilities/scripts/text files.

Most of the directories here are git submodules, linking to other gits.
# Submodule Quick use:
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
* testdata.sh - obsolete way of running the pipeline. (How I was doign it initally)
  
# Sub-modules:
 *   pcl - my fork of PCL
 *   spcl - The stanford PCL fork. (I also have one, but this does not reference it, mine only has a dos2unix run on it.)
 *   libfreenect2 - The same, but for libfreenect2
 *   openni2 - The same, but for Openni2...
 *   ER_port - git submodule of the Elastic Reconstruction port.
 *   ER_myfork - a reference to my fork of it (unused, but will be a clone of ER_port)
 *   GraphOptimizerTest - Eriks GO-tester.
 *   StSTK - Structure SDK
 *   3D-re - Erik's 3D-reconstruction program (it just records data.)
    
# Directories:
 *   setup - my partal setup scripts.
 *   misc - misc programs/related projects.
 *   notes - misc notes.
 *   utils - misc utilities.
 *   freenect2 - incomplete attempt to apply image registration using the libfreenect2 library.
 *   oni_stuff - Has my own OpenNI utilities. ni2Recorder (What I use to record data.) ni1Recorder/ni1Reader/ni2Reader (Readers very simply try to access data)
              - Has a converter submodule, this is my Oni2 -> Oni1 converting library.

