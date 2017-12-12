# VisioTec Libraries #

This repository contains ready-to-use computer vision libraries developed at the VisioTec group from the CTI-Renato Archer research institute.

## Resources ##

* Homepage: [https://sites.google.com/site/geraldofsilveira/]()
* Issue Tracking: [https://github.com/lukscasanova/vtec/issues]()   

## Compiling Instructions ##

In the [lib](lib) folder, you'll encounter our pre-compiled libraries.
To compile the examples, use the following commands:

```
git clone https://github.com/lukscasanova/vtec.git
cd vtec
mkdir build
cd build
cmake ..
make
```


## Libraries ##

### Homography Optimizer ###

This library provides software capable of estimating the homography and photometric parameters that, when applied to a reference image, will minimize the pixel intensity-based error to a current analyzed image. We call this algorithm Intensity-Based Global (IBG), as it is uses direct approach to the estimation (i.e. no feature extraction step), hence Intensity-Based; and it is robust to global illumination changes in the image. We also offer 3 variants of the algorithm, which make different assumptions about the motion constraints involved.

#### Documentation and Citing ####

The technical report available [here]() describes the software and its working principles. If you use this software in an academic context, please cite the technical report, using:

```
@TechReport{nogueira2017,
  author =  {Lucas Nogueira and Ely de Paiva and Geraldo Silveira},
  title =   {VISIOTEC Intensity-based Homography Optimization Software: Basic Theory and Use Cases},
  institution = {CTI},
  year =  {2017},
  address =   {Brazil}
}

```


#### Examples ####

After compiling, run the following commands from the root of the repository.

* Homography Optimizer: 
```bash
  $ ./build/vtec_ibg_optimize_homography_example
```

* Visual Tracking
```bash
  $ ./build/vtec_ibg_tracker_example
```

More details on the examples can be found on the [technical report]()


## Licensing ##

This software is being made available for research purposes only.  See
the [LICENSE](LICENSE.txt) file in this directory for conditions of use.

## Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/lukscasanova/vtec/issues).
