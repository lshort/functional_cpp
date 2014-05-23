/**  This module provides support for composing functions in C++.  
     Composing lambdas, really, but it provides a lightweight way
     to convert any unary function to a lambda.  
*/

#include <functional>


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
    template<typename Lambda1, typename Lambda2>
    auto operator* (Lambda1 l1, Lambda2 l2)
    {  return [l1, l2](auto x) { return l1(l2(x)); };  };

    /**  Casts any function to a lambda
         @param[in] fp The input function pointer
         @return A lambda function which applies fp to its arguments */
    template<typename return_type, typename ...params>
    auto _L( return_type (*fp) (params... args))
      { return [fp] (params... args) { return fp(args...); }; };
}

