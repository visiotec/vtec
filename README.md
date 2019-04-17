# VisioTec Libraries #

This repository contains ready-to-use computer vision libraries developed at the VisioTec research group of the CTI Renato Archer. Further information about this group can be found [here](https://sites.google.com/site/geraldofsilveira/talks#TOC-Project-VISIOTEC-in-5-slides).

## Video Examples ##

Click on the thumbnails to watch the videos on YouTube. These videos were created using the VisioTec Libraries in our ROS environment. This environment is also publicly available [here](https://github.com/lukscasanova/vtec_ros).

* Intensity-based visual tracking with full 8-DoF homography

[![YouTube](https://img.youtube.com/vi/r7kZLqQ5xbI/0.jpg)](https://www.youtube.com/watch?v=r7kZLqQ5xbI)

* Robust intensity-based visual tracking with full 8-DoF homography and occlusion handling

[![YouTube](https://img.youtube.com/vi/qhAFe8IbIHc/0.jpg)](https://www.youtube.com/watch?v=qhAFe8IbIHc)

## Installation ##

### System Requirements ###

The master branch contains libraries that have been tested on Ubuntu 16.04. 
To compile and use that branch, you must satisfy the following requirements:

* GCC version 5.4.1 or later
* CMake version 2.8.3 or later
* Git
* OpenCV version 3.2.0 or later

### Download and Compiling ###

There are two ways of getting our libraries. You can either use the [releases](https://github.com/lukscasanova/vtec/releases) page or use **git** to clone the repo.

#### Latest Release ####

Using the latest release version allows you to use the most stable version of our code. Follow the instructions on the [releases](https://github.com/lukscasanova/vtec/releases) page for the installation details.

#### Cloning The Repository ####

Cloning the repository allows you to be up-to-date with the latest -- but possibly unstable -- changes in our codebase. You should be familiar with Git to use this option. You can get more information about it in [here](https://help.github.com/articles/set-up-git). To clone and compile, use the following instructions.

```
git clone https://github.com/lukscasanova/vtec.git
```


Compile the examples code with the following commands:

```
cd vtec
mkdir build
cd build
cmake ..
make
```

## Libraries ##

### Homography Optimizer ###

This library estimates the homography and photometric parameters that minimize the pixel intensity-based error between the reference the current images. This algorithm is called Intensity-Based Global Homography Optimizer (IBGHO), as it is uses a direct approach to the estimation, i.e. with no intermediate steps such as feature extraction or matching, and is robust to global illumination changes and partial occlusions. We also offer 3 variants of the algorithm, which make different assumptions about the motion constraints involved.

#### Documentation and Citing ####

The technical report available [here](https://github.com/lukscasanova/vtec/blob/master/vtec_ibgho_TR.pdf) describes the software and its working principles. If you use this software, please cite the technical report using:

```
@TechReport{nogueira2019,
  author = {Lucas Nogueira and Ely de Paiva and Geraldo Silveira},
  title  = {{VTEC} robust intensity-based homography optimization software},
  number = {CTI-VTEC-TR-01-19},
  institution = {CTI},
  year = {2019},
  address = {Brazil}
}
```

#### Examples ####

After compiling, run the following commands *from the root* of the repository.

* Homography Optimizer: 
```
  $ ./build/ibg_optimize_homography_example
```

* Visual Tracking:
```
  $ ./build/ibg_tracker_with_predictor_example
```

* Visual Tracking Robust to Partial Occlusion:
```
  $ ./build/ibg_tracker_robust_example
```

More details on the examples can be found on the [technical report](https://github.com/lukscasanova/vtec/blob/opencv/vtec_ibgho_TR.pdf).


## Resources ##

* Releases: [https://github.com/lukscasanova/vtec/releases](https://github.com/lukscasanova/vtec/releases)

* IBGHO Technical Report: [vtec_ibgho_TR.pdf](https://github.com/lukscasanova/vtec/blob/opencv/vtec_ibgho_TR.pdf)

* VisioTec ROS package: [https://github.com/lukscasanova/vtec_ros](https://github.com/lukscasanova/vtec_ros/)

* Geraldo Silveira's website: [https://sites.google.com/site/geraldofsilveira/](https://sites.google.com/site/geraldofsilveira/)


## Licensing ##

This software is being made available for research purposes only.  See the [LICENSE](LICENSE.txt) file in this directory for conditions of use.


## Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/lukscasanova/vtec/issues).
