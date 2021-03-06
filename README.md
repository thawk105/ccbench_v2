# CCBench_v2 : Redesign and Implement Many Concurrency Control
![build_and_test](https://github.com/thawk105/ccbench_v2/workflows/build_and_test/badge.svg)

The following repository is the predecessor of this repository.<br>
https://github.com/thawk105/ccbench

---

## Installing a binary distribution package
On Debian/Ubuntu Linux, execute below statement.
```
$ git clone --recurse-submodules this_repository
$ cd ccbench_v2
$ sudo apt update -y && sudo apt-get install -y $(cat build_tools/ubuntu.deps)
```

## Prepare using
- Processing of build_tools/build_script_masstree.sh :<br>
```
$ cd ccbench_v2
$ ./build_tools/build_script_masstree.sh
```
Build third_party/masstree.
- Build by referring to .github/workflows/build_and_test.yml. 

---

## Data Structure
### Masstree
This is a submodule.  
tanabe's wrapper is src/index/masstree\_beta/include/masstree\_beta\_wrapper.hpp

---

## Details for improving performance
- It uses xoroshiro128plus which is high performance random generator.
- It is friendly to Linux vertual memory system.
- It reduces memory management cost by our original technique.
- It refrain from creating temporary objects to improve performance as much as possible.
- It fixed bug of original cicada.
- It modifies almost protocols appropriately to improve performance.

---

## Welcome
Welcome pull request about 
- Improvement of performance in any workloads.
- Bug fix.
- Improvement about comments (doxygen style is recommended).
- Improvement of versatile.
- Extending CCBench
- Extend tests.
