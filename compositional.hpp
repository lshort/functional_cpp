/**  This module provides support for composing functions in C++.  
     Composing lambdas, really, but it provides a lightweight way
     to convert any function to a lambda.  
*/

#include <functional>
#include <type_traits>
#include <boost/proto/core.hpp>

namespace functional {
    /**  Maps the function across all the elements of the retainer, 
         constructing a new container of the same type from the results.  
         The container type must support push_back.
         @param[in] function The lambda function to apply
         @param[in] container The container of values to pass to the fcn
         @return The newly constructed container with the results */
    auto map = [] (const auto &function, const auto &container )
    {
        auto retval = container;
        retval.clear();
        for (const auto &elem : container)
            retval.push_back(function(elem));
        return retval;
    };

    auto flip = [] (const auto &function) {
        return [function] (auto x, auto y) { return function(y,x); };
    };
}


namespace mutates {
    /**  Maps the function across all the elements of the container, 
         replacing the values in the container as it goes.  
         @param[in] function The lambda function to apply
         @param[in] container The container of values to pass to the fcn
         @return The newly constructed container with the results */
    auto tmap = [] (const auto &function, auto &container )
    {
        for (auto &elem : container)
            elem = function(elem);
    };
}


namespace compositional {
    /**  Composes two functions, which must be lambdas
         @param[in] l1 The outer function
         @param[in] l2 The inner function
         @return A lambda function, the composition of l1 and l2 */
    template<typename Lambda1, typename Lambda2 >
    //             class = typename std::enable_if<std::is_function<Lambda1>::value>::type>
    auto operator* (Lambda1 l1, Lambda2 l2)
    {  return [l1, l2](auto&& ... x) { return l1(l2(std::forward<decltype(x)>(x)...)); };  };



    /**  Casts any function to a lambda
         @param[in] fp The input function pointer
         @return A lambda function which applies fp to its arguments */
    template<typename return_type, typename ...params>
    auto _L( return_type (*fp) (params... args))
      { return [fp] (params... args) { return fp(args...); }; };



    /**  Casts any function to a lambda, binding the first argument to x
         @param[in] fp The input function pointer
         @param[in] x The value of the first argument to the function
         @return A lambda function which applies fp, taking x as the first
         @return argument of the function invocation, others supplied at call site 
    */
    template<typename return_type, typename arg1_type, typename ...params>
    auto _L1( return_type (*fp) (arg1_type x, params...args), arg1_type x)
    { return [fp, x] (params...args) { return fp(x,args...); };  };

    /**  Casts any function to a lambda, binding the first two arguments to x, y
         @param[in] fp The input function pointer
         @param[in] x The value of the first argument to the function
         @param[in] y The value of the second argument to the function
         @return A lambda function which applies fp, taking x as the first two
         @return arguments of the function invocation, others supplied at call site 
    */
    template<typename return_type, typename arg1_type, typename arg2_type, 
             typename ...params>
    auto _L2( return_type (*fp) (arg1_type x, arg2_type y, params...args), 
              arg1_type x, arg2_type y)
    { return [fp, x, y] (params...args) { return fp(x,y,args...); };  };

    /**  Casts any function to a lambda, binding the first 3 arguments to x,y,z
         @param[in] fp The input function pointer
         @param[in] x The value of the first argument to the function
         @param[in] y The value of the second argument to the function
         @param[in] z The value of the third argument to the function
         @return A lambda function which applies fp, taking x,y,z as the first 3
         @return arguments of the function invocation, others supplied at call site 
    */
    template<typename return_type, typename arg1_type, typename arg2_type, 
             typename arg3_type, typename ...params>
    auto _L3( return_type (*fp) (arg1_type x, arg2_type y, arg3_type z, params...args), 
              arg1_type x, arg2_type y, arg3_type z)
    { return [fp, x, y, z] (params...args) { return fp(x,y,z,args...); };  };

}
