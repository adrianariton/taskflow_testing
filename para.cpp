#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <taskflow/taskflow.hpp> 
#include <taskflow/algorithm/reduce.hpp>
#include <taskflow/core/task.hpp>

/***
 * init should be 0 for expected results
*/
template <typename B, typename E, typename T, typename O>
tf::Task one_of(tf::Taskflow& taskflow, B beg, E end, T& init, O bop) {
    auto reduce_bop = [&] (int l, int r) mutable throw() -> int
    { 
        if (bop(r) > 0)
        return 1;
        if (bop(l) > 0)
        return 1;
        return 0;
    };
    return taskflow.reduce(beg, end, init, reduce_bop);
}
template <typename B, typename E, typename T, typename O>
tf::Task maxf_of(tf::Taskflow& taskflow, B beg, E end, T& init, O bop) {
    auto reduce_bop = [&] (int l, int r) mutable throw() -> int
    { 
        return bop(l) > bop(r) ? l : r;
    };
    return taskflow.reduce(beg, end, init, reduce_bop);
}

template <typename B, typename E, typename T, typename O>
tf::Task minf_of(tf::Taskflow& taskflow, B beg, E end, T& init, O bop) {
    auto reduce_bop = [&] (int l, int r) mutable throw() -> int
    { 
        return bop(l) < bop(r) ? l : r;
    };
    return taskflow.reduce(beg, end, init, reduce_bop);
}


/***
 * init should be 1 for expected results
*/
template <typename B, typename E, typename T, typename O>
tf::Task allf_of(tf::Taskflow& taskflow, B beg, E end, T& init, O bop) {

    // o workey, no goody :( will doodey tommorowey
    auto reduce_bop = [&] (int l, int r) mutable throw() -> int
    { 
        return bop(l) && bop(r);
    };
    return taskflow.reduce(beg, end, init, reduce_bop);
}
int main(){
  
    tf::Executor executor;
    tf::Taskflow taskflow;
    int sum = 1;
    std::vector<int> vec;
    std::vector<int>::iterator first, last;

    tf::Task init = taskflow.emplace([&](){
        vec   = {1, 2, 5, 7};
        first = vec.begin();
        last  = vec.end();
        sum = 1;
    });

    tf::Task task = allf_of(taskflow, std::ref(first), std::ref(last), sum, 
        [] (int l) { return l%2; } 
    );

    // wrong! must use std::ref, or first and last are captured by copy
    // tf::Task task = taskflow.reduce(first, last, sum, [] (int l, int r) { 
    //   return l + r;    // binary reducer operator
    // });

    init.precede(task);
    init.precede(task);

    executor.run(taskflow).wait();
  return 0;
}