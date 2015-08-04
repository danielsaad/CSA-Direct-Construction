# CSA-Direct-Construction
Compressed Suffix Array construction using plug-and-play succinct data structures from Simon Gog's sdsl.


##Compilation
First, execute the scrit from sdsl to install the library.

```shell
external/sdsl-lite-master/install.sh .
```
Next, go to thebuild folder.
```shell
cd build
```
Then, with cmake generate makefiles and compile the executable.

```shell
cmake ../
make release
```
Finally, install the executable in the bin folder.

```shell
make install
```

##Execution




